#pragma once

#include "BasicObjLoader.hpp"

namespace assets {
template <int N, typename T>
void	BasicObjLoader::parse(std::stringstream& sstream, glm::vec<N, T>& vec, int requiredCount) {
	for (int i = 0; i < N; i++) {
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
