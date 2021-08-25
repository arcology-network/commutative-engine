#pragma once

template<typename T0, typename T1, typename T2>
struct Commutative {
	std::vector<Transition<T0, T1, T2>> buffer;
	void Insert(std::vector<Transition<T0, T1, T2>>& delta) {
		buffer.insert(buffer.end(), delta.begin(), delta.end());
	}

	void Check(std::vector<uint32_t>& whiteList, std::vector<uint32_t>& outTxs) {
		std::set<uint32_t> lookup(whiteList.begin(), whiteList.end()); // valid TX ids

		tbb::concurrent_vector<Transition<T0, T1, T2>*> validBuffer;
		validBuffer.reserve(buffer.size());
		
		//Get the whitelisted ones only
		tbb::parallel_for(std::size_t(0), buffer.size(), [&](std::size_t i) {
			if (lookup.find(buffer[i].tx) != lookup.end()) { 
				validBuffer.push_back(&buffer[i]);
			}
		});

		std::chrono::steady_clock::time_point t0 = std::chrono::steady_clock::now();
		tbb::parallel_sort(validBuffer.begin(), validBuffer.end(), [](auto& lft, auto& rgt) {
			if (lft->key == rgt->key) {
				if (lft->delta == rgt->delta) {
					return lft->tx < rgt->tx;
				}
				return lft->delta > rgt->delta;
			}
			return lft->key < rgt->key;
		});
		//std::cout << "Commutative parallel_sort (): " << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - t0).count() << " ms" << std::endl;

		//t0 = std::chrono::steady_clock::now();
		if (validBuffer.size() <= 1) {
			return;
		}

		T2 value = validBuffer[0]->delta;
		for (std::size_t i = 0; i < validBuffer.size() - 1; i++) {
			if (validBuffer[i]->key == validBuffer[i + 1]->key) {
				if (value + validBuffer[i + 1]->delta >= 0) {
					value += validBuffer[i + 1]->delta;
					validBuffer[i]->isValid = validBuffer[i + 1]->isValid = true;
				}
			}
			else {
				value = validBuffer[i + 1]->delta;
			}
		}

		// Remove duplicate tx IDs
		tbb::parallel_sort(validBuffer.begin(), validBuffer.end(), [](auto& lft, auto& rgt) { return (lft->tx < rgt->tx);} );
		auto last = std::unique(validBuffer.begin(), validBuffer.end(), [](auto& lft, auto& rgt) {return lft->tx == rgt->tx; });

		outTxs.reserve(std::distance(validBuffer.begin(), last));
		tbb::parallel_for(std::size_t(0), validBuffer.size(), [&](std::size_t i) {
			if(validBuffer[i]->isValid)
				outTxs.push_back(validBuffer[i]->tx);
		});
		//std::cout << "Commutative std::unique (): " << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - t0).count() << " ms" << std::endl;
	}
	void Clear() { buffer.clear(); }
};
