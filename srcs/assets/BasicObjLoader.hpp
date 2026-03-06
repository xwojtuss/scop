#pragma once

#include <fstream>
#include <sstream>
#include <random>
#include <string>
#include <functional>
#include <stdexcept>

#include "IModelLoader.hpp"
#include "Resources.hpp"
#include "../render/GpuTypes.hpp"
#include "../scene/WorldInfo.hpp"

namespace assets {
struct FaceIndex {
	uint32_t vertexIndex;
	uint32_t texCoordIndex;
	uint32_t normalIndex;
};
class BasicObjLoader : public IModelLoader {
private:
	std::vector<ftm::vec3>																	m_vertices;
	std::vector<ftm::vec3>																	m_normals;
	std::vector<ftm::vec2>																	m_textureCoordinates;
	std::vector<uint32_t>																	m_indices;
	std::vector<ftm::vec<FaceIndex, 3>>														m_faces;
	std::unordered_map<std::string, std::function<void(std::stringstream&)>>	m_loaders;

	void		loadVertex(std::stringstream& sstream);
	void		loadFace(std::stringstream& sstream);
	void		loadTextureCoordinates(std::stringstream& sstream);
	void		loadVertexNormals(std::stringstream& sstream);
	void		parseIndices(std::stringstream& sstream, FaceIndex& faceIndex);
	void		createMeshData(MeshData& meshData);
	
	template <typename T, std::size_t N>
	void		parse(std::stringstream& sstream, ftm::vec<T, N>& vec, std::size_t requiredCount = N);
	
	static void			skip(std::stringstream& sstream);
	static ftm::vec2	mapUV(const ftm::vec3& pos, const ftm::vec3& normal, float scale);
	static void			changeOrigin(MeshData& meshData, ftm::vec3 origin);

public:
	BasicObjLoader();
	virtual ~BasicObjLoader();

	MeshData	toMeshData(const char* path) override;
	MeshData	toMeshData(std::string path) override;
};
}

#include "BasicObjLoader.tpp"
