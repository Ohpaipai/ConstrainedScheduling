#include "Graph.h"



Graph::Graph()
{
	filename = "";
	nodus.clear();
	Maxtime = 999;
	_addNumber = 0;
	_orNumber = 0;
	_notNumber = 0;
	Graghname = "";
}

Graph::Graph(std::string _filename)
{
	filename =_filename;
	nodus.clear();
	Maxtime = 999;
	_addNumber = 0;
	_orNumber = 0;
	_notNumber = 0;
	Graghname = "";
}


Graph::~Graph()
{
	filename.clear();
	nodus.clear();
	Maxtime = 0;
	_addNumber = 0;
	_orNumber = 0;
	_notNumber = 0;
	Graghname.clear();
}



void Graph::MakeGraph()
{
	char tempString[999999];
	//openfile
	ifile.open(filename, std::ios::in);
	//record node component
	std::vector<std::string>leaf;
	//read file string
	std::string paragraph;

	bool inputs = false;
	bool outputs = false;
	bool names = false;
	bool modles = false;
	bool specialcase = false;

	while (1) {
		ifile >> paragraph;
		//not annotation
		if (paragraph[0] != '#') 
		{
			//read over
			if (paragraph == ".end") break; 
			// endl
			else if(paragraph == "\\")
			{ }
			//is model
			else if (paragraph == ".model")
			{
				inputs = false;
				outputs = false;
				names = false;
				modles = true;
			}
			//give initial node
			else if (paragraph == ".inputs") 
			{
				inputs = true;
				outputs = false;
				names = false;
				modles = false;
			}
			//give output node
			else if (paragraph == ".outputs") //output nodes
			{
				inputs = false;
				outputs = true;
				names = false;
				modles = false;
			}
			//give boolean function
			else if (paragraph == ".names") 
			{
				
			}
			else if (inputs)
			{
				Node temNode;
				temNode.initial(paragraph, _null);
				Tree temTree;
				temTree.initial(temNode, Maxtime);
				nodus.push_back(temTree);
			}
			else if (outputs)
			{
				Node temNode;
				temNode.initial(paragraph, _over);
				Tree temTree;
				temTree.initial(temNode, Maxtime);
				nodus.push_back(temTree);
			}
			else if (modles)
			{
				
			}
			else if (names)
			{

			}
		}
		else {
			ifile.getline(tempString, LEN_LENGTH);
		}
	}
}
