#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <time.h>
#include "defines.h"
#include "pw0.c"
#include "padding.c"
#include "dw.c"
#include "pw1.c"

void randominit(unsigned char * input, int size, int range){
    time_t t;
    srand((unsigned)time(&t));
    for(int i=0;i<size;i++){
        input[i]=rand() % range;
        printf("%d ",input[i]);
    }
    printf("\n");
    return;
}

void main(){

    unsigned char *input = (unsigned char*)malloc(PW0INPUTSIZE_1 * PW0INPUTSIZE_1 * PW0INPUTC_1*sizeof(unsigned char));
    unsigned char *pw0filter =(unsigned char*)malloc(PWFILTERSIZE * PWFILTERSIZE * PW0OUTPUTC_1*sizeof(unsigned char));
    unsigned char *dwfilter = (unsigned char*)malloc(DWFILTERSIZE * DWFILTERSIZE * sizeof(unsigned char));
    unsigned char *pw1filter =(unsigned char*)malloc(PWFILTERSIZE * PWFILTERSIZE * PW1OUTPUTC_1*sizeof(unsigned char));
    unsigned char *output =(unsigned char*)malloc(PW0OUTPUTSIZE_1*PW0OUTPUTSIZE_1*PW0OUTPUTC_1*sizeof(unsigned char));
    unsigned char *output_padded =(unsigned char*)malloc((PW0OUTPUTSIZE_1 + padding)*(PW0OUTPUTSIZE_1 + padding)*PW0OUTPUTC_1*sizeof(unsigned char));
    unsigned char *dwoutput = (unsigned char *)malloc(DWOUTPUTSIZE_1*DWOUTPUTSIZE_1*DWOUTPUTC_1*sizeof(unsigned char));
    unsigned char *block1_output =(unsigned char*)malloc(PW1OUTPUTSIZE_1*PW1OUTPUTSIZE_1*PW1OUTPUTC_1*sizeof(unsigned char));
    printf("input matrix \n");
    randominit(input,PW0INPUTSIZE_1 * PW0INPUTSIZE_1 * PW0INPUTC_1,255);

    printf("filter matrix \n");
    randominit(dwfilter,3 * 3,10);
    randominit(pw0filter,1 * 1 * PW0OUTPUTC_1,10);
    randominit(pw1filter,1 * 1 * PW1OUTPUTC_1,10);

    //perform pointwise convolution and save output in output
    PW0(PW0INPUTSIZE_1*PW0INPUTSIZE_1,PW0OUTPUTSIZE_1*PW0OUTPUTSIZE_1,
    PW0INPUTC_1,PW0OUTPUTC_1,input,pw0filter,output);
    free(input);

    //pad the output
    padImg(output,output_padded,PW0OUTPUTSIZE_1 + padding,DWINPUTC_1);
    free(output);

    //output of depthwise is stored in output again
    DW(DWINPUTSIZE_1+padding,DWFILTERSIZE,DWINPUTC_1,DWOUTPUTC_1,output_padded,dwfilter
    ,dwoutput,2);
    free(output_padded);

    //output of pointwise is stored in block1_output
    PW1(PW1INPUTSIZE_1*PW1INPUTSIZE_1,PW1OUTPUTSIZE_1*PW1OUTPUTSIZE_1,PW1INPUTC_1,
    PW0OUTPUTC_1,dwoutput,pw1filter,block1_output);
    free(dwoutput);
    
    free(pw0filter);
    free(pw1filter);
    
    //end of iteration 1

    // begin iteration 2
    unsigned char *block2_output =(unsigned char*)malloc(PW1OUTPUTSIZE_2*PW1OUTPUTSIZE_2*PW1OUTPUTC_2*sizeof(unsigned char));
    unsigned char *output =(unsigned char*)malloc(PW0OUTPUTSIZE_2*PW0OUTPUTSIZE_2*PW0OUTPUTC_2*sizeof(unsigned char));
    unsigned char *output_padded =(unsigned char*)malloc((PW0OUTPUTSIZE_2 + padding)*(PW0OUTPUTSIZE_2 + padding)*PW0OUTPUTC_2*sizeof(unsigned char));
    unsigned char *dwoutput = (unsigned char *)malloc(DWOUTPUTSIZE_2*DWOUTPUTSIZE_2*DWOUTPUTC_2*sizeof(unsigned char));
    randominit(pw0filter,1 * 1 * PW0OUTPUTC_2,10);
    randominit(pw1filter,1 * 1 * PW1OUTPUTC_2,10);

    //perform pointwise convolution and save output in output
    PW0(PW0INPUTSIZE_2*PW0INPUTSIZE_2,PW0OUTPUTSIZE_2*PW0OUTPUTSIZE_2,
    PW0INPUTC_2,PW0OUTPUTC_2,block1_output,pw0filter,output);

    //pad the output
    padImg(output,output_padded,PW0OUTPUTSIZE_2 + padding,DWINPUTC_2);

    //output of depthwise is stored in output again
    DW(DWINPUTSIZE_2+padding,DWFILTERSIZE,DWINPUTC_2,DWOUTPUTC_2,output_padded,dwfilter
    ,dwoutput,1);

    //output of pointwise is stored in block2_output
    PW1(PW1INPUTSIZE_2*PW1INPUTSIZE_2,PW1OUTPUTSIZE_2*PW1OUTPUTSIZE_2,PW1INPUTC_2,
    PW0OUTPUTC_2,dwoutput,pw1filter,block2_output);
    free(output_padded);
    free(block1_output);
    free(output);
    free(dwoutput);

    //end of iteration 2

    // begin iteration 3
    unsigned char *block3_output =(unsigned char*)malloc(PW1OUTPUTSIZE_3*PW1OUTPUTSIZE_3*PW1OUTPUTC_3*sizeof(unsigned char));
    unsigned char *output =(unsigned char*)malloc(PW0OUTPUTSIZE_3*PW0OUTPUTSIZE_3*PW0OUTPUTC_3*sizeof(unsigned char));
    unsigned char *output_padded =(unsigned char*)malloc((PW0OUTPUTSIZE_3 + padding)*(PW0OUTPUTSIZE_3 + padding)*PW0OUTPUTC_3*sizeof(unsigned char));
    unsigned char *dwoutput = (unsigned char *)malloc(DWOUTPUTSIZE_3*DWOUTPUTSIZE_3*DWOUTPUTC_3*sizeof(unsigned char));

    randominit(pw0filter,1 * 1 * PW0OUTPUTC_3,10);
    randominit(pw1filter,1 * 1 * PW1OUTPUTC_3,10);

    //perform pointwise convolution and save output in output
    PW0(PW0INPUTSIZE_3*PW0INPUTSIZE_3,PW0OUTPUTSIZE_3*PW0OUTPUTSIZE_3,
    PW0INPUTC_3,PW0OUTPUTC_3,block2_output,pw0filter,output);

    //pad the output
    padImg(output,output_padded,PW0OUTPUTSIZE_3 + padding,DWINPUTC_3);

    //output of depthwise is stored in output again
    DW(DWINPUTSIZE_3+padding,DWFILTERSIZE,DWINPUTC_3,DWOUTPUTC_3,output_padded,dwfilter
    ,dwoutput,2);

    //output of pointwise is stored in block3_output
    PW1(PW1INPUTSIZE_3*PW1INPUTSIZE_3,PW1OUTPUTSIZE_3*PW1OUTPUTSIZE_3,PW1INPUTC_3,
    PW0OUTPUTC_3,dwoutput,pw1filter,block3_output);
    free(output_padded);
    free(block2_output);
    free(output);
    free(dwoutput);

    //end of iteration 3

    // begin iteration 4
    unsigned char *block4_output =(unsigned char*)malloc(PW1OUTPUTSIZE_4*PW1OUTPUTSIZE_4*PW1OUTPUTC_4*sizeof(unsigned char));
    unsigned char *output =(unsigned char*)malloc(PW0OUTPUTSIZE_4*PW0OUTPUTSIZE_4*PW0OUTPUTC_4*sizeof(unsigned char));
    unsigned char *output_padded =(unsigned char*)malloc((PW0OUTPUTSIZE_4 + padding)*(PW0OUTPUTSIZE_4 + padding)*PW0OUTPUTC_4*sizeof(unsigned char));
    unsigned char *dwoutput = (unsigned char *)malloc(DWOUTPUTSIZE_4*DWOUTPUTSIZE_4*DWOUTPUTC_4*sizeof(unsigned char));

    randominit(pw0filter,1 * 1 * PW0OUTPUTC_4,10);
    randominit(pw1filter,1 * 1 * PW1OUTPUTC_4,10);

    //perform pointwise convolution and save output in output
    PW0(PW0INPUTSIZE_4*PW0INPUTSIZE_4,PW0OUTPUTSIZE_4*PW0OUTPUTSIZE_4,
    PW0INPUTC_4,PW0OUTPUTC_4,block3_output,pw0filter,output);

    //pad the output
    padImg(output,output_padded,PW0OUTPUTSIZE_4 + padding,DWINPUTC_4);

    //output of depthwise is stored in output again
    DW(DWINPUTSIZE_4+padding,DWFILTERSIZE,DWINPUTC_4,DWOUTPUTC_4,output_padded,dwfilter
    ,dwoutput,1);

    //output of pointwise is stored in block4_output
    PW1(PW1INPUTSIZE_4*PW1INPUTSIZE_4,PW1OUTPUTSIZE_4*PW1OUTPUTSIZE_4,PW1INPUTC_4,
    PW0OUTPUTC_4,dwoutput,pw1filter,block4_output);
    free(output_padded);
    free(block3_output);
    free(output);
    free(dwoutput);

    //end of iteration 4

    // begin iteration 5
    unsigned char *block5_output =(unsigned char*)malloc(PW1OUTPUTSIZE_5*PW1OUTPUTSIZE_5*PW1OUTPUTC_5*sizeof(unsigned char));
    unsigned char *output =(unsigned char*)malloc(PW0OUTPUTSIZE_5*PW0OUTPUTSIZE_5*PW0OUTPUTC_5*sizeof(unsigned char));
    unsigned char *output_padded =(unsigned char*)malloc((PW0OUTPUTSIZE_5 + padding)*(PW0OUTPUTSIZE_5 + padding)*PW0OUTPUTC_5*sizeof(unsigned char));
    unsigned char *dwoutput = (unsigned char *)malloc(DWOUTPUTSIZE_5*DWOUTPUTSIZE_5*DWOUTPUTC_5*sizeof(unsigned char));

    randominit(pw0filter,1 * 1 * PW0OUTPUTC_5,10);
    randominit(pw1filter,1 * 1 * PW1OUTPUTC_5,10);

    //perform pointwise convolution and save output in output
    PW0(PW0INPUTSIZE_5*PW0INPUTSIZE_5,PW0OUTPUTSIZE_5*PW0OUTPUTSIZE_5,
    PW0INPUTC_5,PW0OUTPUTC_5,block4_output,pw0filter,output);

    //pad the output
    padImg(output,output_padded,PW0OUTPUTSIZE_5 + padding,DWINPUTC_5);

    //output of depthwise is stored in output again
    DW(DWINPUTSIZE_5+padding,DWFILTERSIZE,DWINPUTC_5,DWOUTPUTC_5,output_padded,dwfilter
    ,dwoutput,1);

    //output of pointwise is stored in block5_output
    PW1(PW1INPUTSIZE_5*PW1INPUTSIZE_5,PW1OUTPUTSIZE_5*PW1OUTPUTSIZE_5,PW1INPUTC_5,
    PW0OUTPUTC_5,dwoutput,pw1filter,block5_output);
    free(output_padded);
    free(block4_output);
    free(output);
    free(dwoutput);

    //end of iteration 5

    // begin iteration 6
    unsigned char *block6_output =(unsigned char*)malloc(PW1OUTPUTSIZE_6*PW1OUTPUTSIZE_6*PW1OUTPUTC_6*sizeof(unsigned char));
    unsigned char *output =(unsigned char*)malloc(PW0OUTPUTSIZE_6*PW0OUTPUTSIZE_6*PW0OUTPUTC_6*sizeof(unsigned char));
    unsigned char *output_padded =(unsigned char*)malloc((PW0OUTPUTSIZE_6 + padding)*(PW0OUTPUTSIZE_6 + padding)*PW0OUTPUTC_6*sizeof(unsigned char));
    unsigned char *dwoutput = (unsigned char *)malloc(DWOUTPUTSIZE_6*DWOUTPUTSIZE_6*DWOUTPUTC_6*sizeof(unsigned char));

    randominit(pw0filter,1 * 1 * PW0OUTPUTC_6,10);
    randominit(pw1filter,1 * 1 * PW1OUTPUTC_6,10);

    //perform pointwise convolution and save output in output
    PW0(PW0INPUTSIZE_6*PW0INPUTSIZE_6,PW0OUTPUTSIZE_6*PW0OUTPUTSIZE_6,
    PW0INPUTC_6,PW0OUTPUTC_6,block5_output,pw0filter,output);

    //pad the output
    padImg(output,output_padded,PW0OUTPUTSIZE_6 + padding,DWINPUTC_6);

    //output of depthwise is stored in output again
    DW(DWINPUTSIZE_6+padding,DWFILTERSIZE,DWINPUTC_6,DWOUTPUTC_6,output_padded,dwfilter
    ,dwoutput,2);

    //output of pointwise is stored in block6_output
    PW1(PW1INPUTSIZE_6*PW1INPUTSIZE_6,PW1OUTPUTSIZE_6*PW1OUTPUTSIZE_6,PW1INPUTC_6,
    PW0OUTPUTC_6,dwoutput,pw1filter,block6_output);
    free(output_padded);
    free(block5_output);
    free(output);
    free(dwoutput);

    //end of iteration 6

    // begin iteration 7
    unsigned char *block7_output =(unsigned char*)malloc(PW1OUTPUTSIZE_7*PW1OUTPUTSIZE_7*PW1OUTPUTC_7*sizeof(unsigned char));
    unsigned char *output =(unsigned char*)malloc(PW0OUTPUTSIZE_7*PW0OUTPUTSIZE_7*PW0OUTPUTC_7*sizeof(unsigned char));
    unsigned char *output_padded =(unsigned char*)malloc((PW0OUTPUTSIZE_7 + padding)*(PW0OUTPUTSIZE_7 + padding)*PW0OUTPUTC_7*sizeof(unsigned char));
    unsigned char *dwoutput = (unsigned char *)malloc(DWOUTPUTSIZE_7*DWOUTPUTSIZE_7*DWOUTPUTC_7*sizeof(unsigned char));

    randominit(pw0filter,1 * 1 * PW0OUTPUTC_7,10);
    randominit(pw1filter,1 * 1 * PW1OUTPUTC_7,10);

    //perform pointwise convolution and save output in output
    PW0(PW0INPUTSIZE_7*PW0INPUTSIZE_7,PW0OUTPUTSIZE_7*PW0OUTPUTSIZE_7,
    PW0INPUTC_7,PW0OUTPUTC_7,block6_output,pw0filter,output);

    //pad the output
    padImg(output,output_padded,PW0OUTPUTSIZE_7 + padding,DWINPUTC_7);

    //output of depthwise is stored in output again
    DW(DWINPUTSIZE_7+padding,DWFILTERSIZE,DWINPUTC_7,DWOUTPUTC_7,output_padded,dwfilter
    ,dwoutput,1);

    //output of pointwise is stored in block7_output
    PW1(PW1INPUTSIZE_7*PW1INPUTSIZE_7,PW1OUTPUTSIZE_7*PW1OUTPUTSIZE_7,PW1INPUTC_7,
    PW0OUTPUTC_7,dwoutput,pw1filter,block7_output);
    free(output_padded);
    free(block6_output);
    free(output);
    free(dwoutput);

    //end of iteration 7

    // begin iteration 8
    unsigned char *block8_output =(unsigned char*)malloc(PW1OUTPUTSIZE_8*PW1OUTPUTSIZE_8*PW1OUTPUTC_8*sizeof(unsigned char));
    unsigned char *output =(unsigned char*)malloc(PW0OUTPUTSIZE_8*PW0OUTPUTSIZE_8*PW0OUTPUTC_8*sizeof(unsigned char));
    unsigned char *output_padded =(unsigned char*)malloc((PW0OUTPUTSIZE_8 + padding)*(PW0OUTPUTSIZE_8 + padding)*PW0OUTPUTC_8*sizeof(unsigned char));
    unsigned char *dwoutput = (unsigned char *)malloc(DWOUTPUTSIZE_8*DWOUTPUTSIZE_8*DWOUTPUTC_8*sizeof(unsigned char));

    randominit(pw0filter,1 * 1 * PW0OUTPUTC_8,10);
    randominit(pw1filter,1 * 1 * PW1OUTPUTC_8,10);

    //perform pointwise convolution and save output in output
    PW0(PW0INPUTSIZE_8*PW0INPUTSIZE_8,PW0OUTPUTSIZE_8*PW0OUTPUTSIZE_8,
    PW0INPUTC_8,PW0OUTPUTC_8,block7_output,pw0filter,output);

    //pad the output
    padImg(output,output_padded,PW0OUTPUTSIZE_8 + padding,DWINPUTC_8);

    //output of depthwise is stored in output again
    DW(DWINPUTSIZE_8+padding,DWFILTERSIZE,DWINPUTC_8,DWOUTPUTC_8,output_padded,dwfilter
    ,dwoutput,1);

    //output of pointwise is stored in block8_output
    PW1(PW1INPUTSIZE_8*PW1INPUTSIZE_8,PW1OUTPUTSIZE_8*PW1OUTPUTSIZE_8,PW1INPUTC_8,
    PW0OUTPUTC_8,dwoutput,pw1filter,block8_output);
    free(output_padded);
    free(block7_output);
    free(output);
    free(dwoutput);

    //end of iteration 8

    // begin iteration 9
    unsigned char *block9_output =(unsigned char*)malloc(PW1OUTPUTSIZE_9*PW1OUTPUTSIZE_9*PW1OUTPUTC_9*sizeof(unsigned char));
    unsigned char *output =(unsigned char*)malloc(PW0OUTPUTSIZE_9*PW0OUTPUTSIZE_9*PW0OUTPUTC_9*sizeof(unsigned char));
    unsigned char *output_padded =(unsigned char*)malloc((PW0OUTPUTSIZE_9 + padding)*(PW0OUTPUTSIZE_9 + padding)*PW0OUTPUTC_9*sizeof(unsigned char));
    unsigned char *dwoutput = (unsigned char *)malloc(DWOUTPUTSIZE_9*DWOUTPUTSIZE_9*DWOUTPUTC_9*sizeof(unsigned char));

    randominit(pw0filter,1 * 1 * PW0OUTPUTC_9,10);
    randominit(pw1filter,1 * 1 * PW1OUTPUTC_9,10);

    //perform pointwise convolution and save output in output
    PW0(PW0INPUTSIZE_9*PW0INPUTSIZE_9,PW0OUTPUTSIZE_9*PW0OUTPUTSIZE_9,
    PW0INPUTC_9,PW0OUTPUTC_9,block8_output,pw0filter,output);

    //pad the output
    padImg(output,output_padded,PW0OUTPUTSIZE_9 + padding,DWINPUTC_9);

    //output of depthwise is stored in output again
    DW(DWINPUTSIZE_9+padding,DWFILTERSIZE,DWINPUTC_9,DWOUTPUTC_9,output_padded,dwfilter
    ,dwoutput,1);

    //output of pointwise is stored in block9_output
    PW1(PW1INPUTSIZE_9*PW1INPUTSIZE_9,PW1OUTPUTSIZE_9*PW1OUTPUTSIZE_9,PW1INPUTC_9,
    PW0OUTPUTC_9,dwoutput,pw1filter,block9_output);
    free(output_padded);
    free(block8_output);
    free(output);
    free(dwoutput);

    //end of iteration 9

    // begin iteration 10
    unsigned char *block10_output =(unsigned char*)malloc(PW1OUTPUTSIZE_10*PW1OUTPUTSIZE_10*PW1OUTPUTC_10*sizeof(unsigned char));
    unsigned char *output =(unsigned char*)malloc(PW0OUTPUTSIZE_10*PW0OUTPUTSIZE_10*PW0OUTPUTC_10*sizeof(unsigned char));
    unsigned char *output_padded =(unsigned char*)malloc((PW0OUTPUTSIZE_10+ padding)*(PW0OUTPUTSIZE_10 + padding)*PW0OUTPUTC_10*sizeof(unsigned char));
    unsigned char *dwoutput = (unsigned char *)malloc(DWOUTPUTSIZE_10*DWOUTPUTSIZE_10*DWOUTPUTC_10*sizeof(unsigned char));

    randominit(pw0filter,1 * 1 * PW0OUTPUTC_10,10);
    randominit(pw1filter,1 * 1 * PW1OUTPUTC_10,10);

    //perform pointwise convolution and save output in output
    PW0(PW0INPUTSIZE_10*PW0INPUTSIZE_10,PW0OUTPUTSIZE_10*PW0OUTPUTSIZE_10,
    PW0INPUTC_10,PW0OUTPUTC_10,block9_output,pw0filter,output);

    //pad the output
    padImg(output,output_padded,PW0OUTPUTSIZE_10 + padding,DWINPUTC_10);

    //output of depthwise is stored in output again
    DW(DWINPUTSIZE_10+padding,DWFILTERSIZE,DWINPUTC_10,DWOUTPUTC_10,output_padded,dwfilter
    ,dwoutput,1);

    //output of pointwise is stored in block10_output
    PW1(PW1INPUTSIZE_10*PW1INPUTSIZE_10,PW1OUTPUTSIZE_10*PW1OUTPUTSIZE_10,PW1INPUTC_10,
    PW0OUTPUTC_10,dwoutput,pw1filter,block10_output);
    free(output_padded);
    free(block9_output);
    free(output);
    free(dwoutput);

    //end of iteration 10

    // begin iteration 11
    unsigned char *block11_output =(unsigned char*)malloc(PW1OUTPUTSIZE_11*PW1OUTPUTSIZE_11*PW1OUTPUTC_11*sizeof(unsigned char));
    unsigned char *output =(unsigned char*)malloc(PW0OUTPUTSIZE_11*PW0OUTPUTSIZE_11*PW0OUTPUTC_11*sizeof(unsigned char));
    unsigned char *output_padded =(unsigned char*)malloc((PW0OUTPUTSIZE_11+ padding)*(PW0OUTPUTSIZE_11 + padding)*PW0OUTPUTC_11*sizeof(unsigned char));
    unsigned char *dwoutput = (unsigned char *)malloc(DWOUTPUTSIZE_11*DWOUTPUTSIZE_11*DWOUTPUTC_11*sizeof(unsigned char));

    randominit(pw0filter,1 * 1 * PW0OUTPUTC_11,10);
    randominit(pw1filter,1 * 1 * PW1OUTPUTC_11,10);

    //perform pointwise convolution and save output in output
    PW0(PW0INPUTSIZE_11*PW0INPUTSIZE_11,PW0OUTPUTSIZE_11*PW0OUTPUTSIZE_11,
    PW0INPUTC_11,PW0OUTPUTC_11,block10_output,pw0filter,output);

    //pad the output
    padImg(output,output_padded,PW0OUTPUTSIZE_11 + padding,DWINPUTC_11);

    //output of depthwise is stored in output again
    DW(DWINPUTSIZE_11+padding,DWFILTERSIZE,DWINPUTC_11,DWOUTPUTC_11,output_padded,dwfilter
    ,dwoutput,1);

    //output of pointwise is stored in block11_output
    PW1(PW1INPUTSIZE_11*PW1INPUTSIZE_11,PW1OUTPUTSIZE_11*PW1OUTPUTSIZE_11,PW1INPUTC_11,
    PW0OUTPUTC_11,dwoutput,pw1filter,block11_output);
    free(output_padded);
    free(block10_output);
    free(output);
    free(dwoutput);

    //end of iteration 11

    // begin iteration 12
    unsigned char *block12_output =(unsigned char*)malloc(PW1OUTPUTSIZE_12*PW1OUTPUTSIZE_12*PW1OUTPUTC_12*sizeof(unsigned char));
    unsigned char *output =(unsigned char*)malloc(PW0OUTPUTSIZE_12*PW0OUTPUTSIZE_12*PW0OUTPUTC_12*sizeof(unsigned char));
    unsigned char *output_padded =(unsigned char*)malloc((PW0OUTPUTSIZE_12+ padding)*(PW0OUTPUTSIZE_12 + padding)*PW0OUTPUTC_12*sizeof(unsigned char));
    unsigned char *dwoutput = (unsigned char *)malloc(DWOUTPUTSIZE_12*DWOUTPUTSIZE_12*DWOUTPUTC_12*sizeof(unsigned char));

    randominit(pw0filter,1 * 1 * PW0OUTPUTC_12,10);
    randominit(pw1filter,1 * 1 * PW1OUTPUTC_12,10);

    //perform pointwise convolution and save output in output
    PW0(PW0INPUTSIZE_12*PW0INPUTSIZE_12,PW0OUTPUTSIZE_12*PW0OUTPUTSIZE_12,
    PW0INPUTC_12,PW0OUTPUTC_12,block11_output,pw0filter,output);

    //pad the output
    padImg(output,output_padded,PW0OUTPUTSIZE_12 + padding,DWINPUTC_12);

    //output of depthwise is stored in output again
    DW(DWINPUTSIZE_12+padding,DWFILTERSIZE,DWINPUTC_12,DWOUTPUTC_12,output_padded,dwfilter
    ,dwoutput,1);

    //output of pointwise is stored in block12_output
    PW1(PW1INPUTSIZE_12*PW1INPUTSIZE_12,PW1OUTPUTSIZE_12*PW1OUTPUTSIZE_12,PW1INPUTC_12,
    PW0OUTPUTC_12,dwoutput,pw1filter,block12_output);
    free(output_padded);
    free(block11_output);
    free(output);
    free(dwoutput);

    //end of iteration 12

    // begin iteration 13
    unsigned char *block13_output =(unsigned char*)malloc(PW1OUTPUTSIZE_13*PW1OUTPUTSIZE_13*PW1OUTPUTC_13*sizeof(unsigned char));
    unsigned char *output =(unsigned char*)malloc(PW0OUTPUTSIZE_13*PW0OUTPUTSIZE_13*PW0OUTPUTC_13*sizeof(unsigned char));
    unsigned char *output_padded =(unsigned char*)malloc((PW0OUTPUTSIZE_13+ padding)*(PW0OUTPUTSIZE_13 + padding)*PW0OUTPUTC_13*sizeof(unsigned char));
    unsigned char *dwoutput = (unsigned char *)malloc(DWOUTPUTSIZE_13*DWOUTPUTSIZE_13*DWOUTPUTC_13*sizeof(unsigned char));

    randominit(pw0filter,1 * 1 * PW0OUTPUTC_13,10);
    randominit(pw1filter,1 * 1 * PW1OUTPUTC_13,10);

    //perform pointwise convolution and save output in output
    PW0(PW0INPUTSIZE_13*PW0INPUTSIZE_13,PW0OUTPUTSIZE_13*PW0OUTPUTSIZE_13,
    PW0INPUTC_13,PW0OUTPUTC_13,block12_output,pw0filter,output);

    //pad the output
    padImg(output,output_padded,PW0OUTPUTSIZE_13 + padding,DWINPUTC_13);

    //output of depthwise is stored in output again
    DW(DWINPUTSIZE_13+padding,DWFILTERSIZE,DWINPUTC_13,DWOUTPUTC_13,output_padded,dwfilter
    ,dwoutput,2);

    //output of pointwise is stored in block13_output
    PW1(PW1INPUTSIZE_13*PW1INPUTSIZE_13,PW1OUTPUTSIZE_13*PW1OUTPUTSIZE_13,PW1INPUTC_13,
    PW0OUTPUTC_13,dwoutput,pw1filter,block13_output);
    free(output_padded);
    free(block12_output);
    free(output);
    free(dwoutput);

    //end of iteration 13

    // begin iteration 14
    unsigned char *block14_output =(unsigned char*)malloc(PW1OUTPUTSIZE_14*PW1OUTPUTSIZE_14*PW1OUTPUTC_14*sizeof(unsigned char));
    unsigned char *output =(unsigned char*)malloc(PW0OUTPUTSIZE_14*PW0OUTPUTSIZE_14*PW0OUTPUTC_14*sizeof(unsigned char));
    unsigned char *output_padded =(unsigned char*)malloc((PW0OUTPUTSIZE_14+ padding)*(PW0OUTPUTSIZE_14 + padding)*PW0OUTPUTC_14*sizeof(unsigned char));
    unsigned char *dwoutput = (unsigned char *)malloc(DWOUTPUTSIZE_14*DWOUTPUTSIZE_14*DWOUTPUTC_14*sizeof(unsigned char));

    randominit(pw0filter,1 * 1 * PW0OUTPUTC_14,10);
    randominit(pw1filter,1 * 1 * PW1OUTPUTC_14,10);

    //perform pointwise convolution and save output in output
    PW0(PW0INPUTSIZE_14*PW0INPUTSIZE_14,PW0OUTPUTSIZE_14*PW0OUTPUTSIZE_14,
    PW0INPUTC_14,PW0OUTPUTC_14,block13_output,pw0filter,output);

    //pad the output
    padImg(output,output_padded,PW0OUTPUTSIZE_14 + padding,DWINPUTC_14);

    //output of depthwise is stored in output again
    DW(DWINPUTSIZE_14+padding,DWFILTERSIZE,DWINPUTC_14,DWOUTPUTC_14,output_padded,dwfilter
    ,dwoutput,1);

    //output of pointwise is stored in block14_output
    PW1(PW1INPUTSIZE_14*PW1INPUTSIZE_14,PW1OUTPUTSIZE_14*PW1OUTPUTSIZE_14,PW1INPUTC_14,
    PW0OUTPUTC_14,dwoutput,pw1filter,block14_output);
    free(output_padded);
    free(block13_output);
    free(output);
    free(dwoutput);

    //end of iteration 14

    // begin iteration 15
    unsigned char *block15_output =(unsigned char*)malloc(PW1OUTPUTSIZE_15*PW1OUTPUTSIZE_15*PW1OUTPUTC_15*sizeof(unsigned char));
    unsigned char *output =(unsigned char*)malloc(PW0OUTPUTSIZE_15*PW0OUTPUTSIZE_15*PW0OUTPUTC_15*sizeof(unsigned char));
    unsigned char *output_padded =(unsigned char*)malloc((PW0OUTPUTSIZE_15+ padding)*(PW0OUTPUTSIZE_15 + padding)*PW0OUTPUTC_15*sizeof(unsigned char));
    unsigned char *dwoutput = (unsigned char *)malloc(DWOUTPUTSIZE_15*DWOUTPUTSIZE_15*DWOUTPUTC_15*sizeof(unsigned char));

    randominit(pw0filter,1 * 1 * PW0OUTPUTC_15,10);
    randominit(pw1filter,1 * 1 * PW1OUTPUTC_15,10);

    //perform pointwise convolution and save output in output
    PW0(PW0INPUTSIZE_15*PW0INPUTSIZE_15,PW0OUTPUTSIZE_15*PW0OUTPUTSIZE_15,
    PW0INPUTC_15,PW0OUTPUTC_15,block14_output,pw0filter,output);

    //pad the output
    padImg(output,output_padded,PW0OUTPUTSIZE_15 + padding,DWINPUTC_15);

    //output of depthwise is stored in output again
    DW(DWINPUTSIZE_15+padding,DWFILTERSIZE,DWINPUTC_15,DWOUTPUTC_15,output_padded,dwfilter
    ,dwoutput,1);

    //output of pointwise is stored in block15_output
    PW1(PW1INPUTSIZE_15*PW1INPUTSIZE_15,PW1OUTPUTSIZE_15*PW1OUTPUTSIZE_15,PW1INPUTC_15,
    PW0OUTPUTC_15,dwoutput,pw1filter,block15_output);
    free(output_padded);
    free(block14_output);
    free(output);
    free(dwoutput);

    //end of iteration 15

    // begin iteration 16
    unsigned char *block16_output =(unsigned char*)malloc(PW1OUTPUTSIZE_16*PW1OUTPUTSIZE_16*PW1OUTPUTC_16*sizeof(unsigned char));
    unsigned char *output =(unsigned char*)malloc(PW0OUTPUTSIZE_16*PW0OUTPUTSIZE_16*PW0OUTPUTC_16*sizeof(unsigned char));
    unsigned char *output_padded =(unsigned char*)malloc((PW0OUTPUTSIZE_16+ padding)*(PW0OUTPUTSIZE_16 + padding)*PW0OUTPUTC_16*sizeof(unsigned char));
    unsigned char *dwoutput = (unsigned char *)malloc(DWOUTPUTSIZE_16*DWOUTPUTSIZE_16*DWOUTPUTC_16*sizeof(unsigned char));

    randominit(pw0filter,1 * 1 * PW0OUTPUTC_16,10);
    randominit(pw1filter,1 * 1 * PW1OUTPUTC_16,10);

    //perform pointwise convolution and save output in output
    PW0(PW0INPUTSIZE_16*PW0INPUTSIZE_16,PW0OUTPUTSIZE_16*PW0OUTPUTSIZE_16,
    PW0INPUTC_16,PW0OUTPUTC_16,block15_output,pw0filter,output);

    //pad the output
    padImg(output,output_padded,PW0OUTPUTSIZE_16 + padding,DWINPUTC_16);

    //output of depthwise is stored in output again
    DW(DWINPUTSIZE_16+padding,DWFILTERSIZE,DWINPUTC_16,DWOUTPUTC_16,output_padded,dwfilter
    ,dwoutput,1);

    //output of pointwise is stored in block16_output
    PW1(PW1INPUTSIZE_16*PW1INPUTSIZE_16,PW1OUTPUTSIZE_16*PW1OUTPUTSIZE_16,PW1INPUTC_16,
    PW0OUTPUTC_16,dwoutput,pw1filter,block16_output);
    free(output_padded);
    free(block15_output);
    free(output);
    free(dwoutput);

    //end of iteration 16
}