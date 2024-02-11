#include "the1.h"


void Swap(unsigned short* arr, int f, int s, long& swap, double& avg_dist, double& max_dist){ 
    //if it is called by medianof3, do not make swap when indexes are equal
  
    unsigned short temp = arr[f];
    *(arr+f) = arr[s];
    *(arr+s) = temp;
    int diff;
    ( (s-f) < 0) ? (diff = f-s) : (diff = s-f);
    if(diff > max_dist)
        max_dist = diff;
    double total = avg_dist * swap;
    total+= diff;
    swap++;
    avg_dist = total / (swap);
}


void Median(unsigned short* arr, int size, bool hoare, long& swap, double& avg_dist, double& max_dist){
    if(size < 3)
        return;
    unsigned first = arr[0];
    unsigned mid = arr[(size-1)/2];
    unsigned last = arr[size-1];
    if(! ((first != mid) && (mid!= last) && (first != last)))
        return;
    if( ((first < mid ) && (mid < last)) || ((first > mid) && (mid > last)) ){
        //mid is median
        if(hoare)
            return;//swapping mid and mid(no change)
        else{
                if((size-1)/2 == (size - 1))
                    return;
                Swap(arr, (size-1)/2, size-1, swap, avg_dist, max_dist);//swap mid goes to last position (swap)
        }
        
    }
    else if( ( (mid < first) && (first < last)) || ((mid > first) && (first > last)) ){
        //first is median
        if(hoare){
            if(0 == (size-1)/2)
                    return;
            Swap(arr, 0, (size-1)/2, swap, avg_dist, max_dist);//swap first to mid
        }
        else{
            if(0 == size-1)
                    return;
            Swap(arr, 0 , size-1, swap, avg_dist, max_dist);//swap first to last
        }
    } 
    else{
        //last is median
        if(hoare){
            if(size-1 == (size-1)/2)
                return;
            Swap(arr, size-1, (size-1)/2, swap, avg_dist, max_dist);//swap last to mid
        }
        else
            return; //swap last to last(no change)
    }
    return;
}

int Lomuto(unsigned short* arr, int size, long & swap, double& avg_dist, double& max_dist){
    unsigned short pivot = arr[size-1];
    int i = -1;
    for(int j = 0; j < size-1; j++){
        if(arr[j] >= pivot ){
            i++;
            Swap(arr, i, j, swap, avg_dist, max_dist);
        }
    }
    Swap(arr, i+1, size-1, swap, avg_dist, max_dist);
    return i+1;
}


int Hoare(unsigned short* arr, int size,long& swap, double& avg_dist, double& max_dist){
    unsigned short pivot = arr[(size-1) / 2];
    int i = -1;
    int j = size;
    while(1){
        do{
            j--;
        }while(arr[j] < pivot);

        do{
            i++;
        }while(arr[i] > pivot);

        if(i < j)
            Swap(arr, i ,j, swap, avg_dist, max_dist);
        else
            return j;
    }
}
 // FIRST WRITE THE QUICK SORT, THEN ADD CODE OF SWAP DISTANCE 
int quickSort(unsigned short* arr, long& swap, double& avg_dist, double& max_dist, bool hoare, bool median_of_3, int size){
    //Your code here
    int l_call = 0, r_call = 0;
    if(size>1){
        int pivot_index;
        if(median_of_3)
            Median(arr, size, hoare,swap, avg_dist, max_dist); //depending on the partition algorithm the pivot will be put there
        if(!hoare){
            pivot_index = Lomuto(arr, size, swap, avg_dist, max_dist);
            l_call = quickSort(arr, swap, avg_dist, max_dist, hoare, median_of_3, (pivot_index)); //pivota kadarki /(pivot dahil değil)
            r_call = quickSort(arr+pivot_index+1, swap, avg_dist, max_dist, hoare, median_of_3, (size- pivot_index-1));//pivottan sonrası (pivot yok)
        }
        else{
            pivot_index = Hoare(arr, size, swap, avg_dist, max_dist);
            l_call = quickSort(arr, swap, avg_dist, max_dist, hoare, median_of_3, (pivot_index+1) ); //until the pivot /(pivot is included)
            r_call = quickSort(arr+pivot_index+1, swap, avg_dist, max_dist, hoare, median_of_3, (size- pivot_index-1)); //after the pivot (pivot is not included)
        }
    }
    return l_call + r_call+1;
}
