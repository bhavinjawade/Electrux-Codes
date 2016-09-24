#include <iostream>

struct Node
{
	std::string name;
	Node *next, *prev;
	NodeMgr *child;
};

class NodeTreeMgr
{
	Node *start, *end;
public:
	NodeMgr()
	{
		start = NULL;
		end = NULL;
	}
	int add_node(std::string &name, std::string parent)
	{
		if(start == NULL)
		{
			if(parent == "none")
			{
				start = create_new_node();
				end = start;
				end->name = name;
			}
			else
			{
				
			}
		}
	}

	Node *create_new_node()
	{
		Node *temp;
		temp->name.clear();
		temp->next = NULL;
		temp->prev = NULL;
		temp->child = NULL;
		return temp;
	}
};

class XML_Parser
{
	FILE *file;
	std::string _file;
public:
	XML_Parser()
	{
		file = NULL;
		_file.clear();
	}

	int xml_open(std::string __file)
	{
		if(__file.find(".xml") == std::string::npos)
		{
			return 0;
		}
		FILE *file = fopen(_file.c_str(), "a+");
		if(file == NULL)
		{
			return 0;
		}
		return 1;
	}

	int xml_close()
	{
		int ret = (fclose(file) == 0) ? 1 : 0;
		file = NULL;
		return ret;
	}

	int xml_parse()
	{
		if(!ini_isopen(file)) return 0;
		rewind(file);
	}

	int ini_isopen(INI_Parser *file)
	{
		return (file == NULL) ? 0 : 1;
	}
};

int main()
{

	return 0;
}
