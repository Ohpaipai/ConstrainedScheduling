#include"Graph.h"

int main(int argc, char* argv[]) {
	Graph g;
	//std::cout << "please input list  [-r/-l]  [fileposition] [time/resource]\n";
	if(argc==7)
	{ 
		g.makeCircuitDiagram(argv[3]);
		std::stringstream ss;
		int a, b, c;
		ss << argv[4];
		ss >> a;
		ss.clear();
		ss << argv[5];
		ss >> b;
		ss.clear();
		ss << argv[6];
		ss >> c;
		g.COut(g.ml_rcs(a,b,c),'l');
	}
	else if(argc==5)
	{ 
		g.makeCircuitDiagram(argv[3]);
		std::stringstream ss;
		int a;
		ss << argv[4];
		ss >> a;
		g.COut(g.ALAP(a), 'r');
	}
	else
	{
		std::cout << "wrong input . Please read README\n";
	}
	//g.makeCircuitDiagram("test.blif");
	

	//g.setSchedule();
	
	//std::cout << g.ALAP(100) << std::endl;
	//std::cout << g.ml_rcs(2, 1, 1) << std::endl;
	
	//g.COut(g.ALAP(100),'r');
	//g.Output();
	

}