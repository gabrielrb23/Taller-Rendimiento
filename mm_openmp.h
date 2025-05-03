/**************************************************************
*	Pontificia Universidad Javeriana
*	Autor: Gabriel Riaño y Dary Palacios
*	Materia: Sistemas Operativos
*	Descripción: Cabecera para funciones de multiplicación
*			de matrices utilizando OpenMP. Contiene
*			prototipos de funciones para inicialización,
*			impresión, multiplicación paralela de matrices
*			y medición del tiempo de ejecución.
**************************************************************/

#ifndef MM_OPENMP_H
#define MM_OPENMP_H

#include <stddef.h>  // Para el tipo size_t

// Inicia la medición del tiempo
void InicioMuestra();

// Finaliza la medición del tiempo y muestra el resultado
void FinMuestra();

// Inicializa dos matrices con valores aleatorios
void iniMatrix(size_t *m1, size_t *m2, int D);

// Imprime una matriz si su dimensión es menor que 9
void impMatrix(size_t *matrix, int D);

// Multiplica dos matrices de forma paralela usando OpenMP
void multiMatrix(size_t *mA, size_t *mB, size_t *mC, int D);

#endif