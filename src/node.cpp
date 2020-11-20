#include "node.hpp"

namespace transport
{
	int Node::getParent()
	{
		return this->parent;
	}
	int Node::getPathLen()
	{
		return this->PathLen;
	}
	void Node::setParent(int parent)
	{
		this->parent = parent;
	}
	void Node::setPathLen(int len)
	{
		this->PathLen = len;
	}
}
