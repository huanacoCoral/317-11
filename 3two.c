#include <stdio.h>
#include <string.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int size, rank;//procesador y numero de procesadores
    char frase[200]; // Aumentamos la longitud de la frase
    char frase_dividida[2][100]; 
    //2 para partes pares e impares, 100 como límite de longitud de cada parte
    
    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	//ahora leeremos los datos
    if (rank == 0) {
        printf("Introduce una frase: ");
        fgets(frase, sizeof(frase), stdin);
    }

    // Broadcast de la frase a todos los procesos
    MPI_Bcast(frase, 200, MPI_CHAR, 0, MPI_COMM_WORLD);

    // Tokenizar la frase en palabras
    char *palabra = strtok(frase, " ");
    char palabras[100][50]; // Almacenamiento temporal

    int contador = 0;
    while (palabra != NULL) {
        strcpy(palabras[contador], palabra); //cpopiando palabras 
        contador++;
        palabra = strtok(NULL, " ");
    }

    // Dividir las palabras entre los procesos
    if (rank == 0) {
        int k = 0;
        for (int i = 0; i < contador; i += 2) {
            strcat(frase_dividida[0], palabras[i]);
            strcat(frase_dividida[0], " ");
        }
    }

    if (rank == 1) {
        int k = 1;
        for (int i = 1; i < contador; i += 2) {
            strcat(frase_dividida[1], palabras[i]);
            strcat(frase_dividida[1], " ");
        }
    }

    // Comunicar las partes entre los procesos
    MPI_Send(frase_dividida[0], 100, MPI_CHAR, 1, 0, MPI_COMM_WORLD);
    MPI_Send(frase_dividida[1], 100, MPI_CHAR, 0, 0, MPI_COMM_WORLD);

    // Recibir las partes en el otro proceso
    if (rank == 0) {
        MPI_Recv(frase_dividida[1], 100, MPI_CHAR, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    } else if (rank == 1) {
        MPI_Recv(frase_dividida[0], 100, MPI_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }

    // Cada proceso imprime su parte de la frase
    printf("Proceso %d: %s\n", rank, frase_dividida[rank]);

    MPI_Finalize();
    return 0;
}

