#include "Manager.h"
using namespace std;

vector<string> split(string& str, const string& deli) { //String Split Function to Recognition of Commmand
	vector<string> cuts;
	size_t pos = 0;
	string cut;
	while ((pos = str.find(deli)) != string::npos) {
		cut = str.substr(0, pos);
		cuts.push_back(cut);
		str.erase(0, pos + deli.length());
	}
	cuts.push_back(str);

	if (cuts[cuts.size() - 1].length() == 0) {
		cuts.pop_back();
	}

	return cuts;
}

Manager::Manager()
{
	graph = nullptr;
	fout.open("log.txt", ios::app);
	load = 0;
}

Manager::~Manager()
{
	if(load)
		delete graph;
	fout.close();
}

void Manager::run(const char* command_txt){
	ifstream fin;
	fin.open(command_txt);
		
	if(!fin)
	{
		fout<<"[ERROR] command file open error!"<<endl;
		return;
	}

	string buf;

	/*
	All Function returns existance of error
	return 1; or return true; means "expected runtime error"
	*/
	while(getline(fin, buf))
	{
		int result = 0;
		vector<string> cuts;
		cuts = split(buf, "\t");
		if (cuts[0] == "LOAD") {
			if (cuts.size() != 2) result = 100;
			else {
				char temp[128];
				strcpy(temp, cuts[1].c_str());
				result = 100 * LOAD(temp);
			}
		}
		else if (cuts[0] == "PRINT") result = 200 * PRINT();
		else if (cuts[0] == "BFS") {
			if (cuts.size() != 2) result = 300;
			else result = 300 * mBFS(stoi(cuts[1]));
		}
		else if (cuts[0] == "DFS") {
			if (cuts.size() != 2) result = 400;
			else result = 400 * mDFS(stoi(cuts[1]));
		}
		else if (cuts[0] == "DFS_R") {
			if (cuts.size() != 2) result = 500;
			else result = 500 * mDFS_R(stoi(cuts[1]));
		}
		else if (cuts[0] == "KRUSKAL") result = 600 * mKRUSKAL();
		else if (cuts[0] == "DIJKSTRA") {
			if (cuts.size() != 2) result = 600;
			else result = 600 * mDIJKSTRA(stoi(cuts[1]));
		}
		else if (cuts[0] == "BELLMANFORD") {
			if (cuts.size() != 3) result = 700;
			else result = 700 * mBELLMANFORD(stoi(cuts[1]), stoi(cuts[2]));
		}
		else if (cuts[0] == "FLOYD") result = 800 * mFLOYD();
		else if (cuts[0] == "EXIT") {
			fout << "=====EXIT=====" << endl;
			fout << "Success" << endl;
			fout.close();
			exit(0);
		}
		// print errorcode when error exist
		if (result) printErrorCode(result);
	}	
	fin.close();
}

bool Manager::LOAD(char* filename)
{
	return 1;
}

bool Manager::PRINT()
{
	if(graph->printGraph())
		return 1;
	return 0;
}

bool Manager::mBFS(int vertex)
{
	return 1;
}

bool Manager::mDFS(int vertex)
{
	return 1;
}


bool Manager::mDFS_R(int vertex)
{
	return 1;
}

bool Manager::mDIJKSTRA(int vertex)
{
	return 1;
}

bool Manager::mKRUSKAL()
{
	return 1;
}

bool Manager::mBELLMANFORD(int s_vertex, int e_vertex)
{
	return 1;
}

bool Manager::mFLOYD()
{
	return 1;
}

void Manager::printErrorCode(int n)
{
	fout<<"======== ERROR ========"<<endl;
	fout<<n<<endl;
	fout<<"======================="<<endl;
}
