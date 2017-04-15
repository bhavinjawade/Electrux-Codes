#include <iostream>
#include <cstdarg>
#include <vector>
#include <map>
#include "Graph.hpp"


int main()
{
	Electrux::Graph graph(Electrux::Graph::Direction::DIRECTED);

	/*
	graph.add_node(1);
	graph.add_node(2);
	graph.add_node(3);
	graph.add_node(4);
	graph.add_node(5);
	graph.add_node(6);

	graph.add_edge(1, 2, 1);
	graph.add_edge(1, 3, 3);
	graph.add_edge(1, 6, 2);
	graph.add_edge(2, 3, 3);
	graph.add_edge(2, 5, 5);
	graph.add_edge(3, 4, 6);
	graph.add_edge(6, 4, 1);
	graph.add_edge(6, 5, 4);
	*/
	///*
	graph.add_node(1);
	graph.add_node(2);
	graph.add_node(3);
	graph.add_node(4);
	graph.add_node(5);
	graph.add_node(6);

	graph.add_edge(1, 2, 1);
	graph.add_edge(1, 6, 5);
	graph.add_edge(1, 3, 9);
	graph.add_edge(2, 3, 4);
	graph.add_edge(2, 4, 15);
	graph.add_edge(2, 6, 3);
	graph.add_edge(3, 4, 10);
	graph.add_edge(4, 5, 7);
	graph.add_edge(6, 4, 11);
	//*/

	std::vector<int> path;

	auto sd = graph.CustomGetShortestPath(1, 5, path); //Will show all possible paths.
	std::cout << "\n\n\nShortest distance: " << sd.dist << " and path: ";
	graph.disp_node_tree(sd.path);
	std::cout << "\n\n\n\n";

	system("pause");
	return 0;
}
