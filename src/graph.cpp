#pragma once
#include "graph.hpp"

namespace Transport
{
	Graph::Graph(int VertQuan):VerticesQuan(VertQuan), fullness(0)
	{
		AdjecentVert.resize(VerticesQuan);
	}

	void Graph::addVertex(std::vector<int>& AdjVert, std::shared_ptr<Vertex> VertexPtr)
	{
		MapPtrVertex[VertexPtr] = fullness;
		AdjecentVert[fullness] = AdjVert;
		fullness++;
	}

	int Graph::getVertexId(std::shared_ptr<Vertex> VertexPtr)
	{
		return MapPtrVertex[VertexPtr];
	}

}