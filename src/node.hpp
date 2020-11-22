#pragma once

namespace transport
{
	class Node
	{
	private:
		int parent_;
		double path_len_ = 0;
	public:
		void SetParent(int parent);
		int GetParent() const;
		void SetPathLen(double len);
		double GetPathLen() const;
	};
}
