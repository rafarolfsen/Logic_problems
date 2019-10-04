//
// Rafael Amaro Rolfsen
// USP São Carlos
// Computer Scientist
//

#include <stdlib.h>
#include <stdio.h>


int calculate_cost(int posa, int posb){   // function for calculate tiredness

    int result = 0, diff = 0;       // declaration of integer values for result and difference 
    int i, aux = 1;                 // declaration of integer values for auxiliar information
    
    diff = posa - posb;             // calculate difference between the two positions
    
    if(diff < 0){
        diff = diff * (-1);         // be sure that the diference is a positive number
    }


    if(diff%2 == 0){                        // if difference is a even number do:
        
        for(i=0; i < diff/2; i++){          // for minimize the tiredness they should walk
            result = result + (aux*2);      // the same distance, so every movment will reduce
            aux++;                          // the distance by 2 and increment the cost of aux
        }                                   // for the next step.
    
    }else{                                  // if difference is a odd number do:

        for(i=0; i < diff/2; i++){          // for minimize the tiredness they should walk
            result = result + (aux*2);      // the close as possible of the same distance,
            aux++;                          // so every movement will reduce the distance by 2 
        }                                   // and increment the cost of aux for the next step                       
                                           
        result += aux;                      // at the end just one of them will give the final step
    }                                       // for cmplete the odd distance

    return result;                          // return the minimum cost
}


int main(int argc, char *argv[ ]){

    int posa, posb;         // declaration of integer values for positions of friends a and b
    int result;             // declaration of integer for sum of tiredness

    scanf("%d", &posa);        // read values for a and b positions
    scanf("%d", &posb);

    result = calculate_cost(posa, posb);  // call function that calculate tiredness

    printf("%d\n", result);         // print the final result

    return 0;
}