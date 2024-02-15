#include "the3.h"


std::string A,B;
int global_match, global_mismatch, global_gap;
int dp[10005][10005];

int compare( int i ,int j){
    if(A[i] == B[j])
        return global_match;
    else    
        return -global_mismatch;
}

int F(std::string& pos_alignment, int& call_count, int i , int j){
    call_count++;
    if(call_count == 1000000){
        pos_alignment = "STACK LIMIT REACHED";
        return INT_MIN;
    }

    if(i < 0 || j < 0 )
        return -45000;
    if((i == 0) && (j == 0)){
        if(A[i] == B[j]){
            pos_alignment = A[i];
            return global_match;
        }
        else{
            pos_alignment = "!";
            return -global_mismatch;
        }
    }
    if(i == 0){ 
        //decrement only j, when it becomes 0, comparison with 0, reverse of being reduced is empty
        std::string a = "";
        int mid = 0;
        int flag = 1;
        for(int z = 0; z <= j;z++){
            if( (A[0] == B[z]) && flag){ //valid for at most one time
                a += A[0];
                mid += global_match;
                flag = 0;
            }
            else{
                a += "_";
                mid -= global_gap;
            }
        }
        pos_alignment = a;
        return mid;
    }
    if(j == 0){ //sadece i yi azalt, 
        std::string a = "";
        int flag = 1;
        int mid = 0;
        for(int z = 0; z <= i;z++){
            if(A[z] == B[0] && flag){
                a += B[0];
                mid += global_match;
                flag = 0;
            }
            else{
                a += ".";
                mid -= global_gap;
            }
        }
        pos_alignment = a;
        return mid;
    }
    int score;
    std::string a, b, c;
    int result_1 = F(a, call_count,  i-1, j -1 );
    if(result_1 == INT_MIN){
        pos_alignment = a;
        return INT_MIN;
    }
    result_1 += compare(i, j);
    int result_2 = F(b, call_count, i-1, j );
     if(result_2 == INT_MIN){
        pos_alignment = b;
        return INT_MIN;
     }
    result_2 -=global_gap;
    int result_3 = F(c, call_count,  i  , j -1 );
     if(result_3 == INT_MIN){
        pos_alignment = c;
        return INT_MIN;
     }
    result_3 -= global_gap;
    score = result_1;
    if(score < result_2)
        score = result_2;
    else if(score < result_3)
        score = result_3;
    
    if(score == result_1){
        if(A[i] != B[j])
            pos_alignment = a + "!";
        else
            pos_alignment = a + A[i];
        
    }
    else if(score == result_2)//gap at second
        pos_alignment = b + ".";
    else
        pos_alignment = c + "_";
    return score;
}


/* 
PART 1
you are expected to call recursive_alignment (as the name suggests) recursively to find an alignment. 
initial call_count value given to you will be 0.
you should check if call_count >= 1000000, if so, set possible_alignment string to "STACK LIMIT REACHED", return INT_MIN (or anything - it will not be checked).
*/
int recursive_alignment(std::string sequence_A, std::string sequence_B, int gap, int mismatch, int match, std::string &possible_alignment, int call_count){
    int c_count = 0;
    A = sequence_A;
    B = sequence_B;
    global_match = match;
    global_mismatch = mismatch;
    global_gap = gap;
    int l1 = sequence_A.length()-1;
    int l2 = sequence_B.length()-1;
    int highest_alignment_score = F(possible_alignment, c_count, l1, l2 );

    return highest_alignment_score;    
}

/* 
PART 2
you are expected to create a dynamic programming table to find the highest alignment score. 
then you will need to reconstruct a possible alignment string from the table.
*/
int dp_table_alignment(std::string sequence_A, std::string sequence_B, int gap, int mismatch, int match, std::string &possible_alignment){
    int found_match = 0;
    int lengtha = sequence_A.length();
    int lengthb = sequence_B.length();
    for(int j = 0; j < lengthb; j++){ //dp [A][B]
        if(sequence_A[0] == sequence_B[j])
            found_match = 1;
        if(found_match)
            dp[0][j] = match - j * gap;
        else
            dp[0][j] = -mismatch - j*gap;
    }
    for(int i = 0; i < lengtha; i++){ //dp [A][B]
        if(sequence_A[i] == sequence_B[0])
            found_match = 1;
        if(found_match)
            dp[i][0] = match - i * gap;
        else
            dp[i][0] = -mismatch - i*gap;
    }
    for(int i =1 ; i < lengtha; i++)
        for(int j = 1; j < lengthb; j++){
            int result1 = dp[i-1][j-1] + compare(i, j);
            int result2 = dp[i-1][j] - gap;
            int result3 = dp[i][j-1] - gap;
            int score = result1;
            if(score < result2)
                score = result2;
            if(score < result3)
                score = result3;
            if(score == result1)
                dp[i][j] = result1;
            else if(score == result2)
                dp[i][j] = result2;
            else
                dp[i][j] = result3;
        }
    int highest_alignment_score = dp[lengtha-1][lengthb-1];
  
    //now we should find the string
    int i = lengtha-1;
    int j = lengthb-1;
    int curr = highest_alignment_score;
    while( (i> 0) && (j> 0)){
        if(curr == dp[i-1][j-1] + compare(i, j)){
            if(sequence_A[i] == sequence_B[j])
                possible_alignment = sequence_A[i] + possible_alignment;
            else
                possible_alignment = "!" + possible_alignment;
            i--;
            j--;
        }
        else if(curr == dp[i-1][j] - gap ){
            i--;
            possible_alignment = "." + possible_alignment;
        }
        else{
            j--;
            possible_alignment = "_" + possible_alignment;
        }
        curr = dp[i][j];
    }
    //handle zero case
    if( (i == 0) && (j == 0)){
        if(sequence_A[i] == sequence_B[j])
            possible_alignment = sequence_A[i] + possible_alignment;
        else
            possible_alignment = "!" + possible_alignment;
    }

    else if(j == 0){ //decrement only i, 
        std::string a = "";
        int flag = 1;
        for(int z = 0; z <= i;z++){
            if(sequence_A[z] == sequence_B[0] && flag){
                a += sequence_B[0];
                flag = 0;
            }
            else
                a += ".";
        }
        possible_alignment = a + possible_alignment;
    }
    else{ //decrement only j, 
        std::string a = "";
        int flag = 1;
        for(int z = 0; z <= j;z++){
            if(sequence_A[0] == sequence_B[z] && flag){
                a += sequence_A[0];
                flag = 0;
            }
            else
                a += "_";
        }
        possible_alignment = a + possible_alignment;
    }
    
    return highest_alignment_score;    
}
