#ifndef _GRAPH_H
#define _GRAPH_H

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <queue>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

/* Class to store Vertices in the graph.
   Each vertex has its own adjacency list to store all the edges 
   originating from that particular vertex.
   Each vertex has a name (string ).*/
class Vertex{
        public:
        vector<pair<int,Vertex *> > adj; //cost of edge, destination vertex
        string name;                     //name of the vertex
        Vertex(string s){                //constructor
                name=s;
        }
        void printNeighbours();          //prints all neighbours of the vertex
};


/* Compare class for using in priority queues. */
class CompareGreater {
    public:
       bool operator()(const pair<int,Vertex *> x,const pair<int,Vertex *> y){ //returns the pair with the greater value (weight, here)
                return (x.first > y.first);                                    //each pair is actually weight of edge and end point of edge
        }
};

/* struct to store edges in the graph. */

struct Edge {
        Vertex *vertex1;                        //initial vertex
        Vertex *vertex2;                        //final vertex
        int weight;                             //cost/weight of the edge
	Edge(Vertex *v1, Vertex *v2, int w):vertex1(v1), vertex2(v2), weight(w) {}
};


/* Our main class : Graph class
   Stores a graph.
   Implements Kruskal's , Prim's and Dijkstra's algorithms.
   Our graph can be weighted and directed. */
class Graph{
        bool directed;                                  //boolean for checking if graph is directed or not
        unsigned int numV;                              //number of vertices
        vector<string> vertices;                        //names of all vertices
        vector<Edge*> edges;                            //stores all edges in graph
        public:
        Graph(bool temp = false){
                numV=0;
                directed = temp;
        }
        map<string, Vertex *> work;                     //stores the map from name of vertex to Vertex class
        unsigned int getIndex(const string&);           //returns the index from name of vertex. Index refers to vertex number in the graph
        void MSTPrim(string );                          //implements Prim's algo
        void MSTKruskal();                              //implements Kruskal's algo
        map<string,pair<int,string> > Dijkstra(string start);//implements Dijkstra's algo
        void BFS(const string& );                       //implements BFS
        void addvertex(const string&);                  //adds a new vertex to graph
        void addedge(const string& from, const string& to, double cost);//adds a new edge to graph
};

#endif // _GRAPH_H
