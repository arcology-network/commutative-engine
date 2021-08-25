#pragma once
namespace codec {
	template<typename T>
	std::vector<char> Encode(std::vector<T> vec) {
		std::vector<char>buffer(vec.size() * sizeof(T), 0);
		for (std::size_t i = 0; i < vec.size(); i++) {
			memcpy(buffer.data() + i * sizeof(T), &vec[i], sizeof(T));
		}
		return buffer;
	}

	template<typename T>
	std::vector<char> Encode(T value) {
		std::vector<char>buffer(sizeof(T));
		memcpy(buffer.data(), &value, sizeof(value));
		return buffer;
	}

	template<typename T>
	T Decode(char* buffer) {
		T value;
		memcpy(&value, buffer, sizeof(T));
		return value;
	}

	template<typename T>
	T Decode(std::string str) {
		T num;
		memcpy(&num, str.data(), std::min<uint64_t>(str.size(), sizeof(num)));
		return num;
	}
}

