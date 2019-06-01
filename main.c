#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void insertNode(char name[], int duration){
    insertChrono(name, duration, &chrono_head);
    alpha_head = insertAlpha(alpha_head, name, duration);
    duration_head = insertDuration(duration_head, name, duration);
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

void deleteNode(char name[]){
    deleteNodeChrono(&chrono_head, name);
    deleteNodeAlpha(&alpha_head, name);
    deleteNodeDuration(&duration_head, name);
}

//print methods
void printList(song* ch, song* alp, song* dur){
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
}

void printChoice(){
    printf("Enter your choice:\n");
    printf("\t1 to insert a song into the list.\n");
    printf("\t2 to delete a song from list.\n");
    printf("\t3 to print the songs in the list.\n");
    printf("\t4 to print the songs to an output file.\n");
    printf("\t5 to end.\n");

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

    printList(chrono_head, alpha_head, duration_head);
}

int main() {

    readFile();
    printChoice();

    return 0;
}