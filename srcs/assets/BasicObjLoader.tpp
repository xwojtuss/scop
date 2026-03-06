#pragma once

#include "BasicObjLoader.hpp"

namespace assets {
template <typename T, std::size_t N>
void	BasicObjLoader::parse(std::stringstream& sstream, ftm::vec<T, N>& vec, std::size_t requiredCount) {
	for (std::size_t i = 0; i < N; i++) {
		if (sstream.eof()) {
			if (i >= requiredCount)
				return;
			else
				throw std::runtime_error("Not enough components in vector");
		}
		sstream >> vec[i];
	}
	if (!sstream.eof())
		throw std::runtime_error("Too many components in vector");
}
}
