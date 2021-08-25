#pragma once
bool TestTransitionCodec();
bool TestBatchCodec();
bool TestEuResultCodec();
bool TestEuResultInt128Codec();
bool TestPicklistCodec();
bool TestEuResultToTransitions();
bool TestBalanceCalculation();
bool TestBalanceCheck();
bool TestBalanceCheck2();
bool TestBalanceCheckPerformance(int max);

bool TestRewritableDetectionConflict();

bool TestRewritableDetection();
bool TestRewritableDetectionPerformance(int max);