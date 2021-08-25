#include "stdafx.h"

bool TestConcurrentDebit() {
	void* commut = Start();

	/*Initial balance */
	// 100 + 50 + 10 - 150 - 10
	Transition<uint32_t, keyType, deltaType> Alice_balance(std::numeric_limits<uint32_t>::max(), "blockchain://eth1.0/Alice/Balance", 100); // initial balance
	Transition<uint32_t, keyType, deltaType> Alice_minus_150(3, "blockchain://eth1.0/Alice/Balance", -150);
	Transition<uint32_t, keyType, deltaType> Alice_minus_10(4, "blockchain://eth1.0/Alice/Balance", -10);

	// 200 + 20 - 220
	Transition<uint32_t, keyType, deltaType> Bob_balance(std::numeric_limits<uint32_t>::max(), "blockchain://eth1.0/Bob/Balance", 200);
	Transition<uint32_t, keyType, deltaType> Bob_minus_20(5, "blockchain://eth1.0/Bob/Balance", -20);
	Transition<uint32_t, keyType, deltaType> Bob_minus_200(6, "blockchain://eth1.0/Bob/Balance", -220);


	std::vector<Transition<uint32_t, keyType, deltaType> > delta = { Alice_balance, Alice_minus_150, Alice_minus_10, Bob_balance, Bob_minus_20, Bob_minus_200 };
	std::vector<uint32_t> txs = Transition<uint32_t, keyType, deltaType>::Txs(delta);
	std::vector<char> keys = Transition<uint32_t, keyType, deltaType>::Keys(delta);
	std::vector<deltaType> values = Transition<uint32_t, keyType, deltaType>::Delta(delta);
	std::vector<uint32_t> keyLenghs = Transition<uint32_t, keyType, deltaType>::KeyLenghs(delta);

	Insert(commut, (char*)txs.data(), (char*)keys.data(), (char*)keyLenghs.data(), (char*)values.data(), delta.size());
	
	std::vector<uint32_t> txWhiteList{ 3, 4, 5, 6, std::numeric_limits<uint32_t>::max() };
	std::vector<uint32_t> outTx(txWhiteList.size());
	uint32_t outCount = 0;

    char msg[1024];
	Detect(commut, (char*)txWhiteList.data(), txWhiteList.size(), (char*)outTx.data(), (char*)&outCount, nullptr);

	return outCount == 4 &&
		outTx[0] == outTx[1] == std::numeric_limits<uint32_t>::max() &&
		outTx[3] == 5 &&
		outTx[5] == 5;
}