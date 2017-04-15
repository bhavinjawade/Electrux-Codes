#include "Graph.hpp"

namespace Electrux
{
	Graph::Graph()
	{
		start = end = nullptr;
		directed = Direction::DIRECTED;
	}

	Graph::Graph(int direction)
	{
		start = end = nullptr;
		if (direction != Direction::DIRECTED && direction != Direction::UNDIRECTED)
			directed = Direction::DIRECTED;
		else directed = direction;
	}

	bool Graph::add_node(int id)
	{
		NodeList *base;
		if ((base = GetNodeList(id)) != nullptr)
		{
			return false;
		}
		else
		{
			if (start == nullptr)
			{
				start = end = new NodeList;
				start->set_node(id);
			}
			else
			{
				end->setNext(new NodeList);
				end->getNext()->setPrev(end);
				end->getNext()->setNext(nullptr);
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
		while (it != nullptr)
		{
			if (it->get_node() == id)
			{
				Node *deleter = it->getStart();							//
				while (deleter != nullptr)								//
				{														//
					NodeList *deletion = GetNodeList(deleter->id);		//Handle the deletion of this node from all other nodes
					deletion->delete_edge(it->get_node());				//
					deleter = deleter->next;							//
				}														//
				if (it == start)
				{
					start = start->getNext();
					start->setPrev(nullptr);
				}
				else if (it == end)
				{
					end = it->getPrev();
					it->getPrev()->setNext(nullptr);
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

	void Graph::disp_node_tree(std::vector<int> vec)
	{
		for (auto it = vec.begin(); it != vec.end(); ++it)
		{
			std::cout << *it << "->";
		}
		std::cout << "X\n";
	}

	bool Graph::add_edge(int srcnode, int destnode, int weight)
	{
		NodeList *src = GetNodeList(srcnode), *dest = GetNodeList(destnode);
		if (src == nullptr || dest == nullptr) return false;
		if (directed == Direction::DIRECTED)
		{
			src->add_edge(destnode, weight);
		}
		else if (directed == Direction::UNDIRECTED)
		{
			src->add_edge(destnode, weight);
			dest->add_edge(srcnode, weight);
		}
		return true;
	}

	bool Graph::delete_edge(int from, int to)
	{
		NodeList *node1 = GetNodeList(from), *node2 = GetNodeList(to);
		if (node1 == nullptr || node2 == nullptr) return false;
		if (directed == Direction::DIRECTED)
		{
			node1->delete_edge(to);
		}
		else if (directed == Direction::UNDIRECTED)
		{
			node1->delete_edge(to);
			node2->delete_edge(from);
		}
		return true;
	}

	NodeList* Graph::GetNodeList(int _base)
	{
		NodeList *temp = start;
		while (temp != nullptr)
		{
			if (temp->get_node() == _base)
			{
				return temp;
			}
			temp = temp->getNext();
		}
		return nullptr;
	}

	bool Graph::NodeListExists(int _base)
	{
		NodeList *temp = start;
		while (temp != nullptr)
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
		while (temp != nullptr)
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

	ShortestPathData Graph::CustomGetShortestPath(int src, int dest, std::vector<int> &path, int dist)
	{
		if (std::find(path.begin(), path.end(), src) != path.end()) return { -1, path }; //Prevent Cycle lock in graph

		path.push_back(src);
		NodeList *srclist = GetNodeList(src);

		//std::cout << "New node: " << src << " with dist = " << dist << "\n";
		//disp_node_tree(path);
		//std::cout << "\n";
		//std::cout << "New node end\n\n";
		ShortestPathData data = { -1, path };

		std::vector<int> origpath = path;

		if (srclist->get_node() == dest)
		{
			//std::cout << "final data new = " << dist << " with path = ";
			//disp_node_tree(path);
			//std::cout << "\nExiting: " << src << "\n";
			//std::cout << "\n\n";
			data.dist = dist;
			data.path = path;

			return data;
		}

		Node *it = srclist->getStart();
		if (it == nullptr)
		{
			//std::cout << "No path available on node " << src << ". Returning";
			//disp_node_tree(data.path);
			//std::cout << " and dist: " << data.dist << "\n";
			return data;
		}
		data.dist = 0;

		ShortestPathData newdata;
		int found = 0;

		while (it != nullptr)
		{
			if ((newdata = CustomGetShortestPath(it->id, dest, path, dist + it->weight)).dist > 0)
			{
				//std::cout << "Received new data: " << newdata.dist << ", prevdata: " << data.dist << "\n";
				if (data.dist > newdata.dist || data.dist == 0)
				{
					std::cout << "Possible Path found... dist = " << newdata.dist << " with path = ";
					disp_node_tree(newdata.path);
					std::cout << "\n\n";
					data = newdata;
				}
				found++;
			}
			path = origpath;
			it = it->next;
		}

		//std::cout << "Exiting: " << src << " with Found: " << found << " and data.dist = " << data.dist << "\n\n\n";

		if (found <= 0)
		{
			data = { -1, path };
		}

		return data;

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
		while (temp != nullptr)
		{
			os << "\nNode: " << temp->get_node() << "\n";
			if (temp->getStart() == nullptr)
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