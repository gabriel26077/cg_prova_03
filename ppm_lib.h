#ifndef PPM_LIB_H
#define PPM_LIB_H

#include "shared.h"

void export_to_ppm( 
	const RGB_t* matrix,
	int width,
	int height,
	const char *filename
);

#endif