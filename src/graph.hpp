#pragma once
#include <vector>
#include <memory>
#include <unordered_map>
#include "vertices.hpp"



namespace transport
{
	class Graph
	{
	private:
		int vertices_quan_, fullness_ = 0;
	public:
		std::unordered_map<std::shared_ptr<Vertex>, int> map_ptr_vertex;
		std::vector<std::vector<int>> adjecent_vert;
		std::vector<std::vector<int>> edge_weight_vec;		// Every road is stored twice

		void AddVertex(const std::vector<int>& adj_vert,
					   const std::vector<int>& edge_weight,
					   const std::shared_ptr<Vertex> vertex_ptr);
		int GetVertexId(const std::shared_ptr<Vertex> vertex_ptr) const;

		Graph(int vert_quan);
//		~Graph() = default;
	};
}
