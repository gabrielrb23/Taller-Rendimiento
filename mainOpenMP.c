/**************************************************************
*	Pontificia Universidad Javeriana
*	Autor: Gabriel Riaño y Dary Palacios
*	Materia: Sistemas Operativos
*	Descripción: Multiplicación de matrices cuadradas utilizando
*			paralelismo mediante la librería OpenMP.
*			El programa inicializa dos matrices, realiza
*			su multiplicación en paralelo y mide el tiempo
*			de ejecución.
**************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>
#include "mm_openmp.h"  // Cabecera con las funciones auxiliares

int main(int argc, char *argv[]) {
	// Validación de argumentos de entrada
	if (argc < 3) {
		printf("\n Uso: $./ejecutable SIZE Hilos \n\n");
		return -1;
	}

	// Conversión de argumentos: tamaño de la matriz y número de hilos
	int N = atoi(argv[1]);
	int TH = atoi(argv[2]);

	// Reserva de memoria dinámica para las matrices A, B y C
	size_t *matrixA = (size_t *)calloc(N * N, sizeof(size_t));
	size_t *matrixB = (size_t *)calloc(N * N, sizeof(size_t));
	size_t *matrixC = (size_t *)calloc(N * N, sizeof(size_t));

	// Inicializa la semilla para los valores aleatorios
	srand(time(NULL));

	// Define el número de hilos que usará OpenMP
	omp_set_num_threads(TH);

	// Inicializa matrices A y B con valores aleatorios
	iniMatrix(matrixA, matrixB, N);

	// Muestra las matrices A y B (si el tamaño es pequeño)
	impMatrix(matrixA, N);
	impMatrix(matrixB, N);

	// Inicia la medición del tiempo
	InicioMuestra();

	// Multiplicación paralela de matrices con OpenMP
	multiMatrix(matrixA, matrixB, matrixC, N);

	// Finaliza la medición del tiempo
	FinMuestra();

	// Imprime la matriz resultado
	impMatrix(matrixC, N);

	// Libera la memoria usada por las matrices
	free(matrixA);
	free(matrixB);
	free(matrixC);

	return 0;
}