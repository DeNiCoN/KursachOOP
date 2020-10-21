#pragma once
#include "router.hpp"
#include "node.hpp"
#include <list>

namespace Transport
{
	std::vector<int> RouterTypeFirst::FindRoute(const VecVecInt& AdjecentVert, const VecVecInt& EdgeWeight, const int StartVert, const int EndVert)
	{
		int current = StartVert, i;
		std::vector<int> ResultRout, RevRes;
		std::vector<bool> visited(AdjecentVert.size(), false);
		std::vector<Node> NodeVec(AdjecentVert.size());
		std::vector<int>::const_iterator iter;
		std::vector<int>::const_reverse_iterator RevIter;
		std::list<int> queue;

		NodeVec[current].setPathLen(0);
		NodeVec[current].setParent(-1);
		visited[current] = true;
		queue.push_back(current);

		while (!queue.empty())
		{
			i = 0;
			current = queue.front();
			queue.pop_front();
			if (current == EndVert)
				continue;
			for (iter = AdjecentVert[current].cbegin(); iter != AdjecentVert[current].cend() ; ++iter)
			{
				if (visited[*iter])
				{
					if (NodeVec[*iter].getPathLen() > NodeVec[current].getPathLen() + EdgeWeight[current][i])
					{
						NodeVec[*iter].setPathLen(NodeVec[current].getPathLen() + EdgeWeight[current][i]);
						NodeVec[*iter].setParent(current);
					}
				}
				else
				{
					visited[*iter] = true;
					NodeVec[*iter].setParent(current);
					NodeVec[*iter].setPathLen(NodeVec[current].getPathLen() + EdgeWeight[current][i]);
					queue.push_back(*iter);
				}
				i++;
			}
		}

		current = EndVert;

		while (current != -1)
		{
			RevRes.push_back(current);
			current = NodeVec[current].getParent();
		}
		RevRes.shrink_to_fit();

		ResultRout.resize(RevRes.size());
		i = 0;
		for (RevIter = RevRes.crbegin(); RevIter != RevRes.crend(); RevIter++)
		{
			ResultRout[i]=(*RevIter);
			i++;
		}

		return ResultRout;
	}

	std::vector<int> RouterTypeSecond::FindRoute(const VecVecInt& AdjecentVert, const VecVecInt& EdgeWeight, const int StartVert, const int EndVert)
	{
		std::vector<int> ResultRout;
		return ResultRout;
	}
}