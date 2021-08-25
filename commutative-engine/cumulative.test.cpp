#include "stdafx.h"


//typedef deltaType deltaType;

bool TestBalanceCalculation() {
	/*
	"Alice -> "Bob    "10"),
	"Alice -> "Bob    "20"),
	"Alice -> "Carol  "30"),

	"Bob   -> "Alice  "20"),
	"Bob   -> "Alice  "30"),
	"Bob   -> "Carol  "40"),

	"Carol -> "Alice  "20"),
	"Carol -> "Alice  "30"),
	"Carol -> "Carol  "40")

	Alice = (100 - 10 - 20 - 30 + 20 + 30 + 20 + 30); // 140
	Bob   = (200 - 20 - 30 - 40 + 10 + 20); // 140
	Carol = (300 + 30 + 40 - 20 - 30 - 40 + 40); //320
	*/
	
	/*Initial balance */
	Transition<uint32_t, keyType, deltaType> Alice(111, "Alice_Balance", 100 );
	Transition<uint32_t, keyType, deltaType> Bob  (222, "Bob_Balance",   200 );
	Transition<uint32_t, keyType, deltaType> Carol(333, "Carol_Balance", 300 );

	/* "Alice -> "Bob  = "10" */
	Transition<uint32_t, keyType, deltaType> T00(0, "Alice_Balance",  -10 );
	Transition<uint32_t, keyType, deltaType> T01(1, "Bob_Balance",    +10 );

	/* Alice -> Bob  = 20 */
	Transition<uint32_t, keyType, deltaType> T02(2, "Alice_Balance",  -20 );
	Transition<uint32_t, keyType, deltaType> T03(3, "Bob_Balance",    +20 );

	/* Alice -> Carol  = 30 */
	Transition<uint32_t, keyType, deltaType> T04(4, "Alice_Balance",  -30 );
	Transition<uint32_t, keyType, deltaType> T05(5, "Carol_Balance",  +30 );

	/* Bob -> Alice  = 20 */
	Transition<uint32_t, keyType, deltaType> T06(6, "Bob_Balance",    -20 );
	Transition<uint32_t, keyType, deltaType> T07(7, "Alice_Balance",  +20 );

	/* Bob -> Alice  = 30 */
	Transition<uint32_t, keyType, deltaType> T08(8, "Bob_Balance",    -30 );
	Transition<uint32_t, keyType, deltaType> T09(9, "Alice_Balance",  +30 );

	/* Bob -> Carol  = 40 */
	Transition<uint32_t, keyType, deltaType> T10(10, "Bob_Balance",   -40 );
	Transition<uint32_t, keyType, deltaType> T11(11, "Carol_Balance", +40 );

	/* Carol -> Alice  = 20 */
	Transition<uint32_t, keyType, deltaType> T12(12, "Carol_Balance", -20 );
	Transition<uint32_t, keyType, deltaType> T13(13, "Alice_Balance", +20 );

	/* Carol -> Alice  = 30 */
	Transition<uint32_t, keyType, deltaType> T14(14, "Carol_Balance", -30 );
	Transition<uint32_t, keyType, deltaType> T15(15, "Alice_Balance", +30 );

	/* Carol -> Carol  = 40 */
	Transition<uint32_t, keyType, deltaType> T16(16, "Carol_Balance", -40 );
	Transition<uint32_t, keyType, deltaType> T17(17, "Carol_Balance", +40 );

	std::vector<Transition<uint32_t, keyType, deltaType>> Transitions {
		Alice, T00, T01, T02, T03, T04, T05,
		Bob, T06, T07, T08, T09, T10, T11,
		Carol, T12, T13, T14, T15, T16, T17
	};

	auto allTrans = std::vector<Transition<uint32_t, keyType, deltaType>>({ T00, T01, T02, T03, T04, T05,T06, T07, T08, T09, T10, T11, T12, T13, T14, T15, T16, T17 });


	Commutative<uint32_t, keyType, deltaType> commutative;
	commutative.Insert(allTrans);
	
	std::vector<uint32_t> whiteList;
	for (std::size_t i = 0; i < allTrans.size(); i++) {
		whiteList.push_back(i);
	}

	std::vector<uint32_t> outTx;
	commutative.Check(whiteList, outTx);

	return true;
}

//
//bool TestBalanceCheck() {
//	/* "Alice -> "Bob  = "10" */
//	Transition<uint32_t, keyType, deltaType> T00(
//		0, { 
//			codec::Decode<uint64_t>("Alice_Balance"), codec::Decode<uint64_t>("Alice_Balance"), codec::Decode<uint64_t>("Bob_Balance",
//			100, -10, +10 }), {
//			types::UINT128, types::UINT128, types::UINT128 }, {
//			types::CUMULATIVE_READ, types::CUMULATIVE_WRITE, types::CUMULATIVE_WRITE });
//
//	/* "Alice -> "Bob  = "20" */
//	Transition<uint32_t, keyType, deltaType> T01(
//		1, {
//			codec::Decode<uint64_t>("Alice_Balance"), codec::Decode<uint64_t>("Alice_Balance"), codec::Decode<uint64_t>("Bob_Balance",
//			100, -20, +20 }), {
//			types::UINT128, types::UINT128, types::UINT128 }, {
//			types::CUMULATIVE_READ, types::CUMULATIVE_WRITE, types::CUMULATIVE_WRITE });
//
//	/* Alice -> Carol  = 30 */
//	Transition<uint32_t, keyType, deltaType> T02(
//		2, {
//			codec::Decode<uint64_t>("Alice_Balance"), codec::Decode<uint64_t>("Alice_Balance"), codec::Decode<uint64_t>("Carol_Balance",
//			100, -30, +30 }), {
//			types::UINT128, types::UINT128, types::UINT128 }, {
//			types::CUMULATIVE_READ, types::CUMULATIVE_WRITE, types::CUMULATIVE_WRITE });
//
//	
//	/* Bob -> Alice  = 20 */
//	Transition<uint32_t, keyType, deltaType> T03(
//		3, {
//			codec::Decode<uint64_t>("Bob_Balance"), codec::Decode<uint64_t>("Bob_Balance"), codec::Decode<uint64_t>("Alice_Balance",
//			200, -20, +20 }), {
//			types::UINT128, types::UINT128, types::UINT128 }, {
//			types::CUMULATIVE_READ, types::CUMULATIVE_WRITE, types::CUMULATIVE_WRITE });
//
//	
//	/* Bob -> Alice  = 30 */
//	Transition<uint32_t, keyType, deltaType> T04(
//		4, {
//			codec::Decode<uint64_t>("Bob_Balance"), codec::Decode<uint64_t>("Bob_Balance"), codec::Decode<uint64_t>("Alice_Balance",
//			200, -30, +30 }), {
//			types::UINT128, types::UINT128, types::UINT128 }, {
//			types::CUMULATIVE_READ, types::CUMULATIVE_WRITE, types::CUMULATIVE_WRITE });
//
//
//	/* Bob -> Carol  = 40 */
//	Transition<uint32_t, keyType, deltaType> T05(
//		5, {
//			codec::Decode<uint64_t>("Bob_Balance"), codec::Decode<uint64_t>("Bob_Balance"), codec::Decode<uint64_t>("Carol_Balance",
//			200, -40, +40 }), {
//			types::UINT128, types::UINT128, types::UINT128 }, {
//			types::CUMULATIVE_READ, types::CUMULATIVE_WRITE, types::CUMULATIVE_WRITE });
//
//	/* Carol -> Alice  = 20 */
//	Transition<uint32_t, keyType, deltaType> T06(
//		6, {
//			codec::Decode<uint64_t>("Carol_Balance"), codec::Decode<uint64_t>("Carol_Balance"), codec::Decode<uint64_t>("Alice_Balance",
//			300, -20, +20 }), {
//			types::UINT128, types::UINT128, types::UINT128 }, {
//			types::CUMULATIVE_READ, types::CUMULATIVE_WRITE, types::CUMULATIVE_WRITE });
//
//	
//	/* Carol -> Alice  = 30 */
//	Transition<uint32_t, keyType, deltaType> T07(
//		7, {
//			codec::Decode<uint64_t>("Carol_Balance"), codec::Decode<uint64_t>("Carol_Balance"), codec::Decode<uint64_t>("Alice_Balance",
//			300, -30, +30 }), {
//			types::UINT128, types::UINT128, types::UINT128 }, {
//			types::CUMULATIVE_READ, types::CUMULATIVE_WRITE, types::CUMULATIVE_WRITE });
//	
//	/* Carol -> Carol  = 40 */
//	Transition<uint32_t, keyType, deltaType> T08(
//		8, {
//			codec::Decode<uint64_t>("Carol_Balance"), codec::Decode<uint64_t>("Carol_Balance"), codec::Decode<uint64_t>("Carol_Balance",
//			300, -40, +40 }), {
//			types::UINT128, types::UINT128, types::UINT128 }, {
//			types::CUMULATIVE_READ, types::CUMULATIVE_WRITE, types::CUMULATIVE_WRITE });
//
//	std::array<char, 1024> buffer;
//
//	Arbitrator<uint32_t, keyType, deltaType> arbitrator;
//
//	T00.Encode(buffer.data());
//	arbitrator.Insert(buffer.data());
//
//	T01.Encode(buffer.data());
//	arbitrator.Insert(buffer.data());
//
//	T02.Encode(buffer.data());
//	arbitrator.Insert(buffer.data());
//
//	T03.Encode(buffer.data());
//	arbitrator.Insert(buffer.data());
//
//	T04.Encode(buffer.data());
//	arbitrator.Insert(buffer.data());
//
//	T05.Encode(buffer.data());
//	arbitrator.Insert(buffer.data());
//
//	T06.Encode(buffer.data());
//	arbitrator.Insert(buffer.data());
//
//	T07.Encode(buffer.data());
//	arbitrator.Insert(buffer.data());
//
//	T08.Encode(buffer.data());
//	arbitrator.Insert(buffer.data());
//	
//	Picker<uint64_t> tempPicker;
//	tempPicker.hashes = { { 0 },{ 1 },{ 2 },{ 3 },{ 4 },{ 5 },{ 6 },{ 7 },{ 8 } };
//
//	tempPicker.Encode(buffer.data());
//
//	Picker<uint64_t> picker;
//	picker.Decode(buffer.data());
//
//	if (tempPicker.hashes != std::vector<std::vector<uint64_t>>(picker.hashes.begin(), picker.hashes.begin() + picker.GetLength())) {
//		std::cout << "Picker mismatched !" << std::endl;
//		return false;
//	}
//		
//	std::vector<uint8_t> flags(picker.GetLength(), false);
//	arbitrator.Detect(buffer.data(), flags.data());
//
//	if (std::count(flags.begin(), flags.end(), true) != flags.size()) {
//		std::cout << "TestBalanceCheck() Error !" << std::endl;
//		return false;
//	}
//	
//	std::cout << "TestBalanceCheck(): --------------- Successful !" << std::endl;
//	return false;
//}
//
//bool TestBalanceCheck2() {
//	Transition<uint32_t, keyType, deltaType> T00(
//		0, {
//			codec::Decode<uint64_t>("Alice_Balance"), codec::Decode<uint64_t>("Alice_Balance"), codec::Decode<uint64_t>("Bob_Balance",
//			100, -70, +10 }), {
//			types::UINT128, types::UINT128, types::UINT128 }, {
//				types::CUMULATIVE_READ, types::CUMULATIVE_WRITE, types::CUMULATIVE_WRITE });
//
//	/* "Alice -> "Bob  = "20" */
//	Transition<uint32_t, keyType, deltaType> T01(
//		1, {
//			codec::Decode<uint64_t>("Alice_Balance"), codec::Decode<uint64_t>("Alice_Balance"), codec::Decode<uint64_t>("Bob_Balance",
//			100, -20, +20 }), {
//			types::UINT128, types::UINT128, types::UINT128 }, {
//				types::CUMULATIVE_READ, types::CUMULATIVE_WRITE, types::CUMULATIVE_WRITE });
//
//	/* Alice -> Carol  = 30 */
//	Transition<uint32_t, keyType, deltaType> T02(
//		2, {
//			codec::Decode<uint64_t>("Alice_Balance"), codec::Decode<uint64_t>("Alice_Balance"), codec::Decode<uint64_t>("Carol_Balance",
//			100, -30, +30 }), {
//			types::UINT128, types::UINT128, types::UINT128 }, {
//				types::CUMULATIVE_READ, types::CUMULATIVE_WRITE, types::CUMULATIVE_WRITE });
//
//	/* Bob -> Alice  = 20 */
//	Transition<uint32_t, keyType, deltaType> T03(
//		3, {
//			codec::Decode<uint64_t>("Bob_Balance"), codec::Decode<uint64_t>("Bob_Balance"), codec::Decode<uint64_t>("Alice_Balance",
//			200, -20, +20 }), {
//			types::UINT128, types::UINT128, types::UINT128 }, {
//				types::CUMULATIVE_READ, types::CUMULATIVE_WRITE, types::CUMULATIVE_WRITE });
//
//
//	/* Bob -> Alice  = 30 */
//	Transition<uint32_t, keyType, deltaType> T04(
//		4, {
//			codec::Decode<uint64_t>("Bob_Balance"), codec::Decode<uint64_t>("Bob_Balance"), codec::Decode<uint64_t>("Alice_Balance",
//			200, -30, +30 }), {
//			types::UINT128, types::UINT128, types::UINT128 }, {
//				types::CUMULATIVE_READ, types::CUMULATIVE_WRITE, types::CUMULATIVE_WRITE });
//
//
//	/* Bob -> Carol  = 40 */
//	Transition<uint32_t, keyType, deltaType> T05(
//		5, {
//			codec::Decode<uint64_t>("Bob_Balance"), codec::Decode<uint64_t>("Bob_Balance"), codec::Decode<uint64_t>("Carol_Balance",
//			200, -40, +40 }), {
//			types::UINT128, types::UINT128, types::UINT128 }, {
//				types::CUMULATIVE_READ, types::CUMULATIVE_WRITE, types::CUMULATIVE_WRITE });
//
//	/* Carol -> Alice  = 20 */
//	Transition<uint32_t, keyType, deltaType> T06(
//		6, {
//			codec::Decode<uint64_t>("Carol_Balance"), codec::Decode<uint64_t>("Carol_Balance"), codec::Decode<uint64_t>("Alice_Balance",
//			300, -20, +20 }), {
//			types::UINT128, types::UINT128, types::UINT128 }, {
//				types::CUMULATIVE_READ, types::CUMULATIVE_WRITE, types::CUMULATIVE_WRITE });
//
//
//	/* Carol -> Alice  = 30 */
//	Transition<uint32_t, keyType, deltaType> T07(
//		7, {
//			codec::Decode<uint64_t>("Carol_Balance"), codec::Decode<uint64_t>("Carol_Balance"), codec::Decode<uint64_t>("Alice_Balance",
//			300, -30, +30 }), {
//			types::UINT128, types::UINT128, types::UINT128 }, {
//				types::CUMULATIVE_READ, types::CUMULATIVE_WRITE, types::CUMULATIVE_WRITE });
//
//	/* Carol -> Carol  = 40 */
//	Transition<uint32_t, keyType, deltaType> T08(
//		8, {
//			codec::Decode<uint64_t>("Carol_Balance"), codec::Decode<uint64_t>("Carol_Balance"), codec::Decode<uint64_t>("Carol_Balance",
//			300, -40, +40 }), {
//			types::UINT128, types::UINT128, types::UINT128 }, {
//				types::CUMULATIVE_READ, types::CUMULATIVE_WRITE, types::CUMULATIVE_WRITE });
//
//	void* arbitrators = Start();
//	char msgBuffer[256];
//
//	std::vector<Transition<uint32_t, keyType, deltaType>> ins = { T00, T01, T02, T03, T04, T05, T06, T07, T08 };
//
//	Picker<uint64_t> picker;
//	picker.hashes.resize(ins.size());
//	std::vector<uint64_t> hashes(ins.size(), 0);
//	for (std::size_t i = 0; i < ins.size(); i++) {
//		std::vector<char> buffer(256, 0);
//		ins[i].Encode(buffer.data());
//
//		picker.hashes[i] = { ins[i].hash };
//		Insert(arbitrators, buffer.data(), msgBuffer);
//	}
//
//	std::vector<uint8_t> flags(ins.size(), true);
//
//	std::vector<char> pickerBuffer(256, 0);
//	picker.Encode(pickerBuffer.data());
//	Detect(arbitrators, pickerBuffer.data(), (char*)flags.data(), msgBuffer);
//
//	if (flags[0] != false || std::count(flags.begin(), flags.end(), true) != flags.size() - 1) {
//		std::cout << "TestBalanceCheck2() Error !" << std::endl;
//		return false;
//	}
//
//	std::cout << "TestBalanceCheck2(): --------------- Successful !" << std::endl;
//	return true;
//}
//
//bool TestBalanceCheckPerformance(int max) { 
//	Picker<uint64_t> picker;
//	picker.hashes.resize(max);
//	std::vector<uint8_t> flags(max, true);
//
//	char msgBuffer[256];
//	void* arbitrators = Start();
//	for (std::size_t i = 0; i < max; i++) {
//		Transition<uint32_t, keyType, deltaType> in(
//			i, {
//				codec::Decode<uint64_t>("Alice_Balance"), codec::Decode<uint64_t>("Alice_Balance"), codec::Decode<uint64_t>("Bob_Balance",
//				100, -70, +10 }), {
//				types::UINT128, types::UINT128, types::UINT128 }, {
//					types::CUMULATIVE_READ, types::CUMULATIVE_WRITE, types::CUMULATIVE_WRITE });
//
//		picker.hashes[i] = { in.hash };
//
//		std::vector<char> buffer(4096, 0);
//		in.Encode(buffer.data());
//		Insert(arbitrators, buffer.data(), msgBuffer);
//	}
//	std::vector<char> pickerBuffer(max * 32, 0);
//
//	picker.Encode(pickerBuffer.data());
//	auto t0 = std::chrono::steady_clock::now();
//	Detect(arbitrators, pickerBuffer.data(), (char*)flags.data(), msgBuffer);
//	std::cout << "TestBalanceCheckPerformance::Detect(): " << max << " = " << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - t0).count() << " ms" << std::endl;
//	return true;
//}



