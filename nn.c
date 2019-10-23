#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main(){

    int sizes[] = {4,6,10,20,1};
    int number_of_layers=(sizeof(sizes)/sizeof(sizes[0]))-1;    //descomptem la taula final (q seria la del node final)
    double random_value;
    srand ( time ( NULL));
    //printf("%s","holaaa");
    double*** wij = (double***)malloc(sizeof(double**)*number_of_layers);
    for (int n=0 ; n<number_of_layers ; n++){
        wij[n]= (double**) malloc(sizeof(double**)*sizes[n]);   //creo cada tabla que apuntara a otra tabla con doubles
    }
    
    int x=0;

    for (int n=0 ; n<number_of_layers ; n++){
        for(int i=0; i<sizes[n]; i++){  //creamos tabla que guarde tantas posiciones como tablas pueda tener!
            wij[n][i]= (double*) malloc(sizeof(double*)*sizes[n+1]); //cada posicion de la tabla apunta a otra tabla con sizes[i]+1 elementos
            x++;
        }
    }
    
    for (int n=0 ; n<number_of_layers; n++){
        for(int i=0; i<sizes[n] ; i++){ //para cada una de las tablas reservare espacio para los sizes[i+1] elementos
            for(int j=0; j<sizes[n+1] ; j++){   //rellenamos cada uno de esos [i+1] elementos
                wij[n][i][j]= (double)rand()/RAND_MAX*2.0-1.0;
            }
        }
    }

for (int n=0 ; n<number_of_layers ; n++){
        for(int i=0; i<sizes[n] ; i++){
            for (int j=0; j<sizes[n+1] ; j++){
                printf("%lf ",(double)wij[n][i][j]);
            }
            printf("\n");
        }
        printf("\n");
    }

}