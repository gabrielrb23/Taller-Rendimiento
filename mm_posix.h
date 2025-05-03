/**************************************************************
*	Pontificia Universidad Javeriana
*	Autor: Gabriel Riaño
*	Materia: Sistemas Operativos
*	Fichero: mm_posix.h
*	Descripción: Cabecera del módulo para la multiplicación
*			de matrices usando hilos POSIX (Pthreads).
*			Define estructuras, variables globales y
*			prototipos de funciones utilizadas en el
*			programa principal.
**************************************************************/

#ifndef MM_POSIX_H
#define MM_POSIX_H

#include <pthread.h>

// Tamaño total de memoria compartida para matrices A, B y C
#define DATA_SIZE (1024*1024*64*3)

// Variables globales para acceso compartido entre hilos
extern pthread_mutex_t MM_mutex;   // Mutex para sincronización
extern double *mA, *mB, *mC;	   // Punteros a matrices
extern double MEM_CHUNK[];		 // Bloque único de memoria compartida

// Estructura que contiene los parámetros que se pasan a cada hilo
struct parametros {
	int nH;   // Número total de hilos
	int idH;  // Identificador del hilo
	int N;	// Tamaño de la matriz
};

// Inicia medición del tiempo
void InicioMuestra();

// Finaliza medición del tiempo y muestra el resultado
void FinMuestra();

// Inicializa matrices A y B con valores aleatorios
void iniMatrix(int SZ);

// Imprime una matriz si su tamaño es menor a 12
void impMatrix(int sz, double *matriz);

// Función que ejecutará cada hilo para calcular su bloque de filas
void *multiMatrix(void *variables);

#endif