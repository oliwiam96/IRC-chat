#include <sys/types.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sqlite3.h> 
#include <pthread.h>

#define SERVER_PORT 1234
#define QUEUE_SIZE 5
#define MAX_CLIENTS 20



//struktura zawierająca dane, które zostaną przekazane do wątku
typedef struct thread_client_data_t{
	struct sockaddr_in address; /* Client remote adress */
	int fd; /* Connection file descriptor */
	int user_id;
	int data_base_id;


} t_client;
//struktura zawierająca dane, które zostaną przekazane do wątku
typedef struct thread_data_t
{
    int fd;
} t_typ;

int user_id_count = 0;
t_client *clients[MAX_CLIENTS]; // TODO przerobic na vector (C++)

static int callback(void *data, int argc, char **argv, char **azColName){
	int i;
	fprintf(stderr, "%s: ", (const char*)data);
	
	for(i = 0; i<argc; i++){
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}
	
	printf("\n");
	return 0;
}
static int callback_login_validation(void *data, int argc, char **argv, char **azColName){
	char *a = (char*) data;
	strcpy(a, argv[0]);
	return 0;
}
bool login_validation(sqlite3 *db, char *zErrMsg, int rc, char *name, char *password)
{
	char sql_select[80];
	strcpy(sql_select, "SELECT PASSWORD from USERS WHERE NAME = \"");
	strcat(sql_select, name);
	strcat(sql_select, "\";");
	char *password_select = (char *) malloc(50* sizeof(char));
	printf("%s\n", sql_select);
	rc = sqlite3_exec(db, sql_select, callback_login_validation, (void*)password_select, &zErrMsg);
	if( rc != SQLITE_OK ) {
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	} else {
		fprintf(stdout, "Operation \"password checking\" done successfully\n");
	}
	password_select = (char*) password_select;
	bool identical = !strcmp(password_select, password);
	free(password_select);
	return identical;
}
static int callback_name_free_validation(void *data, int argc, char **argv, char **azColName){
	int *a = (int*) data;
	*a = atoi(argv[0]);
	return 0;
}
bool name_free_validation(sqlite3 *db, char *zErrMsg, int rc, char *name)
{
	char sql_select[80];
	strcpy(sql_select, "SELECT COUNT(*) from USERS WHERE NAME = \"");
	strcat(sql_select, name);
	strcat(sql_select, "\";");
	int ile;
	printf("%s\n", sql_select);
	rc = sqlite3_exec(db, sql_select, callback_name_free_validation, (void*)&ile, &zErrMsg);
	if( rc != SQLITE_OK ) {
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	} else {
		fprintf(stdout, "Operation \"name free/taken\" done successfully\n");
	}
	printf("Ile wynosi: %d\n", ile);
	return ile == 0;
}

void add_new_user(sqlite3 *db, char *zErrMsg, int rc, char *name, char *password)
{
	char sql_insert[80];
	strcpy(sql_insert, "INSERT INTO USERS(NAME, PASSWORD, ACTIVE) VALUES (\"");
	strcat(sql_insert, name);
	strcat(sql_insert, "\", \"");
	strcat(sql_insert, password);
	strcat(sql_insert, "\", 1);");
	printf("%s\n", sql_insert);
	rc = sqlite3_exec(db, sql_insert, callback, 0, &zErrMsg);
	if( rc != SQLITE_OK ) {
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	} else {
		fprintf(stdout, "Operation \"add new user\" done successfully\n");
	}
}


void add_client(t_client *client)
{
	for(int i = 0; i < MAX_CLIENTS; i++)
	{
		if(!clients[i])
		{
			clients[i] = client;
			return;
		}
	}
}

void wykonaj_polecenie(char* msg)
{
	printf("Wykonuje polecenie: %s\n", msg);

	sqlite3 *db;
	char *zErrMsg = 0;
	int rc;
	//char *sql;

	/* Open database */
	rc = sqlite3_open("test.db", &db);
	
	if( rc ) {
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
	} else {
		fprintf(stdout, "Opened database successfully\n");
	}
	char *pch; //a pointer to the beginning of the token
	printf ("Splitting string \"%s\" into tokens:\n", msg);
	pch = strtok(msg, " ");
	/** MOZLIWE WIADOMOSCI OD KLIENTA DO SERWERA **/
	if(!strcmp(pch, "\\LOGIN"))
	{
		printf("LOGOWANIE\n");
		pch = strtok(NULL, " ");
		printf("Login to: %s\n", pch);
		char name[50];
		strcpy(name, pch);
		pch = strtok(NULL, " ");
		printf("Haslo to: %s\n", pch);
		char password[50];
		strcpy(password, pch);
		if(login_validation(db, zErrMsg, rc, name, password))
			printf("Haslo ok\n");
		else
			printf("Haslo zle\n");
		// TODO #if haslo ok, write \\LOGINSUCCESSFUL dodaj do listy polaczonych (aktywnych) 			// uzytkownikow
		// TODO #else  write \\WRONGPASSWORD
	}
	sqlite3_close(db);
}
void sklejanie(char* buffer, char** lewy, char** prawy)
{
	if(buffer == NULL) //poprzedni lancuch konczyl sie ';', dalej pusty ciag, koniec
	{
		*lewy = NULL;
		*prawy = NULL;
	
	}
	else
	{
		char * pch = strchr(buffer, ';');//returns a pointer to the first occurrence of ';'in the buffer
		if(pch == NULL) // nie ma juz ';', ale lancuch nie jest pusty, buffer trzeba bedzie przepisac
		{
			*lewy = NULL;
			*prawy = buffer;
		}
		else if(pch == buffer)	// ; jest pierwszym znakiem, puste polecenie ; (po ; moze cos byc), 						// zignoruj ten znak
		{
			sklejanie(buffer+1, lewy, prawy);
		}
		else
		{
			*lewy = strtok(buffer, ";"); //oddziel do pierwszego wystapienia ';'
			*prawy = strtok(NULL, ""); //reszte wrzuc do prawy
		}
	}

}

//funkcja opisującą zachowanie wątku - musi przyjmować argument typu (void *) i zwracać (void *)
void *ThreadBehavior(void *t_data)
{
	pthread_detach(pthread_self());
	t_client *th_data = (t_client *)t_data;
    
	/* nowe rzeczy
	int n_odczytane2;
	char buffer2[50];
	while( (n_odczytane2 = read(th_data->fd, buffer2, 49)) > 0) //odczytanie powiodlo sie
	{
		if(n_odczytane2 > 0)
		{
			buffer2[n_odczytane2] = '\0';
			printf("%s\n", buffer2);
			
			
		}
			
	}*/
    
	bool stop = false;
	int buffer_length = 50;
	char buffer[buffer_length];
	int przesuniecie = 0;
	char *lewy;
	char *prawy;
	do{

		int n_odczytane = read(th_data->fd, buffer + przesuniecie, buffer_length-1 - przesuniecie);
		if(n_odczytane > 0){

			buffer[przesuniecie+n_odczytane] = '\0';
			printf("%s\n", buffer);
			sklejanie(buffer, &lewy, &prawy);
			while(lewy != NULL)
			{
				char kopia_wykonaj[strlen(lewy)];
				strcpy(kopia_wykonaj, lewy);
				
				wykonaj_polecenie(kopia_wykonaj);
				for(int i = 0; i < MAX_CLIENTS; i++)
				{
					if(!clients[i])
						break;
					else if(clients[i] != th_data)
					{
						char kopia[buffer_length];
						strcpy(kopia, lewy);
						kopia[strlen(lewy)] = '\n'; //czy to jest ok? :<
						write(clients[i]->fd, kopia, strlen(lewy)+1);
						//if(strcmp(lewy, "PAPA") == 0) // na razie to nie dziala
							//stop = true;
					}
				
				}
				sklejanie(prawy, &lewy, &prawy);
			}
			if(prawy != NULL)
			{
				strcpy(buffer, prawy);
				przesuniecie = strlen(prawy);
				printf("Buffer ma: %s\n", buffer);
			}
			else
			{
				przesuniecie = 0;
			}
			printf("Przesuniecie: %d\n", przesuniecie);
			
			
		}
        
	} while(!stop);

	free(t_data);
	pthread_exit(NULL);
}

//funkcja obsługująca połączenie z nowym klientem
void handleConnection(int connection_socket_descriptor) {
    //wynik funkcji tworzącej wątek
    int create_result = 0;
    

    //uchwyt na wątek
    pthread_t thread1;

    //dane, które zostaną przekazane do wątku
    //TODO w odpowiednim miejscu zwolnienie pamięci- czy dobrze, ze pod koniec watku?
    //t_typ *t_data =(t_typ*) malloc(sizeof(t_typ));
	t_client *client_data = (t_client*) malloc(sizeof(t_client));
	
    
    // wypełnienie pól struktury
    //t_data->fd = connection_socket_descriptor;
	client_data->fd = connection_socket_descriptor;
	client_data->user_id = user_id_count++;
	add_client(client_data);

    create_result = pthread_create(&thread1, NULL, ThreadBehavior, (void *)client_data);
    if (create_result){
       printf("Błąd przy próbie utworzenia wątku, kod błędu: %d\n", create_result);
       exit(-1);
    }

    
}

int main(int argc, char* argv[])
{
	printf("Serwer wystartowany\n");
	int server_socket_descriptor; // to samo co listenfd
	int connection_socket_descriptor; // to samo co connfd
	int bind_result;
	int listen_result;
	char reuse_addr_val = 1;
	struct sockaddr_in server_address;

	//inicjalizacja gniazda serwera

	memset(&server_address, 0, sizeof(struct sockaddr)); // to samo co serv_addr
	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = htonl(INADDR_ANY);
	server_address.sin_port = htons(SERVER_PORT);
	
	// Utworzenie gniazda
	server_socket_descriptor = socket(AF_INET, SOCK_STREAM, 0); // to samo co listenfd
	if (server_socket_descriptor < 0)
	{
	   fprintf(stderr, "%s: Błąd przy próbie utworzenia gniazda..\n", argv[0]);
	   exit(1);
	}
	printf("Utworzono gniazdo serwera\n");
	setsockopt(server_socket_descriptor, SOL_SOCKET, SO_REUSEADDR, (char*)&reuse_addr_val, sizeof(reuse_addr_val));

	// Bind
	bind_result = bind(server_socket_descriptor, (struct sockaddr*)&server_address, sizeof(struct sockaddr));
	if (bind_result < 0)
	{
	   fprintf(stderr, "%s: Błąd przy próbie dowiązania adresu IP i numeru portu do gniazda.\n", argv[0]);
	   exit(1);
	}
	printf("Bind ok\n");
	
	// Listen
	listen_result = listen(server_socket_descriptor, QUEUE_SIZE); // tam QUEUE_SIZE == 5; to nie jest max klientow
	if (listen_result < 0) {
	   fprintf(stderr, "%s: Błąd przy próbie ustawienia wielkości kolejki.\n", argv[0]);
	   exit(1);
	}
	printf("Listen ok\n");

	// Accept clients
	while(1)
	{
	   connection_socket_descriptor = accept(server_socket_descriptor, NULL, NULL);
	   if (connection_socket_descriptor < 0)
	   {
		   fprintf(stderr, "%s: Błąd przy próbie utworzenia gniazda dla połączenia.\n", argv[0]);
		   exit(1);
	   }
		printf("Mam klienta!\n");

	    handleConnection(connection_socket_descriptor);
	}

	close(server_socket_descriptor);
	return(0);
}
