#include <stdio.h>
#include <stdlib.h>
#include <time.h>
/*
typedef struct NN
{
    double*** nn_weights;
    double** nn_tresholds;

};*/

void display_matrix(double*** wij,  int layer_sizes[] , int number_of_tables){
    for (int n=0 ; n<number_of_tables ; n++){
            for(int i=0; i<layer_sizes[n+1] ; i++){
                for (int j=0; j<layer_sizes[n] ; j++){
                    printf("%lf ",(double)wij[n][i][j]);
                }
                printf("\n");
            }
            printf("\n");
        }
}


void display_tresholds(double** tresholds,  int layer_sizes[] , int number_of_layers){
    for (int n=0 ; n<number_of_layers ; n++){
            for(int i=0; i<layer_sizes[n] ; i++){
                printf("%lf\t",tresholds[n][i]);
            }
            printf("\n");
        }
}

double*** init_nn_weights(int layer_sizes[], int number_of_tables){

    double*** wij = (double***)malloc(sizeof(double**)*number_of_tables);
    
    for (int n=0 ; n<number_of_tables ; n++){
        wij[n]= (double**) malloc(sizeof(double**)*layer_sizes[n]);         //creo cada tabla que apuntara a otra tabla con doubles
    }
    for (int n=0 ; n<number_of_tables ; n++){
        for(int i=0; i<layer_sizes[n+1]; i++){                                //creamos tabla que guarde tantas posiciones como tablas pueda tener!
            wij[n][i]= (double*) malloc(sizeof(double*)*layer_sizes[n]); //cada posicion de la tabla apunta a otra tabla con sizes[i]+1 elementos
        }
    }
    for (int n=0 ; n<number_of_tables; n++){
        for(int i=0; i<layer_sizes[n+1] ; i++){                               //para cada una de las tablas reservare espacio para los sizes[i+1] elementos
            for(int j=0; j<layer_sizes[n] ; j++){                          //rellenamos cada uno de esos [i+1] elementos
                wij[n][i][j]= (double)rand()/RAND_MAX*2.0-1.0;
            }
        }
    }
    return wij;
}

double** init_nn_tresholds(int layer_sizes[], int number_of_layers){                  //units of input layer are not gonna have tresholds, because we dont need them 

    double** tresholds = (double**)malloc(sizeof(double*)*number_of_layers);
    for(int n=1 ; n<number_of_layers ; n++){                                         //creamos tabla que guarde tantas posiciones como tablas pueda tener!
        tresholds[n]= (double*) malloc(sizeof(double)*layer_sizes[n]);              //cada posicion de la tabla apunta a otra tabla con sizes[i]+1 elementos
    }
    for(int n=1 ; n<number_of_layers ; n++){                                         //creamos tabla que guarde tantas posiciones como tablas pueda tener!
        for(int i ; i<layer_sizes[n] ; i++){
            tresholds[n][i]=(double)rand()/RAND_MAX*2.0-1.0;
        }
    }

    return tresholds;
}

int main(){
    srand ( time ( NULL ) ) ;
    int layer_sizes[] = {4,10,20,30,1};
    int number_of_layers=(sizeof(layer_sizes)/sizeof(layer_sizes[0]));    //descomptem la taula final (q seria la del node final)
    int number_of_tables=number_of_layers-1;

    double*** wij = init_nn_weights(layer_sizes,number_of_tables);
    //double** nn_tresholds= init_nn_tresholds(layer_sizes,number_of_layers);
    //display_matrix(wij,layer_sizes,number_of_tables);

    double** tresholds = (double**)malloc(sizeof(double*)*number_of_layers-1);
    

    for(int n=0 ; n<number_of_layers-1 ; n++){                                         //creamos tabla que guarde tantas posiciones como tablas pueda tener!
        tresholds[n]= (double*) malloc(sizeof(double)*layer_sizes[n+1]);              //cada posicion de la tabla apunta a otra tabla con sizes[i]+1 elementos
    }

    for(int n=0 ; n<number_of_layers-1 ; n++){                                         //creamos tabla que guarde tantas posiciones como tablas pueda tener!
        for(int i=0 ; i<layer_sizes[n+1] ; i++){
            tresholds[n][i]=(double)rand()/RAND_MAX*2.0-1.0;
        }
    }

    for(int n=0 ; n<number_of_layers-1 ; n++){                                         //creamos tabla que guarde tantas posiciones como tablas pueda tener!
        for(int i=0 ; i<layer_sizes[n+1] ; i++){
            printf("%lf\t",tresholds[n][i]);
        }
        printf("\n");
    }

    //display_tresholds(nn_tresholds,layer_sizes,number_of_layers);
    
}