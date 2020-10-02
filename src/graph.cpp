#pragma once
#include "graph.hpp"
#include "vertexes.hpp"

namespace Transport
{
	Graph::Graph(int VertQuan)
	{
		VerticesQuan = VertQuan;
		std::vector<std::unique_ptr<Vertex>> PtrVetexVec(VerticesQuan);
	}
}