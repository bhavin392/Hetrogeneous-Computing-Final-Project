#include "hw_defines.h"

void top(uint64_t v1_addr,
		 uint64_t v2_addr,
		 uint64_t v3_addr) {

	//Define Device MMRs
	volatile uint8_t  * VECFlags  = (uint8_t *)VEC;
	volatile uint8_t  * DMAFlags   = (uint8_t  *)(DMA);
	volatile uint64_t * DMARdAddr  = (uint64_t *)(DMA+1);
	volatile uint64_t * DMAWrAddr  = (uint64_t *)(DMA+9);
	volatile uint32_t * DMACopyLen = (uint32_t *)(DMA+17);

	//Transfer Input Matrices
	//Transfer M1
	*DMARdAddr  = v1_addr;
	*DMAWrAddr  = V1ADDR;
	*DMACopyLen = vec_size;
	*DMAFlags   = DEV_INIT;
	//Poll DMA for finish
	while ((*DMAFlags & DEV_INTR) != DEV_INTR);
	//Transfer M2
	*DMARdAddr  = v2_addr;
	*DMAWrAddr  = V2ADDR;
	*DMACopyLen = vec_size;
	*DMAFlags   = DEV_INIT;
	//Poll DMA for finish
	while ((*DMAFlags & DEV_INTR) != DEV_INTR);

	//Start the accelerated function
	*VECFlags = DEV_INIT;
	//Poll function for finish
	while ((*VECFlags & DEV_INTR) != DEV_INTR);

	//Transfer M3
	*DMARdAddr  = V3ADDR;
	*DMAWrAddr  = v3_addr;
	*DMACopyLen = vec_size;
	*DMAFlags   = DEV_INIT;
	//Poll DMA for finish
	while ((*DMAFlags & DEV_INTR) != DEV_INTR);
	return;
}
