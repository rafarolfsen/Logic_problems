//
// Rafael Amaro Rolfsen
// USP São Carlos
// Computer Scientist
//

#include <stdlib.h>
#include <stdio.h>

char** read_game(int* first, int* second){  // function for alocate and save info about the matrix

    int i, j;                               // declare auxiliar integers
    char c;                                 // declare auxiliar char
    char** mat = NULL;                      // declare the char matrix

    mat = (char**) malloc(sizeof(char*)*3);         // alocate space for the 3 char* lines of the matrix  

    for(i=0; i<3; i++){
        mat[i] = (char*) malloc(sizeof(char)* 3);   // for each line alocate 3 char positions
    }

    for(i=0; i < 3; i++){                       
        for(j=0; j < 3; j++){               // read the positions
            scanf("%c", &c);
            mat[i][j] = c;
            if(c == 'X'){
                *first = *first + 1;        // save the number os plays of each player
            }                               // in the arguments of function
            else if(c == '0'){
                *second = *second + 1;
            }
        }
        scanf("%*c");                       // read and discard the \n
    }

    return mat;                             // return the alocated matrix
}

void vert_horiz(int* auxf, int* auxs, char** mat, int* result){

    int i, j, aux1, aux2, aux3, aux4;   // declaration of auxiliar ints

    for(i=0; i<3; i++){                 // loop for check first axis positions
        aux1 = 0;                       // aux1 for X in horizontal
        aux2 = 0;                       // aux2 for 0 in horizontal
        aux3 = 0;                       // aux3 for X in vertical
        aux4 = 0;                       // aux4 for 0 in vertical

        for(j=0; j<3; j++){             //lopp for check second axis positions
            if(mat[i][j] == 'X'){
                aux1++;
            }    
            if(mat[i][j] == '0'){       // increases the auxiliar values
                aux2++;
            }
            if(mat[j][i] == 'X'){
                aux3++;
            }
            if(mat[j][i] == '0'){
                aux4++;
            }
        }

        if(aux1 == 3 || aux3 == 3){     // check if exist any vicory sequence
            *result = 1;                // and count how many for each player
            *auxf = *auxf + 1;          // result = winner player
        }
        if(aux2 == 3 || aux4 == 3){
            *result = 2;
            *auxs = *auxs + 1;
        }

    }

    return;
}

void diagonals(int* auxf, int* auxs, char** mat, int*result){

    int i, j, aux1 = 0, aux2 = 0;           // declaration of auxiliar ints 
                                            // aux1 for X in first diagonal 
                                            // aux2 for 0 in first diagonal

    for(i=0; i<3; i++){
        if(mat[i][i] == 'X'){           // increases the auxiliar values
            aux1++;
        }
        if(mat[i][i] == '0'){
            aux2++;
        }
    } 

    if(aux1 == 3){                  // check if exist any vicory sequence
        *result = 1;                // and count how many for each player
        *auxf = *auxf + 1;          // result = winner player
    }
    if(aux2 == 3 ){                 
        *result = 2;
        *auxs = *auxs + 1;
    }

    aux1 = 0;                       // aux1 for X in second diagonal
    aux2 = 0;                       // aux2 for 0 in second diagonal

    for(i=0; i<3; i++){
        if(mat[i][2-i] == 'X'){     // increases the auxiliar values
            aux1++;
        }
        if(mat[i][2-i] == '0'){
            aux2++;
        }
    }

    if(aux1 == 3){                  // check if exist any vicory sequence
        *result = 1;                // and count how many for each player
        *auxf = *auxf + 1;          // result = winner player
    }
    if(aux2 == 3 ){
        *result = 2;
        *auxs = *auxs + 1;
    }

    return;
}

int veify_winner(char** mat){                   // function for verify if exist a winner

    int result = 0, auxf = 0, auxs = 0;         // declaration of int auxiliar and result
                                                // auxf and auxs for number of winner sequences

    vert_horiz(&auxf, &auxs, mat, &result);     // call function for vertical and horizontal check

    diagonals(&auxf, &auxs, mat, &result);      // call function for diagonals check


    if(auxf+auxs == 0){                 // if has no victory sequence, result = 0
        result = 0;
    }
    else if(auxf > 0 && auxs > 0){      // if both players have won it is a invalid result
        result = 3;                     // and result = 4
    }

    return result;           // return the final case of result
}


int main(int argc, char *argv[ ]){

    char** mat;                                 // declaration of char matrix
    int first = 0, second = 0, result = 0;      // declaration of integers for number of plays and result

    mat = read_game(&first, &second);           // function for read the game and save the matix                          

    if(first < second || first > second +1){    // if the matrix have more plays of one of the players
        printf("Inválido \n");                  // can have by the rules, it is a invalid game
        return 0;
    }

    if(first >= 3){                             // if exist the possibility of a winner, call the function
        result = veify_winner(mat);             // to search for a winner and save the result
    }                                           // 0 if has no winner, 1 if first player won, 2 if second player won
                                                // 3 if both players won an it is a invalid game.

    if(result == 0 && first+second == 9){       // if the game has no winner and all spaces are used                      
        printf("Empate\n");                     // print empate
    }
    else if(result == 0){                       // if has no winner and have space for new play
        if(first == second){                    // verify if is first or second player turn 
            printf("Primeiro\n");
        }
        else{
            printf("Segundo\n");
        }
    }
    else if(result == 1){                       // if first player won
        printf("Primeiro_venceu\n");
    }
    else if(result == 2){                       // if secoond player won
        printf("Segundo_venceu\n");
    }                                                       
    else{                                       // if result = 3 both players won
        printf("Inválido \n");                  // and it is a invalid game
    }

    for(first = 0; first < 3; first++){         // free the alocated memory and fill space with NULL
        free(mat[first]);                       // for more security
        mat[first] = NULL;
    }
    free(mat);
    mat = NULL;

    return 0;
}
