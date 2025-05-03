# Taller-Rendimiento

## Archivos principales

| Archivo            | Descripción breve                                                                 |
|--------------------|------------------------------------------------------------------------------------|
| **mainFork.c**     | Programa principal que inicia la versión basada en procesos Fork.                 |
| **mm_fork.c**      | Función de multiplicación que usa procesos hijos (Fork).                          |
| **mainPosix.c**    | Programa principal para la versión con hilos POSIX.                               |
| **mm_posix.c**     | Implementación de la multiplicación usando `pthread` y un mutex.                  |
| **mainOpenMP.c**   | Programa principal de la variante OpenMP.                                         |
| **mm_openmp.c**    | Cálculo paralelo con directivas `#pragma omp`.                                    |
| **Makefile**       | Compila automáticamente las tres versiones.                                       |
| **lanzador.pl**    | Ejecuta todas las pruebas, promedia 30 repeticiones y guarda los resultados en    |

---

## Compilación
make

##Ejecucion
./lanzador.pl

##Borrar resultados y ejecutables
make clean
