#include "graph.hpp"

namespace transport
{
	Graph::Graph(int VertQuan):VerticesQuan(VertQuan), AdjecentVert(VertQuan), EdgeWeightVec(VertQuan)
	{
	}

	void Graph::addVertex(const std::vector<int>& AdjVert, const std::vector<int>& EdgeWeight, const std::shared_ptr<Vertex> VertexPtr)
	{
		MapPtrVertex[VertexPtr] = fullness;		//fullness even to id of Vertex
		AdjecentVert[fullness] = AdjVert;
		EdgeWeightVec[fullness] = EdgeWeight;
		fullness++;
	}

	int Graph::getVertexId(const std::shared_ptr<Vertex> VertexPtr) const
	{
		return MapPtrVertex.at(VertexPtr);
	}

}
