#include "the4.h"

// do not add extra libraries here
std::vector<std::vector<int>> dp(602, std::vector<int>(602));


int solver(int X, int Y, bool** possible_plots){
    if(dp[X][Y]!= 360000)
        return dp[X][Y];
   if(possible_plots[X][Y]){
       dp[X][Y] = 0;
       return dp[X][Y];
   }      
   if( X == 1 && Y == 1){
       dp[1][1] = 1;
       return 1;
   }
   int temp_min = 360000;
   for(int i = 1; i <= X/2; i++){ //enough to iterate first half of possibilites since after that just order is vice versa
       int piece1 = solver(i, Y , possible_plots );
       int piece2 = solver(X - i, Y, possible_plots);
       int inner = piece1 + piece2;
       if(inner < temp_min)
           temp_min = inner;
    }
    for(int j = 1; j <= Y/2; j++){
       int piece1 = solver(X, j, possible_plots );
       int piece2 = solver(X, Y-j, possible_plots);
       int inner = piece1 + piece2;
       if(inner < temp_min)
           temp_min = inner;
    }
    dp[X][Y] = temp_min;
    return temp_min;
}
int divide_land(int X, int Y, bool** possible_plots){
    for(int i= 0; i < 602; i++)
        for(int j=0; j < 602; j++)
            dp[i][j] = 360000;
    if(X==0&&Y==0)
        return X*Y;
    return solver(X, Y, possible_plots); //done to avoid multiple initializations
}
