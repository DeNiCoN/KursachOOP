#include "router.hpp"
#include "node.hpp"
#include <list>
#include <deque>
#include <unordered_set>

namespace transport
{
	std::vector<int> RouterBreadthFS::FindRoute(const Graph& graph, const int start_vert, const int end_vert)
	{
		try
		{


			int current = start_vert;
			int i;
			std::vector<int> rev_res;
			rev_res.reserve(graph.adjecent_vert.size() / 2);
			if (start_vert == end_vert)
			{
				return { start_vert };
			}
			std::unordered_set<int> visited;
			std::unordered_map<int, Node> node_vec;
			std::vector<int>::const_iterator iter;
			std::vector<int>::const_reverse_iterator rev_iter;
			std::deque<int> queue;

			node_vec[end_vert].SetParent(-1);
			node_vec[current].SetPathLen(0);
			node_vec[current].SetParent(-1);
			visited.insert(current);
			queue.push_back(current);

			while (!queue.empty())
			{
				i = 0;
				current = queue.front();
				queue.pop_front();
				if (current == end_vert)
					continue;
				for (iter = graph.adjecent_vert[current].cbegin(); iter != graph.adjecent_vert[current].cend(); ++iter)
				{
					if (visited.contains(*iter))
					{
						if (node_vec[*iter].GetPathLen() > node_vec[current].GetPathLen() + graph.edge_weight_vec[current][i])
						{
							node_vec[*iter].SetPathLen(node_vec[current].GetPathLen() + graph.edge_weight_vec[current][i]);
							node_vec[*iter].SetParent(current);
						}
					}
					else
					{
						visited.insert(*iter);
						node_vec[*iter].SetParent(current);
						node_vec[*iter].SetPathLen(node_vec[current].GetPathLen() + graph.edge_weight_vec[current][i]);
						queue.push_back(*iter);
					}
					i++;
				}
			}

			current = end_vert;

			if (node_vec[current].GetParent() == -1)
				throw start_vert;

			while (current != -1)
			{
				rev_res.push_back(current);
				current = node_vec[current].GetParent();
			}

			return std::vector<int>(rev_res.rbegin(), rev_res.rend());
		}
		catch (int ex)
		{
			std::vector<int> error = { ex };
			std::cout << "No rout exists from vertex {id} " << ex << std::endl;
			return error;
		}
	}

	std::vector<int> RouterDepthFS::FindRoute(const Graph& graph, const int start_vert, const int end_vert)
	{
		try
		{
			std::vector<int> result_rout, rev_res;
			if (start_vert == end_vert)
			{
				result_rout.push_back(start_vert);
				return result_rout;
			}
			std::vector<bool> visited(graph.adjecent_vert.size(), false);
			std::vector<Node> node_vec(graph.adjecent_vert.size());
			std::vector<int>::const_iterator iter;
			std::vector<int>::const_reverse_iterator rev_iter;
			bool next;
			int i;

			int current = start_vert;

			node_vec[current].SetParent(-1);
			node_vec[current].SetPathLen(0);
			visited[start_vert] = true;

			while (true)
			{
				i = 0;
				next = false;
				for (iter = graph.adjecent_vert[current].cbegin(); iter != graph.adjecent_vert[current].cend(); iter++)
				{
					if (!visited[*iter])
					{
						next = true;
						visited[*iter] = true;
						node_vec[*iter].SetPathLen(node_vec[current].GetPathLen() + graph.edge_weight_vec[current][i]);
						node_vec[*iter].SetParent(current);
						current = *iter;
						break;
					}
				}
				if (current == end_vert)
					break;

				if (current == start_vert)
					throw start_vert;

				if (next)
					continue;

				current = node_vec[current].GetParent();
			}

			while (current != -1)
			{
				i = 0;
				rev_res.push_back(current);
				for (iter = graph.adjecent_vert[current].cbegin(); iter != graph.adjecent_vert[current].cend(); iter++)
				{
					if (node_vec[*iter].GetPathLen() + graph.edge_weight_vec[current][i] < node_vec[current].GetPathLen() && visited[*iter])
					{
						node_vec[current].SetParent(*iter);
						node_vec[current].SetPathLen(node_vec[*iter].GetPathLen() + graph.edge_weight_vec[current][i]);
					}
					i++;
				}
				current = node_vec[current].GetParent();
			}

			rev_res.shrink_to_fit();
			result_rout.resize(rev_res.size());
			i = 0;
			for (rev_iter = rev_res.crbegin(); rev_iter != rev_res.crend(); rev_iter++)
			{
				result_rout[i] = (*rev_iter);
				i++;
			}

			return result_rout;
		}

		catch (int ex)
		{
			std::vector<int> error = { ex };
			std::cout << "No rout exists from vertex {id} " << ex << std::endl;
			return error;
		}
	}
}
