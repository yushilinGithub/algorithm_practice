#include <functional>
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <algorithm>
struct GraphEdge {
  int from;
  int to;
  int weight;
  GraphEdge(){};
  GraphEdge(int from_,int to_,int weight_):from(from_),to(to_),weight(weight_){}
  bool operator>(GraphEdge e) const { return e.weight > weight; }
};
class Graph {
private:
  int numEdge=0;

public:
  int vertexN;
  std::vector<std::list<GraphEdge> > graph;
  std::vector<GraphEdge> ges;
  Graph(int v) {
    vertexN = v;
	graph.resize(v);
  }
  void addEdge(GraphEdge edge){
	  int from = edge.from;
	  int to = edge.to;
	  graph[from].push_back(edge);
	  ges.push_back(edge);
  }
};
class Disjointset{
	public:
		std::vector<int> parent;
		std::vector<int> rank;
		Disjointset(int n){
			rank.assign(n,0);
			for(int i=0;i<n;i++){
				parent.push_back(i);
			}
		}
};
int find(Disjointset dsj,int x){
	while (dsj.parent[x]!=x) {
	    x = dsj.parent[x];
	}
	return dsj.parent[x];
}
void Union(Disjointset subset,int x,int y){
	int parentx = find(subset,x);
	int parenty = find(subset, x);
	if(parentx==parenty){
		return;
	}
	if (subset.rank[parentx]<subset.rank[parenty]) {
		subset.parent[parentx] = subset.parent[parenty];
	}
	else if (subset.rank[parentx]>subset.rank[parenty]) {
	    subset.parent[parenty] = subset.parent[parentx];
	}
	else if(subset.rank[parentx]>subset.rank[parenty]){
		subset.parent[parentx] = subset.parent[parenty];
		subset.rank[parentx]++;
	}

}
int minSpanTree(Graph* graph){
	
	std::sort(graph->ges.begin(),graph->ges.end(),std::greater<GraphEdge>());
	std::vector<GraphEdge> result;
	result.resize(graph->vertexN);

	Disjointset subset(graph->vertexN);

	int v=0,e=0;
	
	while (v<graph->vertexN-1 && e<graph->ges.size()) {
		GraphEdge nextEdge = graph->ges[e++];
		int src = nextEdge.from;
		int dst = nextEdge.to;
		int fx = find(subset,src);
		int fy = find(subset,dst);
		if(fx!=fy){
			Union(subset,fx,fy);
			result[v++] = nextEdge;
		}
	}
	for(int i=0;i<v;i++){
		std::cout<<" "<<result[i].weight;
	}
	std::cout<<std::endl;
	return 0;
}

int main(int argc, char **argv) {
  Graph* graph = new Graph(6);
  GraphEdge ge1(1,2,5);
  graph->addEdge(ge1);
  GraphEdge ge2(1,3,6);
  graph->addEdge(ge2);
  GraphEdge ge3(3,4,7);
  graph->addEdge(ge3);
  GraphEdge ge4(4,5,2);
  graph->addEdge(ge4);
  GraphEdge ge5(0,5,7);
  graph->addEdge(ge5);
  GraphEdge ge6(0,3,9);
  graph->addEdge(ge6);
  GraphEdge ge7(1,5,2);
  graph->addEdge(ge7);

  int n= minSpanTree(graph);
  
}
