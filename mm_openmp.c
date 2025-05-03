/**************************************************************
*	Pontificia Universidad Javeriana
*	Autor: Gabriel Riaño y Dary Palacios
*	Materia: Sistemas Operativos
*	Descripción: Implementación de funciones para la
*			multiplicación clásica de matrices con OpenMP.
*			Incluye inicialización de matrices, impresión
*			condicional, multiplicación paralela y
*			medición de tiempo de ejecución.
**************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <omp.h>		   // Librería para paralelismo con OpenMP
#include "mm_openmp.h"	 // Cabecera del módulo

// Variables estáticas para almacenar los tiempos de inicio y fin
static struct timeval inicio, fin;

// Función que marca el inicio del cronómetro
void InicioMuestra() {
	gettimeofday(&inicio, NULL);
}

// Función que marca el final del cronómetro y muestra el tiempo transcurrido
void FinMuestra() {
	gettimeofday(&fin, NULL);
	fin.tv_usec -= inicio.tv_usec;
	fin.tv_sec  -= inicio.tv_sec;
	double tiempo = (double)(fin.tv_sec * 1000000 + fin.tv_usec);  // Conversión a microsegundos
	printf("%.0f\n", tiempo);
}

// Inicializa las matrices m1 y m2 con valores determinísticos
void iniMatrix(size_t *m1, size_t *m2, int D) {
	for (int i = 0; i < D * D; i++) {
		m1[i] = i * 2;
		m2[i] = i + 2;
	}
}

// Imprime la matriz si su dimensión es menor que 9
void impMatrix(size_t *matrix, int D) {
	if (D < 9) {
		printf("\nMatriz:\n");
		for (int i = 0; i < D * D; i++) {
			if (i % D == 0) printf("\n");
			printf(" %zu ", matrix[i]);
		}
		printf("\n**-----------------------------**\n");
	}
}

// Multiplicación de matrices paralela con OpenMP
void multiMatrix(size_t *mA, size_t *mB, size_t *mC, int D) {
	size_t Suma, *pA, *pB;

	// Sección paralela usando OpenMP
	#pragma omp parallel
	{
		// Distribuye las iteraciones del primer bucle entre hilos
		#pragma omp for
		for (int i = 0; i < D; i++) {
			for (int j = 0; j < D; j++) {
				pA = mA + i * D;  // Apuntador al inicio de la fila i de mA
				pB = mB + j;	  // Apuntador a la columna j de mB
				Suma = 0;
				for (int k = 0; k < D; k++, pA++, pB += D) {
					Suma += *pA * *pB;  // Producto escalar de fila i por columna j
				}
				mC[i * D + j] = Suma;  // Asigna el resultado a la matriz C
			}
		}
	}
}