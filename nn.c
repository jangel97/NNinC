#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main(){

    int layer_sizes[] = {4,6,10,20,1};
    int number_of_layers=(sizeof(layer_sizes)/sizeof(layer_sizes[0]))-1;    //descomptem la taula final (q seria la del node final)
    double random_value;
    srand ( time ( NULL));

    double*** wij = (double***)malloc(sizeof(double**)*number_of_layers);
    
    for (int n=0 ; n<number_of_layers ; n++){
        wij[n]= (double**) malloc(sizeof(double**)*layer_sizes[n]);         //creo cada tabla que apuntara a otra tabla con doubles
    }
    for (int n=0 ; n<number_of_layers ; n++){
        for(int i=0; i<layer_sizes[n+1]; i++){                                //creamos tabla que guarde tantas posiciones como tablas pueda tener!
            wij[n][i]= (double*) malloc(sizeof(double*)*layer_sizes[n]); //cada posicion de la tabla apunta a otra tabla con sizes[i]+1 elementos
        }
    }
    for (int n=0 ; n<number_of_layers; n++){
        for(int i=0; i<layer_sizes[n+1] ; i++){                               //para cada una de las tablas reservare espacio para los sizes[i+1] elementos
            for(int j=0; j<layer_sizes[n] ; j++){                          //rellenamos cada uno de esos [i+1] elementos
                wij[n][i][j]= (double)rand()/RAND_MAX*2.0-1.0;
            }
        }
    }

/*  JUEGO DE PRUEBAS    
Miramos entre la capa 0 y la capa 1 la matriz de sinapsis
*/
    for (int x=0;   x<layer_sizes[1]    ;   x++ ){
        for (int k=0    ;   k<layer_sizes[0]    ;   k++){
            printf("%lf",wij[0][x][k]);                             //para la capa 0, miramos su matriz de transicion de pesos (valor sinapsis), que es de 4x6 (4 neuronas capa 0, 6 neuronas capa 1)
        }   
        printf("\n");
    }
 printf("\n");
 printf("----------------------------------------------");
  printf("\n");

//Para imprimir todas las matrices
for (int n=0 ; n<number_of_layers ; n++){
        for(int i=0; i<layer_sizes[n+1] ; i++){
            for (int j=0; j<layer_sizes[n] ; j++){
                printf("%lf ",(double)wij[n][i][j]);
            }
            printf("\n");
        }
        printf("\n");
    }



}