#!/usr/bin/perl

#**************************************************************
#     Pontificia Universidad Javeriana
#     Autor: Gabriel Riaño y Dary Palacios
#     Materia: Sistemas Operativos
#     Descripción: Script para ejecutar pruebas de multiplicación
#     de matrices con múltiples procesos y guardar resultados
#     compatibles con Excel (.csv)
#**************************************************************/

$Path = `pwd`;
chomp($Path);

@Nombre_Ejecutable = ("mmClasicaFork", "mmClasicaOpenMP", "mmClasicaPosix");
@Size_Matriz = ("15", "50", "100", "200");
@Num_Hilos   = (1, 2, 4, 8);
$Repeticiones = 30;

foreach $Nombre_Ejecutable (@Nombre_Ejecutable) {
	# Verifica si el ejecutable existe
	$executable_path = "$Path/$Nombre_Ejecutable";
	unless (-e $executable_path) {
		die "El ejecutable '$Nombre_Ejecutable' no se encuentra en la ruta '$Path'.\n";
	}
	foreach $size (@Size_Matriz) {
		foreach $hilo (@Num_Hilos) {
			$file = "$Path/$Nombre_Ejecutable-$size-Hilos-$hilo.csv";
			open($fh, '>>', $file) or die "No se puede abrir el archivo '$file': $!";
			print $fh "Tiempo\n";
			# Ejecuta las repeticiones
			for ($i = 0; $i < $Repeticiones; $i++) {
				$output = `$Path/$Nombre_Ejecutable $size $hilo`;
				chomp($output);  # Remueve salto de línea final
				$output =~ s/^\s+|\s+$//g;  # Elimina espacios al inicio o final
				print $fh "$output\n";
			}
			close($fh);
		}
	}
}
