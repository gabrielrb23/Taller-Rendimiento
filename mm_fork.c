/**************************************************************
*	Pontificia Universidad Javeriana
*	Autor: Gabriel Riaño
*	Materia: Sistemas Operativos
*	Descripción: Implementación de funciones auxiliares para
*			la multiplicación de matrices utilizando múltiples
*			procesos mediante fork(). Contiene funciones para
*			inicializar, imprimir y multiplicar matrices,
*			además de medir el tiempo de ejecución.
**************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include "mm_fork.h"

// Variables estáticas para registrar el tiempo de inicio y fin
static struct timeval inicio, fin;

// Función para registrar el momento de inicio del cálculo
void InicioMuestra() {
	gettimeofday(&inicio, NULL);
}

// Función para registrar el momento de finalización y mostrar tiempo transcurrido
void FinMuestra() {
	gettimeofday(&fin, NULL);
	fin.tv_usec -= inicio.tv_usec;
	fin.tv_sec  -= inicio.tv_sec;
	double tiempo = (double) (fin.tv_sec * 1000000 + fin.tv_usec);  // Conversión a microsegundos
	printf("%.0f\n", tiempo);
}

// Multiplica un subconjunto de filas de matA por matB y guarda el resultado en matC
void multiMatrix(double *mA, double *mB, double *mC, int D, int filaI, int filaF) {
	for (int i = filaI; i < filaF; i++) {
		for (int j = 0; j < D; j++) {
			double suma = 0.0;
			for (int k = 0; k < D; k++) {
				suma += mA[i * D + k] * mB[k * D + j];
			}
			mC[i * D + j] = suma;
		}
	}
}

// Imprime una matriz en pantalla si su dimensión es menor que 9
void impMatrix(double *matrix, int D) {
	if (D < 9) {
		printf("\nMatriz:\n");
		for (int i = 0; i < D * D; i++) {
			if (i % D == 0) printf("\n");
			printf(" %.2f ", matrix[i]);
		}
		printf("\n");
	}
}

// Inicializa dos matrices con valores aleatorios entre 0 y 9
void iniMatrix(double *mA, double *mB, int D) {
	for (int i = 0; i < D * D; i++) {
		mA[i] = rand() % 10;
		mB[i] = rand() % 10;
	}
}
