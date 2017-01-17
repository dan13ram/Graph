#include "graph.cpp"

using namespace std;

int main(){
        Graph *temp=new Graph(true);
        temp->addvertex("a");
        temp->addvertex("b");
        temp->addvertex("c");
        temp->addvertex("d");
        temp->addvertex("e");
        temp->addvertex("f");
        temp->addvertex("g");
        temp->addvertex("h");
        temp->addedge("a","b",20);
        temp->addedge("a","d",80);
        temp->addedge("a","g",90);
        temp->addedge("b","f",10);
        temp->addedge("c","f",50);
        temp->addedge("c","h",20);
        temp->addedge("c","d",10);
        temp->addedge("d","g",20);
        temp->addedge("e","b",50);
        temp->addedge("e","g",30);
        temp->addedge("f","c",10);
        temp->addedge("f","d",40);
        temp->addedge("g","a",20);
        map<string,pair<int,string> > distance = temp->Dijkstra("a");
        cout<<"Distance from 'a' to 'a' is "<<distance["a"].first<<" and parent is '"<<distance["a"].second;
        cout<<"'"<<endl;
        cout<<"Distance from 'a' to 'b' is "<<distance["b"].first<<" and parent is '"<<distance["b"].second;
        cout<<"'"<<endl;
        cout<<"Distance from 'a' to 'c' is "<<distance["c"].first<<" and parent is '"<<distance["c"].second;
        cout<<"'"<<endl;
        cout<<"Distance from 'a' to 'd' is "<<distance["d"].first<<" and parent is '"<<distance["d"].second;
        cout<<"'"<<endl;
        cout<<"Distance from 'a' to 'e' is "<<distance["e"].first<<" and parent is '"<<distance["e"].second;
        cout<<"'"<<endl;
        cout<<"Distance from 'a' to 'f' is "<<distance["f"].first<<" and parent is '"<<distance["f"].second;
        cout<<"'"<<endl;
        cout<<"Distance from 'a' to 'g' is "<<distance["g"].first<<" and parent is '"<<distance["g"].second;
        cout<<"'"<<endl;
        cout<<"Distance from 'a' to 'h' is "<<distance["h"].first<<" and parent is '"<<distance["h"].second;
        cout<<"'"<<endl;
        return 0;

}
