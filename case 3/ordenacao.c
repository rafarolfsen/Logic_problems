#include "ordenacao.h"
#include <stdio.h>

int* bubble_sort(int *vector, int size){    // método de ordenação simples tempo Big O(n²) 
                                            // e memória Big O(1) 

    int i, j, aux, count = 0;               // inicia variaveis de loop, auxiliar e contador
                                            // para evitar checagem desnecessária

    if(size < 2){                           // verifica se o vetor tem ao menos 2 elementos
        return vector;                      // caso não tenha é retornado o vetor
    }
   
    for(i=0; i < size; i++){                // aplica as comparações n-1 vezes
        for(j=0; j < size-count; j++){      // compara apenas elementos que ainda não 
                                            // foram préviamente comprados
            
            if(vector[j] > vector[j+1]){    // caso o elemento da direita seja maior faz:
                aux = vector[j];            // salva o elemento da esquerda em aux
                vector[j] = vector[j+1];    // coloca o valor do elemento da direita no elemento da esquerda
                vector[j+1] = aux;          // coloca o valor de aux (elemento da esquerda) no elemento da direita
            }

        }
        count++;                            // contador de quantos elementos já foram colocados ao final do vetor
                                            // por serem os maiores não é necessário verifica-los novamente
    }

    return vector;                          // retorna o vetor ordenado
}

void quick_sort(int *vector, int left, int right){    // método de ordenação complexo tempo médio Big O(n*log(n)) e memória Big O(n)

    int i = left, j = right, pivo, aux;         // declara variaveis e inicializa i e j com valor da esquerda e direita respectivamente  
    
    pivo = vector[ (int)((left + right) / 2)];          // marca o pivo como o elemento central do espaço avaliado do vetor
     
    while(i <= j) {                             // enquanto i for menor que j faz:
        while(vector[i] < pivo && i < right) {  // enquanto o valor do vetor em i for menor que o pivo e i for menor que a direita faz:
            i++;                                // incrementa i
        }
        while(vector[j] > pivo && j > left) {   // faz a mesma verificação espelhada para o lado direito do vetor 
            j--;
        }
        if(i <= j) {                            // ao final das verificações observa se o valor de i é menor ou igual a j e faz:
            aux = vector[i];
            vector[i] = vector[j];                   // inverte os valores que estavam em lados errados do pivo
            vector[j] = aux;                    // deixando os valores menores que o pivo a esquerda e os maiores a direita
            i++;
            j--;
        }
    }
     
    if(j > left) {                              // após separar os dois lados(maiores e menores que o pivo) é feita a chamada recursiva
        quick_sort(vector, left, j);                 // de forma a ir dividindo e conquistando até ao final todos os sub espaços estarem 
    }                                           // ordenados em relação aos pivos 
    if(i < right) {                             // lembrando que a chama recursiva gera um novo pivo ao centro do lado esquerdo e direito
        quick_sort(vector, i, right);                // do espaço utilizado na etapa anterior
    }

}