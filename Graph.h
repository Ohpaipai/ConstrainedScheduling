#pragma once
#include<iostream>
#include<string>
#include<map>
#include<fstream>
#include<vector>
#include<set>
#include<sstream>
#include<unordered_set>
#define Operationtime 1
const int LEN_LENGTH = 99999;
//Opreation define
enum Operation{ 
	_null,
	_add,
	_or,
	_not,
	_over,
};




//Node
typedef struct Myclass{
	std::string name;
	Operation stats;
	std::vector<Myclass>Component;
	void initial(std::string _name, Operation _stats) {
		name = _name;
		stats = _stats;
	};
}Node;

typedef struct Myclass2 {
	Node node;
	int level;
	void initial(Node _node,int _level) {
		node = _node;
		level = _level;
	};
}Tree;


class Graph
{
public:
	Graph();
	Graph(std::string _filename);
	~Graph();
	void MakeGraph();
private:
	std::ifstream ifile;
	std::string filename;
	std::vector<Tree>nodus;
	int Maxtime;
	int _addNumber;
	int _notNumber;
	int _orNumber;
	std::string Graghname;
};

