#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <stdarg.h>
/*
typedef struct neuron_t
{
    double** treshold,;

};
*/
const double learning_rate=0.01;
const double momentum=0.9;

double sigmoid(double x)
{
     double exp_value;
     double return_value;
     exp_value = exp(-x);
     return_value = 1 / (1 + exp_value);
     return return_value;
}

const char* getfield(char* line, int num)
{
    const char* tok;
    for (tok = strtok(line, " ");
            tok && *tok;
            tok = strtok(NULL, " \n"))
    {
        if (!--num)
            return tok;
    }
    return NULL;        

}

void display_matrix(double*** wij,  int layer_sizes[] , int number_of_tables){
    printf("---------------------------------------------");
    for (int n=0 ; n<number_of_tables ; n++){
            for(int i=0; i<layer_sizes[n+1] ; i++){
                for (int j=0; j<layer_sizes[n] ; j++){
                    wij[n][i][j]=(double)rand()/RAND_MAX*2.0-1.0;
                    printf("%lf\t",(double)wij[n][i][j]);
                }
                printf("\n");
            }
            printf("\n");
        }
}

void ini_matrix(double*** wij,  int layer_sizes[] , int number_of_tables){
    printf("---------------------------------------------");
    for (int n=0 ; n<number_of_tables ; n++){
            for(int i=0; i<layer_sizes[n+1] ; i++){
                for (int j=0; j<layer_sizes[n] ; j++){
                    wij[n][i][j]=(double)rand()/RAND_MAX*2.0-1.0;
                }
            }
        }
}

void display_tresholds(double** tresholds,  int layer_sizes[] , int number_of_layers){
    for(int n=0 ; n<number_of_layers-1 ; n++){                                         //creamos tabla que guarde tantas posiciones como tablas pueda tener!
        for(int i=0 ; i<layer_sizes[n+1] ; i++){
            printf("%lf\t",tresholds[n][i]);
        }
        printf("\n\n");
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

        for (int n=0 ; n<number_of_tables ; n++){
            for(int i=0; i<layer_sizes[n+1] ; i++){
                for (int j=0; j<layer_sizes[n] ; j++){
                    wij[n][i][j]=(double)rand()/RAND_MAX*2.0-1.0;
                }
            }
        }

    return wij;
}

double*** init_nn_weights_with_zeros(int layer_sizes[], int number_of_tables){

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
                wij[n][i][j]= (double)0;
            }
        }
    }
    return wij;
}

double** init_nn_tresholds(int layer_sizes[], int number_of_layers){                  //units of input layer are not gonna have tresholds, because we dont need them 

   double** tresholds = (double**)malloc(sizeof(double*)*number_of_layers-1);
    

    for(int n=0 ; n<number_of_layers-1 ; n++){                                         //creamos tabla que guarde tantas posiciones como tablas pueda tener!
        tresholds[n]= (double*) malloc(sizeof(double)*layer_sizes[n+1]);              //cada posicion de la tabla apunta a otra tabla con sizes[i]+1 elementos
    }

    for(int n=0 ; n<number_of_layers-1 ; n++){                                         //creamos tabla que guarde tantas posiciones como tablas pueda tener!
        for(int i=0 ; i<layer_sizes[n+1] ; i++){
            tresholds[n][i]=(double)rand()/RAND_MAX*2.0-1.0;
        }
    }

    return tresholds;
}

double** init_nn_tresholds_with_zeros(int layer_sizes[], int number_of_layers){                  //units of input layer are not gonna have tresholds, because we dont need them 

   double** tresholds = (double**)malloc(sizeof(double*)*number_of_layers-1);
    

    for(int n=0 ; n<number_of_layers-1 ; n++){                                         //creamos tabla que guarde tantas posiciones como tablas pueda tener!
        tresholds[n]= (double*) malloc(sizeof(double)*layer_sizes[n+1]);              //cada posicion de la tabla apunta a otra tabla con sizes[i]+1 elementos
    }

    for(int n=0 ; n<number_of_layers-1 ; n++){                                         //creamos tabla que guarde tantas posiciones como tablas pueda tener!
        for(int i=0 ; i<layer_sizes[n+1] ; i++){
            tresholds[n][i]=0;
        }
    }

    return tresholds;
}


double** init_nn_feed_forward(int layer_sizes[], int number_of_layers){                  //units of input layer are not gonna have tresholds, because we dont need them 

   double** tresholds = (double**)malloc(sizeof(double*)*number_of_layers-1);
    

    for(int n=0 ; n<number_of_layers-1 ; n++){                                         //creamos tabla que guarde tantas posiciones como tablas pueda tener!
        tresholds[n]= (double*) malloc(sizeof(double)*layer_sizes[n+1]);              //cada posicion de la tabla apunta a otra tabla con sizes[i]+1 elementos
    }

    for(int n=0 ; n<number_of_layers-1 ; n++){                                         //creamos tabla que guarde tantas posiciones como tablas pueda tener!
        for(int i=0 ; i<layer_sizes[n+1] ; i++){
            tresholds[n][i]=0;
        }
    }

    return tresholds;
}


/*
x: value we desire to scale
Xmin: Max value in dataset
Xmax: Min value in dataset
[Smin,Smax] interval where return value will be defined
The interval will be [0,1], the domain of the Sigmoid function
*/
double scale_data(double x,double Xmin,double Xmax, double Smin, double Smax){
    return ((Smax-Smin)/(Xmax-Xmin))*(x-Xmin) + Smin;
}

/*
s: value we desire to unscale
Xmin: Max value in dataset
Xmax: Min value in dataset
[Smin,Smax] interval where return value will be defined
The interval will be [0,1], the domain of the Sigmoid function


*/
double unscale_data(double s,double Xmin,double Xmax, double Smin, double Smax){
    return ((Xmax-Xmin)/(Smax-Smin))*(s-Smin) + Xmin;
}


double* feed_forward_algorythm(double*** wij,double** nn_tresholds,double** nn_feed_forward,int layer_sizes[],int number_of_layers_except_input_layer ,int number_elem_in_pattern,...){
    va_list list;
    double val;
    double* input_layer_activation; //array that will store each of the activations of the input layer (the patterns) 
    input_layer_activation=malloc(sizeof(double)*number_elem_in_pattern);
    va_start(list,number_elem_in_pattern);
    for (int i=0;   i<number_elem_in_pattern ; i++){
        input_layer_activation[i]= va_arg(list, double);
    }

    //first step is to calculate  nn_feed_forward[0] which depends on input_layer_activation
    double hIi=0;

    for ( int i=0; i<layer_sizes[1] ; i++ ){   //per each neuron in first layer (no input layer) we calculate feed forward
        for (int j=0; j<layer_sizes[0] ; j++){ //per each neuron in the input layer (before layer)
            hIi = hIi + (wij[0][i][j] *  input_layer_activation[j]);
        }
        hIi=hIi-nn_tresholds[0][i]; //nn_tresholds[0] es la capa 2 (la siguiente despues del input layer)
        nn_feed_forward[0][i]=sigmoid(hIi);
    }

    /*
    It is important to note that nn_feed_forward[0][i], 
    corresponds to the layer after the input later
    */
   double hi;
    for(int n=1; n<number_of_layers_except_input_layer ; n++){  //start is n=1 because first case was done before the loop
        for (int i=0 ; i<layer_sizes[n+1] ; i++){  //Per each unit from the layer 2 on...
           hi=0;
           for (int j=0; j<layer_sizes[n] ; j++){
               hi=hi+(wij[n][i][j]*nn_feed_forward[n-1][j]);
           } 
           hi=hi-nn_tresholds[n][i];
           nn_feed_forward[n][i]=sigmoid(hi);
        }
    }

    return nn_feed_forward[number_of_layers_except_input_layer-1];

}

void error_back_propagation(double*** wij,double*** changes_before_weights,double** changes_before_tresholds,double** nn_tresholds,double** nn_feed_forward,double** nn_descent_gradient,int layer_sizes[],int number_of_layers_except_output_layer,double expected_result,int number_elem_in_pattern,...){
    //first we calculate the propagation of the output layer for eahc neuron of it
    va_list list;
    double* propagation_output_layer;
    double change;
    double sum=0;
    double* nn_input_pattern; //array that will store each of the activations of the input layer (the patterns) 
    nn_input_pattern=malloc(sizeof(double)*number_elem_in_pattern);
    va_start(list,number_elem_in_pattern);
    for (int i=0;   i<number_elem_in_pattern ; i++){
        nn_input_pattern[i]= va_arg(list, double);
    }


    //double* result=nn_feed_forward[2];    int layer_sizes[] = {2,10,15,1}; la posicion 2 seria el ultimo, pq la input layer no cuenta
    double* result=nn_feed_forward[number_of_layers_except_output_layer-1]; //result is an araay because there could be more than one unit in the output layer
    //printf("\n---------\nexpected result: %lf",expected_result);
    //printf("nn result: %lf\n------------------\n",result[0]);

    if (result[0] == expected_result){  //CONVERT TO LIST AND COMPARE!!
        return;
    }

    for(int i=0 ; i<layer_sizes[number_of_layers_except_output_layer] ; i++){
        nn_descent_gradient[number_of_layers_except_output_layer-1][i]=result[i]*((double)1-result[i])*(result[i]-expected_result);
    }
     //I have the first formula, but now we have to do the back-propagation to the rest of the network  ;   nn_descent_gradient[number_of_layers_except_output_layer-1][0]
    //backpropagation:
    for (int n=number_of_layers_except_output_layer-1 ; n>0 ; n--){ //per each layer {2,10,15,1}; 
        for (int j=0 ; j<layer_sizes[n] ; j++){
            sum=0;
            for (int i=0 ; i<layer_sizes[n+1]  ; i++ ){
                sum = sum + nn_descent_gradient[n][i]*wij[n][i][j]; 
            }
            nn_descent_gradient[n-1][j] = nn_feed_forward[n-1][j]*(1-nn_feed_forward[n-1][j])*sum;

        }
    }

    //lets update weights except for the one of the L=2 (in my case it is the position 0)
    for (int n=number_of_layers_except_output_layer-1 ; n>0 ; n--){
        for (int i=0 ; i<layer_sizes[n+1] ; i++){
                for (int j=0 ; j<layer_sizes[n] ; j++){
                    change=(-1)*learning_rate*nn_descent_gradient[n][i]*nn_feed_forward[n-1][j]+momentum*changes_before_weights[n][i][j];
                    wij[n][i][j]=wij[n][i][j]+change;
                    changes_before_weights[n][i][j]=change;
                }   
        }
    }
    for (int i=0 ; i<layer_sizes[1] ; i++){
                for (int j=0 ; j<layer_sizes[0] ; j++){
                    change=(-1)*learning_rate*nn_descent_gradient[0][i]*nn_input_pattern[j]+momentum*changes_before_weights[0][i][j];
                    wij[0][i][j]=wij[0][i][j]+change;
                    changes_before_weights[0][i][j]=change;
                }   
    }

    change=0;
    for (int n=number_of_layers_except_output_layer-1 ; n>=0 ; n--){
        for(int i=0 ; i<layer_sizes[n+1] ; i++){
            change=learning_rate*nn_descent_gradient[n][i]+momentum*changes_before_tresholds[n][i];
            nn_tresholds[n][i]=nn_tresholds[n][i]+change;
            changes_before_tresholds[n][i]=change;
        }
    }

}

/*
Como siempre, init_nn_feed_forward o init_nn_descent_gradient, el retorno en la posicion 0, 
Corresponde a valores de la siguiente capa de la input layer


La capa nn
# Power of a hydroelectrical turbine: value to predict

# height over sea level, fall, net fall, flow, power

*/
int main(int argc, char* argv[]){
    srand ( time ( NULL ) ) ;
    int layer_sizes[] = {2,3,7,1};    //2 values to multiply, one to return the result of the multi operation
    int number_of_layers=(sizeof(layer_sizes)/sizeof(layer_sizes[0]));    //descomptem la taula final (q seria la del node final)
    int number_of_tables=number_of_layers-1;
    FILE* stream = fopen(argv[1], "r"); 
    /*
    Initialize data structure
    */
    double*** wij = init_nn_weights(layer_sizes,number_of_tables);
    double*** changes_before_weights = init_nn_weights_with_zeros(layer_sizes,number_of_tables);
    double** nn_tresholds= init_nn_tresholds(layer_sizes,number_of_layers);
    double** changes_before_tresholds= init_nn_tresholds_with_zeros(layer_sizes,number_of_layers);
    double** nn_feed_forward= init_nn_feed_forward(layer_sizes,number_of_layers);
    double** nn_descent_gradient= init_nn_feed_forward(layer_sizes,number_of_layers);
    ini_matrix(wij,layer_sizes,number_of_tables);

 char line[1024];
for(int i=0 ; i<5 ; i++){
   while (fgets(line, 1024, stream))
    {
        double val1 = atof(getfield(strdup(line), 1));
        double val2 = atof(getfield(strdup(line), 2));
        double result = atof(getfield(strdup(line), 3));
        
        double scaled_val1 = scale_data(val1,(double)0,(double)10,(double)0,(double)1);
        double scaled_val2 = scale_data(val2,(double)0,(double)10,(double)0,(double)1);
        double scaled_result = scale_data(result,(double)0,(double)10,(double)0,(double)1);
        
        //printf("%lf\t%lf\t%lf\n",scaled_val1,scaled_val2,scaled_result);
        feed_forward_algorythm(wij,nn_tresholds,nn_feed_forward,layer_sizes,number_of_tables,layer_sizes[0],scaled_val1,scaled_val2);
        error_back_propagation(wij,changes_before_weights,changes_before_tresholds,nn_tresholds,nn_feed_forward,nn_descent_gradient,layer_sizes,number_of_tables,scaled_result,layer_sizes[0], scaled_val1,scaled_val2);
       
    }
double error_total=0;
printf("\nEPOCH: %d\n",i+1);
printf("------------------------------------------------------------------------------\n");
    for(int i=0; i<5 ; i++){
        double val1 = scale_data(i,(double)0,(double)10,(double)0,(double)1);
        double val2 = scale_data(i,(double)0,(double)10,(double)0,(double)1);   
        double s = feed_forward_algorythm(wij,nn_tresholds,nn_feed_forward,layer_sizes,number_of_tables,2,val1,val2)[0];
        
        printf("%d + %d = %lf",i,i,unscale_data(val1+val2,(double)0,(double)10,(double)0,(double)1));
        printf("\nNN: %lf\n",unscale_data(s,(double)0,(double)10,(double)0,(double)1));
        double error = (unscale_data(val1+val2,(double)0,(double)10,(double)0,(double)1)*val2-s)*(unscale_data(val1+val2,(double)0,(double)20,(double)0,(double)1)-s);
        error_total=error_total+error;
        printf("------------------------------------------------------------------------------\n");
        
    }
    printf("Cuadratic error: %lf", error_total/5);
    printf("\n------------------------------------------------------------------------------\n");

}
 

}
