#include<fstream>
#include<sstream>
#include<iostream>
#include<queue>
#include "puzzle.h"
using namespace std;

int nLine = 0;
int nLineLimit = -1;
int nMove[COUNT];
int nMoveLimit[COUNT];



void SolveManually(puzzle pz);
void SolveAutomatically(puzzle pz);

DIRECTION reverse(DIRECTION d);
int stoi(string str);

int main() {
	//Input file
	ifstream inputFile("problems.txt", ifstream::binary);
	string line = "";

	while(getline(inputFile, line)){
		//comment out
		if (line[0] == '%') {}
		//line 0
		else if (nLine == 0) {
			string limit = "";
			istringstream stream(line);
			int n = 0;
			while (getline(stream, limit, ' ')) {
			  nMoveLimit[n++] = stoi(limit);
			}
		}
		//line 1
		else if (nLine == 1) {
			nLineLimit = stoi(line);
		}
		//line 2.3...
		else {
			int n = 0;
			string tmp = "";
			istringstream stream(line);
			int stageWidth, stageHeight;
			while (getline(stream, tmp, ',')) {
				//word 1
				if (n == 0) stageWidth = stoi(tmp);
				//word 2
				else if (n == 1) stageHeight = stoi(tmp);
				//word 3
				else {
					puzzle pz(stageWidth, stageHeight, tmp);
					SolveAutomatically(pz);
				}
				n++;
			}
		}
		for (int n = 0; n < COUNT; n++) {
			if (nMove[n] >= nMoveLimit[n]) return nLine;
		}
		nLine++;
	}
}

//Solve puzzle manuall
void SolveManually(puzzle pz) {
	pz.draw();
	int d = 0;
	while (!pz.check()) {
		cout << "UP:0, DOWN:1, LEFT:2, RIGHT:3" << endl;
		cin >> d;
		if (d < 0 || 3 < d) cout << "Invalid Input." << endl;
		else if (nMove[d] < nMoveLimit[d]) {
			pz.move(static_cast<DIRECTION>(d));
			nMove[d]++;
		}
		else {
			cout << "Over limit." << endl;
		}
		pz.draw();
	}
	cout << "Clear." << endl;
}

//Solve puzzle automatically
void SolveAutomatically(puzzle pz) {
	bool flg = false;
	queue<node*> qu;

	node* p = new node(0, NULL, pz);
	qu.push(p);

	int threshold = (*p).pz.EuclidDistanceFromAnswer();

	while (!flg && !qu.empty()) {
		node* q = qu.front();
		qu.pop();

		for (int i = 0; i < COUNT; i++) {
			DIRECTION d = static_cast<DIRECTION>(i);
			puzzle* pzChild = new puzzle((*q).pz.stageWidth, (*q).pz.stageHeight, (*q).pz.panels);

			if ((*q).id > 0 && ((*q).id - 1) % 4 == reverse(d)) continue;
			if ((*pzChild).move(d)) {
				int euc = (*pzChild).EuclidDistanceFromAnswer();
				if (euc > threshold) continue;
				qu.push(new node((*q).id * 4 + i + 1, q, *pzChild));
				//(*pzChild).draw();
				if ((*pzChild).check()) {
					flg = true;
					break;
				}
			}
		}
	}

	p = qu.back();
	while ((*p).parent != NULL)
	{
		int d = ((*p).id - 1) % 4;
		nMove[d]++;
		p = (*p).parent;
	}
}

DIRECTION reverse(DIRECTION d) {
	switch (d) {
	case UP:
		return DOWN;
	case DOWN:
		return UP;
	case LEFT:
		return RIGHT;
	case RIGHT:
		return LEFT;
	default:
		return STAY;
	}
}

int stoi(string str)
{
    int ret;
    stringstream ss;
    ss << str;
    ss >> ret;
    return ret;
}
