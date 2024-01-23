#include <iostream>
#include<stack>
#include<queue>
#include<list>
#include<vector>
#include<map>

using namespace std; 

class Graph { 
    int v; 
    list<int>* adjlist; //adjacency list to store vertices

    public: 
    Graph(int v){
        this->v=v; //set vertices  
        adjlist=new list<int>[v]; //create new list per graph object 
        
    }

    void addEdge(int from, int to){
        adjlist[from].push_back(to); //create edge in adjacency list 
    }


    void topoBFS(){ 
        vector<int> indegree(v,0); //store all indegrees here, all at first 0 
        for (int x=0; x<v; x++){
            list <int>::iterator a ; 
            for (a=adjlist[x].begin(); a != adjlist[x].end(); a++){ //iterate through and record indegrees for vertices
                indegree[*a]++; 
            }
        }

        queue<int> q; 
        for (int x=0; x<v; x++){
            if (indegree[x]==0){ //all vertices with indeg of 0 are enqueued
                q.push(x); 
            }
        }

        int count=0; //going to use this to determine if there's cycle 
        vector<int>top; //this is where the topological order will be stored 

        while (q.empty()==false){ //aka queue not empty
            int x=q.front(); //dequeue top vertex
            q.pop(); 
            top.push_back(x); //store it in topological vector 

            list<int>::iterator i; 
            for (i=adjlist[x].begin(); i!=adjlist[x].end(); i++){ //iterate through adjcancey list
                if (--indegree[*i]==0){
                    q.push(*i); //add to queue only if indegree of that vertex is now 0
                }

            }

            count++; 

        }

        if (count!=v){
            cout << "There is a cycle, so no BFS can be performed."; 
            return; 
        }

        for (int x=1; x<top.size(); x++){ //now print topological order 
            cout << top[x]<<","; 
       

    }
    }

    

    void recurDFS(int currentv, bool visited[], stack<int>& s, stack<int>& check){ 
        visited[currentv]=true; //set vertex to true 

        list<int>::iterator x; 
        for (x=adjlist[currentv].begin(); x!= adjlist[currentv].end(); x++){ //iterate through adjacent vertices
            if (!visited[*x]){ //continue recurring until reach vertex that has been visited
                recurDFS(*x, visited, s, check); 
            }
        }
        s.push(currentv); //now add to both stacks 
        check.push(currentv); 
    }

    void topoDFS(){

        stack<int> s; //used for topological order DFS 
        stack<int>check; //gonna be used to check cycle 
        bool* visited=new bool[v]; //will track which vertices have been visited 
        for (int x=0; x<v; x++){
            visited[x]=false;  //setting all to false for now 
        }

        for (int x=0; x<v; x++){ //iterate through vertices
            if (visited[x]==false){ //for each vertex if it hasn't been visited yet
                recurDFS(x, visited, s, check); 
            } 

            }
        
        //now let's check if there's a cycle 
        unordered_map<int,int> positions; //use map to record positions of vertices
        int x=0; 

        while (!check.empty()){ //use this stack to fill positions map 
            positions[check.top()]=x; 
            x+=1; 
            check.pop();
        }

        list<int>::iterator i; 
        for (int a=0; a<v; a++){ //now iterate through entire adjacency list and check the positions map
            for (i=adjlist[a].begin(); i!= adjlist[a].end(); i++){ 
                if (positions[a]>positions[*i]){ //if parent vertex is not first there is a cycle
                    cout << "There is a cycle, so no DFS can be performed."; 
                    return; //don't perform DFS if cycle 
                }

            }
        }
    //now let's perform DFS using other stack s
        while (s.size()!=1 && !s.empty()){ //don't want 0 vertex cause graphs start at vertex 1 
            cout << s.top() << ","; 
            s.pop(); 
                
        }


        }



}; 



int main(){ 
    //graph 1 had letter vertices so I converted them to number vertices 
    //where m=1, n=2, o=3, p=4,q=5,r=6,s=7,t-8,u=9,v=10,w=11,x=12,y=13,z=14
    Graph g1 (15); //14 vertices + 1 b/c vertices start at 1 
    g1.addEdge(1,6); 
    g1.addEdge(1,5);
    g1.addEdge(1,12); 
    g1.addEdge(5,8); 
    g1.addEdge(2,5); 
    g1.addEdge(2,3); 
    g1.addEdge(2,9); 
    g1.addEdge(9,8); 
    g1.addEdge(6,9); 
    g1.addEdge(6,13); 
    g1.addEdge(3,6); 
    g1.addEdge(3,10); 
    g1.addEdge(3,7); 
    g1.addEdge(10,12); 
    g1.addEdge(10,11); 
    g1.addEdge(13,10); 
    g1.addEdge(7,6); 
    g1.addEdge(4,7); 
    g1.addEdge(4,3); 
    g1.addEdge(4,14); 
    g1.addEdge(11,14);
    cout << "Topological Sort for Graph 1:"<<endl; 
    cout << "BFS:"; 
    g1.topoBFS(); 
    cout <<endl; 
    cout << "As letters: m,n,p,q,o,s,r,u,y,t,v,x,w,z"<<endl; 
    cout << "DFS:"; 
    g1.topoDFS(); 
    cout <<endl; 
    cout << "As letters: p,n,o,s,m,q,r,y,v,w,z,x,u,t"<<endl; 

    //


    Graph g2 (9); //8 vertices + 1 b/c vertices start at 1 
    g2.addEdge(1,2); 
    g2.addEdge(1,5); 
    g2.addEdge(1,6); 
    g2.addEdge(2,5); 
    g2.addEdge(2,3); 
    g2.addEdge(2,7); 
    g2.addEdge(3,4); 
    g2.addEdge(4,5); 
    g2.addEdge(5,8); 
    g2.addEdge(5,7); 
    g2.addEdge(6,5); 
    g2.addEdge(6,8); 
    g2.addEdge(7,8); 
    g2.addEdge(7,4);   
    cout <<endl; 
    cout << "Topological Sort for Graph 2:"<<endl;
    cout << "BFS:"; 
    g2.topoBFS(); 
    cout <<endl; 
    cout << "DFS:"; 
    g2.topoDFS(); 
}