#include "graph.hpp"

namespace transport
{
	Graph::Graph(const int VertQuan):vertices_quan_(VertQuan), 
									adjecent_vert(VertQuan),
									edge_weight_vec(VertQuan), 
									callback_id_(VertQuan)
	{
		vertex_type_quan_ = CountVertexType();
		type_id_lists_.resize(vertex_type_quan_);
		deleted_type_.resize(vertex_type_quan_, -1);
		for (size_t i = 0; i < vertex_type_quan_; i++)
		{
			type_id_lists_[i].reserve(VertQuan / vertex_type_quan_);
		}
	}

	int Graph::AddVertex(const std::vector<VertexType> type)	//fullness is even to id of Vertex
	{
		for (size_t i = 0; i < type.size(); i++)
		{
			callback_id_[fullness_].push_back(static_cast<int>(type[i]));
			if (deleted_type_[static_cast<int>(type[i])] == -1)
			{
				callback_id_[fullness_].push_back(type_id_lists_[static_cast<int>(type[i])].size());
				type_id_lists_[static_cast<int>(type[i])].push_back(fullness_);
			}
			else
			{
				callback_id_[fullness_].push_back(deleted_type_[static_cast<int>(type[i])]);
				type_id_lists_[static_cast<int>(type[i])][deleted_type_[static_cast<int>(type[i])]] = fullness_;
				deleted_type_[static_cast<int>(type[i])] = -1;
			}
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
		if (!static_cast<bool>(fullness_))
		{
			return -1;
		}
		return std::rand() % fullness_;
	}

	int Graph::GetRandVertex(const VertexType type) const
	{
		if (!static_cast<bool>(type_id_lists_[static_cast<int>(type)].size()))
		{
			return -1;
		}
		return type_id_lists_[static_cast<int>(type)][std::rand() % type_id_lists_[static_cast<int>(type)].size()];
	}

	void Graph::ChangeVertexType(const std::vector<VertexType> new_type, const int id)
	{
		for (size_t i = 0; i < callback_id_[id].size() / 2; i++)
		{
			type_id_lists_[callback_id_[id][2 * i]][callback_id_[id][2 * i + 1]] = -1;
			deleted_type_[callback_id_[id][2 * i]] = callback_id_[id][2 * i + 1];
		}
		callback_id_[id].clear();
		for (size_t i = 0; i < new_type.size(); i++)
		{
			callback_id_[id].push_back(static_cast<int>(new_type[i]));
			if (deleted_type_[static_cast<int>(new_type[i])] == -1)
			{
				callback_id_[id].push_back(type_id_lists_[static_cast<int>(new_type[i])].size());
				type_id_lists_[static_cast<int>(new_type[i])].push_back(id);
			}
			else
			{
				callback_id_[i].push_back(deleted_type_[static_cast<int>(new_type[i])]);
				type_id_lists_[static_cast<int>(new_type[i])][deleted_type_[static_cast<int>(new_type[i])]] = id;
				deleted_type_[static_cast<int>(new_type[i])] = -1;
			}
		}
	}

	double Graph::GetEdgeWeight(const int from, const int to) const
	{
		for (size_t i = 0; i < adjecent_vert[from].size(); i++)
		{
			if (adjecent_vert[from][i] == to)
			{
				return edge_weight_vec[from][i];
			}
		}
		return -1;
	}


	int Graph::CountVertexType() const
	{
		return static_cast<int>(VertexType::LAST);
	}

}
