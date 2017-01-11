#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <queue>
#include <vector>
#include <algorithm>
#include <climits>
#include "graph.h"

using namespace std;

/* function to print all neighbours of a vertex */
void Vertex::printNeighbours(){
        vector<pair<int, Vertex *> >::iterator i;
        for(i = adj.begin(); i != adj.end(); ++i){
                static int k=0;
                cout<<++k<<": "<<i->second->name<<endl;
        }
}
        
/* function to return the vertex number from name of vertex */
unsigned int Graph::getIndex(const string& temp){
        for(unsigned int i=0;i<vertices.size();++i){
                if(vertices[i]==temp) return i;
        }
        return numV;
}

/* simply adds a new vertex to graph */
void Graph::addvertex(const string &name){
        map<string, Vertex *>::iterator itr=work.begin();
        itr=work.find(name);                    //checks if the vertex name is already being used.
        if(itr==work.end()){                    //if not then a new vertex is made and 
                Vertex *v = new Vertex(name);   //and added to our vertex map
                work[name]=v;
                vertices.push_back(name);
                numV++;
                return;
        }
        cout<<"\nVertex already exists!";
}

/* adds a new edge to the graph.
   if the graph is directed, then the edge is added in both the vertices' 
   adjacency lists.
   else only in one of them. */
void Graph::addedge(const string& from, const string& to, double cost){
        map<string, Vertex *>::iterator itr=work.begin();
        Vertex *f=((itr=work.find(from))->second);                 // finds Vertex* from name of vertex
        if(itr==work.end()){
                cout<<"\n Vertex '"<<from<<"' doesn't exist!";
                return;
        }
        Vertex *t=((itr=work.find(to))->second);                   // finds Vertex* from name of vertex
        if(itr==work.end()){
                cout<<"\n Vertex '"<<to<<"' doesn't exist!";
                return;
        }
        edges.push_back(new Edge(f, t, cost));                     //add edge to vector of edges
        pair<int,Vertex *> edge = make_pair(cost,t);               //make and add edge to adjacency list.
        f->adj.push_back(edge);
        if(directed == false ) {                                   // checks if graph is directed.
                edge = make_pair(cost,f);                          // if it is not then edge is added to both adjacency list.
                t->adj.push_back(edge);
        } 
}

/* implements Breadth First Search on the graph 
   and prints out the vertices in the order found. */
void Graph::BFS(const string& s){
        queue<string> q;
        bool *visited = new bool[numV];
        for(unsigned int i = 0; i < numV; i++) visited[i] = false; 
        visited[getIndex(s)]=true;
        q.push(s);
        vector<pair<int, Vertex * > >::iterator i;
        while(!q.empty()){
                string str=q.front();
                cout<<str<<"->";
                q.pop();
                
                for(i = work[str]->adj.begin(); i != work[str]->adj.end(); ++i){
                        if(!visited[getIndex(i->second->name)]){
                                visited[getIndex(i->second->name)] = true;
                                q.push(i->second->name);
                        }
                }
        }
        cout<<"end";
}

        map<Vertex * , Vertex * > PARENT;
        map<Vertex * , int> RANK;
        
        Vertex* find(Vertex *vertex) {
                if (PARENT[vertex] == vertex) 
                        return PARENT[vertex];
                else
                        return find(PARENT[vertex]);    
        }
/* implements Kruskal's algo and 
   prints out all the edges in the Minimum Spanning tree. */
void Graph::MSTKruskal() {
        
        vector<Edge*> res;
        
        for (unsigned int i;i<vertices.size();++i) {
                Vertex* c=work[vertices[i]];
                PARENT[c] = c;
                RANK[c] = 0;
        }

        sort(edges.begin(), edges.end(), [](Edge* x, Edge* y) {return x->weight < y->weight;});   // O(E*log(E))
        
        for (Edge* e : edges) {         // O(E)
                Vertex *root1 = find(e->vertex1);  // O(E) worst case
                Vertex *root2 = find(e->vertex2);
                if (root1 != root2) {
                        res.push_back(e);
                        if (RANK[root1] > RANK[root2]) {
                                PARENT[root2] = root1;
                                RANK[root1]++;
                        } else {
                                PARENT[root1] = root2;
                                RANK[root2]++;
                        }
                }
        }

        for (Edge* e : res) {
                cout << e->vertex1->name << " -- " << e->vertex2->name << "  " << e->weight << endl;
        }
}

/* implements Prim's algo and 
   prints out all the edges in the Minimum Spanning tree. */
void Graph::MSTPrim(string root) {
        map<Vertex *, Vertex *> res;
        map<Vertex *, Vertex *> PARENT;
        map<Vertex *, int> KEY;

        for (auto c : vertices) {
                PARENT[work[c]] = NULL;
                KEY[work[c]] = INT_MAX;
        }
        KEY[work[root]] = 0;
        vector<string> Q = vertices; 

        while (!Q.empty()) {    // O(V)
                string temp = *std::min_element(Q.begin(), Q.end(), [&](string x,string y) {return KEY[work[x]] < KEY[work[y]];});  // O(v)
                Vertex *u= work[temp];
                vector<string>::iterator itr = remove(Q.begin(), Q.end(), temp);  // O(V)
                Q.erase(itr, Q.end());  // erase() following remove() idiom
                if (PARENT[u] != NULL) {
                        res[u] = PARENT[u];   // This is one edge of MST
                }
        
                for(pair<int,Vertex *> v : u->adj ){
                        if (find(Q.begin(),Q.end(),(v.second)->name)!= Q.end()){
                                if(v.first < KEY[v.second]){
                                        PARENT[v.second] = u;
                                        KEY[v.second] = v.first;
                                }
                        }
                }

        }

        for (auto e : res) {
                cout << (e.first)->name << " -- " << (e.second)->name << endl;
        }
}

/* implements Dijkstra's algo and 
   returns the shortes distance (vector) to all other vertices 
   from the start vertex. */
map<string,pair<int,string> > Graph::Dijkstra(string start) {
        map<string,int > weights;
        map<string,string > parents;
        for( unsigned int i=0;i<vertices.size();++i){
                weights[vertices[i]]=INT_MAX;
                parents[vertices[i]]="";
        }
        
        priority_queue<pair<int,Vertex *>, vector<pair<int,Vertex *> >,CompareGreater > Q ;
        
        weights[start] = 0;

        Q.push(make_pair(0,work[start]));
        pair<int,Vertex *> currentNode;
        while (!Q.empty()) {
                currentNode = Q.top();
                Q.pop();
                if (currentNode.first <= weights[(currentNode.second)->name]) {
                        for(pair<int,Vertex *> v : (currentNode.second)->adj ){
                                if (weights[(v.second)->name] > weights[(currentNode.second)->name] + v.first) {
                                        parents[(v.second)->name] = (currentNode.second)->name;
                                        weights[(v.second)->name] = weights[(currentNode.second)->name] + v.first;
                                        Q.push(make_pair(weights[(v.second)->name],v.second));
                                }
                        }
                }
        }
        map<string,pair<int,string> > result;
        for( unsigned int i=0;i<vertices.size();++i){
                result[vertices[i]]=make_pair(weights[vertices[i]],parents[vertices[i]]);
        }
        return result;
}

