#include "the7.h"

// do not add extra libraries here

using namespace std;

vector< vector <int> > adj_matrix;

void get_infection_scores(const std::vector<std::vector<std::pair<int, int>>>& network, std::vector<float>& infection_scores){
    int node_count = network.size();
    infection_scores.resize(node_count);
    adj_matrix.resize(node_count, vector<int>(node_count, 100000000));
    //add edges to matrix, keep in mind that this is directed graph
    for(int i = 0; i < node_count ; i++){
        for(const auto& k: network[i] ){ //pair = (next_node, weight)
            adj_matrix[i][k.first] = k.second;
        }
    }
    //filled adjacency matrix

    //finding all shortest path between each pair of nodes
    for(int k = 0; k < node_count; k++)
        for(int i = 0; i < node_count; i++)
            for(int j = 0; j < node_count; j++)
                if(adj_matrix[i][j] > adj_matrix[i][k] + adj_matrix[k][j])
                    adj_matrix[i][j] = adj_matrix[i][k] + adj_matrix[k][j];
    //find maxDist, largest shortest distance between any pair
    int maxDist = 0;
    int curr;
    for(int i = 0; i < node_count; i++)
        for(int j = 0; j < node_count ; j++){
         curr = adj_matrix[i][j];
            if(curr != 100000000)
                if(curr > maxDist)
                    maxDist = curr;
        }
    maxDist++;
    //form infection_scores vector now
    for(int i = 0; i < node_count ; i++){
        float result = 0;
        int nominator_total = 0;
        for(int j = 0; j < node_count ; j++){
            if(i != j){
                if(adj_matrix[i][j] != 100000000)
                    nominator_total += adj_matrix[i][j];
                else
                    nominator_total += maxDist;
            }
        }
        result = (float)(node_count-1) / nominator_total;  // there is 1 / AIS so we divided it flipped way
        infection_scores[i] = result;
    }                                                         
}
