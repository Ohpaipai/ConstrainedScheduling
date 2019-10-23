#include "Graph.h"
Graph::Graph()
{
}

Graph::~Graph()
{
}

void Graph::makeCircuitDiagram(std::string _filename)
{
	
	this->ifile.open(_filename, std::ios::in);
	std::string inputString;//input
	std::stringstream ss;
	while (1) {
		this->ifile >> inputString;
		if (inputString == ".inputs")
		{
			std::getline(this->ifile, inputString);
			ss.clear();
			ss.str(inputString);
			while (ss>>inputString)
			{
				if (inputString[0] == '#') break;
				if (inputString[0] == '\\') {
					inputString.clear();
					std::getline(this->ifile, inputString);
					ss.clear();
					ss.str(inputString);
				}
				else {
					//add new node
					Node newNode;
					newNode.initial(inputString);
					newNode.status = _NULL;
					this->Circuit.insert(std::pair<std::string, Node>(inputString, newNode));
					inputN.push_back(inputString);
				}

			}
		}
		else if (inputString == ".model")
		{
			this->ifile >> inputString;
			this->projectname = inputString;
		}
		else if (inputString == ".outputs")
		{
			std::getline(this->ifile, inputString);
			ss.clear();
			ss.str(inputString);
			while (ss >> inputString)
			{
				if (inputString[0] == '#') break;
				if (inputString[0] == '\\') {
					inputString.clear();
					std::getline(this->ifile, inputString);
					ss.clear();
					ss.str(inputString);
				}
				else {
					//add new node
					Node newNode;
					newNode.initial(inputString);
					newNode.status = _NULL;
					this->Circuit.insert(std::pair<std::string, Node>(inputString, newNode));
					outputN.push_back(inputString);
				}

			}
		}
		else if(inputString==".names")
		{
			std::vector<std::string>Leaf;
			std::getline(this->ifile, inputString);
			//std::cout << inputString << std::endl;
			ss.clear();
			ss.str(inputString);
			//get Node
			while (ss >> inputString)
			{
				/*if (inputString == "h")
				{


					std::cout << "heds\n";
				}*/
				if (inputString[0] == '#') break;
				if (inputString[0] == '\\') {
					inputString.clear();
					std::getline(this->ifile, inputString);
					ss.clear();
					ss.str(inputString);
				}
				else {
					//add new node
					Leaf.push_back(inputString);
				}

			}
			//read

			/*if (Leaf[Leaf.size() - 1] == "p")
			{
				std::cout << "he\n";
			}*/
			//new input
			inputString.clear();
			std::getline(this->ifile, inputString);
			ss.clear();
			ss.str(inputString);
			bool isnext = false;
			int runtime = Leaf.size() - 1; 
			std::set<std::string>FunctionAboutNode;
			Operation op = _AND;
			while (ss >> inputString)
			{
				if (inputString[0] == '#') break;
				if (inputString[0] == '\\') {
					inputString.clear();
					std::getline(this->ifile, inputString);
					ss.clear();
					ss.str(inputString);
				}
				else {
					for (int i = 0; i < inputString.size(); i++)
					{
						if (inputString[i] == '-') {
							op = _OR;
							isnext = true;
						}
						else if (inputString[i] == '1')
						{
							FunctionAboutNode.insert(Leaf[i]);
						}
						else if (inputString[i] == '0')
						{
							op = _NOT;
							FunctionAboutNode.insert(Leaf[i]);
						}
					}
				}
				ss >> inputString;

				//is or
				if (isnext)
				{
					runtime -= 1;
					if (runtime <= 0) break;
					inputString.clear();


					std::getline(this->ifile, inputString);
					ss.clear();
					ss.str(inputString);
					
				}
				
			}

			//made node

			Node innode;
			innode.initial(Leaf[Leaf.size() - 1]);
			int t=0;
			for (std::set<std::string>::iterator it=FunctionAboutNode.begin();it!=FunctionAboutNode.end();it++)
			{
				std::map<std::string, Node>::iterator itMap = Circuit.find(*it);
				if (itMap != Circuit.end())
				{
					innode.Consist.insert(itMap->first);
					if (itMap->second.level >=t)
					{
						t = itMap->second.level + 1;
					}
					itMap->second.BeConsist.insert(Leaf[Leaf.size()-1]);
				}
				else
				{
					Node n;
					n.initial(*it);
					this->Circuit[*it] =n;
					innode.Consist.insert(*it);
				}
				
			}
			//this->Circuit.insert(std::pair<std::string, Node>(Leaf[Leaf.size()-1],innode));
			innode.level = t;
			innode.status = op;
			this->Circuit[Leaf[Leaf.size() - 1]] = innode;
			/*for (int i = 0; i < Leaf.size()-1; i++)
			{
				std::map<std::string, Node>::iterator itMap = Circuit.find(Leaf[i]);
				this->Circuit[Leaf[Leaf.size() - 1]].BeConsist.push_back(itMap->second);
			}*/
			


		}
		else if (inputString == ".end") break;
	
	}
	this->ifile.close();
}

void Graph::Output()
{
	for (std::map<std::string, Node>::iterator it=Circuit.begin();it!=Circuit.end();it++)
	{
		std::cout << it->second.name << " , " << it->second.status << "   level :"<<it->second.level <<std::endl<<" Consist : ";
		for (std::set<std::string>::iterator iter=it->second.Consist.begin(); iter != it->second.Consist.end();iter++)
		{
			std::cout << *iter << " ";
		}
		std::cout << std::endl<<" beConsist : ";
		for (std::set<std::string>::iterator iter = it->second.BeConsist.begin(); iter != it->second.BeConsist.end(); iter++)
		{
			std::cout << *iter << " ";
		}
		std::cout << std::endl<<"Resourse : AND -> ";
		std::cout << it->second.andResourceNum << " , OR -> " << it->second.orResourceNum << " , NOT -> " << it->second.notResourceNum << std::endl;
		std::cout << std::endl;
	}
}

void Graph::setSchedule()
{
	
	std::vector<std::string>::iterator itString;
	std::vector<std::string>_name;
	for (std::map<std::string, Node>::iterator it = Circuit.begin(); it != Circuit.end(); it++)
	{
		_name.clear();
		std::string name = it->first;

		for (std::set<std::string>::iterator its=it->second.BeConsist.begin();its!= it->second.BeConsist.end();its++)
		{
			//RecursiveForScheduleing(itNode->node, *itTree, itTree->node.name,_n);
			std::map<std::string, Node>::iterator iter = Circuit.find(*its);
			
				switch (iter->second.status)
				{
				case _OR:
					it->second.orResourceNum++;
					break;
				case _AND:
					it->second.andResourceNum++;
					break;
				case _NOT:
					it->second.notResourceNum++;
					break;
				default:
					break;
				}
				_name.push_back(*its);


			
		}
		while (true)
		{
			if (_name.size() == 0) break;
			//std::cout << _name.size() << std::endl;
			std::vector<std::string>_name2;
			for (int i = 0; i < _name.size(); i++)
			{
				
					//BFS to find (in the ready and not ready,can't have repeat
					std::map<std::string, Node>::iterator itN = Circuit.find(_name[i]);
					for (std::set<std::string>::iterator its=itN->second.BeConsist.begin();its!=itN->second.BeConsist.end();its++)
					{
						bool find = false;
						for (int l = 0; l < _name2.size(); l++)
						{
							if (_name2[l] == *its)
							{
								find = true;
								break;
							}
						}
						for (int l = 0; l < _name.size(); l++)
						{
							if (_name[l] == *its)
							{
								find = true;
								break;
							}
						}
						std::map<std::string, Node>::iterator itN2= Circuit.find(*its);
						if (!find)
						{
							switch (itN2->second.status)
							{
							case _OR:
								it->second.orResourceNum++;
								break;
							case _AND:
								it->second.andResourceNum++;
								break;
							case _NOT:
								it->second.notResourceNum++;
								break;
							default:
								break;
							}

							_name2.push_back(itN2->first);
						}
					}


					
				
			}
			_name = _name2;
		}
		
	}
}

bool Graph::ALAP(int _time)
{
	std::map<std::string, Node>ALAPCircuit=this->Circuit;
	for (std::map<std::string, Node>::iterator it=ALAPCircuit.begin();it!=ALAPCircuit.end();it++)
	{
		//it->second.slack = it->second.level;
		it->second.oldlevel = it->second.level;
		it->second.level = -1;
		
	}
	bool _rvalue = true;
	for (int i = 0; i < this->outputN.size(); i++)
	{
		std::map<std::string, Node>::iterator it = ALAPCircuit.find(this->outputN[i]);
		it->second.level = _time;
		int time = _time;
		Recurison(ALAPCircuit, it->first, time - 1, _rvalue);
		if (_rvalue == false)
			break;

	}
	if (_rvalue)
	{
		this->Circuit = ALAPCircuit;
		int a = 0; int b = 0; int c = 0;
		for (std::map<std::string, Node>::iterator it=Circuit.begin();it!=Circuit.end();it++)
		{
			it->second.slack = std::abs(it->second.slack - it->second.level);
			switch (it->second.status)
			{
			case _AND:
				a++;
				break;
			case _OR:
				b++;
				break;
			case _NOT:
				c++;
				break;
			default:
				break;
			}
		}
		if(a!=0)
			this->Restrict_AND_Resource = 1; 
		if(b!=0)
			this->Restrict_OR_Resource = 1; 
		if(c!=0)
			this->Restrict_NOT_Resource = 1;
		this->outputMaxtime = _time;
	}
	return _rvalue;
}

bool Graph::ml_rcs(const int m_and, const int m_or, const int m_not)
{
	this->setSchedule();
	this->Restrict_AND_Resource = m_and; this->Restrict_OR_Resource = m_or; this->Restrict_NOT_Resource = m_not;
	std::map<std::string, Node>MLRCS_Circuit;
	std::priority_queue<Node>andqueue;
	std::priority_queue<Node>notqueue;
	std::priority_queue<Node>orqueue;
	std::vector<Node>ready;
	std::vector<Node>Notready;
	//to check can do it
	int andr = 0;
	int orr = 0;
	int notr = 0;
	for (std::map<std::string,Node>::iterator it=Circuit.begin();it!=Circuit.end();it++)
	{
		
		if (it->second.status == _NULL)
			MLRCS_Circuit[it->first] = it->second;
		else {
			//count exception
			it->second.exception = it->second.andResourceNum * m_and 
									+ it->second.orResourceNum * m_or 
									+ it->second.notResourceNum * m_not;
			//put to ready
			if (it->second.level == 1)
			{
				switch (it->second.status)
				{
				case _OR:
					orr++;
					orqueue.push(it->second);
					break;
				case _AND:
					andr++;
					andqueue.push(it->second);
					break;
				case _NOT:
					notr++;
					notqueue.push(it->second);
					break;
				default:
					break;
				}
			}
			else {
				switch (it->second.status)
				{
				case _OR:
					orr++;
					break;
				case _AND:
					andr++;
					break;
				case _NOT:
					notr++;
					break;
				default:
					break;
				}
				Notready.push_back(it->second);
			}
		}
	}

	int t = 1; 
	//reaally do 
	if ((m_not == 0 && notr != 0) || (m_and == 0 && andr != 0) || (m_or == 0 && orr != 0))
		return false;
	else {
		while (!andqueue.empty()||!orqueue.empty()||!notqueue.empty()||(Notready.size()!=0))
		{
			//and
			for (int i = 0; (i <m_and&&!andqueue.empty()); i++)
			{
				Node tem = andqueue.top();
				tem.level = t;
				MLRCS_Circuit[tem.name] = tem;
				andqueue.pop();
			 
			}
			//or
			for (int i = 0; (i < m_or && !orqueue.empty()); i++)
			{
				Node tem = orqueue.top();
				tem.level = t;
				MLRCS_Circuit[tem.name] = tem;
				orqueue.pop();

			}
			//not
			for (int i = 0; (i < m_not && !notqueue.empty()); i++)
			{
				Node tem = notqueue.top();
				tem.level = t;
				MLRCS_Circuit[tem.name] = tem;
				notqueue.pop();

			}
			//push
			outputMaxtime = t;
			t++;
			std::vector<Node>newNotready;
			for (int i = 0; i < Notready.size(); i++)
			{
				if (Notready[i].level == t)
				{
					bool isnotfind=false;
					//check all the parent are do it
					for (std::set<std::string>::iterator its=Notready[i].Consist.begin();
															its!=Notready[i].Consist.end();
															its++)
					{
						std::map<std::string, Node>::iterator it = MLRCS_Circuit.find(*its);
						if (it == MLRCS_Circuit.end())
						{
							isnotfind = true;
							
							break;
						}
					}
					if (isnotfind)
					{
						Notready[i].level++;
						newNotready.push_back(Notready[i]);
					}
					else {
						switch (Notready[i].status)
						{
						case _OR:
							
							orqueue.push(Notready[i]);
							break;
						case _AND:
							
							andqueue.push(Notready[i]);
							break;
						case _NOT:
							
							notqueue.push(Notready[i]);
							break;
						default:
							break;
						}
					}
				}
				else {
					newNotready.push_back(Notready[i]);
				}
			}

			Notready = newNotready;

		}

		Circuit = MLRCS_Circuit;
		return true;
	}
}

void Graph::mr_lcs()
{
	std::map<std::string, Node>MRLCS_Circuit;
	std::priority_queue<Node,std::vector<Node>,cmp>andqueue;
	std::priority_queue<Node, std::vector<Node>, cmp>notqueue;
	std::priority_queue<Node, std::vector<Node>, cmp>orqueue;
	//put it in ready queue and not ready
	for (std::map<std::string, Node>::iterator it = Circuit.begin(); it != Circuit.end(); it++)
	{
		if (it->second.status == _NULL)
			MRLCS_Circuit[it->first] = it->second;

		if (it->second.oldlevel == 1) {
			switch (it->second.status)
			{
			case _AND:
				it->second.slack = std::abs(1 - it->second.level);
				andqueue.push(it->second);
				break;
			case _OR:
				it->second.slack = std::abs(1 - it->second.level);
				orqueue.push(it->second);
				break;
			case _NOT:
				it->second.slack = std::abs(1 - it->second.level);
				notqueue.push(it->second);
				break;
			default:
				break;

			}
		}
	}
	for (int i = 1; i <= this->outputMaxtime; i++)
	{
		//and
		for (int j = 0; j < this->Restrict_AND_Resource && !andqueue.empty(); j++)
		{
			Node tem = andqueue.top();
			if (tem.slack <= 1)
			{
				tem.level = i;
				MRLCS_Circuit[tem.name] = tem;
				andqueue.pop();
			}
			
		}
		while (!andqueue.empty()&& andqueue.top().slack == 0)
		{
			Node tem = andqueue.top();
			tem.level = i;
			MRLCS_Circuit[tem.name] = tem;
			andqueue.pop();
			this->Restrict_AND_Resource++;
		}
		//or
		for (int j = 0; j < this->Restrict_OR_Resource && !orqueue.empty(); j++)
		{
			Node tem = orqueue.top();
			if (tem.slack <= 1)
			{
				tem.level = i;
				MRLCS_Circuit[tem.name] = tem;
				orqueue.pop();
				
			}
		}
		while (!orqueue.empty() && orqueue.top().slack == 0)
		{
			Node tem = orqueue.top();
			tem.level = i;
			MRLCS_Circuit[tem.name] = tem;
			orqueue.pop();
			this->Restrict_OR_Resource++;
		}
		//not
		for (int j = 0; j < this->Restrict_NOT_Resource && !notqueue.empty(); j++)
		{
			Node tem = notqueue.top();
			if (tem.slack <= 1)
			{
				tem.level = i;
				MRLCS_Circuit[tem.name] = tem;
				notqueue.pop();
				
			}
		}
		while (!notqueue.empty() && notqueue.top().slack == 0)
		{
			Node tem = notqueue.top();
			tem.level = i;
			MRLCS_Circuit[tem.name] = tem;
			notqueue.pop();
			this->Restrict_NOT_Resource++;
		}
		//pull
		if (i == this->outputMaxtime) break;
		std::priority_queue<Node, std::vector<Node>, cmp>newandqueue;
		std::priority_queue<Node, std::vector<Node>, cmp>newnotqueue;
		std::priority_queue<Node, std::vector<Node>, cmp>neworqueue;
		for (std::map<std::string, Node>::iterator it = Circuit.begin(); it != Circuit.end(); it++)
		{
			if (it->second.oldlevel == i + 1) {
				bool find = true;
				for (std::set<std::string>::iterator its = it->second.Consist.begin(); its != it->second.Consist.end(); its++)
				{
					std::map<std::string, Node>::iterator itm = MRLCS_Circuit.find(*its);
					if (itm == MRLCS_Circuit.end())
					{
						find = false;
						break;
					}

				}
				if (find)
				{
					switch (it->second.status)
					{
					case _AND:
						it->second.slack = it->second.level - i - 1;
						if (it->second.slack < 0)it->second.slack = 0;
						newandqueue.push(it->second);
						break;
					case _OR:
						it->second.slack = it->second.level - i - 1;
						if (it->second.slack < 0)it->second.slack = 0;
						neworqueue.push(it->second);
						break;
					case _NOT:
						it->second.slack = it->second.level - i - 1;
						if (it->second.slack < 0)it->second.slack = 0;
						newnotqueue.push(it->second);
						break;
					default:
						break;

					}
				}
				else it->second.oldlevel++;
				

			}
		}
		while (!andqueue.empty())
		{
			Node tem = andqueue.top();
			tem.slack = tem.level - i - 1;
			if (tem.slack < 0) tem.slack = 0;
			newandqueue.push(tem);
			andqueue.pop();
		}
		while (!orqueue.empty())
		{
			Node tem = orqueue.top();
			tem.slack = tem.level-i-1;
			if (tem.slack < 0) tem.slack = 0;
			neworqueue.push(tem);
			orqueue.pop();
		}
		while (!notqueue.empty())
		{
			Node tem = notqueue.top();
			tem.slack = tem.level - i - 1;
			if (tem.slack < 0) tem.slack = 0;
			newnotqueue.push(tem);
			notqueue.pop();
		}
		andqueue = newandqueue;
		orqueue = neworqueue;
		notqueue = newnotqueue;
	}
	Circuit = MRLCS_Circuit;
}
void Graph::COut(bool can , char input)
{
	if (can)
	{
		if (input == 'l')
		{
			std::cout << "Resource - constrained Scheduling" << std::endl;
			
		}
		else
		{
			//this->Output();
			this->mr_lcs();
			std::cout << "Latency-constrained Scheduling" << std::endl;
		}
		//output
		
		std::vector<std::string>outor;
		std::vector<std::string>outnot;
		std::vector<std::string>outand;
		for (int i = 1; i <= this->outputMaxtime; i++)
		{
			outor.clear();
			outand.clear();
			outnot.clear();
			for (std::map<std::string, Node>::iterator it = Circuit.begin(); it != Circuit.end(); it++)
			{
				if (it->second.level == i)
				{
					switch (it->second.status)
					{
					case _OR:
						outor.push_back(it->first);
						break;
					case _AND:
						outand.push_back(it->first);
						break;
					case _NOT:
						outnot.push_back(it->first);
						break;
					default:
						break;
					}
				}
			}
			std::cout << i << " :";
			std::cout << " {";
			for (int k = 0; k < outand.size(); k++)
			{
				if (k + 1 == outand.size())
					std::cout << outand[k];
				else
					std::cout << outand[k] << ",";
			}
			std::cout << "} ";
			std::cout << " {";
			for (int k = 0; k < outor.size(); k++)
			{
				if (k + 1 == outor.size())
					std::cout << outor[k];
				else
					std::cout << outor[k] << ",";
			}
			std::cout << "} ";
			std::cout << " {";
			for (int k = 0; k < outnot.size(); k++)
			{
				if (k + 1 == outnot.size())
					std::cout << outnot[k];
				else
					std::cout << outnot[k] << ",";
			}
			std::cout << "} ";
			std::cout << std::endl;
	}

		std::cout << "#AND: " << this->Restrict_AND_Resource << std::endl;
		std::cout << "#OR: " << this->Restrict_OR_Resource << std::endl;
		std::cout << "#NOT: " << this->Restrict_NOT_Resource << std::endl;
		std::cout << "END" << std::endl;

	}
	else {
		std::cout << "No feasible solution." << std::endl << "END" << std::endl;
	}
	
}
void Graph::Recurison(std::map<std::string, Node>& _G, std::string _name, int t, bool& can)
{
	if (can == false) {
		return;
	}
	std::map<std::string, Node>::iterator it = _G.find(_name);
	for (std::set<std::string>::iterator its=it->second.Consist.begin();its!=it->second.Consist.end();its++)
	{
		std::map<std::string, Node>::iterator itT= _G.find(*its);
		if (itT->second.status == _NULL)
		{
			itT->second.level = 0;
		}
		else if (itT->second.level == -1)
		{
			itT->second.level = t;
		}
		else if (itT->second.level > t)
		{
			itT->second.level = t;
		}
		if (t - 1 < 0)
		{
			if (itT->second.status != _NULL)
			{
				can = false;
				return;
			}
		}
		else
		{
			
			Recurison(_G, itT->first, t - 1, can);
		}
	}
}
