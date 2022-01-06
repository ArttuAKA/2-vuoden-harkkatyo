#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 3000

struct node
{
    char *sana;
    int count;
    struct node* next;
};

typedef struct node solmu;

solmu *luouusinode(char sana[],int count){
    solmu *uusinode = malloc(sizeof(solmu));
    uusinode->sana = malloc(strlen(sana) + 1);
    strcpy(uusinode->sana, sana);
    uusinode->count = count;
    uusinode->next = NULL;
    return uusinode;
}

//


void printlist(solmu *head){

    solmu *temporary = head;

    if (temporary == NULL){

        return;
    }
    while (temporary != NULL){
        printf("%s %d - ", temporary->sana, temporary->count);
        temporary = temporary->next;
    }

    return;
}


void insert_at_head(solmu **head, solmu *node_to_insert){

        node_to_insert->next = *head;
        *head = node_to_insert;


}


int etsi(solmu *head, char sana[]){

    if (head == NULL){
        return 0;
    }

    solmu *temp = head;

    while (temp->next != NULL){

        if (strcmp(temp->sana,sana) == 0){
            temp->count++;
            return 1;
            }
        temp = temp->next;
    }

    if (strcmp(temp->sana,sana) == 0){
            temp->count++;
            return 1;
            }

    return 0;
}
int hash(char sana[]);
void jarjesta(solmu *array[], int sanat, int erisanat);
void shsort(solmu *array[], int length);
void quicksort(solmu *array[], int low, int high);
void vaihto(solmu *array[], int a, int b);
void lopputuloste(solmu *array[], int sanat, int erisanat);


int main()
{
    solmu *array[SIZE] = {};

    int index;
    int sanat = 0, erisanat = 0;

    FILE *fp;
    char tempword[100] = {};
    char ch;
    int n = 0;


    char filename[50];


            printf("Syota tiedoston nimi  \n");
            scanf("%s", filename);
            fp = fopen(filename, "r");


        clock_t tStart = clock();





    //tehdään uusi node jokaiselle uudelle sanalle. Jos sana löytyy jo sen arvoa korotetaan yhedllä.
    //Nodet laitetaan hashtableen jossa linkitetty lista. Törmäyksissä lisätään uusi node.

   do {

	ch = fgetc(fp);

        if (isalpha(ch) || ch == '\'')
        {
            tempword[n] = ch;
            n++;
        }
        else if (n > 0)
        {
            tempword[n] = '\0';
            n = 0;
            sanat++;

            for (int i = 0; i < strlen(tempword); i++)
            {

                tempword[i] = toupper(tempword[i]);

            }

            index = hash(tempword);

            if (etsi(array[index], tempword) != 1)
            {
                erisanat++;
                insert_at_head(&array[index], luouusinode(tempword, 1));
            }
        }

	}
	while (ch != EOF);

    fclose(fp);


    jarjesta(array, sanat, erisanat);

    printf("Time taken: %.2fs\n", (double)(clock() - tStart) / CLOCKS_PER_SEC);
    return 0;
}

//linkitettylista laitetaan taulukkoon
//Järjestää taulukon quicksortilla
void jarjesta(solmu *array[], int sanat, int length)
{
    solmu *temporary;
    solmu *head = luouusinode("FIRST NODE", 0);
    solmu *finalarray[length];

    temporary = head;

    for (int i = 0; i < SIZE; i++)
    {

        if (array[i] == NULL)
        {
            continue;
        }

        while (temporary->next != NULL)
        {
            temporary = temporary->next;
        }

        temporary->next = array[i];
    }

    temporary = head->next;

    for (int i = 0; i <= length - 1; i++)
    {
        finalarray[i] = temporary;
        temporary = temporary->next;
    }

    quicksort(finalarray, 0, length - 1);


    lopputuloste(finalarray,sanat,length);
}

int hash(char sana[])
{
    int hash = 1;
    int m = 31;
    for (int i = 0; i < strlen(sana); i++)
    {
        hash = m * hash + sana[i];
    }

    hash = hash % 2477;
    if (hash < 0)
    {
        hash = -hash;
    }

    return hash;
}




//Quicksort lajittelu

void quicksort(solmu *array[], int low, int high)
{
    if (low >= high)
    {
        return;
    }

    int pivot = array[low]->count;

    int left = low, i = low, right = high;

    while (i <= right)
    {
        if (array[i]->count > pivot)
        {
            vaihto(array, left, i);
            left++;
            i++;
        }
        else if (array[i]->count < pivot)
        {
            vaihto(array, i, right);
            right--;
        }
        else if (array[i]->count == pivot)
        {
            i++;
        }
    }

    quicksort(array, low, left - 1);
    quicksort(array, right + 1, high);
}

void vaihto(solmu *array[], int a, int b)
{
    solmu *temp = array[a];
    array[a] = array[b];
    array[b] = temp;
}

void lopputuloste(solmu *array[], int sanat, int erisanat){

    printf("Total number of words = %d\nNumber of different words = %d\n", sanat,erisanat);
    printf("100 most common words:\n");


    for (int i = 0; i < 100; i++)
    {
        printf("%-15s %d\n", array[i]->sana, array[i]->count);
    }
}