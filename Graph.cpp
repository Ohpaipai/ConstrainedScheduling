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
	std::string tempString;
	//openfile
	ifile.open(filename, std::ios::in);
	//read file string
	std::string paragraph;
	//vector for names node;
	std::vector<std::string>leaf;

	/*parameter about input*/
	bool inputs = false;
	bool outputs = false;
	bool names = false;
	bool modles = false;

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
				inputs = false;
				outputs = false;
				names = true;
				modles = false;
				std::stringstream ss;
				// read string in this line
				std::string _string="";
				std::getline(ifile,tempString);
				ss.str(tempString);	
				while(1){
					ss>>_string;
					//nonsensese line
					if(_string[0]=='#') break;
					//last input
					if(ss.eof()){
						//change line
						if(_string=="//"){
							//read new line
							std::getline(ifile,tempString);
							/*clear last data*/
							ss.clear();
							ss.str("");
							_string.clear();
							//read to streamstring
							ss.str(tempString);
						}
						else{
							//check has same element
							bool issame=false;
							for(int i=0;i<leaf.size();i++){
								if(leaf[i]==_string){
									issame=true;
									break;
								}
							}
							if(issame){
								leaf.push_back(_string);
							}
						}	
					}
					//not last input
					else{
						//check has same element
							bool issame=false;
							for(int i=0;i<leaf.size();i++){
								if(leaf[i]==_string){
									issame=true;
									break;
								}
							}
							if(issame){
								leaf.push_back(_string);
							}
						
					}

				}
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
				Graghname = paragraph;					
			}
			else if (names)
			{
					
			}
		}
		else {
			std::getline(ifile,tempString);
		}
	}
}
