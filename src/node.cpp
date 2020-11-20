#include "node.hpp"

namespace transport
{
	int Node::GetParent()
	{
		return this->parent_;
	}
	int Node::GetPathLen()
	{
		return this->path_len_;
	}
	void Node::SetParent(int parent)
	{
		this->parent_ = parent;
	}
	void Node::SetPathLen(int len)
	{
		this->path_len_ = len;
	}
}
