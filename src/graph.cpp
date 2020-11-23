#include "graph.hpp"

namespace transport
{
	Graph::Graph(const int VertQuan):vertices_quan_(VertQuan), 
									adjecent_vert(VertQuan),
									edge_weight_vec(VertQuan), 
									type_id_lists(vertex_type_quan_), 
									callback_id(VertQuan)
	{
		for (size_t i = 0; i < vertex_type_quan_; i++)
		{
			type_id_lists[i].reserve(VertQuan / vertex_type_quan_);
		}
	}

	int Graph::AddVertex(const VertexType type)	//fullness is even to id of Vertex
	{
		callback_id[fullness_].push_back(static_cast<int>(type));
		callback_id[fullness_].push_back(type_id_lists[static_cast<int>(type)].size());
		type_id_lists[static_cast<int>(type)].push_back(fullness_);
		fullness_++;
		if (vertices_quan_ == fullness_)
		{
			vertices_quan_ += 10;
			adjecent_vert.resize(vertices_quan_);
			edge_weight_vec.resize(vertices_quan_);
			callback_id.resize(vertex_type_quan_);
		}
		return fullness_ - 1;
	}

	void Graph::AddEdge(const int f_vertex, const int s_vertex, const double edge_weight)
	{
		adjecent_vert[f_vertex].push_back(s_vertex);
		adjecent_vert[s_vertex].push_back(f_vertex);
		edge_weight_vec[f_vertex].push_back(edge_weight);
		edge_weight_vec[s_vertex].push_back(edge_weight);
	}

	int Graph::GetRandVertex() const
	{
		std::srand(std::time(nullptr));
		return std::rand() % fullness_;
	}

	int Graph::GetRandVertex(const VertexType type) const
	{
		std::srand(std::time(nullptr));
		return type_id_lists[static_cast<int>(type)][std::rand() % type_id_lists[static_cast<int>(type)].size()];
	}
}
