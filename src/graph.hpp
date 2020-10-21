#pragma once
#include <vector>
#include <memory>
#include <unordered_map>
#include "vertices.hpp"



namespace Transport
{
	class Graph
	{
	private:
		int VerticesQuan, fullness = 0;
	public:
		std::unordered_map<std::shared_ptr<Vertex>, int> MapPtrVertex;
		std::vector<std::vector<int>> AdjecentVert;
		std::vector<std::vector<int>> EdgeWeightVec;		// Every road is stored twice

		void addVertex(const std::vector<int>& AdjVert, const std::vector<int>& EdgeWeight, const std::shared_ptr<Vertex> VertexPtr);
		int getVertexId(const std::shared_ptr<Vertex> VertexPtr) const;

		Graph(int VertQuan);
//		~Graph() = default;
	};
}