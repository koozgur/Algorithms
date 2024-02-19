#include "the6.h"

// do not add extra libraries here


using namespace std;



int find_structure(std::vector< std::vector<std::pair<int,int> > >& bond_energies, std::vector< std::vector<std::pair<int,int> > >& lowest_energy_structure) {
    int node_count = bond_energies.size();
    lowest_energy_structure.resize(node_count);
    vector<int> visited(node_count, 0);
    vector<int> totalDist(node_count, INT_MAX);
    totalDist[0] = 0;
    int lowest_total_energy = 0;
    vector<int> parent(node_count,0);
    priority_queue< pair<int,int> , vector< pair<int, int > >, greater<pair<int,int>> >pq;
    //start from vertex 0
    
    pq.push(make_pair(0,0)); //first is weight , second is vertex
    //but in the bond_energies , first one is nextvertex second one is weight
    while(!pq.empty()){
        auto p = pq.top();
        pq.pop();
        
        if(visited[p.second])
            continue;
        else{
            int cur_vertex = p.second; 
            int cur_edge = p.first;
            visited[cur_vertex] = 1;
            for(int i = 0; i< bond_energies[cur_vertex].size();i++){
                int next_vertex = bond_energies[cur_vertex][i].first;
                int edge = bond_energies[cur_vertex][i].second;
                if(!visited[next_vertex] && totalDist[next_vertex] > edge){
                    totalDist[next_vertex] = edge;
                    pq.push(make_pair(edge, next_vertex));
                    parent[next_vertex] = cur_vertex;
                }
            }

        }
    }
    for(int j = 1; j < node_count; j++){
        int x = parent[j];
        for(int k = 0; k < bond_energies[x].size(); k++){
            if(bond_energies[x][k].first == j){
                lowest_energy_structure[x].push_back(make_pair(j, bond_energies[x][k].second));
                lowest_energy_structure[j].push_back(make_pair(x, bond_energies[x][k].second));
                lowest_total_energy += bond_energies[x][k].second;
                break;
            }
        }
    }
    return lowest_total_energy;
}
int find_longest_chain(std::vector< std::vector<std::pair<int,int> > >& molecule_structure, std::vector<int>& chain){
    int longest_chain_size = 0;
    vector<int> parent(molecule_structure.size(),0);
    vector<int>current_distance(molecule_structure.size(), INT_MAX);
    current_distance[0] = 0;
    queue<int> q;
    q.push(0); //send node numbers

    //bfs with finding depth
    while(!q.empty()){
        int cur_vertex = q.front();
        q.pop();
        for(int i = 0; i < molecule_structure[cur_vertex].size(); i++){
            int next_vertex = molecule_structure[cur_vertex][i].first;
            if(current_distance[next_vertex] == INT_MAX){
                current_distance[next_vertex] = current_distance[cur_vertex] + 1;
                q.push(next_vertex);
            }
        }
    }
    int max = 0;
    int furtherst_node1 = -1, furtherst_node2;
    //find furthest one
    for(int j = 0; j < current_distance.size(); j++){
        if(current_distance[j] > max){
            max = current_distance[j];
            furtherst_node1 = j;
        }
    }
    
    //j is one of the furthest nodes
    //now make bfs from that node and find another furthest one

    for(int i = 0; i < current_distance.size(); i++)
        current_distance[i] = INT_MAX;
    current_distance[furtherst_node1] = 0;

    q.push(furtherst_node1);
    while(!q.empty()){
        int cur_vertex = q.front();
        q.pop();
        for(int i = 0; i < molecule_structure[cur_vertex].size(); i++){
            int next_vertex = molecule_structure[cur_vertex][i].first;
            if(current_distance[next_vertex] == INT_MAX){
                current_distance[next_vertex] = current_distance[cur_vertex] + 1;
                q.push(next_vertex);
            }
        }
    }

    max = 0;
    for(int j = 0; j < current_distance.size(); j++){
        if(current_distance[j] > max){
            max = current_distance[j];
            furtherst_node2 = j;
        }
    }
    //other side's furtherst node is node2
    //now find path between these two nodes and that will give me the result, from node 1 to node 2

    for(int i = 0; i < current_distance.size(); i++)
        current_distance[i] = INT_MAX;
    current_distance[furtherst_node1] = 0;

    q.push(furtherst_node1);
    while(!q.empty()){
        int cur_vertex = q.front();
        q.pop();
        for(int i = 0; i < molecule_structure[cur_vertex].size(); i++){
            int next_vertex = molecule_structure[cur_vertex][i].first;
            if(current_distance[next_vertex] == INT_MAX){
                current_distance[next_vertex] = current_distance[cur_vertex] + 1;
                q.push(next_vertex);
                parent[next_vertex] = cur_vertex;
            }
            if(next_vertex == furtherst_node2)
                break;
        }
    }
    //form the path based on parent content from node2 -> node1
    int parent_node = parent[furtherst_node2];
    chain.push_back(furtherst_node2);
    longest_chain_size+=2; //at first, you consider 2 nodes
    while(true){
        chain.push_back(parent_node);
        if(parent_node == furtherst_node1)
            break;
        longest_chain_size++;
        parent_node = parent[parent_node];
        
    }


    return longest_chain_size;
}
