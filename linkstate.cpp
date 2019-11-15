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
  int distanceFromSrc= INT_MAX;
  int viaNode;

};

void printList(vector<int> v){
  cout << "[";
  for (int i=0; i< v.size(); i++){
    cout<< "\'"<<v.at(i)<<"\'";
    if (i != v.size()-1)
      cout<<",";
    }
    cout <<"]"<<endl;
  }



int existsIn(vector<int> nodes, int nodeId){
  for (int i=0; i< nodes.size(); i++){
    if ( nodes.at(i) == nodeId){
      return i;
    }
  }
  return -1;

}
int generateGraph(){
  string line;
  ifstream graphData ("Adj1.txt");
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
      // cout << nodeA<< " " << nodeB <<" "<< lengthAB<<endl;

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
        // cout << "Node: "<< temp.id << "created!"<<endl;

      }
      else{
        //cout<<"Node " <<foundIndex << " was found!"<<endl;
        graph.at(foundIndex).neighbors.insert(pair<int,int>(stoi(nodeB), stoi(lengthAB)));
      }


    }
    for (int i=0; i< graph.size(); i++){
      // cout << "Node " << graph.at(i).id << "------"<<endl;
      map<int, int>:: iterator itr;
      for (itr = graph.at(i).neighbors.begin(); itr!=graph.at(i).neighbors.end(); ++itr){
        //cout << "Neighbor: " << itr-> first<< " Distance: "<< itr->second<<endl;
      }
    }
  }
  else{
    cout <<"Unable to open file."<<endl;
  }
  return 0;
}

int dijkstra(int source, int dest){
  vector<int> visited;
  vector<int> unvisited;
  int shortestPath=0;
  int currentNode;
  int tempShortestPath=INT_MAX;

  //populate unvisited list
  for (int i=0; i< graph.size(); i++){
    unvisited.push_back(i);
  }
  graph.at(source).distanceFromSrc=0;

  int leastCostNode;
  int leastCost;
  currentNode= source;
  //visited.push_back(currentNode);
  map<int, int>:: iterator itr;
  int key;
  int value;

  do{
    shortestPath= graph.at(currentNode).distanceFromSrc;
    leastCost=INT_MAX;
    int anyUnvisitedNeighborsLeft=0;
    cout << "Visited: ";
    printList(visited);
    cout <<endl<<"Unvisited: ";
    printList(unvisited);
    cout<<endl;

    cout <<"Current node: " << currentNode <<endl;
    cout <<"Current shortest path: "<<shortestPath<<endl;

    for (itr = graph.at(currentNode).neighbors.begin(); itr!=graph.at(currentNode).neighbors.end(); ++itr){
      key = itr->first;
      value = itr->second;
      cout << "Neighbor: " << key<< " Distance: "<< value<<endl;

      if( (shortestPath+value) < graph.at(key).distanceFromSrc){
        cout<<"Edge path length " << key << " path distance " << (shortestPath+value)<<endl;
        graph.at(key).distanceFromSrc = shortestPath+value;
        graph.at(key).viaNode = currentNode;
      }

      if (value < leastCost && existsIn(visited, key)==-1){
        leastCostNode = key;
        leastCost = value;
        anyUnvisitedNeighborsLeft=1;
        //cout << "New cheap node: " << leastCostNode << " of distance: "<<leastCost<<endl;
      }

    }
    if(anyUnvisitedNeighborsLeft){
      cout <<"Least cost node: "<<leastCostNode<<endl;
      //shortestPath+= leastCost;
      vector<int>::iterator ptr = unvisited.begin();
      advance(ptr, existsIn(unvisited,currentNode));
      unvisited.erase(ptr);
      visited.push_back(currentNode);
      currentNode = leastCostNode;
    }
    else{
      visited.push_back(currentNode);
      unvisited.clear();
      cout << "Visited: ";
      printList(visited);
      cout <<endl<<"Unvisited: ";
      printList(unvisited);
      cout<<endl;

    }
    for (int i=0; i< graph.size(); i++){
      if(graph.at(i).distanceFromSrc< tempShortestPath && graph.at(i).distanceFromSrc>0){
        tempShortestPath = graph.at(i).distanceFromSrc;
        shortestPath+= tempShortestPath;
      }
      cout<< "Node: "<<graph.at(i).id << " SP: "<<graph.at(i).distanceFromSrc << " via: "<<graph.at(i).viaNode<<endl;
    }


    cout << "----------------------"<<endl;
  }
  while (unvisited.size() >0);


return 0;

void generateRoutingTable(){

  return;
}
}
int main(){
  generateGraph();
  dijkstra(0,2);
  return 0;
}
