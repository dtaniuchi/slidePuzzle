#include<cstdlib>
#include<fstream>
#include<sstream>
#include<iostream>
using namespace std;

enum DIRECTION { UP, DOWN, LEFT, RIGHT, COUNT, STAY };
const string Answer = "123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

class puzzle {
public:
	int stageWidth;
	int stageHeight;
	string panels;
	int blank;
public:
	//コンストラクタ
	puzzle() { stageWidth = 0; stageHeight = 0; panels = ""; blank = 0; }
	puzzle(int w, int h, string ps) {
		stageWidth = w;
		stageHeight = h;
		panels = ps;
		blank = 0;
		while (blank < w * h && 
			ps[blank] != '0') 
			blank++;
	}

	//デストラクタ
	~puzzle() {
	}

	void swap(int i, int j) {
		if (i >= stageWidth * stageHeight || j >= stageWidth * stageHeight) return;
	}

	//blankを指定した位置に移動
	void moveBlankAt(int idx) {
		if (idx >= stageWidth * stageHeight) return;
		while (blank % stageWidth < idx % stageWidth) move(UP);
		while (blank % stageWidth > idx % stageWidth) move(DOWN);
		while (blank / stageWidth < idx / stageWidth) move(RIGHT);
		while (blank / stageWidth > idx / stageWidth) move(LEFT);
	}

	//空白パネルをd方向のパネルと入れ替える
	bool move(DIRECTION d) {
		int idx = blank;
		switch (d) {
		case UP:
			if (blank >= stageWidth) {
				//nMove[UP]++;
				idx -= stageWidth;
			}
			break;
		case DOWN:
			if (blank < stageWidth * stageHeight - stageWidth) {
				//nMove[DOWN]++;
				idx += stageWidth;
			}
			break;
		case LEFT:
			if (blank % stageWidth != 0) {
				//nMove[LEFT]++;
				idx -= 1;
			}
			break;
		case RIGHT:
			if (blank % stageWidth != stageWidth - 1) {
				//nMove[RIGHT]++;
				idx += 1;
			}
			break;
		default:
		  break;
		}
		char c = panels[idx];
		if (c != '0' && c != '=') {
			panels[blank] = c;
			blank = idx;
			panels[idx] = '0';
			return true;
		}
		else return false;
	}

	//整列しているかチェック
	bool check()
	{
		if (panels.size() == 0) return false;
		for (int i = 0; i < stageWidth * stageHeight; i++) {
			if (i == stageWidth  * stageHeight - 1) {
				if (panels[i] != '0') return false;
			}
			else if (panels[i] != '=' && panels[i] != Answer[i])
				return false;
		}
		return true;
	}

	//文字cが正しい場所にあるかチェック
	bool check(char c) {
		if (panels.find(c) == string::npos) return true;
		if (c == '=' || panels.find(c) == Answer.find(c)) return true;
		else return false;
	}

	//描画
	void draw() {
		if (panels.size() != stageWidth * stageHeight + 1) return;
		for (int h = 0; h < stageHeight; h++) {
			for (int w = 0; w < stageWidth; w++) {
				char c = panels[w + h * stageWidth];
				if (c == '0') c = ' ';
				cout << c << " ";
			}
			cout << endl;
		}
	}

	int EuclidDistanceFromAnswer() {
		int d = 0;
		for (int i = 0; i < stageWidth * stageHeight - 1; i++) {
			if (panels[i] == '=') continue;
			int x, y;
			int answerX, answerY;
			char c = Answer[i];
			answerX = i % stageWidth + 1;
			answerY = i / stageWidth + 1;
			for (int j = 0; j < stageWidth * stageHeight; j++) {
				if (panels[j] == c) {
					x = j % stageWidth + 1;
					y = j / stageWidth + 1;
					break;
				}
			}
			d += abs(x - answerX) + abs(y - answerY);
		}
		return d;
	}
};

class node {
public:
	int id;
	node* parent;
	puzzle pz;
public:
	node(int i, node* prt, puzzle p) {
		id = i;
		parent = prt;
		pz = p;
	}
};

