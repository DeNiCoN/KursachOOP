#pragma once

namespace transport
{
	class Node
	{
	private:
		int parent_;
		double path_len_ = 0;
	public:
		void SetParent(const int parent);
		int GetParent() const;
		void SetPathLen(const double len);
		double GetPathLen() const;
	};
}
