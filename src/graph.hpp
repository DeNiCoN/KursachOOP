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
		int VerticesQuan, fullness;
	public:
		std::unordered_map<std::shared_ptr<Vertex>, int> MapPtrVertex;
		std::vector<std::vector<int>> AdjecentVert;

		void addVertex(std::vector<int>& AdjVert, std::shared_ptr<Vertex> VertexPtr);
		int getVertexId(std::shared_ptr<Vertex> VertexPtr);

		Graph(int VertQuan);
//		~Graph() = default;
	};
}