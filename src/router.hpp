#pragma once
#include <vector>
#include "graph.hpp"

namespace Transport
{
	class Router
	{
	public:
		virtual std::vector<int> FindRoute(const std::vector<std::vector<int>> &AdjecentVert, const int StartVert, const int EndVert) = 0;
	};
	
	class RouterTypeFirst :public Router
	{
	public:
		std::vector<int> FindRoute(const std::vector<std::vector<int>>& AdjecentVert, const int StartVert, const int EndVert) override;
	};

	class RouterTypeSecond :public Router
	{
	public:
		std::vector<int> FindRoute(const std::vector<std::vector<int>>& AdjecentVert, const int StartVert, const int EndVert) override;
	};
}