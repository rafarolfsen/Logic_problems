//
// Rafael Amaro Rolfsen
// USP São Carlos
// Computer Scientist
//

#include <stdlib.h>
#include <stdio.h>
#include "ordenacao.h"

typedef struct{ // struct for a pair and a size
    int a;
    int b;
    int size;
} Pair;

void add_pair( Pair* visited, int* visitedsize, int a, int b, int size){ // function to add a new pair to the vector of struct

    //printf(".%d %d %d.\n", a, b, size);

    visited = realloc(visited, (sizeof(Pair) * (*visitedsize+1) ) );    // realloc the vector size
    visited[*visitedsize].a = a;
    visited[*visitedsize].b = b;                                        // set values
    visited[*visitedsize].size = size; 
    *visitedsize = *visitedsize + 1;                                    //increase vector size indicator

    return;
}

int pair_size(Pair* visited, int visitedsize, int a, int b){            // function for return pair size

    int i;

    for(i=0; i < visitedsize; i++){                             
        if(visited[i].a == a && visited[i].b == b){             // try to find the pair
            return visited[i].size;                             // return the pair size
        }
    }

    return 0;                                                   // if not found return 0
}

int* readvec(int n){                        // function for alocate and read int vector

    int* vec =  NULL;                       // declare vector and auxiliar int
    int i;

    vec = (int*) malloc (sizeof(int)*n);    // alocate space for vector

    for(i=0; i<n; i++){
        scanf("%d", &vec[i]);               // read the vector
    }

    return vec;                             // return the vector
}

int visited_search(Pair* visited, int visitedsize, int aux1, int aux2){ //function to check if a pair have been visited
    
    int i;

    for(i=0; i < visitedsize; i++){
        if(visited[i].a == aux1 && visited[i].b == aux2){       // try to find the pair
            return 0;                                           // if found return 0
        }
    }

    return 1;                                                  // if not found return 1
} 

int binary_vec_search(int* vec, int left, int right, int sum) { // function to search value at the vector
    
    int middle;
    
    if (right >= left) { 
        
        middle = left + (right - left) / 2; 
  
        if (vec[middle] == sum){                                    // use recursive call to check the side that 
            return 0;                                               // can contain the value until find it and return 0
        }                                                           // or do not find and return 1
        else if (vec[middle] > sum){ 
            return binary_vec_search(vec, left, middle-1, sum); 
        }
        else{
            return binary_vec_search(vec, middle + 1, right, sum); 
        }
    } 

    return 1; 
} 
  

int* biggestseq(int* vec, int n, int* resultsize){       // function for find biggest fibonacci sequence

    int i, j, aux1, aux2, aux3, aux4, aux, sum, visitedsize = 0, size;   // declare auxiliar variables
    Pair* visited = malloc(sizeof(Pair)*1);         // allocate inicial Pair vector
    Pair biggest;
    int* result = NULL;

    biggest.size = 0;

    for(i=0; i<n-1; i++){                           // for each position in vector
        for(j=i+1; j<n; j++){                       // compare with all bigger positions
            
            aux1 = vec[i];                          // save the 2 initial values for this attempt
            aux2 = vec[j];

            sum = aux1+aux2;                        // save the sum of the 2 values

            aux4 = aux2;                            // prepare future auxiliar

            if(visited_search(visited, visitedsize, aux1, aux2) == 1){              // if it is not a already calculated pair:
                size = 2;                                                           // start pair sequence size in 0
                while( binary_vec_search(vec, 0, n-1, sum) == 0){     // while the values are a fibonacci sequence:
                    size++;                                                         // increase pair sequence size
                    aux3 = aux4;                                                    // atualize the values and sum
                    aux4 = sum;
                    sum = aux3+aux4;
                    if(visited_search(visited, visitedsize, aux3, aux4) == 1){
                        add_pair(visited, &visitedsize, aux3, aux4, 0);     // if is a not visited add it as a 0 size because when vector
                    }                                                       // is ordered this will be the biggest sequence with this pair 
                }                                                              
                                                                            // if it is a full new pair
                add_pair(visited, &visitedsize, aux1, aux2, size);          // save this new pair sequence size
                if(size > biggest.size){
                    biggest.a = aux1;
                    biggest.b = aux2;
                    biggest.size = size;
                }
                visitedsize++;
            }

        }

    }

    free(visited);      // FREE ALOCATED MEMORY
    visited = NULL;     // set as null for security

    *resultsize = biggest.size;                             // save result size

    result = (int*) malloc (sizeof(int) * (*resultsize) );  // alocate memory for result vector

    aux1 = biggest.a;
    aux2 = biggest.b;
    sum = aux1+aux2;

    result[0] = aux1;
    result[1] = aux2;               // save result vector values

    for(i=2; i<(*resultsize); i++){
        result[i] = sum;
        aux1 = aux2;
        aux2 = sum;
        sum = aux1+aux2;
    }

    return result;              // return result
}

int main(int argc, char *argv[ ]){

    int n, i;                                       // declare int for vector size
    int* vec = NULL;                                // declare vector
    int* result = NULL;                             // declare result vector
    int resultsize;                                 // auxiliar int size

    scanf("%d", &n);                // read vector size

    vec = readvec(n);               // call function for alocate and read the vector

    quick_sort(vec, 0, n-1);        // sort the vector using quicksort (imported header file)

    result = biggestseq(vec, n, &resultsize);       // call function for search biggest fibonacci sequence

    for(i=0; i<resultsize; i++){
        printf("%d ", result[i]);                   //print prefix biggest fibonacci sequence
    }

    for(i=0; i<n; i++){                             // print the other elements after the prefix (sorted)
        if(binary_vec_search(result, 0, resultsize-1, vec[i]) == 1){
            printf("%d ", vec[i]);                  // if is not present in result vector print
        }
    }                                               // was not specified if the after prefixed sequence need or not to be
                                                    // sorted and if i should or not print repeated values that appears at
                                                    // prefix
    return 0;
}