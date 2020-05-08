#include "../defines.h"

volatile int stage;

typedef struct {
    TYPE * a;
    TYPE * b;
    TYPE * c;
    int r_size;
    int c_size;
    int chan_size;
    int k_size;
    int k_chan;
} vec_struct;

void genData(vec_struct * ges) {
    int r,c,k;

    for( r=0; r < ges->r_size * ges->c_size * ges->chan_size; r++ ) {
        ges->a[r] = r;
        ges->c[r] = 0;
    }

    for (k = 0; k< ges->k_size* ges->k_size * ges->k_chan; k++){
        ges->b[k]=1;
    }
}
