#include "BasicObjLoader.hpp"

using namespace assets;

ftm::vec2	BasicObjLoader::mapUV(const ftm::vec3& pos, const ftm::vec3& normal, float scale) {
	ftm::vec2 uv;

	float ax, ay, az;
	ax = std::abs(normal[0]);
	ay = std::abs(normal[1]);
	az = std::abs(normal[2]);

	ftm::vec2 uvAxis;

	if (ax >= ay && ax >= az) {
		uvAxis = ftm::vec2(pos[2], pos[1]);
	} else if (ay >= ax && ay >= az) {
		uvAxis = ftm::vec2(pos[0], pos[2]);
	} else {
		uvAxis = ftm::vec2(pos[0], pos[1]);
	}

	float nx = normal[0] / (ax + ay + az);
	float ny = normal[1] / (ax + ay + az);
	float nz = normal[2] / (ax + ay + az);

	if (std::abs(nx) >= std::abs(ny) && std::abs(nx) >= std::abs(nz)) {
		uv = ftm::vec2(pos[2], pos[1]);
	} else if (std::abs(ny) >= std::abs(nx) && std::abs(ny) >= std::abs(nz)) {
		uv = ftm::vec2(pos[0], pos[2]) * scale;
	} else {
		uv = ftm::vec2(pos[0], pos[1]) * scale;
	}
	uv *= scale;

	if (nx < 0.0f)
		uv[0] = -uv[0];
	if (ny < 0.0f)
		uv[1] = -uv[1];
	if (nz < 0.0f)
		uv = -uv;
	
	uv[1] *= -1.0f;

	return uv;
}

BasicObjLoader::BasicObjLoader() {
	m_loaders["v"] = [this](std::stringstream& sstream) { loadVertex(sstream); };
	m_loaders["f"] = [this](std::stringstream& sstream) { loadFace(sstream); };
	m_loaders["vt"] = [this](std::stringstream& sstream) { loadTextureCoordinates(sstream); };
	m_loaders["vn"] = [this](std::stringstream& sstream) { loadVertexNormals(sstream); };
	m_loaders[""] = skip;
	m_loaders["#"] = skip;
	m_loaders["o"] = skip;
	m_loaders["g"] = skip;
	m_loaders["s"] = skip;
	m_loaders["l"] = skip;
	m_loaders["vp"] = skip;
	m_loaders["mtllib"] = skip;
	m_loaders["usemtl"] = skip;
	m_loaders["\n"] = skip;
}

MeshData	BasicObjLoader::toMeshData(std::string path) {
	return toMeshData(path.c_str());
}

MeshData	BasicObjLoader::toMeshData(const char* path) {
	std::ifstream file(path);
	MeshData meshData;

	m_vertices.clear();
	m_normals.clear();
	m_textureCoordinates.clear();
	m_indices.clear();
	m_faces.clear();

	if (!file.is_open())
		throw std::runtime_error("Failed to open file: " + std::string(path));

	std::string line;
	while (std::getline(file, line)) {
		std::stringstream sstream(line);
		std::string prefix;

		sstream >> prefix;
		auto it = m_loaders.find(prefix);
		if (it == m_loaders.end())
			throw std::runtime_error("Unsupported line prefix: " + prefix);
		if (!sstream.eof() && sstream.get() != ' ')
			throw std::runtime_error("Expected space after line prefix: " + prefix);
		it->second(sstream);
	}
	createMeshData(meshData);
	return meshData;
}

void	BasicObjLoader::loadTextureCoordinates(std::stringstream& sstream) {
	ftm::vec3 texCoord(0.0f, 0.0f, 1.0f);
	ftm::vec2 pos;

	parse(sstream, texCoord, 2);
	
	pos = ftm::vec2(texCoord[0] / texCoord[2], texCoord[1] / texCoord[2]);
	pos[1] = 1.0f - pos[1];
	m_textureCoordinates.push_back(pos);
}

void	BasicObjLoader::loadVertexNormals(std::stringstream& sstream) {
	ftm::vec3 normal;

	parse(sstream, normal, 3);

	m_normals.push_back(normal);
}

void	BasicObjLoader::loadVertex(std::stringstream& sstream) {
	ftm::vec3 vertex;
	ftm::vec4 pos;

	pos[3] = 1.0f;

	parse(sstream, pos, 3);

	vertex = ftm::vec3(pos[0] / pos[3], pos[1] / pos[3], pos[2] / pos[3]);
	m_vertices.push_back(vertex);
}

void	BasicObjLoader::loadFace(std::stringstream& sstream) {
	ftm::vec<FaceIndex, 4> face;
	int i = 0;

	for (i = 0; i < 4; i++) {
		if (sstream.eof() || sstream.peek() == '\n') {
			if (i >= 3)
				break;
			else
				throw std::runtime_error("Faces must have at least 3 vertices");
		}
		parseIndices(sstream, face[i]);
		if (face[i].vertexIndex <= 0)
			throw std::runtime_error("Vertex indices in faces must be greater than 0");
	}
	m_faces.push_back(ftm::vec<FaceIndex, 3>(face[0], face[1], face[2]));
	if (i == 3)
		return;
	m_faces.push_back(ftm::vec<FaceIndex, 3>(face[0], face[2], face[3]));
}

void	BasicObjLoader::parseIndices(std::stringstream& sstream, FaceIndex& faceIndex) {
	std::string indices;
	std::getline(sstream, indices, ' ');

	std::stringstream indicesStream(indices);
	std::string indexStr;

	indicesStream >> faceIndex.vertexIndex;
	faceIndex.texCoordIndex = 0;
	faceIndex.normalIndex = 0;

	if (indicesStream.fail())
		throw std::runtime_error("Failed to parse vertex index in face");
	if (indicesStream.peek() == ' ' || indicesStream.eof())
		return;
	if (indicesStream.peek() != '/')
		throw std::runtime_error("Expected '/' after vertex index in face");
	indicesStream.get();
	if (indicesStream.peek() == '/') {
		indicesStream.get();
	} else {
		indicesStream >> faceIndex.texCoordIndex;
		if (indicesStream.fail())
			throw std::runtime_error("Failed to parse texture coordinate index in face");
		if (indicesStream.peek() == ' ' || indicesStream.eof())
			return;
		if (indicesStream.peek() != '/')
			throw std::runtime_error("Expected '/' after texture coordinate index in face");
		indicesStream.get();
	}
	indicesStream >> faceIndex.normalIndex;
}

void	BasicObjLoader::createMeshData(MeshData& meshData) {
	render::Vertex vertex;
	ftm::vec3 color(0.0f);
	ftm::vec3 colorJump = ftm::vec3(0.1f);
	ftm::vec3 minBounds(std::numeric_limits<float>::max());
	ftm::vec3 maxBounds(std::numeric_limits<float>::lowest());

	try {
		for (const auto& face : m_faces) {
			color += colorJump;
			ftm::vec3 normal;

			ftm::vec3 a = m_vertices[face[1].vertexIndex - 1] - m_vertices[face[0].vertexIndex - 1];
			ftm::vec3 b = m_vertices[face[2].vertexIndex - 1] - m_vertices[face[0].vertexIndex - 1];
			normal = ftm::normalize(ftm::cross(a, b));

			for (int i = 0; i < 3; i++) {
				vertex.pos = m_vertices[face[i].vertexIndex - 1];

				minBounds = ftm::min(minBounds, vertex.pos);
				maxBounds = ftm::max(maxBounds, vertex.pos);

				if (face[i].texCoordIndex > 0 && face[i].texCoordIndex <= m_textureCoordinates.size())
					vertex.texCoord = m_textureCoordinates[face[i].texCoordIndex - 1];
				else
					vertex.texCoord = mapUV(vertex.pos, normal, 1.0f);
				vertex.color = color;
				meshData.vertices.push_back(vertex);
				meshData.indices.push_back(static_cast<uint32_t>(meshData.vertices.size() - 1));
			}
			if (color[0] >= 0.99f) color = ftm::vec3(0.0f);
		}
	} catch(const std::exception& e) {
		throw std::runtime_error("Error creating mesh data: " + std::string(e.what()));
	}
	changeOrigin(meshData, (minBounds + maxBounds) * 0.5f);
}

void	BasicObjLoader::changeOrigin(MeshData& meshData, ftm::vec3 origin) {
	for (auto& vertex : meshData.vertices) {
		vertex.pos -= origin;
	}
}

void	BasicObjLoader::skip(std::stringstream& sstream) {
	(void)sstream;
}

BasicObjLoader::~BasicObjLoader() {
}
