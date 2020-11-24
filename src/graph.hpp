#pragma once
#include <vector>
#include <memory>
#include <unordered_map>
#include <ctime>
#include "vertex_type.hpp"
#include "vertices.hpp"



namespace transport
{
	class Graph
	{
	private:
		int vertices_quan_;
		int fullness_ = 0, vertex_type_quan_ = 9;
	public:
		std::vector<std::vector<int>> adjecent_vert;
		std::vector<std::vector<double>> edge_weight_vec;		// Every road is stored twice
		std::vector<std::vector<int>> type_id_lists;
		std::vector<std::vector<int>> callback_id;
		
		int AddVertex(const VertexType type);
		void AddEdge(const int f_vertex, const int s_vertex, const double edge_weight);
		int GetRandVertex() const;
		int GetRandVertex(const VertexType type) const;
		void ChangeVertexType(const VertexType type, const int id);

		Graph(int const vert_quan);
//		~Graph() = default;
	};
}
