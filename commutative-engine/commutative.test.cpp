#include "stdafx.h"

//typedef deltaType deltaType;

bool TestBalanceCalculation() {
	
	/*Initial balance */
	// 100 + 50 + 10 - 150 - 10
	Transition<uint32_t, keyType, deltaType> Alice(std::numeric_limits<uint32_t>::max(), "blockchain://eth1.0/Alice/Balance", 100); // initial balance
	Transition<uint32_t, keyType, deltaType> Alice_minus_150(3, "blockchain://eth1.0/Alice/Balance", -150);
	Transition<uint32_t, keyType, deltaType> Alice_minus_10(4, "blockchain://eth1.0/Alice/Balance", -10);

	// 200 + 20 - 220
	Transition<uint32_t, keyType, deltaType> Bob  (std::numeric_limits<uint32_t>::max(), "blockchain://eth1.0/Bob/Balance", 200);
	Transition<uint32_t, keyType, deltaType> Bob_plus_20(5, "blockchain://eth1.0/Bob/Balance", -20);
	Transition<uint32_t, keyType, deltaType> Bob_minus_200(6, "blockchain://eth1.0/Bob/Balance", -220);

	std::vector<Transition<uint32_t, keyType, deltaType>> transitions {
		Alice,
		Alice_minus_150,
		Alice_minus_10,
		Bob,
		Bob_plus_20,
		Bob_minus_200,
	};

	auto txs = Transition<uint32_t, keyType, deltaType>::Txs(transitions);
	auto keys = Transition<uint32_t, keyType, deltaType>::Keys(transitions);
	auto delta = Transition<uint32_t, keyType, deltaType>::Delta(transitions);

	Insert(commut, txs.data, delta.data);

	Commutative<uint32_t, keyType, deltaType> commutative;
	commutative.Insert(transitions);
	
	std::vector<uint32_t> whiteList{3, 4, 5, 6, std::numeric_limits<uint32_t>::max() };
	std::vector<uint32_t> outTx;
	commutative.Check(whiteList, outTx);

	return true;
}
