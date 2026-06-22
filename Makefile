all:
	gcc elementos_de_cg.c main.c ppm_lib.c -lm -o app
	./app
