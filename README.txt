Instrucciones de Ejecucion Visor Tarea 1:
----------------------------------------

0 - El programa debe ejecutarse en Sistema Operativo Windwows
1 - Descomprimir archivo Visor.rar
2 - Se recomienda copiar algun video de prueba en el directorio "T1\build"
3 - Posicionarse en la directorio "T1"
4 - Editar en el archivo "Makefile" las variables OPENCV_HEADERS y OPENCV_LIBS:
	OPENCV_HEADERS  := "(ruta de instalacion opencv)\opencv-2.4.9\include"
	OPENCV_LIBS     := "(ruta de instalacion opencv)\opencv-2.4.9\...\bin"

5 - Ejecutar comando "make". Con esto se compila el codigo fuente "Visor.cpp" que se encuentra
	en el directorio "T1\src", y se genera el ejecutable "Visor.exe" en el directorio "T1\build"
6 - Ejecutar archivo "Visor.exe" con los parametros necesarios. Ejemplos:
	
	Visor.exe 00010.mp4 AJUSTE_1.5_-30
	Visor.exe 00010.mp4 CONV_-1_0_1_-2_0_2_-1_0_1
	Visor.exe 00010.mp4 MEDIANA_9