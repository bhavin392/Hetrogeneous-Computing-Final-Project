#include <stdio.h>
#include "defines.h"

void DW(int isize, int fsize, int ichannel, int ochannel,
unsigned char *input, unsigned char *filter, unsigned char *output, int stride){

    int sum=0;
    int i,j=0;
    int op=0;
    if(stride == 1){
        i=0;
        j=0;
    }else if(stride ==2){
        i=1;
        j=1;
    }else{
        printf("stride value wrong");
        return;
    }

    for(int ch=0; ch<ochannel; ch++){
        for(; i<(isize - 2); i=i+stride){
            for(;j < (isize -2); j=j+stride){
                for(int k=0; k< fsize; k++){
                    for(int l=0; l<fsize;l++){
                        
                        sum+= input[(ch * isize * isize) + ((k * isize) + l) + j + (i* isize)] * filter[(k * fsize)+l];
                        
                    }
                }

                if(sum>255){
                    sum = 255;
                }else if(sum<0){
                    sum =0;
                }
                output[op]=sum;
                sum=0;
                op++;
            }
            if(stride == 1){
                j=0;
            }else if(stride ==2){
                j=1;
            }
        }
        if(stride == 1){
            i=0;
        }else if(stride ==2){
            i=1;
        }
    }


}