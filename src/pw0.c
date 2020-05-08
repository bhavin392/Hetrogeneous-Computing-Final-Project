#include <stdio.h>

void PW0(int isize, int osize, int ichannel, int ochannel,
unsigned char * input, unsigned char * filter, unsigned char * output){


    int sum=0;
    int t=0;
    for(int f=0; f<ochannel; f++){
        for(int i=0; i<isize;i++){
            for(int k=0; k<ichannel;k++){
                sum+=input[i + (isize*k)] * filter[f];
            }

            if(sum < 0){
                sum=0;
            }else if(sum > 255){
                sum =255;
            }
            output[t] = sum;
            sum=0;
            t++;
        }
    }
}
