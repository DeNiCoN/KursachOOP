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
		int vertices_quan_, vertex_type_quan_;
		int fullness_ = 0;
		std::vector<std::vector<int>> type_id_lists_;
		std::vector<std::vector<int>> callback_id_;
		std::vector<int> deleted_type_;

	public:
		std::vector<std::vector<int>> adjecent_vert;
		std::vector<std::vector<double>> edge_weight_vec;		// Every road is stored twice

		explicit Graph(const int VertQuan);

		int AddVertex(const std::vector<VertexType> type);
		void AddEdge(const int f_vertex, const int s_vertex, const double edge_weight);
		int GetRandVertex() const;
		int GetRandVertex(const VertexType type) const;
		void ChangeVertexType(const std::vector<VertexType> new_type, const int id);
		int CountVertexType() const;
		double GetEdgeWeight(const int from, const int to) const;

//		~Graph() = default;
	};
}
