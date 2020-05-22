#include <bits/stdc++.h>
using namespace std;

int st[100000];

void disp(vector<int> A)
{
    int curr_pos = 1;
    int per_line = 1;

    while(curr_pos < 4*A.size())
    {
        for(int j = 0; j < per_line; j++, curr_pos++)
        {
            cout<<st[curr_pos]<<" \t ";
        }

        per_line = 2*per_line;
        cout<<endl;
    }

}

void buildTree(vector<int> A, int tree_idx, int start, int end)
{
    if(start == end)
    {
        st[tree_idx] = A[start];
    }
    else
    {
        int mid = start + (end - start)/2;

        buildTree(A, 2*tree_idx, start, mid);
        buildTree(A, 2*tree_idx + 1, mid+1, end);

        st[tree_idx] = st[2*tree_idx] + st[2*tree_idx + 1];
    }
}

int main()
{
    //initialization
    memset(st, -1, sizeof(st));

    std::vector<int> A = {1, 2, 3, 4, 5};

    buildTree(A, 1, 0, A.size() - 1);

    disp(A);

    return 1;
}
