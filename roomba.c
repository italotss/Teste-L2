#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <setjmp.h>

typedef struct infoRoomba{
    int x, y; // posicao do aspirador
    int dir; // 0 = norte, 1 = leste, 2 = sul, 3 = oeste
    } infoRoomba;

void criaSala(FILE *fp, int *out[]);
void moveRoomba(FILE *fp, float tamX, float tamY, int *out[]);



int main(){

    FILE *fp = fopen("teste.txt", "r");
    int i=0;
    int saida[2];
    if (fp == NULL){
        printf("erro ao abrir o arquivo\n");
        return 0;
    }

    criaSala(fp, saida);

    fclose(fp);
    return 0;
}


void criaSala(FILE *fp, int *out[]){
    int i=0;
    while (fscanf(fp, "%d", &out[i]) == 1){
        i++;
    }
    int tamX = out[0];
    int tamY = out[1];
    if(fp != EOF){
        moveRoomba(fp, tamX, tamY, out);
    }
}

void moveRoomba(FILE *fp, float tamX, float tamY, int *out[]){

    infoRoomba robo;
    robo.x = 0, robo.y = 0, robo.dir = 0; 
    char ch;
    while((ch = fgetc(fp)) != EOF){
        switch(ch){

        case 'F':

            if(robo.dir == 0 && robo.y < tamY) //caminha norte
                robo.y++;
            else if (robo.dir == 1 && robo.x < tamY) //caminha leste
                robo.x++;
            else if (robo.dir == 2 && robo.y > 0) //caminha sul
                robo.y--;
            else if (robo.dir == 3 && robo.x > 0) // caminha oeste
                robo.x--;
            
            break;

        case 'T':

            if(robo.dir == 0 && robo.y > 0) //caminha sul
                robo.y--;
            else if (robo.dir == 1 && robo.x > 0){ //caminha oeste
                robo.x--;}
            else if (robo.dir == 2 && robo.y < tamY) //caminha norte
                robo.y++;
            else if (robo.dir == 3 && robo.x < tamY) // caminha leste
                robo.x++;
            
            break;
        
        case 'D':
            robo.dir++;

            if(robo.dir > 3)
                robo.dir = 0;  //uma volta inteira
            break;

        case 'E':
            robo.dir--;

            if(robo.dir < 0)
                robo.dir = 3;  //uma volta inteira
            break;
        
        default:
            break;
        }

        if(isdigit(ch) == 1){
            if(robo.dir == 0){
                printf("N %d %d\n", robo.x, robo.y);
            }
            if(robo.dir == 1){
                printf("L %d %d\n", robo.x, robo.y);
            }
            if(robo.dir == 2){
                printf("S %d %d\n", robo.x, robo.y);
            }
            if(robo.dir == 3){
                printf("O %d %dd\n", robo.x, robo.y);
            }
            criaSala(fp, out);
        }
    }
    if(ch == EOF){
        if(robo.dir == 0){
            printf("N %d %d\n", robo.x, robo.y);
            }
        else if(robo.dir == 1){
            printf("L %d %d\n", robo.x, robo.y);
            }
        else if(robo.dir == 2){
            printf("S %d %d\n", robo.x, robo.y);
            }
        else if(robo.dir == 3){
            printf("O %d %d\n", robo.x, robo.y);
            }
        exit(1);
    }
}