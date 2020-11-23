#pragma once
#include <vector>
#include "graph.hpp"

namespace transport
{
	using VecVecInt = std::vector<std::vector<int>>;
	using VecVecDoub = std::vector<std::vector<double>>;
	class Router
	{
	public:
		virtual std::vector<int> FindRoute(const Graph& graph, const int StartVert, const int EndVert) = 0;
	};
	
	class RouterTypeFirst :public Router
	{
	public:
		std::vector<int> FindRoute(const Graph& graph, const int StartVert, const int EndVert) override;
	};

	class RouterTypeSecond :public Router
	{
	public:
		std::vector<int> FindRoute(const Graph& graph, const int StartVert, const int EndVert) override;
	};
}
