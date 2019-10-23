#pragma once
#include<iostream>
#include<string>
#include<map>
#include<fstream>
#include<vector>
#include<set>
#include<sstream>
#include<algorithm>
#include<queue>
#define Operationtime 1
//Opreation define
enum Operation {
	_NULL,
	_AND,
	_OR,
	_NOT,
	_OVER,
};


typedef struct Myclass {
	std::set<std::string>Consist; //parent
	std::set<std::string>BeConsist;//children
	std::string name;//name
	Operation status;//status(like add ,or ,not),node
	int andResourceNum;//*
	int orResourceNum;//+
	int notResourceNum;//~
	int level;
	int slack;
	int oldlevel;
	int exception;
	void initial(std::string _name) {
		this->andResourceNum = 0;
		this->orResourceNum = 0;
		this->notResourceNum = 0;
		this->level = 0;
		this->slack = 0;
		this->oldlevel = 0;
		this->status = _NULL;
		this->name = _name;
	}
	bool operator< (const Myclass& b) const   
	{
		if (this->exception==b.exception)  return this->BeConsist.size()<b.BeConsist.size();
		else return this->exception < b.exception;
	}
}Node;
struct cmp
{
	bool operator()(Node a, Node b)
	{
		if (a.slack == b.slack)
		{
			//if (a.oldlevel == b.oldlevel)
			return a.BeConsist.size() < b.BeConsist.size();
			//else
				//return a.oldlevel > b.oldlevel;
		}
		else return a.slack > b.slack;
	}
};
class Graph
{
public:
	Graph();
	~Graph();
	void makeCircuitDiagram(std::string);
	void Output();
	void setSchedule();
	bool ALAP(int _time);
	bool ml_rcs(const int m_and, const int m_or, const int m_not);
	void mr_lcs();
	void COut(bool,char);
	void Recurison(std::map<std::string, Node>&, std::string, int, bool&);
private:
	std::map<std::string, Node>Circuit;
	int Restrict_AND_Resource;
	int Restrict_OR_Resource;
	int Restrict_NOT_Resource;
	int MaxtimeInASAP;
	int outputMaxtime;
	std::ifstream ifile;
	std::string projectname;
	std::vector<std::string>inputN;
	std::vector<std::string>outputN;
};
