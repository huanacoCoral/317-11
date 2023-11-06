#include <stdio.h>
#include <string.h>
#include <omp.h>

int main() {
    int procesador;
    char ca[] = "tres tristes tigres trigaban trigo por culpa del bolivar";
    
    char *palabra;
    char cad[100]; 
        strcpy(cad, ca);
    int x=1;
    int y=0;
    #pragma omp parallel
    {
        procesador = omp_get_thread_num();
    //   printf("1 Proceso en procesador %d\n", procesador);
       
	printf(" \n");
	
         //Solo el hilo 0 ejecutará esta parte
        if (y == 0) {
            palabra = strtok(ca," ");
            while (palabra != NULL) {
                printf(" .%s", palabra); 
                palabra = strtok(NULL, " ");
                //printf(" .%s", palabra);
                palabra = strtok(NULL, " ");
                //printf("Proceso en procesador xxxx %d\n", x);
            }
            
        }
        
        
        
         printf(" \n"); 
      //   printf("y%d\n", y);
        if (y == 2) {
        
        palabra = strtok(cad," ");
        
            while (palabra != NULL) {
                
                palabra = strtok(NULL, " ");
                printf(" *%s", palabra);
                palabra	 = strtok(NULL, " ");
               
            }
        }
        
        y=y+1;
    }

    printf("\nIndependiente\n");
    return 0; 
}

