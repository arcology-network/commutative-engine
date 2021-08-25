#pragma once
template <typename T0, typename T1, typename T2>
struct Transition {
	T0 tx; // transaction hash
	T1 key;
	T2 delta;
	bool isValid = false;

	Transition<T0, T1, T2>(){}
	Transition<T0, T1, T2>(T0 tx, T1 key, T2 delta) : tx(tx), key(key), delta(delta) {}

	template <typename T0, typename T1, typename T2>
	static std::vector<T0> Txs(std::vector<Transition<T0, T1, T2>>& transitions) {
		std::vector<T0> txs(transitions.size());
		for (std::size_t i = 0; i < transitions.size(); i ++) {
			txs[i] = transitions[i].tx;
		}
		return txs;
	}

	template <typename T0, typename T1, typename T2>
	static std::vector<char> Keys(std::vector<Transition<T0, T1, T2>>& transitions) {
		std::vector<char> keys;
		for (std::size_t i = 0; i < transitions.size(); i++) {
			keys.insert(keys.end(), transitions[i].key.begin(), transitions[i].key.end());
		}
		return keys;
	}

	template <typename T0, typename T1, typename T2>
	static std::vector<T2> Delta(std::vector<Transition<T0, T1, T2>>& transitions) {
		std::vector<T2> delta(transitions.size());
		for (std::size_t i = 0; i < transitions.size(); i++) {
			delta[i] = transitions[i].delta;
		}
		return delta;
	}

	template <typename T0, typename T1, typename T2>
	static std::vector<uint32_t> KeyLenghs(std::vector<Transition<T0, T1, T2>>& transitions) {
		std::vector<uint32_t> lenghs(transitions.size());
		for (std::size_t i = 0; i < transitions.size(); i++) {
			lenghs[i] = transitions[i].key.size();
		}
		return lenghs;
	}
};

