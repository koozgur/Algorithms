#include "the2.h"


/*
    arr       : array to be sorted, in order to get points this array should contain be in sorted state before returning
    ascending : true for ascending, false for descending 
    size      : number of elements in the array
*/
int find_max_length(std::string* arr, int size){
    int mid = 0;
    for(int i = 0; i < size; i++){
        if(arr[i].length() > mid)
            mid = arr[i].length();
    }
    return mid;
}
int countSort(std::string* arr, int size, int digit_no, bool ascending){
    //range is fixed, from 'A' to 'Z' , 26 many
    //digit no from right side
    int it_count = 0;
    int* C = new int[27]; 
  /
    std::string* B = new std::string[size];

    for(int a = 0; a < 27; a++){ //do not count iterations there
        C[a] = 0;
    }
    for(int j = 0; j < size; j++){
        it_count++;
        int A_J;
        int index = digit_no;//you cannot directly put the digit_no as index, you should make: sizeofstring - digit_no- 1
        if(arr[j].length() < (digit_no+1))
            A_J = 0;
        else
            A_J = arr[j][index] - 64;
        C[A_J]++;  
    }
    for(int j = 1; j < 27; j++){
        it_count++;
        C[j] += C[j-1];
    }
    for(int j = size-1; j > -1; j--){
        it_count++;
        int A_J;
        int index = digit_no;
        if(arr[j].length() < (digit_no+1))
            A_J = 0;
        else
            A_J = arr[j][index] - 64;
        B[C[A_J]-1] = arr[j];
        C[A_J]--;
    }
    for(int i = 0; i < size; i++){
        it_count++;
        arr[i] = B[i];
    }
    delete[] C;
    delete[] B;
    return it_count;
}
int radix_string_sort(std::string* arr, int size, bool ascending){
     if (!arr) {
        return 0;
    }
    int max_len = find_max_length(arr,size);
    int iterations = 0;
    for(int i = max_len-1; i >= 0; i--){
        iterations+= countSort(arr, size, i, ascending);
    }
    //make it ascending, then make it descending way. Do not make that swapping at the inner function causes multiple swaps and thus unexpected order.
    if(!ascending){
        int mid = size/2;
        for(int index = 0; index < mid; index++)
            std::swap(arr[index], arr[size-index-1]);
    } 
    return iterations;    
    
} 
