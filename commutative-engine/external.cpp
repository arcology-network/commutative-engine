#include "stdafx.h"

void* Start() {
	return new Commutative<uint32_t, std::string, deltaType>();
}

void Insert(void* enginePtr, char* txs, char* path, char* pathLen, char* values, uint32_t count) {
	auto engine = ((Commutative<uint32_t, std::string, deltaType>*)(enginePtr));

	std::vector<uint32_t> positions(count + 1, 0);
	for (std::size_t i = 0; i < count; i++) {
		positions[i + 1] = positions[i] + ((uint32_t*)(pathLen))[i];
	}

	std::vector<Transition<uint32_t, std::string, deltaType>> transitions(count);
	std::vector<std::string> paths(count);
	for (std::size_t i = 0; i < count; i ++) {
		std::string key(path + positions[i], path + positions[i + 1]);	
		deltaType deltaV;
		memcpy(&deltaV, values + i * sizeof(deltaType), sizeof(deltaType));

		Transition<uint32_t, std::string, deltaType> transition(((uint32_t*)(txs))[i], key, deltaV);
		transitions[i] = Transition<uint32_t, std::string, deltaType> (((uint32_t*)(txs))[i], key, deltaV);		
	}
	engine->Insert(transitions);
}

void Detect(void* enginePtr, char* txWhiteList, char count, char* outWhilteList, char* outCount, char* msg) {
	auto engine = ((Commutative<uint32_t, std::string, deltaType>*)(enginePtr));
	
	std::vector<uint32_t> validTxs((uint32_t*)txWhiteList, (uint32_t*)txWhiteList + (count) * sizeof(uint32_t));
	std::vector<uint32_t> filteredTxs;
	engine->Check(validTxs, filteredTxs);

	*outCount = filteredTxs.size();
	memcpy(outWhilteList, filteredTxs.data(), filteredTxs.size() * sizeof(uint32_t));
}

void Clear(void* enginePtr) {
	((Commutative<uint32_t, std::string, deltaType>*)(enginePtr))->Clear();
}

void Stop(void* enginePtr) {
	delete (Commutative<uint32_t, std::string, deltaType>*)(enginePtr);
}

void GetVersion(char* ver) {
	std::strcpy(ver, version);
}

void GetProduct(char* productInfo) {
	std::strcpy(productInfo, product);
}