#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main(){

    int sizes[] = {4,10,10,1};
    int number_of_layers=(sizeof(sizes)/sizeof(sizes[0]));
    double random_value;
    srand ( time ( NULL));
    //printf("%s","holaaa");

    double*** wij = (double***)malloc(sizeof(double**)*number_of_layers);
    for (int i=0 ; i<number_of_layers ; i++){
        wij[i]= (double**) malloc(sizeof(double**)*sizes[i]);   //creo cada tabla que apuntara a otra tabla con doubles
    }
    
    for (int i=0 ; i<number_of_layers ; i++){
        for(int j=0; j<number_of_layers ; j++){
            wij[i][j]= (double*) malloc(sizeof(double*)*2); //cada tabla de cada capa tiene 2 tablas
        }
    }
  
  for (int n=0 ; n<number_of_layers ; n++){
        for(int i=0; i<number_of_layers ; i++){
            for(int j=0; j<sizes[n] ; j++){
                wij[n][i][j]= (double)rand()/RAND_MAX*2.0-1.0;;
            }
        }
    }
    
    
for (int n=0 ; n<number_of_layers ; n++){
        for(int i=0; i<number_of_layers ; i++){
            for (int j=0; j<sizes[n] ; j++){
                printf("%lf ",(double)wij[n][i][j]);
            }
            printf("\n");
        }
        printf("\n");
    }

}