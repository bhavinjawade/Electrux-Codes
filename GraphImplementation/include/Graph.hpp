#include "NodeList.hpp"

namespace Electrux
{
	class Graph
	{
		NodeList *start, *end;
		int directed;
	public:
		enum Direction
		{
			DIRECTED,
			NONDIRECTED
		};
		Graph();
		Graph(int direction);
		bool add_node(int id);
		bool delete_node(int id);
		bool add_edge(int srcnode, int destnode, int weight);
		bool delete_edge(int from, int to);
		NodeList *GetNodeList(int _base);
		bool NodeListExists(int _base);
		int edge_exists(int from, int to);
		std::vector<int> getNodes();
		std::map<int, int> getShortestDistances(int src, int dest);
		void arrangeVisits(std::vector<mnode> &vec);
		bool findInVector(std::vector<mnode> &vec, int id);
		friend std::ostream & Graph::operator << (std::ostream &os, const Graph &graph);
	};
}