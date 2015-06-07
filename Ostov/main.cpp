#include <iostream>
#include <fstream>
#include <algorithm>
#include <queue>
#include <vector>

int n;
int** mtrx;
bool* used;
bool* ostov;

std::queue<int> que;
std::vector<std::vector<int>> ost;

void make_ostov(int start){
	for (int i = 0; i < n; i++){
		used[i] = false;
	}
	que.push(start);
	used[start] = true;
	ostov[start] = true;
	while (!que.empty()){
		int v = que.front();
		que.pop();
		used[v] = true;
		for (int i = 0; i < n; i++){
			if (mtrx[v][i]){
				int to = i;
				if (!used[to]){
					if (!ostov[to]){
						ostov[to] = true;
						ost.at(v).push_back(to);
						que.push(to);
					}
				}
			}
		}
	}
}

int main(int** argv, int argc){

	std::ifstream in("input.txt");
	std::ofstream out("output.txt");

	in >> n;

	mtrx = new int*[n];
	for (int i = 0; i < n; i++){
		mtrx[i] = new int[n];
	}

	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++){
			in >> mtrx[i][j];
		}
	}
	in.close();
	used = new bool[n];
	for (int i = 0; i < n; i++){
		used[i] = false;
	}
	ostov = new bool[n];
	for (int i = 0; i < n; i++){
		ostov[i] = false;
	}

	ost = std::vector<std::vector<int>>(n,std::vector<int>());
	
	make_ostov(0);
	
	int count = 0;
	for (int i = 0; i < n; i++){
		count += ost.at(i).size();
		if (!ostov[i]){
			out << -1;
			out.close();
			return 0;
		}
	}
	out << count << std::endl;
	for (int i = 0; i < n; i++){
		if (!ost.at(i).empty()){
			for (int j = 0; j < ost.at(i).size(); j++){
				out << (i + 1) << " " << ost.at(i).at(j)+1 << std::endl;
			}
		}
	}
	return 0;
}