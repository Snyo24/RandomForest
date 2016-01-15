#include "RandomForest.h"

#include <iostream>
#include <vector>

using namespace std;
using namespace rf;

int main() {
	Node n;
	Tree t;
	t.root = n;


	const int aa[] = {1};
	vector<float> v(aa, aa+1);
	const int bb[] = {1,3};
	vector<float> v2(bb, bb+2);
	Pair x(v, 0);
	Pair y(v2, 1);
	Pair z(v2, 0);
	Pair a(v, 1);
	Pair b(v2, 1);
	Pair c(v, 1);
	Pair d(v2, 0);
	Pair e(v, 0);
	n.push(x);
	n.push(y);
	n.push(z);
	n.push(a);
	n.push(b);
	n.push(c);
	n.push(d);
	n.push(e);



	cout << n << endl;
	cout << n.isLeaf() << endl;
	bool tf[8] = {true, false, true, false, true, true, false, false};
	cout << n.infoGain(tf) << endl;
	n.split(tf);
	cout << n << endl;
	cout << n.isLeaf() << endl;
	return 0;
}