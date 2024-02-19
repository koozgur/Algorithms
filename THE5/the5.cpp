#include "the5.h"

// do not add extra libraries here

void findCycles(const std::vector<std::vector<int>>&, std::vector<std::vector<int>>&, std::vector<int>);
bool isBidirectional(int i ,int j, const std::vector<std::vector<int>>& matrix);
bool dfs(int i ,int j,const std::vector<std::vector<int>>& matrix, std::vector<int>&);

//we need topological sorting there
void run(const std::vector<std::vector<int>>& dependencyMatrix, bool& isCompilable, std::vector<int>& compileOrder, std::vector<std::vector<int>>& cyclicDependencies){
    //int size_matrix = dependencyMatrix[0].size();
    int size_matrix = dependencyMatrix[0].size();

    std::vector<int> zero_degreees;
    std::vector<int> order;
    std::vector<int> queue; //act as an queue, we will use two pointers
    int ptr_front = -1; //ptr to first element
    int ptr_last = 0; //ptr to last element
    std::vector<int>degree(size_matrix,0);
    std::vector<int>flag_zero_degrees(size_matrix,0); //non-cycle ones are flagged

    for(int i = 0; i < size_matrix; i++)
        for(int j = 0; j < size_matrix; j++){
            if(dependencyMatrix[i][j])
                degree[j]++; //j has incoming edge
        }

    for(int i = 0; i < size_matrix; i++){ //go from smaller, after finding one value use a vector to add order sorted manner , not directly the 0 degreed ones, testcase 10 showed the problem
        if((degree[i] == 0) && (queue.size() == 0)){
            queue.push_back(i);
            flag_zero_degrees[i] = 1;
            ptr_front = 0;
            ptr_last ++; //points behind the last element
        }
        else if(degree[i] == 0){
            zero_degreees.push_back(i);
            flag_zero_degrees[i] = 1;
        }
        else{

        }
    }
    int zero_vector_index = 0;

    while(! ( (ptr_front == ptr_last) || (ptr_front == -1) )){ //take each 0 degreed vertex smaller to larger, if zero degreed is smaller insert that first
        int current_vertex =  queue[ptr_front];
        if(zero_vector_index < zero_degreees.size() && (zero_degreees[zero_vector_index] < current_vertex)){
            order.push_back(zero_degreees[zero_vector_index]);
            zero_vector_index++;
        }
        order.push_back(current_vertex);
        ptr_front++; //popping the vertex from queue
        for(int i = 0; i < size_matrix ; i++){
            if(dependencyMatrix[current_vertex][i]){
                degree[i]--;
                if(!degree[i]){
                    flag_zero_degrees[i] = 1;
                    queue.push_back(i);
                    ptr_last++;
                }
            }
        }

    }
    while(zero_vector_index < zero_degreees.size()){
        order.push_back(zero_degreees[zero_vector_index]);
        zero_vector_index++;
    }
    bool flag = true;
    //if queue is empty but still there are remaining ones, then there is a cycle
    //go over flag_zero_degrees vector's 0 values
    for(int i = 0; i < size_matrix ; i++){
        if(flag_zero_degrees[i] == 0){
            flag = false;
        }
    }
    if(!flag){
        isCompilable = false;
        findCycles(dependencyMatrix, cyclicDependencies, flag_zero_degrees);
    }
    else{
        compileOrder = order;
        isCompilable = true;
    } 

    return;

}

void findCycles(const std::vector<std::vector<int>>& matrix, std::vector<std::vector<int>>& cyclicDependencies, std::vector<int> flag_zero_degrees){
    std::vector<int>part_of_cycle(matrix[0].size(),0);
    std::vector<int>current_cycle;
    for(int i = 0; i < matrix[0].size(); i++){
        current_cycle.clear();
        unsigned j = i+1;
        if(!flag_zero_degrees[i] && !part_of_cycle[i]){
            current_cycle.push_back(i);
            while(j < matrix[0].size() ){
                if(!part_of_cycle[j])
                    if(isBidirectional(i, j, matrix)){
                        part_of_cycle[j] = 1;
                        current_cycle.push_back(j);
                    }

                j++;
            }
        }
        if(current_cycle.size()==1 && (!isBidirectional(current_cycle[0],current_cycle[0],matrix)))
            continue;
        if(!current_cycle.empty())
            cyclicDependencies.push_back(current_cycle);
    }
}

bool isBidirectional(int i ,int j, const std::vector<std::vector<int>>& matrix){
    std::vector<int> visited(matrix[0].size(),0);
    std::vector<int> visited1(matrix[0].size(),0);
    if(dfs(i,j,matrix, visited) && dfs(j,i,matrix, visited1))
        return true;
    else
        return false;
}

bool dfs(int i ,int j, const std::vector<std::vector<int>>& matrix, std::vector<int> & visited){ //go from i to j. if you can, return true.
    visited[i] = 1;
    for(int k = 0; k < matrix[0].size(); k++){
        if(matrix[i][k]){
            if(k == j)
                return true;
            if(!visited[k])
                if(dfs(k, j, matrix, visited))
                    return true;
        }
    }
    return false;
}
