#include <bits/stdc++.h>
using namespace std;

void print2DArray(vector<vector<int>> A)
{
    for(auto x : A)
    {
        for(auto y : x) cout<< y <<" ";
        cout<<endl;
    }
    cout<<endl;
}

void printSol(vector<vector<int>> dp, string A, string B, set<string> &sol, string &curr, int i, int j)
{
    // cout<<"New Call:" << i <<","<< j <<"->"<< curr <<endl;

    if(i == 0 || j == 0 || dp[i][j] == 0)
    {
        reverse(curr.begin(), curr.end());
        // cout<< curr <<endl;
        sol.insert(curr);
        return;
    }

    if(dp[i-1][j-1] == dp[i][j] - 1 && dp[i][j] > dp[i-1][j] && dp[i][j] > dp[i][j-1] )
    {
        curr.push_back(A[i-1]);
        printSol(dp, A, B, sol, curr, i-1, j-1);
    }
    else
    {
        if(dp[i][j] == dp[i-1][j] && dp[i][j] == dp[i][j-1])
        {
            string curr_a = curr;
            string curr_b = curr;

            printSol(dp, A, B, sol, curr_a, i, j-1);
            printSol(dp, A, B, sol, curr_b, i-1, j);
        }
        else if(dp[i-1][j] > dp[i][j-1])
        {
            printSol(dp, A, B, sol, curr, i-1, j);
        }
        else printSol(dp, A, B, sol, curr, i, j-1);
    }
}

int lcs(string A, string B)
{
    vector<vector<int>> dp( A.size()+1, vector<int>(B.size()+1, 0) );

    for(int i = 0; i <= A.size(); i++)
    {
        for(int j = 0; j <= B.size(); j++)
        {
            if( i == 0 || j == 0 )
            {
                dp[i][j] = 0;
                // continue;
            }
            else if(A[i-1] == B[j-1]) dp[i][j] = dp[i-1][j-1] + 1;
            else dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
        }
    }
    print2DArray(dp);

    set<string> sol;
    string curr;
    printSol(dp, A, B, sol, curr, A.size(), B.size());
    cout<<"All the lcs are as follows-> ";
    for(auto x: sol) cout<< x <<" ";
    cout<<endl;



    return dp[A.size()][B.size()];
}

int main()
{
    // string A = "AXATBGGA";
    // string B = "XGATBG";

    string A = "abcd";
    string B = "bacd";

    // string A = "AGGTAB";
    // string B = "GXTXAYB";

    int tmp = lcs(A, B);
    cout<<"Length of longest common subsequence:"<< tmp <<endl;

    return 0;
}
