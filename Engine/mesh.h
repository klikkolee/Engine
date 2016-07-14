#ifndef ENGINE_MESH_H
#define ENGINE_MESH_H
#include "GL/glew.h"
#include <string>
#include <memory>

struct MeshData;

//class containing mesh data
class Mesh
{
private:
	std::shared_ptr<MeshData> data;
public:
	Mesh();
	//parses mesh data from a file. returns true on succes and false on failure
	bool LoadFromFile(std::string file);
	void Draw() const;

	static Mesh TestTriangle();//temp
	static Mesh TestCube(); //temp
};

#endif // !ENGINE_MESH_H
