#include "router.hpp"
#include "node.hpp"
#include <list>

namespace transport
{
	std::vector<int> RouterTypeFirst::FindRoute(const VecVecInt& adjecent_vert,
												const VecVecInt& edge_weight,
												const int start_vert,
												const int end_vert)
	{
		try
		{


			int current = start_vert, i;
			std::vector<int> result_rout, rev_res;
			std::vector<bool> visited(adjecent_vert.size(), false);
			std::vector<Node> node_vec(adjecent_vert.size());
			std::vector<int>::const_iterator iter;
			std::vector<int>::const_reverse_iterator rev_iter;
			std::list<int> queue;

			node_vec[end_vert].SetParent(-1);
			node_vec[current].SetPathLen(0);
			node_vec[current].SetParent(-1);
			visited[current] = true;
			queue.push_back(current);

			while (!queue.empty())
			{
				i = 0;
				current = queue.front();
				queue.pop_front();
				if (current == end_vert)
					continue;
				for (iter = adjecent_vert[current].cbegin(); iter != adjecent_vert[current].cend(); ++iter)
				{
					if (visited[*iter])
					{
						if (node_vec[*iter].GetPathLen() > node_vec[current].GetPathLen() + edge_weight[current][i])
						{
							node_vec[*iter].SetPathLen(node_vec[current].GetPathLen() + edge_weight[current][i]);
							node_vec[*iter].SetParent(current);
						}
					}
					else
					{
						visited[*iter] = true;
						node_vec[*iter].SetParent(current);
						node_vec[*iter].SetPathLen(node_vec[current].GetPathLen() + edge_weight[current][i]);
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

	std::vector<int> RouterTypeSecond::FindRoute(const VecVecInt& adjecent_vert,
												 const VecVecInt& edge_weight,
												 const int start_vert,
												 const int end_vert)
	{
		try
		{
			std::vector<int> result_rout, rev_res;
			std::vector<bool> visited(adjecent_vert.size(), false);
			std::vector<Node> node_vec(adjecent_vert.size());
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
				for (iter = adjecent_vert[current].cbegin(); iter != adjecent_vert[current].cend(); iter++)
				{
					if (!visited[*iter])
					{
						next = true;
						visited[*iter] = true;
						node_vec[*iter].SetPathLen(node_vec[current].GetPathLen() + edge_weight[current][i]);
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
				for (iter = adjecent_vert[current].cbegin(); iter != adjecent_vert[current].cend(); iter++)
				{
					if (node_vec[*iter].GetPathLen() + edge_weight[current][i] < node_vec[current].GetPathLen() && visited[*iter])
					{
						node_vec[current].SetParent(*iter);
						node_vec[current].SetPathLen(node_vec[*iter].GetPathLen() + edge_weight[current][i]);
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
