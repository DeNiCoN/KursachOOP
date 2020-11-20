#pragma once
#include <vector>
#include "graph.hpp"

namespace transport
{
	using VecVecInt = std::vector<std::vector<int>>;
	class Router
	{
	public:
		virtual std::vector<int> FindRoute(const VecVecInt& AdjecentVert, const VecVecInt& EdgeWeight, const int StartVert, const int EndVert) = 0;
	};
	
	class RouterTypeFirst :public Router
	{
	public:
		std::vector<int> FindRoute(const VecVecInt& AdjecentVert, const VecVecInt& EdgeWeight, const int StartVert, const int EndVert) override;
	};

	class RouterTypeSecond :public Router
	{
	public:
		std::vector<int> FindRoute(const VecVecInt& AdjecentVert, const VecVecInt& EdgeWeight, const int StartVert, const int EndVert) override;
	};
}
