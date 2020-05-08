#include "hw_defines.h"

void conv(){
    uint8_t * v1base = (uint8_t *)V1ADDR;
    uint8_t * v2base = (uint8_t *)V2ADDR;
    uint8_t * v3base = (uint8_t *)V3ADDR;
    TYPE    * v1     = (TYPE    *)v1base;
    TYPE    * v2     = (TYPE    *)v2base;
    TYPE    * v3     = (TYPE    *)v3base;

    int sum=0;
    

    if(convType == 0){
        int t=0;
        int isize=R*C;
        #pragma clang loop unroll(full)
        for(int f=1; f<KC; f++){
        #pragma clang loop unroll(full)
            for(int i=0; i<isize;i++){
                for(int k=0; k<IC;k++){
                    sum+=v1[i + (isize*k)] * v2[f];
                }

                if(sum < 0){
                    sum=0;
                }else if(sum > 255){
                    sum =255;
                }
                v3[t] = sum;
                sum=0;
                t++;
            }
        }
    } else if(convType == 1){
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
        int isize=R+padding;
        #pragma clang loop unroll(full)
        for(int ch=0; ch<IC; ch++){
            #pragma clang loop unroll(full)
            for(; i<(isize - 2); i=i+stride){
                #pragma clang loop unroll(full)
                for(;j < (isize -2); j=j+stride){
                    for(int k=0; k< fsize; k++){
                        for(int l=0; l<fsize;l++){
                        
                            sum+= v1[(ch * isize * isize) + ((k * isize) + l) + j + (i* isize)] * v2[(k * fsize)+l];
                        
                        }
                    }

                    if(sum>255){
                        sum = 255;
                    }else if(sum<0){
                        sum =0;
                    }
                    v3[op]=sum;
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
    
}
