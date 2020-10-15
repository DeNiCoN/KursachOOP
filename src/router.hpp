#pragma once
#include <vector>
#include "graph.hpp"

namespace Transport
{
	class Router
	{
	public:
		virtual std::vector<int> FindRoute(std::vector<std::vector<int>> &AdjecentVert, std::shared_ptr<Vertex> StartVert, std::shared_ptr<Vertex> EndVert) = 0;
	};
	
	class RouterTypeFirst :public Router
	{
	public:
		std::vector<int> FindRoute(std::vector<std::vector<int>>& AdjecentVert, std::shared_ptr<Vertex> StartVert, std::shared_ptr<Vertex> EndVert) override;
	};

	class RouterTypeSecond :public Router
	{
	public:
		std::vector<int> FindRoute(std::vector<std::vector<int>>& AdjecentVert, std::shared_ptr<Vertex> StartVert, std::shared_ptr<Vertex> EndVert) override;
	};
}