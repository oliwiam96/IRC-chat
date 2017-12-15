#include <stdio.h>
#include <string.h>

void wykonaj_polecenie(char* polecenie)
{
	printf("Wykonuje polecenie: %s\n", polecenie);
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
			//printf("Koniec\n");
		}
		else if(pch == buffer)	// ; jest pierwszym znakiem, puste polecenie ; (po ; moze cos byc), 						// zignoruj ten znak
		{
			sklejanie(buffer+1, lewy, prawy);
		}
		else
		{
			*lewy = strtok(buffer, ";"); //oddziel do pierwszego wystapienia ';'
			*prawy = strtok(NULL, ""); //reszte wrzuc do prawy
			//printf("lewy: %s\n", *lewy);
			//printf("prawy: %s\n", *prawy);
		}
	}

}
int main ()
{
	
	
	int przesuniecie = 0;
	char buffer[90];
	char *lewy;
	char *prawy;
	//printf("%d\n", (int) strlen(NULL));
	bool czy = true;
	while(czy)
	{
		
		strcpy(buffer, "\\SIGNIN oli oli123;\\MSG informatycy czesc :);;\\ROOMS;\\USE");
     		//int n_odczytane = read(th_data->fd, buffer + przesuniecie, 49- przesuniecie);
		int n_odczytane = strlen(buffer);
     		if(n_odczytane > 0)
		{
			sklejanie(buffer, &lewy, &prawy);
			//printf("\nBuffer: %s\nLewy: %s\nPrawy: %s\n", buffer, lewy, prawy);
			while(lewy != NULL)
			{
				
				wykonaj_polecenie(lewy);
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
		czy = false;
	}
	

	

	return 0;
}
