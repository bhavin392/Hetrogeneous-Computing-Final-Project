//Standard Libraries
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdint.h>
#include "../defines.h"

#define DEV_INIT	0x01
#define DEV_INTR	0x04

//Specify row/column sizes
#define vec_len 	(R)*(C)*IC
#define vec_size    vec_len*sizeof(TYPE)
#define kern_len    1*KC
#define kern_size   kern_len*sizeof(TYPE)

// Device MMR addresses
#define TOP			0x2f000000
#define VEC		    0x2f000019
#define DMA			0x2ff00000

// Specify the scratchpad addresses for variables
#define SPM			0x2f100000
#define V1ADDR		SPM + (vec_size * 0)
#define V2ADDR		SPM + (vec_size * 1)
#define V3ADDR		SPM + (kern_size * 2)
