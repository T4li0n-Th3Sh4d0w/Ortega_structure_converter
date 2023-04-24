#include "DrawFunctions.h"


void Structure::Create_Indicies(int loop_amount)
{
	GLuint table[36] = { 0, 1, 3, 1, 2, 3, 4, 5, 7, 5, 6, 7, 0, 1, 4, 1, 4, 5, 2, 3, 7, 2, 6, 7, 0, 3, 4, 3, 4, 7, 1, 2, 5, 2, 5, 6 };

	GLuint* CuboidIndices = new GLuint[MaxIndexCount + 3];
	for (int cuboid_number = 0; cuboid_number < loop_amount; cuboid_number++)
	{
		int next_cuboid_id = 8 * cuboid_number;
		for (int i = 0; i < 36; i++)
		{
			CuboidIndices[i + cuboid_number * 36] = table[i] + next_cuboid_id;
			if (i >=36)  throw std::overflow_error("Too much indices was generated");
		}
	}

	this->CuboidIndices = CuboidIndices;
}

Structure::Vertex* Structure::CreateCuboid(Vertex* target, float x, float y, float z, float side, float top, float back)//Creating cuboid based on input values
{
	int i = 0;
	float thickness = 0.18f;
	float crossbar = 1.0f;

	target[i].Position = { 0.0f + side, 0.0f + top,  0.0f +back }; // 0
	target[i].Color = { 0.83f, 0.70f, 0.44f };
	target[i].Texture = { 0.0f, 0.0f };
	i++;

	target[i].Position = { 0.0f + side, y + top, 0.0f + back }; // 1
	target[i].Color = { 0.83f, 0.70f, 0.44f };
	target[i].Texture = { 0.0f, 1.0f };
	i++;

	target[i].Position = { x + side, y + top, 0.0f + back }; // 2
	target[i].Color = { 0.83f, 0.70f, 0.44f };
	target[i].Texture = { 1.0f, 1.0f };
	i++;

	target[i].Position = { x + side,  0.0f + top,  0.0f + back }; //3
	target[i].Color = { 0.83f, 0.70f, 0.44f };
	target[i].Texture = { 1.0f, 0.0f };
	i++;

	target[i].Position = { 0.0f + side,  0.0f + top, z + back };//4
	target[i].Color = { 0.83f, 0.70f, 0.44f };
	target[i].Texture = { 0.0f, 0.0f };
	i++;

	target[i].Position = { 0.0f + side, y + top, z + back };//5
	target[i].Color = { 0.83f, 0.70f, 0.44f };
	target[i].Texture = { 0.0f, 1.0f };
	i++;

	target[i].Position = { x + side, y + top, z + back };//6
	target[i].Color = { 0.83f, 0.70f, 0.44f };
	target[i].Texture = { 1.0f, 1.0f };
	i++;

	target[i].Position = { x + side,  0.0f + top, z + back };//7
	target[i].Color = { 0.83f, 0.70f, 0.44f };
	target[i].Texture = { 1.0f, 0.0f };
	i++;


	return target;

}

Structure::Structure(size_t MaxQuadCount, int loop) // Class constructor
{
	SetVariables(MaxQuadCount);
	Create_Indicies(loop);
}

Structure::~Structure()
{
	
}

void Structure::DrawStructure(float x, float y, float z, GLuint NumberofCuboids, int shelf_amount)
{
	int m_vertex = Vertices.size();
	if(m_vertex != MaxVertexCount && m_vertex < MaxVertexCount )
	{
		GLuint VertexAmount = 8 * NumberofCuboids;
		float xu, yu, zu;
		xu = x / 100.0f;
		yu = y / 100.0f;
		zu = z / 100.0f;
		Vertex* vertices = new Vertex[VertexAmount + 1];
		vertices = (Structure::CreateCuboid(vertices, xu, 0.18f, zu, 0.0f, 0.0f, 0.0f));
		if (Vertices.size() < VertexAmount)
		{
			for (int i = 0; i < 8; i++)
			{
				Vertices.push_back(vertices[i]);
			}
		}

		vertices = (Structure::CreateCuboid(vertices, 0.18f, yu, zu, 0.0f, 0.0f, 0.0f));
		if (Vertices.size() < VertexAmount)
		{
			for (int i = 0; i < 8; i++)
			{
				Vertices.push_back(vertices[i]);
			}
		}

		vertices = (Structure::CreateCuboid(vertices, 0.18f, yu, zu, xu, 0.0f, 0.0f));
		if (Vertices.size() < VertexAmount)
		{
			for (int i = 0; i < 8; i++)
			{
				Vertices.push_back(vertices[i]);
			}
		}


		vertices = (Structure::CreateCuboid(vertices, xu + 0.18f, 0.18f, 1.0f, 0.0f, yu - 0.18f, 0.0f));
		if (Vertices.size() < VertexAmount)
		{
			for (int i = 0; i < 8; i++)
			{
				Vertices.push_back(vertices[i]);
			}
		}

		vertices = (Structure::CreateCuboid(vertices, xu + 0.18f, 0.18f, -1.0f, 0.0f, yu - 0.18f, zu));
		if (Vertices.size() < VertexAmount)
		{
			for (int i = 0; i < 8; i++)
			{
				Vertices.push_back(vertices[i]);
			}
		}

		if (shelf_amount != 0)
		{

			for (int i = 0; i < shelf_amount; i++)
			{
				vertices = (Structure::CreateCuboid(vertices, xu, 0.18f, zu, 0.0f, (yu / (shelf_amount + 1)), 0.0f));
				if (Vertices.size() < VertexAmount)
				{
					for (int i = 0; i < 8; i++)
					{
						Vertices.push_back(vertices[i]);
					}
				}
			}
		}
	
	}
	
}

size_t Structure::GetMaxQuadCount()
{
	return size_t(MaxQuadCount);
}

size_t Structure::GetMaxVertexCount()
{
	return size_t(MaxVertexCount);
}

size_t Structure::GetMaxIndexCount()
{
	return size_t(MaxIndexCount);
}

GLuint* Structure::GetCuboidIndices()
{
	return CuboidIndices;
}

void Structure::SetVariables(size_t MaxStructures)
{
	MaxQuadCount = MaxStructures *6;
	MaxIndexCount = MaxStructures * 36; // Max Sets of Indices ( Used to draw a triangles )
	MaxVertexCount = (MaxStructures * 8);
}

std::vector<Structure::Vertex> Structure::GetVertices() //Returns current Verticies vector
{
	return Vertices;
}


void Structure::ClearVector() // Clears the Verticies vector (one that is beeing sent to OpenGl vertex buffer)
{
	Vertices.clear();
}