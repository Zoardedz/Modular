#pragma once
#include <string>
#include <DirectXMath.h>

struct Vertex3D
{
	struct
	{
		float x;
		float y;
		float z;
	};
};

struct Vertex2D
{
	struct
	{
		float x;
		float y;
		float u;
		float v;
	};
};

class Vertex
{
public:
	std::vector<float> Vert2DToVectorFloat(Vertex2D vertex)
	{
		std::vector<float> thereturn;
		thereturn.push_back(vertex.x);
		thereturn.push_back(vertex.y);
		return thereturn;
	}
};