#include "Graph.hpp"

namespace Electrux
{
	Graph::Graph()
	{
		start = end = NULL;
		directed = Direction::DIRECTED;
	}

	Graph::Graph(int direction)
	{
		start = end = NULL;
		if (direction != Direction::DIRECTED && direction != Direction::NONDIRECTED)
			directed = Direction::DIRECTED;
		else directed = direction;
	}

	bool Graph::add_node(int id)
	{
		NodeList *base;
		if ((base = GetNodeList(id)) != NULL)
		{
			return false;
		}
		else
		{
			if (start == NULL)
			{
				start = end = new NodeList;
				start->set_node(id);
			}
			else
			{
				end->setNext(new NodeList);
				end->getNext()->setPrev(end);
				end->getNext()->setNext(NULL);
				end = end->getNext();
				end->set_node(id);
			}
			NodeList *list = new NodeList;
			list->set_node(id);
		}
		return true;
	}

	bool Graph::delete_node(int id)
	{
		NodeList *it = start;
		while (it != NULL)
		{
			if (it->get_node() == id)
			{
				Node *deleter = it->getStart();							//
				while (deleter != NULL)									//
				{														//
					NodeList *deletion = GetNodeList(deleter->id);		//Handle the deletion of this node from all other nodes
					deletion->delete_edge(it->get_node());				//
					deleter = deleter->next;							//
				}														//
				if (it == start)
				{
					start = start->getNext();
					start->setPrev(NULL);
				}
				else if (it == end)
				{
					end = it->getPrev();
					it->getPrev()->setNext(NULL);
				}
				else
				{
					it->getPrev()->setNext(it->getNext());
					it->getNext()->setPrev(it->getPrev());
				}
				delete it;
				return true;
			}
			it = it->getNext();
		}
		return false;
	}

	bool Graph::add_edge(int srcnode, int destnode, int weight)
	{
		NodeList *src = GetNodeList(srcnode), *dest = GetNodeList(destnode);
		if (src == NULL || dest == NULL) return false;
		if (directed == Direction::DIRECTED)
		{
			src->add_edge(destnode, weight);
		}
		else if (directed == Direction::NONDIRECTED)
		{
			src->add_edge(destnode, weight);
			dest->add_edge(srcnode, weight);
		}
		return true;
	}

	bool Graph::delete_edge(int from, int to)
	{
		NodeList *node1 = GetNodeList(from), *node2 = GetNodeList(to);
		if (node1 == NULL || node2 == NULL) return false;
		if (directed == Direction::DIRECTED)
		{
			node1->delete_edge(to);
		}
		else if (directed == Direction::NONDIRECTED)
		{
			node1->delete_edge(to);
			node2->delete_edge(from);
		}
		return true;
	}

	NodeList* Graph::GetNodeList(int _base)
	{
		NodeList *temp = start;
		while (temp != NULL)
		{
			if (temp->get_node() == _base)
			{
				return temp;
			}
			temp = temp->getNext();
		}
		return NULL;
	}

	bool Graph::NodeListExists(int _base)
	{
		NodeList *temp = start;
		while (temp != NULL)
		{
			if (temp->get_node() == _base)
			{
				return true;
			}
			temp = temp->getNext();
		}
		delete temp;
		return false;
	}
	int Graph::edge_exists(int from, int to)
	{
		NodeList *fromnode = GetNodeList(from);
		if (fromnode == 0) return -1;
		if (!NodeListExists(to)) return -1;
		int dist = fromnode->edge_exists(to);
		if (dist != 0) return dist;
		return 0;
	}
	std::vector<int> Graph::getNodes()
	{
		NodeList *temp = start;
		std::vector<int> allnodes;
		allnodes.clear();
		while (temp != NULL)
		{
			allnodes.push_back(temp->get_node());
			temp = temp->getNext();
		}
		return allnodes;
	}
	std::map<int, int> Graph::getShortestDistances(int src, int dest)
	{
		std::map<int, int> dist;
		std::map<int, bool> visited;

		auto nodes = getNodes();
		for (auto it = nodes.begin(); it != nodes.end(); ++it)
		{
			dist[*it] = 0;
			visited[*it] = false;
		}
		std::vector<mnode> visits;
		visits.push_back({ src, 0 });
		dist[src] = 0;
		while (!visits.empty())
		{
			int check = visits.begin()->id;
			visits.erase(visits.begin());
			for (auto it = nodes.begin(); it != nodes.end(); ++it)
			{
				if (edge_exists(check, *it) > 0)
				{
					if (dist[*it] > dist[check] + edge_exists(check, *it) || dist[*it] == 0)
					{
						dist[*it] = dist[check] + edge_exists(check, *it);
					}

					if (!visited[*it])
					{
						visited[*it] = true;
						visits.push_back({ *it, dist[*it] });
						arrangeVisits(visits);
					}
				}
			}
		}
		return dist;
	}
	void Graph::arrangeVisits(std::vector<mnode> &vec)
	{
		std::vector<mnode> vtemp;
		while (!vec.empty())
		{
			auto temp = vec.begin();
			for (auto it = vec.begin(); it != vec.end(); ++it)
			{
				if (temp->dist > it->dist)
				{
					temp = it;
				}
			}
			vtemp.push_back(*temp);
			vec.erase(temp);
		}
		vec = vtemp;
	}
	bool Graph::findInVector(std::vector<mnode> &vec, int id)
	{
		for (auto it = vec.begin(); it != vec.end(); ++it)
		{
			if (it->id == id)
			{
				return true;
			}
		}
		return false;
	}
	std::ostream & operator << (std::ostream &os, const Graph &graph)
	{
		NodeList *temp = graph.start;
		while (temp != NULL)
		{
			os << "\nNode: " << temp->get_node() << "\n";
			if (temp->getStart() == NULL)
			{
				os << "----No outgoing edge available----\n";
			}
			else
			{
				os << *temp;
			}
			temp = temp->getNext();
		}
		delete temp;
		return os;
	}
}