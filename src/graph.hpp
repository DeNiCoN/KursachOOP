#pragma once
#include <vector>
#include <memory>


namespace Transport
{
	class Graph
	{
	private:
		int VerticesQuan;
	public:
		Graph(int VertQuan);
		~Graph() = default;
	};
}