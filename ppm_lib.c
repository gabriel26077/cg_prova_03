#include "ppm_lib.h"


#include <stdio.h>
#include <stdlib.h>
/*
float mapping(float x, float min_x, float  max_x, float min_y, float max_y) {
	if(max_x - min_x == 0) return 0.0;

	return (((max_y - min_y) / (max_x - min_x)) * (x - min_x)) + min_y;
}
*/




void export_to_ppm(const RGB_t* matrix, int width, int height, const char *filename){
	FILE* f = fopen(filename, "w");

	fprintf(f, "P3\n");
	fprintf(f, "%d %d\n", width, height);
	fprintf(f, "255\n");


	char* string_buffer = malloc(30*1024*1024); // 30 megabytes de buffer (+ que o suficiente)
    char* current_cursor = string_buffer;


	for(int i=0; i<width*height; i++) {
		int r = (int) (matrix[i].r * 255);
		int g = (int) (matrix[i].g * 255);
		int b = (int) (matrix[i].b * 255);

		int avanco_cursor = sprintf(current_cursor, "%d %d %d ", r, g, b);
		current_cursor += avanco_cursor;

	}

	fprintf(f, "%s\n", string_buffer);
	
}