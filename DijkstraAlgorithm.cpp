#include <iostream> 
#include <queue> 
#include <utility> 
#include <list>
#define INFINITY 99999999 //assign infinity as large number 

using namespace std; 

class Graph { 
    int v; 
public: 
    list <pair<int,int > >* adjacencylist; //adjacency list->pointer of list of pairs 
    Graph (int v){ //to create graph of v vertices 
        this->v=v; //assign vertex 
        adjacencylist=new list<pair<int,int > >[v]; //allocate new memory 
    }

    void addEdge(int from, int to, int weight){ //directed graph 
        adjacencylist[from].push_back(make_pair(to,weight)); 
        //pair consists of destination and weight and the pair is aassigned to list index of the source vertex 
    }

    void StartingGraph(){ 
        cout << "Beginning Graph:"; 
        cout << "\n"; 
        list<pair<int, int> >::iterator x; 
        //iterate through adjacency list to output graph information 
        for (int y=0; y<v; y++){
            for (x = adjacencylist[y].begin(); x!=adjacencylist[y].end(); x++){
                cout << y << "->" << (*x).first<< " : " << (*x).second<<endl; 
        }

        }

            
        }


    void Dijkstra (int from){ 
        //create a priority queue that is a min heap 
        priority_queue<pair<int,int>, vector<pair<int,int> >, greater<pair<int,int> > > Q; 
        vector <int> weight(v, INFINITY); //vector to record the weights 
        //set everything to infinity first 

        //first vertex goes in 
        Q.push(make_pair(from,0)); //this is first vertex being added 
        weight[from]=0; //distance for start vertex is 0 

        while (Q.empty()==false){ //while queue isn't empty 
            //take from top of pq b/c it'll be vertex with min distance 
            int min=Q.top().first; //store the vertex at top as min 
            Q.pop(); //take it off 

            list<pair<int, int> >::iterator x; //create iterator 
            for (x = adjacencylist[min].begin(); x!=adjacencylist[min].end(); x++){ //iterate through to find adjacent vertices 
                //assign next vertex and weight to pair 
                int nextv=(*x).first; 
                int newweight=(*x).second; 

                //update distances if necessary aka if path to other vertex is now shorter
                if ((weight[min] + newweight) < weight[nextv]){
                        weight[nextv]=weight[min]+ newweight; 
                        Q.push(make_pair(nextv, weight[nextv])); //now add updated pair to queue 
                }
                //other distances will remain unchanged 
            }   


        }
       
       //now output resulting short path tree 
       cout << "Shortest Path from Vertex "<<from<<":"<<endl; 
       for (int x=0; x<v; x++){ 
        cout<<"to "<<x<<" : "<<weight[x]<<endl; 
       }




    }




}; 






int main() { 
    int vertices=10; //10 vertices total

    Graph graph(vertices); //create graph 
    //20 edges 
    graph.addEdge(0,1,2); 
    graph.addEdge(1,3,5); 
    graph.addEdge(2,1,8); 
    graph.addEdge(1,2,3); 
    graph.addEdge(0,3,5); 
    graph.addEdge(3,2,1); 
    graph.addEdge(2,4,3); 
    graph.addEdge(3,4,8); 
    graph.addEdge(2,6,6); 
    graph.addEdge(0,6,8); 
    graph.addEdge(6,5,3); 
    graph.addEdge(4,5,4); 
    graph.addEdge(3,9,5); 
    graph.addEdge(9,8,1); 
    graph.addEdge(5,9,6); 
    graph.addEdge(1,8,3); 
    graph.addEdge(0,7,11); 
    graph.addEdge(7,5,5); 
    graph.addEdge(4,8,9); 
    graph.addEdge(2,8,6); 

    graph.StartingGraph(); 

    graph.Dijkstra(0); 




   
    
    
}