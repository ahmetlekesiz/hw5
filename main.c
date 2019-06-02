//Ahmet Lekesiz - 150118509
//Computer Programming - Homework 5

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct song{
    char songName[25];
    int duration;
    struct song * chrono_next;
    struct song * alpha_next;
    struct song * duration_next;
    struct song * random_next;
} typedef song;

//roots
song * chrono_head = NULL, * alpha_head = NULL, * duration_head = NULL, * random_head = NULL;

char randomName[25];
int randomDuration;

//insert methods
void insertChrono(char name[], int duration, song ** root){
    if((*root) == NULL){
        *root = malloc(sizeof(song));
        (*root)->duration = duration;
        strcpy((*root)->songName, name);
        (*root)->chrono_next = NULL;
    }else{
        song *iter = *root;
        //find the tail for chrono
        while(iter->chrono_next != NULL){
            iter = iter->chrono_next;
        }
        //add to chrono
        iter->chrono_next = malloc(sizeof(song));
        iter->chrono_next->duration = duration;
        strcpy(iter->chrono_next->songName, name);
        iter->chrono_next->chrono_next = NULL;
    }
}

song * insertAlpha(song * root, char name[], int duration){
    if(root == NULL){ //if the link list is empty
        root = malloc(sizeof(song));
        root->alpha_next = NULL;
        strcpy((root)->songName, name);
        root->duration = duration;
        return root;
    }
    if(strcmp((root)->songName, name) > 0){ //lower than first element
        //we are changing the root
        song * temp = (song*)malloc(sizeof(song));
        strcpy((temp)->songName, name);
        temp->duration = duration;
        temp->alpha_next = root;
        root = temp;
        return root;
    }
    //add between songs or add end of the list
    song * iter = root;
    while(iter->alpha_next != NULL && strcmp(iter->alpha_next->songName, name) < 0){
        iter = iter->alpha_next;
    }
    song * temp = (song*)malloc(sizeof(song));
    temp->alpha_next = iter->alpha_next;
    iter->alpha_next = temp;
    temp->duration = duration;
    strcpy((temp)->songName, name);
    return root;
}

song * insertDuration(song * root, char name[], int duration){
    if(root == NULL){ //if the link list is empty
        root = malloc(sizeof(song));
        root->duration_next = NULL;
        strcpy((root)->songName, name);
        root->duration = duration;
        return root;
    }
    if(root->duration > duration){ //lower than first element
        //we are changing the root
        song * temp = (song*)malloc(sizeof(song));
        strcpy((temp)->songName, name);
        temp->duration = duration;
        temp->duration_next = root;
        root = temp;
        return root;
    }
    //add between songs or add end of the list
    song * iter = root;
    while(iter->duration_next != NULL && iter->duration_next->duration < duration){
        iter = iter->duration_next;
    }
    song * temp = (song*)malloc(sizeof(song));
    temp->duration_next = iter->duration_next;
    iter->duration_next = temp;
    temp->duration = duration;
    strcpy((temp)->songName, name);
    return root;
}

void insertRandom(char name[], int duration, song ** root){
    if((*root) == NULL){
        *root = malloc(sizeof(song));
        (*root)->duration = duration;
        strcpy((*root)->songName, name);
        (*root)->random_next = NULL;
    }else{
        song *iter = *root;
        //find the tail for chrono
        while(iter->random_next != NULL){
            iter = iter->random_next;
        }
        iter->random_next= malloc(sizeof(song));
        iter->random_next->duration = duration;
        strcpy(iter->random_next->songName, name);
        iter->random_next->random_next = NULL;
    }
}

void insertNode(char name[], int duration){
    insertChrono(name, duration, &chrono_head);
    alpha_head = insertAlpha(alpha_head, name, duration);
    duration_head = insertDuration(duration_head, name, duration);
    insertRandom(name, duration, &random_head);
}

//delete methods
void deleteNodeChrono(song ** ch_root, char name[]){
    song *iter = (*ch_root);
    song *temp;

    //check if the root and name is same
    if(strcmp((*ch_root)->songName, name) == 0){
        temp = (*ch_root);
        *ch_root = (*ch_root)->chrono_next;
        free(temp);
        return;
    }

    while(iter != NULL && strcmp(iter->chrono_next->songName, name)!=0){
        iter = iter->chrono_next;
    }
    if(iter->chrono_next == NULL){
        printf("there is no song like that");
        return;
    }

    temp = iter->chrono_next;
    iter->chrono_next = iter->chrono_next->chrono_next;
    free(temp);
}

void deleteNodeAlpha(song ** alpha_root, char name[]){
    song *iter = (*alpha_root);
    song *temp;

    //check if the root and name is same
    if(strcmp((*alpha_root)->songName, name) == 0){
        temp = (*alpha_root);
        *alpha_root = (*alpha_root)->alpha_next;
        free(temp);
        return;
    }

    while(iter != NULL && strcmp(iter->alpha_next->songName, name)!=0){
        iter = iter->alpha_next;
    }
    if(iter->alpha_next == NULL){
        printf("there is no song like that");
        return;
    }

    temp = iter->alpha_next;
    iter->alpha_next = iter->alpha_next->alpha_next;
    free(temp);
}

void deleteNodeDuration(song ** duration_root, char name[]){
    song *iter = (*duration_root);
    song *temp;

    //check if the root and name is same
    if(strcmp((*duration_root)->songName, name) == 0){
        temp = (*duration_root);
        *duration_root = (*duration_root)->duration_next;
        free(temp);
        return;
    }

    while(iter != NULL && strcmp(iter->duration_next->songName, name)!=0){
        iter = iter->duration_next;
    }
    if(iter->duration_next == NULL){
        printf("there is no song like that");
        return;
    }

    temp = iter->duration_next;
    iter->duration_next = iter->duration_next->duration_next;
    free(temp);
}

void deleteNodeRandom(song ** ch_root, char name[]){
    song *iter = (*ch_root);
    song *temp;

    //check if the root and name is same
    if(strcmp((*ch_root)->songName, name) == 0){
        temp = (*ch_root);
        *ch_root = (*ch_root)->random_next;
        free(temp);
        return;
    }

    while(iter != NULL && strcmp(iter->random_next->songName, name)!=0){
        iter = iter->random_next;
    }
    if(iter->random_next == NULL){
        printf("there is no song like that");
        return;
    }

    temp = iter->random_next;
    iter->random_next = iter->random_next->random_next;
    free(temp);
}

void deleteNode(char name[]){
    deleteNodeChrono(&chrono_head, name);
    deleteNodeAlpha(&alpha_head, name);
    deleteNodeDuration(&duration_head, name);
    deleteNodeRandom(&random_head, name);
}

void push(song** head, char name[], int duration)
{
    // Allocate the new Node in the heap and set its data
    song* newNode = (song*)malloc(sizeof(song));
    strcpy(newNode->songName, name);
    newNode->duration = duration;

    // Set the .next pointer of the new Node to point to the current
    // first node of the list.
    newNode->random_next = *head;

    // Change the head pointer to point to the new Node, so it is
    // now the first node in the list.
    *head = newNode;
}
song* CopyList(song* head)
{
    song* current = head;	// used to iterate over original list
    song* newList = NULL; // head of the new list
    song* tail = NULL;	// point to last node in new list

    while (current != NULL)
    {
        // special case for the first new Node
        if (newList == NULL)
        {
            newList = (song*)malloc(sizeof(song));
            strcpy(newList->songName, current->songName);
            newList->duration = current->duration;
            newList->random_next = NULL;
            tail = newList;
        }
        else
        {
            tail->random_next = (song*)malloc(sizeof(song));
            tail = tail->random_next;
            strcpy(tail->songName, current->songName);
            tail->duration = current->duration;
            tail->random_next = NULL;
        }
        current = current->random_next;
    }

    return newList;
}
int listSize(song * random_head){
    int counter = 0;
    while(random_head!=NULL){
        counter++;
        random_head = random_head->random_next;
    }
    return counter;
}

//print methods
void randomSong(song * random_head){
    char songName[25];
    int duration;
    if (random_head == NULL)
        return;
    srand(time(NULL));

    strcpy(songName, random_head->songName);
    duration = random_head->duration;
    song *current = random_head;
    int n;
    for (n=2; current!=NULL; n++){
        if (rand() % n == 0){
            strcpy(songName, current->songName);
            duration = current->duration;
        }
        current = current->random_next;
    }
    strcpy(randomName, songName);
    randomDuration = duration;
}

void printRandom(song* random_head){
    int size = listSize(random_head);
    song* temp = CopyList(random_head);

    printf("The list in random order:\n");

    int i = 1;
    int hour = 0;
    int min = 0;
    while(i<=size){
        randomSong(temp);
        char name[25];
        strcpy(name, randomName);
        int duration = randomDuration;
        hour = duration / 60;
        min = duration % 60;
        printf("\t%d. %s %d:%d\n", i, name, hour, min);
        deleteNodeRandom(&temp, name);
        i++;
    }
}

void printList(song* ch, song* alp, song* dur, song* random_head){
    int i = 1;
    int hour = 0;
    int min = 0;
    printf("The list in chronological order:\n");
    while(ch!=NULL){
        hour = ch->duration / 60;
        min = ch->duration % 60;
        printf("\t%d. %s %d:%d\n", i, ch->songName, hour, min);
        ch = ch->chrono_next;
        i++;
    }

    i=1;
    printf("The list in alphabetical order:\n");
    while(alp!=NULL){
        hour = alp->duration / 60;
        min = alp->duration % 60;
        printf("\t%d. %s %d:%d\n", i, alp->songName, hour, min);
        alp = alp->alpha_next;
        i++;
    }

    i=1;
    printf("The list in duration-time order:\n");
    while(dur!=NULL){
        hour = dur->duration / 60;
        min = dur->duration % 60;
        printf("\t%d. %s %d:%d\n", i, dur->songName, hour, min);
        dur = dur->duration_next;
        i++;
    }

    printRandom(random_head);
}

void printChoice(){
    int choice = 0;
    char input[100];
    char songName[25];
    char duration[10];
    char hour[3];
    char min[3];
    int h;
    int m;
    int dur;
    char hourSingle[2];
    char minSingle[2];



    while(choice != 5){
        printf("Enter your choice:\n");
        printf("\t1 to insert a song into the list.\n");
        printf("\t2 to delete a song from list.\n");
        printf("\t3 to print the songs in the list.\n");
        printf("\t4 to print the songs to an output file.\n");
        printf("\t5 to end.\n");
        scanf("%d", &choice);
        getchar();
        if(choice == 1){
            printf("Enter a song name with duration:\n");
            gets(input);
            printf("%s", input);
            char *piece = strtok(input, "\t");
            strcpy(songName, piece);
            piece = strtok(NULL, "\t");
            strcpy(duration, piece);
            char *secondPiece = strtok(piece, ":");
            strcpy(hour, secondPiece);
            secondPiece = strtok(NULL, ":");
            strcpy(min, secondPiece);
            if(hour[0]== '0'){
                hourSingle[0] = hour[1];
                hourSingle[1] = '\0';
                h = atoi(hourSingle);
            }else{
                h = atoi(hour);
            }
            if(min[0]== '0'){
                minSingle[0] = min[1];
                minSingle[1] = '\0';
                m = atoi(minSingle);
            }else{
                m = atoi(min);
            }
            dur = (60*h)+m;
            insertNode(songName, dur);

        }else if(choice == 2){
            printf("Enter a song name:\n");
            gets(input);
            deleteNode(input);
        }else if(choice == 3){
            printList(chrono_head, alpha_head, duration_head, random_head);
        }else if(choice == 4){
            printf("Enter a file name:\n");
            gets(input);
            FILE * fp;
            int i;
            fp = fopen (input, "w");

            int k = 1;
            int hour = 0;
            int min = 0;
            fprintf(fp, "The list in chronological order:\n");
            while(chrono_head!=NULL){
                hour = chrono_head->duration / 60;
                min = chrono_head->duration % 60;
                fprintf(fp, "\t%d. %s %d:%d\n", k, chrono_head->songName, hour, min);
                chrono_head = chrono_head->chrono_next;
                k++;
            }

            k=1;
            fprintf(fp, "The list in alphabetical order:\n");
            while(alpha_head!=NULL){
                hour = alpha_head->duration / 60;
                min = alpha_head->duration % 60;
                fprintf(fp, "\t%d. %s %d:%d\n", k, alpha_head->songName, hour, min);
                alpha_head = alpha_head->alpha_next;
                k++;
            }

            k=1;
            fprintf(fp, "The list in duration-time order:\n");
            while(duration_head!=NULL){
                hour = duration_head->duration / 60;
                min = duration_head->duration % 60;
                fprintf(fp, "\t%d. %s %d:%d\n", k, duration_head->songName, hour, min);
                duration_head = duration_head->duration_next;
                k++;
            }

            int size = listSize(random_head);
            song* temp = CopyList(random_head);

            fprintf(fp, "The list in random order:\n");

            int o = 1;
            int ho = 0;
            int mi = 0;
            while(o<=size){
                randomSong(temp);
                char name[25];
                strcpy(name, randomName);
                int duration = randomDuration;
                ho = duration / 60;
                mi = duration % 60;
                fprintf(fp, "\t%d. %s %d:%d\n", o, name, ho, mi);
                deleteNodeRandom(&temp, name);
                o++;
            }

            fclose (fp);
            printf("Output is printed to the file %s\n", input);
        }else if(choice == 5){
            return;
        }
    }
}

void readFile(){
    FILE * fPointer;
    fPointer = fopen("songs.txt", "r");
    char singleLine[150];
    char songName[25];
    char duration[10];
    char hour[3];
    char min[3];
    int h;
    int m;
    int dur;
    char hourSingle[2];
    char minSingle[2];

    while ( fgets ( singleLine, sizeof singleLine, fPointer ) != NULL ){
        if(singleLine != "\n"){
            char *piece = strtok(singleLine, "\t");
            strcpy(songName, piece);
            piece = strtok(NULL, "\t");
            strcpy(duration, piece);
            char *secondPiece = strtok(piece, ":");
            strcpy(hour, secondPiece);
            secondPiece = strtok(NULL, ":");
            strcpy(min, secondPiece);
            if(hour[0]== '0'){
                hourSingle[0] = hour[1];
                hourSingle[1] = '\0';
                h = atoi(hourSingle);
            }else{
                h = atoi(hour);
            }
            if(min[0]== '0'){
                minSingle[0] = min[1];
                minSingle[1] = '\0';
                m = atoi(minSingle);
            }else{
                m = atoi(min);
            }
            dur = (60*h)+m;
            insertNode(songName, dur);
        }
    }


    fclose(fPointer);
}

int main() {

    readFile();
    printChoice();

    return 0;
}