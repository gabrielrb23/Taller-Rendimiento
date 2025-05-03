/**************************************************************
*	Pontificia Universidad Javeriana
*	Autor: Gabriel Riaño
*	Materia: Sistemas Operativos
*	Fichero: mm_posix.c
*	Descripción: Implementación del algoritmo clásico de
*			multiplicación de matrices usando hilos POSIX
*			(Pthreads). Incluye funciones para inicialización,
*			impresión, paralelización con `pthread_create`,
*			y medición de tiempo de ejecución.
**************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include <pthread.h>
#include "mm_posix.h"

// Mutex global para sincronización
pthread_mutex_t MM_mutex;

// Bloque de memoria contigua para almacenar matrices A, B y C
double MEM_CHUNK[DATA_SIZE];

// Punteros globales a las matrices
double *mA, *mB, *mC;

// Variables para medición de tiempo
static struct timeval inicio, fin;
 
// Marca el inicio de la medición de tiempo
void InicioMuestra() {
	gettimeofday(&inicio, NULL);
}

// Marca el final y calcula el tiempo total transcurrido
void FinMuestra() {
	gettimeofday(&fin, NULL);
	fin.tv_usec -= inicio.tv_usec;
	fin.tv_sec  -= inicio.tv_sec;
	double tiempo = (double)(fin.tv_sec * 1000000 + fin.tv_usec);  // Conversión a microsegundos
	printf("%.0f\n", tiempo);
}

// Inicializa matrices A y B con valores aleatorios entre 0 y 9, y pone C en cero
void iniMatrix(int SZ) {
	for (int i = 0; i < SZ * SZ; i++) {
		mA[i] = rand() % 10;
		mB[i] = rand() % 10;
		mC[i] = 0;
	}
}

// Imprime una matriz si su dimensión es menor a 12
void impMatrix(int sz, double *matriz) {
	if (sz < 12) {
		for (int i = 0; i < sz * sz; i++) {
			if (i % sz == 0) printf("\n");
			printf(" %.3f ", matriz[i]);
		}
		printf("\n>-------------------->\n");
	}
}
 
// Función que ejecuta cada hilo. Calcula un bloque de filas de la matriz resultado.
void *multiMatrix(void *variables) {
	struct parametros *data = (struct parametros *)variables;

	// Cálculo de los índices de inicio y fin del bloque de filas que debe procesar el hilo
	int ini = (data->N / data->nH) * data->idH;
	int fin = (data->N / data->nH) * (data->idH + 1);

	// Multiplicación clásica fila × columna
	for (int i = ini; i < fin; i++) {
		for (int j = 0; j < data->N; j++) {
			double sumaTemp = 0.0;
			double *pA = mA + (i * data->N);  // Apunta al inicio de la fila i de A
			double *pB = mB + j;			  // Apunta a la columna j de B

			for (int k = 0; k < data->N; k++, pA++, pB += data->N)
				sumaTemp += (*pA * *pB);	  // Producto escalar fila i × columna j

			pthread_mutex_lock(&MM_mutex);
			mC[i * data->N + j] = sumaTemp;
			pthread_mutex_unlock(&MM_mutex);
		}
	}

	// Libera los datos del hilo y finaliza
	free(data);
	pthread_exit(NULL);
}