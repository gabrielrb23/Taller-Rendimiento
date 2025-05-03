/**************************************************************
*	Pontificia Universidad Javeriana
*	Autor: Gabriel Riaño y Dary Palacios
*	Materia: Sistemas Operativos
*	Descripción: Cabecera que declara las funciones utilizadas
*			en la multiplicación de matrices con procesos
*			fork(). Incluye funciones para inicialización,
*			impresión, multiplicación y medición de tiempo.
**************************************************************/

#ifndef MM_FORK_H
#define MM_FORK_H

#include <sys/time.h>

// Inicia la medición de tiempo
void InicioMuestra();

// Finaliza la medición de tiempo y muestra el resultado
void FinMuestra();

// Multiplica un bloque de filas de la matriz A por la matriz B y guarda el resultado en la matriz C
void multiMatrix(double *mA, double *mB, double *mC, int D, int filaI, int filaF);

// Imprime la matriz si su dimensión es menor a 9
void impMatrix(double *matrix, int D);

// Inicializa las matrices A y B con valores aleatorios entre 0 y 9
void iniMatrix(double *mA, double *mB, int D);

#endif