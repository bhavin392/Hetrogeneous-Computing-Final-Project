#include <inttypes.h>
#include "hw_defines.h"

void kernel(){
   uint8_t *inputbase = (uint8_t);
   uint8_t *filterbase = (uint8_t) INPUTMAX;

   double *v1=(double *)inputbase;
   double *v2=(double *)filterbase;
   printf("inside kernel \n");

   #pragma clang loop unroll(full)
   for(int i=0;i<32;i++){
       printf("%ld",v1[i]);
   }

   printf("\n");
    #pragma clang loop unroll(full)
   for(int i=0;i<27;i++){
       printf("%ld",v2[i]);
   }
}