#pragma once

namespace transport
{
	class Node
	{
	private:
		int parent;
		int PathLen = 0;
	public:
		void setParent(int parent);
		int getParent();
		void setPathLen(int len);
		int getPathLen();
	};
}
