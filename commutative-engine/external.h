#pragma once

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif
	void* Start();
	void Clear(void* enginePtr); // For the next use
	void Stop(void* enginePtr); // Delete the rewritable 

	void Insert(void* enginePtr, char* txs, char* path, char* pathLen, char* delta, uint32_t count);
	void Detect(void* enginePtr, char* txs, char count, char* outTxs, char* outCount, char* msg);

	void GetVersion(char* version); // Get version 
	void GetProduct(char* product); // Get product name

#ifdef __cplusplus
}
#endif
