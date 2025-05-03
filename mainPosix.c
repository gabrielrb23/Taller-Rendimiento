/**************************************************************
*	Pontificia Universidad Javeriana
*	Autor: Gabriel Riaño y Dary Palacios
*	Materia: Sistemas Operativos
*	Descripción: Multiplicación de matrices cuadradas
*			mediante hilos POSIX (Pthreads). El programa
*			reparte el trabajo de multiplicación entre
*			varios hilos, usando memoria compartida.
**************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "mm_posix.h"  // Cabecera con declaraciones de funciones y estructuras

int main(int argc, char *argv[]) {
	// Validación de argumentos de entrada: tamaño matriz y número de hilos
	if (argc < 3) {
		printf("Uso correcto:\n $ ./ejecutable tamMatriz numHilos\n");
		return -1;
	}

	// Conversión de argumentos
	int SZ = atoi(argv[1]);		// Tamaño de la matriz
	int n_threads = atoi(argv[2]); // Número de hilos

	pthread_t p[n_threads];		// Arreglo de hilos
	pthread_attr_t atrMM;		  // Atributos para los hilos

	// Reserva de memoria continua para matrices A, B y C (punteros globales)
	mA = MEM_CHUNK;
	mB = mA + SZ * SZ;
	mC = mB + SZ * SZ;

	// Inicializa matrices A y B con valores aleatorios
	iniMatrix(SZ);

	// Imprime matrices A y B si son pequeñas
	impMatrix(SZ, mA);
	impMatrix(SZ, mB);

	// Inicia medición de tiempo
	InicioMuestra();

	// Inicializa mutex y atributos de hilos
	pthread_mutex_init(&MM_mutex, NULL);
	pthread_attr_init(&atrMM);
	pthread_attr_setdetachstate(&atrMM, PTHREAD_CREATE_JOINABLE); // Los hilos se pueden unir

	// Creación de hilos para ejecutar la multiplicación de forma concurrente
	for (int j = 0; j < n_threads; j++) {
		// Se reserva memoria para los parámetros individuales del hilo
		struct parametros *datos = (struct parametros *) malloc(sizeof(struct parametros));
		datos->idH = j;		 // ID del hilo
		datos->nH  = n_threads; // Total de hilos
		datos->N   = SZ;		// Tamaño de la matriz

		// Se crea el hilo y se pasa la estructura como argumento
		pthread_create(&p[j], &atrMM, multiMatrix, (void *)datos);
	}

	// Espera a que todos los hilos terminen
	for (int j = 0; j < n_threads; j++)
		pthread_join(p[j], NULL);

	// Finaliza medición de tiempo
	FinMuestra();

	// Imprime la matriz resultado si es pequeña
	impMatrix(SZ, mC);

	// Limpieza de recursos
	pthread_attr_destroy(&atrMM);
	pthread_mutex_destroy(&MM_mutex);
	pthread_exit(NULL);  // Finaliza el hilo principal
}