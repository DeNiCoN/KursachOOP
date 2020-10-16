#pragma once
#include "graph.hpp"

namespace Transport
{
	Graph::Graph(int VertQuan):VerticesQuan(VertQuan), AdjecentVert(VertQuan)
	{
	}

	void Graph::addVertex(const std::vector<int>& AdjVert, const std::shared_ptr<Vertex> VertexPtr)
	{
		MapPtrVertex[VertexPtr] = fullness;
		AdjecentVert[fullness] = AdjVert;
		fullness++;
	}

	int Graph::getVertexId(std::shared_ptr<Vertex> VertexPtr) const
	{
		return MapPtrVertex.at(VertexPtr);
	}

}