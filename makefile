# Compilador y opciones comunes
CC = gcc
CFLAGS = -Wall -O2

# Archivos fuente
SRC_FORK = mainFork.c mm_fork.c
SRC_OPENMP = mainOpenMP.c mm_openmp.c
SRC_POSIX = mainPosix.c mm_posix.c

# Ejecutables
EXEC_FORK = mmClasicaFork
EXEC_OPENMP = mmClasicaOpenMP
EXEC_POSIX = mmClasicaPosix

# Reglas para compilar y generar los ejecutables
all: $(EXEC_FORK) $(EXEC_OPENMP) $(EXEC_POSIX)

# Regla para compilar mmClasicaFork
$(EXEC_FORK): $(SRC_FORK)
	$(CC) $(CFLAGS) -o $@ $^

# Regla para compilar mmClasicaOpenMP
$(EXEC_OPENMP): $(SRC_OPENMP)
	$(CC) $(CFLAGS) -o $@ $^ -fopenmp

# Regla para compilar mmClasicaPosix
$(EXEC_POSIX): $(SRC_POSIX)
	$(CC) $(CFLAGS) -o $@ $^ -pthread

# Limpiar archivos generados
clean:
	rm -f $(EXEC_FORK) $(EXEC_OPENMP) $(EXEC_POSIX)
	rm -f mmClasicaFork-*-Hilos-*.csv
	rm -f mmClasicaOpenMP-*-Hilos-*.csv
	rm -f mmClasicaPosix-*-Hilos-*.csv

# Recompilación total
rebuild: clean all