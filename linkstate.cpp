#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <math.h>
#include <bitset>
#include <map>
#include <list>
#include <vector>

using namespace std;
int NUMNODES=0;
struct Node;
vector<Node> graph;

struct Node
{
  int id;
  map<int, int> neighbors;

};
int generateGraph(){
  string line;
  ifstream graphData ("Adj.txt");
  string numNodes;
  if(graphData.is_open()){
    getline(graphData, numNodes);
    NUMNODES= stoi(numNodes);
    cout<< "NUMBEROFNODES: " << NUMNODES <<endl;
    while(getline(graphData,line)){
      struct Node temp;
      string nodeA;
      string nodeB;
      string lengthAB;
      stringstream ss;
      int dne=1;
      int foundIndex;

      ss<< line;
      ss>> nodeA >> nodeB >> lengthAB;
      cout << nodeA<< " " << nodeB <<" "<< lengthAB<<endl;

      //cout<< "Graph size: "<< graph.size()<<endl;
      for (int i=0; i< graph.size(); i++){
        //cout<< "Searching node " << graph.at(i).id<<endl;
        if (graph.at(i).id == stoi(nodeA)){
          dne=0;
          foundIndex = i;
        }
      }
      if(dne){
      //  cout <<"Creating node: "<< nodeA<<endl;
        temp.id= stoi(nodeA);
        temp.neighbors.insert(pair<int,int>(stoi(nodeB), stoi(lengthAB)));
        graph.push_back(temp);
        cout << "Node: "<< temp.id << "created!"<<endl;

      }
      else{
        cout<<"Node " <<foundIndex << " was found!"<<endl;
        graph.at(foundIndex).neighbors.insert(pair<int,int>(stoi(nodeB), stoi(lengthAB)));
      }


    }
    for (int i=0; i< graph.size(); i++){
      cout << "Node " << graph.at(i).id << "------"<<endl;
      map<int, int>:: iterator itr;
      for (itr = graph.at(i).neighbors.begin(); itr!=graph.at(i).neighbors.end(); ++itr){
        cout << "Neighbor: " << itr-> first<< " Distance: "<< itr->second<<endl;
      }
    }
  }
  else{
    cout <<"Unable to open file."<<endl;
  }
  return 0;
}
int main(){
  generateGraph();
  return 0;
}
