/**************************************************************
*	Pontificia Universidad Javeriana
*	Autor: Gabriel Riaño y Dary Palacios
*	Materia: Sistemas Operativos
*	Descripción: Este programa realiza la multiplicación de dos matrices cuadradas
*			de tamaño N × N utilizando múltiples procesos creados mediante `fork`.
*			Cada proceso hijo se encarga de calcular un subconjunto de filas
*			de la matriz resultado, y luego el proceso padre espera a que
*			todos los procesos hijos terminen su ejecución.
**************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>
#include "mm_fork.h"  // Encabezado con funciones

int main(int argc, char *argv[]) {
	// Validación del número de argumentos de entrada
	if (argc < 3) {
		printf("Uso correcto:\n $ ./ejecutable tamMatriz numProcesos\n");
		return -1;
	}

	// Conversión de argumentos a enteros: tamaño de la matriz y número de procesos
	int N = atoi(argv[1]);
	int num_proc = atoi(argv[2]);

	// Reserva dinámica de memoria para las matrices A, B y C (matriz resultado)
	double *matA = (double *) calloc(N * N, sizeof(double));
	double *matB = (double *) calloc(N * N, sizeof(double));
	double *matC = (double *) calloc(N * N, sizeof(double));

	// Inicializa matrices A y B con valores aleatorios
	srand(time(NULL));
	iniMatrix(matA, matB, N);

	// Muestra las matrices A y B si el tamaño es manejable
	impMatrix(matA, N);
	impMatrix(matB, N);

	// Determina cuántas filas calculará cada proceso
	int rows_per_process = N / num_proc;

	// Inicia cronómetro para medición de tiempo
	InicioMuestra();

	// Bucle para crear procesos hijos
	for (int i = 0; i < num_proc; i++) {
		pid_t pid = fork();

		if (pid == 0) {  // Código del proceso hijo
			int filaIni = i * rows_per_process; // Índice de inicio de filas
			int filaFin = (i == num_proc - 1) ? N : filaIni + rows_per_process; // Índice de fin de filas

			// Cada hijo multiplica un bloque de filas
			multiMatrix(matA, matB, matC, N, filaIni, filaFin);

			// Muestra parcial de la matriz resultado (si N es pequeño)
			if (N < 9) {
				printf("\nProceso hijo PID %d calculó filas %d a %d:\n", getpid(), filaIni, filaFin - 1);
				for (int r = filaIni; r < filaFin; r++) {
					for (int c = 0; c < N; c++)
						printf(" %.2f ", matC[N * r + c]);
					printf("\n");
				}
			}

			exit(0);  // Termina el proceso hijo
		} else if (pid < 0) {
			perror("Error al hacer fork");  // Manejo de error en caso de fallo al crear proceso
			exit(1);
		}
	}

	// El padre espera a que todos los procesos hijos terminen
	for (int i = 0; i < num_proc; i++)
		wait(NULL);

	// Finaliza medición de tiempo
	FinMuestra();

	// Libera la memoria reservada
	free(matA);
	free(matB);
	free(matC);

	return 0;
}