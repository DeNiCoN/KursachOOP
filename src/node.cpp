#include "node.hpp"

namespace transport
{
	int Node::GetParent() const
	{
		return this->parent_;
	}
	double Node::GetPathLen() const
	{
		return this->path_len_;
	}
	void Node::SetParent(const int parent)
	{
		this->parent_ = parent;
	}
	void Node::SetPathLen(const double len)
	{
		this->path_len_ = len;
	}
}
