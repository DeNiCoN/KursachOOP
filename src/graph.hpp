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

		void addVertex(const std::vector<int>& AdjVert, const std::shared_ptr<Vertex> VertexPtr);
		int getVertexId(std::shared_ptr<Vertex> VertexPtr) const;

		Graph(int VertQuan);
//		~Graph() = default;
	};
}