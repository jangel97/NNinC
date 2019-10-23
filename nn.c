#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main(){

    int sizes[] = {4,4,10,1};
    int number_of_layers=(sizeof(sizes)/sizeof(sizes[0]))-1;    //descomptem la taula final (q seria la del node final)
    double random_value;
    srand ( time ( NULL));
    //printf("%s","holaaa");
    double*** wij = (double***)malloc(sizeof(double**)*number_of_layers);
    for (int i=0 ; i<number_of_layers ; i++){
        wij[i]= (double**) malloc(sizeof(double**)*sizes[i]);   //creo cada tabla que apuntara a otra tabla con doubles
    }
    
    int x=0;

    for (int i=0 ; i<number_of_layers ; i++){
        for(int j=0; j<sizes[i]; j++){  //creamos tabla que guarde tantas posiciones como tablas pueda tener!
            wij[i][j]= (double*) malloc(sizeof(double*)*sizes[i+1]); //cada posicion de la tabla apunta a otra tabla con sizes[i]+1 elementos
            x++;
        }
    }
    
x=0;
    for (int n=0 ; n<number_of_layers; n++){
        for(int i=0; i<sizes[n] ; i++){ //para cada una de las tablas reservare espacio para los sizes[i+1] elementos
            for(int j=0; j<sizes[n+1] ; j++){
                wij[n][i][j]= (double)rand()/RAND_MAX*2.0-1.0;
                x++;
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