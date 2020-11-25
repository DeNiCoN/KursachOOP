#include "graph.hpp"

namespace transport
{
	Graph::Graph(const int VertQuan):vertices_quan_(VertQuan), 
									adjecent_vert(VertQuan),
									edge_weight_vec(VertQuan), 
									type_id_lists(vertex_type_quan_), 
									callback_id(VertQuan)
	{
		vertex_type_quan_ = CountVertexType();
		for (size_t i = 0; i < vertex_type_quan_; i++)
		{
			type_id_lists[i].reserve(VertQuan / vertex_type_quan_);
		}
	}

	int Graph::AddVertex(const std::vector<VertexType> type)	//fullness is even to id of Vertex
	{
		for (size_t i = 0; i < type.size(); i++)
		{
			callback_id[fullness_].push_back(static_cast<int>(type[i]));
			callback_id[fullness_].push_back(type_id_lists[static_cast<int>(type[i])].size());
			type_id_lists[static_cast<int>(type[i])].push_back(fullness_);
		}
		fullness_++;
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

	void Graph::ChangeVertexType(const VertexType type, const int id)
	{

	}

	int Graph::CountVertexType() 
	{
		return static_cast<int>(VertexType::LAST);
	}

}
