#include <stdio.h>

void padImg(unsigned char *input, unsigned char *output, int out_size, int o_channel){

int k=0,inp=0;
for(int ch=0; ch<o_channel; ch++){
    for(int i=0; i<out_size; i++){
        for(int j=0; j<out_size; j++){
            if(i == 0 || i == (out_size-1)){
                output[k]=0;
            }else if(j == 0 || j == (out_size)-1){
                output[k]=0;
            }else{
                output[k] = input[inp];
                inp++;
            }
            k++;
        }
    }
}
}