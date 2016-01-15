#ifndef RANDOMFOREST_H_
#define RANDOMFOREST_H_

#include <iostream>
#include <vector>

using namespace std;

namespace rf {
	// Constants
	const int MAX_CLASS = 10;
	const float EPSILON = 0.0000001;

	// Definition of type "Pair"
	typedef pair<vector<float>, int> Pair;

	// Override <<
	inline ostream& operator<<(ostream& os, const Pair& p) {
		os << "([";
		for(vector<float>::const_iterator i=p.first.begin(); i!=p.first.end()-1; ++i)
			os << *i << ' ';
	    return os << p.first.back() << "], " << p.second << ')';
	}

	// Declaration of class "Node"
	class Node {
		Node *left;
		Node *right;
		vector<Pair> content;
		// Plz friend class Tree 

	 public:
		Node();
		void split(const bool* l);
		float infoGain(const bool* l);
		int size();
		bool isLeaf();
		void push(Pair x);
		~Node();

		// Override <<
		friend ostream& operator<<(ostream& os, const Node& n) {
			if(n.left && n.right)
				os << '{' << *n.left << ',' << endl << *n.right << '}';

			else {
				for(vector<Pair>::const_iterator i=n.content.begin(); i!=n.content.end(); ++i) {
					os << *i;
					if(i!=n.content.end()-1)
						os << "," << endl;
				}
			}
		    return os;
		}

		// Override []
		Pair& operator[](int idx) {
			return this->content[idx];
		}
	};

	// Declaration of class "Tree"
	class Tree {

	 public:
		Node root;
		Tree();
		~Tree();
	};

	// Declaration of class "Forest"
	class Forest {
		vector<Tree> trees;

	 public:
		Forest(int n, int d);
		~Forest();
	};
}

#endif // RANDOMFOREST_H_