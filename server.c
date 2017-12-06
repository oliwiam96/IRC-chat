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
#include <pthread.h>

#define SERVER_PORT 1234
#define QUEUE_SIZE 5
#define MAX_CLIENTS 20



//struktura zawierająca dane, które zostaną przekazane do wątku
typedef struct thread_client_data_t{
	struct sockaddr_in address; /* Client remote adress */
	int fd; /* Connection file descriptor */
	int user_id;

} t_client;
//struktura zawierająca dane, które zostaną przekazane do wątku
typedef struct thread_data_t
{
    int fd;
} t_typ;

int user_id_count = 0;
t_client *clients[MAX_CLIENTS]; // TODO przerobic na vector (C++)

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

//funkcja opisującą zachowanie wątku - musi przyjmować argument typu (void *) i zwracać (void *)
void *ThreadBehavior(void *t_data)
{
    
    pthread_detach(pthread_self());
    //struct thread_client_data_t *th_data = (struct thread_client_data_t*)t_data;
	t_client *th_data = (t_client *)t_data;
    //dostęp do pól struktury: (*th_data).pole
    
    
	bool stop = false;
	do{
		char buffer[50];
     	int n_odczytane = read(th_data->fd, buffer, 49);
     	if(n_odczytane > 0){

			buffer[n_odczytane] = '\0';
			printf("%s\n", buffer);
			for(int i = 0; i < MAX_CLIENTS; i++)
			{
				if(!clients[i])
					break;
				else if(clients[i] != th_data)
				{
					write(clients[i]->fd, buffer, n_odczytane);
					if(strcmp(buffer, "PAPA") == 0) // na razie to nie dziala
						stop = true;
				}
				
			}
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
