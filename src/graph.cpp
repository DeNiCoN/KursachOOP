#include "graph.hpp"

namespace transport
{
	Graph::Graph(int VertQuan):vertices_quan_(VertQuan), adjecent_vert(VertQuan), edge_weight_vec(VertQuan)
	{
	}

	void Graph::AddVertex(const std::vector<int>& adj_vert,
						  const std::vector<double>& edge_weight,
						  const std::shared_ptr<Vertex> vertex_ptr)
	{
		map_ptr_vertex[vertex_ptr] = fullness_;//fullness even to id of Vertex
		adjecent_vert[fullness_] = adj_vert;
		edge_weight_vec[fullness_] = edge_weight;
		fullness_++;
	}

	int Graph::GetVertexId(const std::shared_ptr<Vertex> VertexPtr) const
	{
		return map_ptr_vertex.at(VertexPtr);
	}

}
