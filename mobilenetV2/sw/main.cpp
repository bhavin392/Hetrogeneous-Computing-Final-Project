#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "bench.h"
#include "../../../common/m5ops.h"

vec_struct ges;

volatile uint8_t  * top   = (uint8_t  *)0x2f000000;
volatile uint32_t * val_a = (uint32_t *)0x2f000001;
volatile uint32_t * val_b = (uint32_t *)0x2f000009;
volatile uint32_t * val_c = (uint32_t *)0x2f000011;

int main(void) {
	m5_reset_stats();
  uint32_t base = 0x80c00000;
  int row= R+padding;
  int col=C+padding;
	TYPE *v1 = (TYPE *)base;
	TYPE *v2 = (TYPE *)(base+8*R*C*IC);
	TYPE *v3 = (TYPE *)(base+16*1*1*KC);
	TYPE *check = (TYPE *)(base+24*R*C*KC);
	int row_len = R;
  int col_len=C;
  int chan_len=IC;
  int k_size=1;
  int k_chan= KC;
  volatile int count = 0;
	stage = 0;

    ges.a = v1;
    ges.b = v2;
    ges.c = v3;
    ges.r_size = row_len;
    ges.c_size = col_len;
    ges.chan_size = chan_len;
    ges.k_size = k_size;
    ges.k_chan = k_chan;

    printf("Generating data\n");
    genData(&ges);
    printf("Data generated\n");

    *val_a = (uint32_t)(void *)v1;
    *val_b = (uint32_t)(void *)v2;
    *val_c = (uint32_t)(void *)v3;
    // printf("%d\n", *top);
    *top = 0x01;
    while (stage < 1) count++;

    printf("Job complete\n");
#ifdef CHECK
    printf("Checking result\n");
    printf("Running bench on CPU\n");

		bool fail = false;
		int i, j, k, k_col, i_col;
	  TYPE sum = 0;
	  TYPE mult = 0;
    int t=0;
    for(int l=0; l<KC;i++){
      for(i=0;i<R*C;i++) {
          for(j=0;j<IC;j++) {
              
              sum += v1[i+(R*C*j)]* v2[l];
              if(sum < 0){
                sum=0;
              }else if(sum > 255){
                sum =255;
              }
              check[t] = sum;
          }
      }
    }
		printf("Comparing CPU run to accelerated run\n");
    for(i=0; i<R*C*KC; i++) {
        if(v3[i] != check[i]) {
            printf("Expected:%f Actual:%f\n", check[i], v3[i]);
            fail = true;
            break;
        }
    }
    if(fail)
        printf("Check Failed\n");
    else
        printf("Check Passed\n");
#endif
	m5_dump_stats();
	m5_exit();
}
