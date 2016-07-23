#include "mesh.h"
#include "log.h"
#include "scene_graph_visitor.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <vector>
#include <assert.h>

struct MeshData
{
	enum
	{
		POSITION_VERTEX_BUFFER,
		INDEX_VERTEX_BUFFER,
		NUM_VERTEX_BUFFERS
	};
	GLuint vertexArrayObject;
	GLuint vertexArrayBuffers[NUM_VERTEX_BUFFERS];
	int numIndices;
	~MeshData()
	{
		glDeleteBuffers(NUM_VERTEX_BUFFERS, vertexArrayBuffers);
		glDeleteVertexArrays(1, &vertexArrayObject);
	}
};

struct  BufferableVector3
{
	float members[3];
	BufferableVector3(const aiVector3D& other) : members{ other.x,other.y,other.z } {}
};

Mesh::Mesh() : data(std::make_shared<MeshData>())
{
	glGenVertexArrays(1, &(data->vertexArrayObject));
	glBindVertexArray(data->vertexArrayObject);
	glGenBuffers(data->NUM_VERTEX_BUFFERS, data->vertexArrayBuffers);
}

bool Mesh::LoadFromFile(std::string file)
{
	Assimp::Importer importer{};
	const aiScene* scene = importer.ReadFile(file.c_str(), aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
	if (scene == nullptr)
	{
		Log("Error: unable to load mesh at file '%s'\n", file.c_str());
		return false;
	}
	const aiMesh* model = scene->mMeshes[0];

	std::vector<BufferableVector3> positions{};
	std::vector<unsigned int> indices;
	for (unsigned int i = 0; i < model->mNumVertices; i++)
	{
		aiVector3D position = model->mVertices[i];
		positions.push_back(BufferableVector3(position));
	}
	for (unsigned int i = 0; i < model->mNumFaces; i++)
	{
		aiFace& face = model->mFaces[i];
		assert(face.mNumIndices==3);
		indices.push_back(face.mIndices[0]);
		indices.push_back(face.mIndices[1]);
		indices.push_back(face.mIndices[2]);
	}
	glBindVertexArray(data->vertexArrayObject);

	glBindBuffer(GL_ARRAY_BUFFER, data->vertexArrayBuffers[data->POSITION_VERTEX_BUFFER]);
	glBufferData(GL_ARRAY_BUFFER, positions.size() * sizeof(positions[0]), positions.data(), GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, data->vertexArrayBuffers[data->INDEX_VERTEX_BUFFER]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(indices[0]),indices.data(),GL_STATIC_DRAW);

	data->numIndices = indices.size();

	return true;
}

void Mesh::Draw() const
{
	glBindVertexArray(data->vertexArrayObject);
	glDrawElements(GL_TRIANGLES, data->numIndices, GL_UNSIGNED_INT, nullptr);
}

void Mesh::Accept(SceneGraphVisitor & visitor)
{
	visitor.Apply(*this);
}

Mesh Mesh::TestTriangle()
{
	Mesh mesh{};
	static const GLfloat gVertexBufferData[] = { -1.0f,-1.0f,0.0f,1.0f,-1.0f,0.0f,0.0f,1.0f,0.0f };

	glBindVertexArray(mesh.data->vertexArrayObject);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, mesh.data->vertexArrayBuffers[mesh.data->POSITION_VERTEX_BUFFER]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(gVertexBufferData), gVertexBufferData, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

	static const GLuint gIndexBufferData[] = { 0,1,2 };

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.data->vertexArrayBuffers[mesh.data->INDEX_VERTEX_BUFFER]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(gIndexBufferData), gIndexBufferData, GL_STATIC_DRAW);

	mesh.data->numIndices = 3;
	glBindVertexArray(0);
	return mesh;
}

Mesh Mesh::TestCube()
{
	Mesh mesh{};
	static const GLfloat gVertexBufferData[] = {
		-1.0f,-1.0f,-1.0f, // triangle 1 : begin
		-1.0f,-1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f, // triangle 1 : end
		1.0f, 1.0f,-1.0f, // triangle 2 : begin
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f,-1.0f, // triangle 2 : end
		1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f,-1.0f,
		1.0f,-1.0f,-1.0f,
		1.0f, 1.0f,-1.0f,
		1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f,-1.0f,
		1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f,-1.0f, 1.0f,
		1.0f,-1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f,-1.0f,-1.0f,
		1.0f, 1.0f,-1.0f,
		1.0f,-1.0f,-1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f,-1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f,-1.0f,
		-1.0f, 1.0f,-1.0f,
		1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,
		1.0f,-1.0f, 1.0f
	};

	glBindVertexArray(mesh.data->vertexArrayObject);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, mesh.data->vertexArrayBuffers[mesh.data->POSITION_VERTEX_BUFFER]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(gVertexBufferData), gVertexBufferData, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

	static const GLuint gIndexBufferData[] = { 2,1,0,5,4,3,8,7,6,11,10,9,14,13,12,17,16,15,20,19,18,23,22,21,26,25,24,29,28,27,32,31,30,35,34,33 };

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.data->vertexArrayBuffers[mesh.data->INDEX_VERTEX_BUFFER]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(gIndexBufferData), gIndexBufferData, GL_STATIC_DRAW);

	mesh.data->numIndices = 36;
	glBindVertexArray(0);
	return mesh;
}
