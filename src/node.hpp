#pragma once

namespace transport
{
	class Node
	{
	private:
		int parent_;
		int path_len_ = 0;
	public:
		void SetParent(int parent);
		int GetParent();
		void SetPathLen(int len);
		int GetPathLen();
	};
}
