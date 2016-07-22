
struct Edge {
	char vertex1;
	char vertex2;
	int weight;
	Edge(char v1, char v2, int w):vertex1(v1), vertex2(v2), weight(w) {}
};

struct Graph {
	vector<char> vertice;
	vector<Edge> edges;
	vector< pair<char, Edge> > adjacent(char u) {
		vector< pair<char, Edge> > res;
		for (Edge e : edges) {
			if (e.vertex1 == u) {
				res.push_back( make_pair(e.vertex2, e));
			} else if (e.vertex2 == u) {
				res.push_back( make_pair(e.vertex1, e));
			}
		}
		return res;
	}
};



void prim(Graph& g, char root) {
	unordered_map<char, char> res;
	unordered_map<char, char> PARENT;
	unordered_map<char, int> KEY;

	for (auto c : g.vertice) {
		PARENT[c] = '\0';
		KEY[c] = INT_MAX;
	}
	KEY[root] = 0;
	vector<char> Q = g.vertice; 

	while (!Q.empty()) {    // O(V)
		char u = *std::min_element(Q.begin(), Q.end(), [&](char x, char y) {return KEY[x] < KEY[y];});  // O(v)
		vector<char>::iterator itr = remove(Q.begin(), Q.end(), u);  // O(V)
		Q.erase(itr, Q.end());  // erase() following remove() idiom
		if (PARENT[u] != '\0') {
			res[u] = PARENT[u];   // This is one edge of MST
		}
		vector< pair<char, Edge> > adj = g.adjacent(u);   // O(E)
		for (pair<char, Edge> v : adj) {
			if (find(Q.begin(), Q.end(), v.first) != Q.end()) {   // O(V)
				if (v.second.weight < KEY[v.first]) {
					PARENT[v.first] = u;
					KEY[v.first] = v.second.weight;
				}
			}
		}
	}

	for (auto e : res) {
		cout << e.first << " -- " << e.second << endl;
	}
}

int main() {

	Graph g;

	char t[] = {'a', 'b', 'c', 'd', 'e', 'f'};
	g.vertice = vector<char>(t, t + sizeof(t)/sizeof(t[0]));

	g.edges.push_back(Edge('a', 'b', 4));
	g.edges.push_back(Edge('a', 'f', 2));
	g.edges.push_back(Edge('f', 'b', 3));
	g.edges.push_back(Edge('c', 'b', 6));
	g.edges.push_back(Edge('c', 'f', 1));
	g.edges.push_back(Edge('f', 'e', 4));
	g.edges.push_back(Edge('d', 'e', 2));
	g.edges.push_back(Edge('d', 'c', 3));

	prim(g, 'a');

	return 0;
}


