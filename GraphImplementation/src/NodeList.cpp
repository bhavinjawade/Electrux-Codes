#include "NodeList.hpp"

namespace Electrux
{
	NodeList::NodeList()
	{
		start = end = NULL;
		node = -1;
	}

	NodeList::NodeList(int _node)
	{
		start = end = NULL;
		node = _node;
	}

	void NodeList::setNext(NodeList *ne)
	{
		next = ne;
	}

	void NodeList::setPrev(NodeList *pr)
	{
		prev = pr;
	}

	NodeList* NodeList::getNext()
	{
		return next;
	}

	NodeList* NodeList::getPrev()
	{
		return prev;
	}
	Node* NodeList::getStart()
	{
		return start;
	}
	void NodeList::set_node(int n)
	{
		node = n;
	}
	int NodeList::get_node()
	{
		return node;
	}
	void NodeList::add_edge(int to_id, int weight)
	{
		if (!edge_exists(to_id))
		{
			if (start == NULL)
			{
				start = end = new Node;
				start->id = to_id;
				start->weight = weight;
				start->next = NULL;
				start->prev = NULL;
			}
			else
			{
				end->next = new Node;
				end->next->prev = end;
				end->next->next = NULL;
				end = end->next;
				end->id = to_id;
				end->weight = weight;
			}
		}
	}
	int NodeList::edge_exists(int to_id)
	{
		Node *it = start;
		while (it != NULL)
		{
			if (it->id == to_id)
				return it->weight;
			it = it->next;
		}
		return 0;
	}
	bool NodeList::delete_edge(int to_id)
	{
		if (edge_exists(to_id))
		{
			Node *it = start;
			while (it != NULL)
			{
				if (it->id == to_id)
				{
					if (it == start)
					{
						start = start->next;
						start->prev = NULL;
					}
					else if (it == end)
					{
						end = it->prev;
						it->prev->next = NULL;
					}
					else
					{
						it->prev->next = it->next;
						it->next->prev = it->prev;
					}
					delete it;
					return true;
				}
				it = it->next;
			}
		}
		return false;
	}
	std::ostream & operator <<(std::ostream &os, const NodeList &obj)
	{
		Node *temp = obj.start;
		while (temp != NULL)
		{
			os << "Destination: " << temp->id << "\tWeight: " << temp->weight << "\n";
			temp = temp->next;
		}
		delete temp;
		return os;
	}
}