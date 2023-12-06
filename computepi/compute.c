#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "compute.h"

/* Number of hits */
unsigned int hits;
/* Mutex Semaphore */
pthread_mutex_t mutex;

/* Thread function */
void * thread_function(void * data) {

    /* The input variable contains the number of points that the thread must
     * calculate */
    int points = *((int *)data);
    
    /* The local variable that shall be used to store the number of points within
     * the circular section */
    int count = 0;     

    /* TO DO: Implement the loop that obtains the random points and counts how
     * many of those lay within the circumference of radius 1 */
      struct drand48_data rand_buffer;
      srand48_r(time(NULL), &rand_buffer);
      double valor_x; /*Aqui creamos los puntos x e y de un punto, para poder saber la coordenada de dicho punto*/
      double valor_y;
      int i;
      for(i = 0; i<points; i++){
      		drand48_r(&rand_buffer, &valor_x);
      		drand48_r(&rand_buffer, &valor_y);
      		if(valor_x*valor_x+valor_y*valor_y<=1){
      			count ++;
      		}
      
      }	/*Aqui lo que hecho es agregar los puntos que se encuentren dentro de la circunferencia. El radio debe ser el punto x elevado al cuadrado mas el punto y elevado al cuadrado
      que es lo que se ha introducido en el condicional. Cada vez que se cumpla la condicion se sumara uno al contador que creeamos anteriormente en la linea 20*/		
      			
    /* TO DO: Add the count to the global variable hits in mutual exclusion */
    pthread_mutex_lock (&mutex);
    hits = hits + count; /*Aqui simplemente añadimos el the count a la variable de hits creada anteriormente*/
    pthread_mutex_unlock (&mutex);
    return NULL;
    

}


void compute(int npoints, int nthreads) {

    /* TO DO: Erase the following line: */
    

    /* TO DO: Launch the threads that will count the points */
    	pthread_mutex_init (&mutex, NULL);
    	pthread_t p_thread[8];
        for (int i = 0; i<nthreads; i++){
        	pthread_create(& p_thread[i], NULL,thread_function, (void*) &npoints);
        }
    	
    

    /* TO DO: Wait for all threads to finish */
    	int status;
    	for (int i = 0; i<nthreads; i++){
        	pthread_join(p_thread[i], (void **)&status);
        }

    /* TO DO: print the ratio of points that meet the criteria */

    /* The following print string can be used to print the calculated value:
     * easter Egg  Profe :D
     * printf("%.8f\n", VALUE_OF_PI);
     * where VALUE_OF_PI is the floating-point value to be printed.
     */
     	double ratio = hits;
     	ratio = ratio/npoints;
     	ratio = ratio/nthreads;
     	double pi = ratio*4;
	printf("Ratio: %.8f\n", ratio);
	printf("Pi: %.8f\n", pi);/*Finalmente se imprime los puntos que han cumplido los criterios que se han puesto*/
}
