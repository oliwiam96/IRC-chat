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

#include "database.h"

#define SERVER_PORT 1234
#define QUEUE_SIZE 5
#define MAX_CLIENTS 50



//struktura zawierająca dane, które zostaną przekazane do wątku
typedef struct thread_client_data_t{
	int fd; /* Connection file descriptor */
        char *name;

} t_client;


Database *db;
pthread_mutex_t	mutexClients;
bool is_server_active = true;

void write_to_client(char *msg, int connfd)
{
    pthread_mutex_lock(&mutexClients);
    write(connfd, msg, strlen(msg));
    pthread_mutex_unlock(&mutexClients);
}


void wykonaj_polecenie(char* msg, t_client * th_data, bool& stop)
{
        printf("Wykonuje polecenie: %s\n", msg);
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
            if(db->login(name, password, th_data->fd))
            {
                printf("Haslo ok\n");
                th_data->name = (char *) malloc((strlen(name)+1) * sizeof(char));
                strcpy(th_data->name, name);
                char answer[] = "\\LOGINSUCCESSFUL\n";
                write_to_client(answer, th_data->fd);
            }
            else
            {
                printf("Haslo zle\n");
                char answer[] = "\\LOGINFAILED\n";
                write_to_client(answer, th_data->fd);
            }

        }
        else if(!strcmp(pch, "\\SIGNUP"))
        {
            printf("TWORZENIE KONTA\n");
            pch = strtok(NULL, " ");
            printf("Login to: %s\n", pch);
            char name[50];
            strcpy(name, pch);
            pch = strtok(NULL, " ");
            printf("Haslo to: %s\n", pch);
            char password[50];
            strcpy(password, pch);
            if(db->createNewAccount(name, password, th_data->fd))
            {
                printf("Sign up ok\n");
                char answer[] = "\\SIGNUPSUCCESSFUL\n";
                write_to_client(answer, th_data->fd);
            }
            else
            {
                printf("Login zajety\n");
                char answer[] = "\\USERNAMEALREADYTAKEN\n";
                write_to_client(answer, th_data->fd);
            }
        }
        else if(!strcmp(pch, "\\LOGOUT"))
        {

            db->logout(th_data->name);
            printf("WYLOGOWANIE\n");
            stop = true;

        }
        else if(!strcmp(pch, "\\SHOWROOMS"))
        {
            printf("POKAZ DOSTEPNE POKOJE\n");
            char answer[550];
            strcpy(answer, "\\ROOMS ");
            char *allRooms = db->getStringWithAllRooms();
            strcat(answer, allRooms);
            strcat(answer, "\n");
            delete allRooms;
            write_to_client(answer, th_data->fd);

        }
        else if(!strcmp(pch, "\\ENTERROOM"))
        {
            printf("WEJDZ DO POKOJU\n");
            pch = strtok(NULL, " ");
            printf("nazwa pokoju to: %s\n", pch);
            char roomName[50];
            strcpy(roomName, pch);
            db->enterRoom(th_data->name, roomName);

        }
        else if(!strcmp(pch, "\\CREATEROOM"))
        {
            printf("UTWORZ POKOJ\n");
            pch = strtok(NULL, " ");
            printf("nazwa pokoju to: %s\n", pch);
            char roomName[50];
            strcpy(roomName, pch);
            if(db->createNewRoom(roomName))
            {
                printf("Create room ok\n");
                char answer[] = "\\CREATEROOMSUCCESSFUL\n";
                write_to_client(answer, th_data->fd);
            }
            else
            {
                printf("Nazwa pokoju zajeta\n");
                char answer[] = "\\ROOMNAMEALREADYTAKEN\n";
                write_to_client(answer, th_data->fd);
            }

        }
        else if(!strcmp(pch, "\\LEAVEROOM"))
        {
            printf("WYJDZ Z POKOJU\n");
            pch = strtok(NULL, " ");
            printf("nazwa pokoju to: %s\n", pch);
            char roomName[50];
            strcpy(roomName, pch);
            db->leaveRoom(th_data->name, roomName);
        }
        else if(!strcmp(pch, "\\DELETEROOM"))
        {
            printf("USUN POKOJ\n");
            pch = strtok(NULL, " ");
            printf("nazwa pokoju to: %s\n", pch);
            char roomName[50];
            strcpy(roomName, pch);
            db->deleteRoom(roomName);
        }
        else if(!strcmp(pch, "\\MSG"))
        {
            printf("WIADOMOSC W POKOJU!!!\n");
            pch = strtok(NULL, " ");
            printf("nazwa pokoju to: %s\n", pch);
            char roomName[50];
            strcpy(roomName, pch);
            char msg2[500];
            strcpy(msg2, "\\MSG ");
            strcat(msg2, roomName);
            strcat(msg2, " ");
            strcat(msg2, th_data->name);


            pch = strtok(NULL, " ");
            while(pch != NULL)
            {
                strcat(msg2, " ");
                strcat(msg2, pch);
                pch = strtok(NULL, " ");
            }

            //strcat(msg2, " ");
            //pch = strtok(NULL, " "); // UWAGA TU BYL BLAD, NIE DO KOLEJNEJ SPACJI, A RESZTE
            //strcat(msg2, pch);
            strcat(msg2, "\n"); // UWAGA ZMIANA- CZY DOBRZE?
            int n = db->getNumberOfUsersInRoom(roomName);
            int *usersConnfdInRoom = db->getArrayofAllUsersConnfdInRoom(roomName);
            for(int i = 0; i < n; i++)
            {
                if(usersConnfdInRoom[i] != th_data->fd) //nie pisz sam do siebie
                {
                    printf("Pisze do klienta wiadomosc o tresci: %s\n", msg2);
                    write_to_client(msg2, usersConnfdInRoom[i]);
                }
            }
        }
        else if(!strcmp(pch, "\\CLOSESERVER"))
        {
            printf("CAŁKOWISTY RESET I ZAMKNIECIE SERVERA\n");
            is_server_active = false;
            db->deleteAllUserFromAllRooms();
        }
        else
        {
            printf("NIEZNANE POLECENIE\n");
            printf("%s\n", pch);

        }


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
    
        bool stop = false;
        int buffer_length = 500;
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
                                printf("Stop: %d\n", stop);
                                wykonaj_polecenie(kopia_wykonaj, th_data, stop);
                                printf("Stop: %d\n", stop);
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

        printf("Ostateczne zakniecie watku");
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

    create_result = pthread_create(&thread1, NULL, ThreadBehavior, (void *)client_data);
    if (create_result){
       printf("Błąd przy próbie utworzenia wątku, kod błędu: %d\n", create_result);
       exit(-1);
    }

    
}

int main(int argc, char* argv[])
{
        printf("Serwer wystartowany\n");
        char fileName[] = "test.db";
        db = new Database(fileName);
        mutexClients = PTHREAD_MUTEX_INITIALIZER;
	int server_socket_descriptor; // to samo co listenfd
	int connection_socket_descriptor; // to samo co connfd
	int bind_result;
	int listen_result;
	char reuse_addr_val = 1;
	struct sockaddr_in server_address;
        is_server_active = true;

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
        while(is_server_active)
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
        printf("Serwer zamknięty\n");
        pthread_mutex_destroy(&mutexClients);
	close(server_socket_descriptor);
	return(0);
}
