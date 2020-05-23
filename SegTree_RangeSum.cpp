// #include "mylib.h"
#include <bits/stdc++.h>
using namespace std;

struct st
{
	int l;
	int r;
	int curr_sum;
	st* left;
	st* right;
};

void disp(st* root)						//Level Order display
{
    queue<st*> tmp;
    st* lb = new st();	//Dummy Node
    tmp.push(root);
    tmp.push(lb);
    while(!tmp.empty())
    {
        if(tmp.front() == lb) //Dummy node on top
        {
            if(tmp.size() == 1) //Terminating case when only dummy node is left
						{
							cout<<endl<<endl;
							break;
						}
            cout<<endl<<endl;
            tmp.push(lb);			//Pop and push dummy node to end of queue
            tmp.pop();
        }
        cout<<tmp.front()->curr_sum<<"  ("<<tmp.front()->l<<","<<tmp.front()->r<<")\t\t";
        if(tmp.front()->left) tmp.push(tmp.front()->left);
        if(tmp.front()->right) tmp.push(tmp.front()->right);
        tmp.pop();
    }
}

st* buildTree(vector <int> &A, int lower, int upper)
{
	if(lower > upper) return NULL;

	// std::cout << "New call:" << lower <<" "<< upper << '\n';
	st* tmp = new st();
	tmp->l = lower;
	tmp->r = upper;

	//Base Case of leaf node
	if(lower == upper)
	{
		tmp->curr_sum = A[lower];
		tmp->left = NULL;
		tmp->right = NULL;
	}
	else
	{
		int mid = lower + (upper-lower)/2;
		tmp->left = buildTree(A, lower, mid);
		tmp->right = buildTree(A, mid+1, upper);

		//Build left and right sub-tree and compute the sum of childs
		tmp->curr_sum = (tmp->left->curr_sum) + (tmp->right->curr_sum);
	}

	return tmp;
}

int getSum(st* itr, int lower, int upper)
{
	// cout<<"Node:"<< itr->l <<","<< itr->r <<"->"<< itr->curr_sum <<endl;
	if( lower > itr->r ||  upper < itr->l )
	{
		// cout<<"No overlap"<<endl;
		return 0;
	}

	if(itr->l >= lower && itr->r <= upper)
	{
		// cout<<"Given Node totally inside range"<<endl;
		return itr->curr_sum;
	}

	// cout<<"Partial overlap"<<endl;
	return ( getSum(itr->left, lower, upper)
	+ getSum(itr->right, lower, upper) );
}

void updateVal(st* itr, int idx, int diff)
{
	if(itr == NULL) return;

	// cout<<"New Call:"<< itr->l <<","<< itr->r <<"->"<<itr->curr_sum<<endl;
	if(idx < itr->l || idx > itr->r)
	{
		// cout<<"Idx to be updated out of node range"<<endl;
		return;
	}

	// cout<<"Inside Node Range"<<endl;
	itr->curr_sum = itr->curr_sum + diff;			//Update the curr_sum for this node
	// cout<<"Updated Sum:"<<itr->curr_sum<<endl;

	updateVal(itr->left, idx, diff);					//Update sum for both children
	updateVal(itr->right, idx, diff);
}

int main()
{
	// cout<<"Hello!!"<<endl;

	vector<int> A = {1, 3, 5, 7, 9, 11};
	// printArray(A);

	st* head = buildTree(A, 0, A.size() - 1);

	//Display the tree
	disp(head);

	//RangeSum Query
	int lower = 2;
	int upper = 5;
	int tmp1 = getSum(head, lower, upper);
	cout<<"rangeSum:"<<lower<<","<<upper<<"->"<<tmp1<<endl;

	//Updation
	A[2] = -5;
	//Diff = NewVal - OldVal
	//updateVal(root, idx, diff)
	updateVal(head, 2, -10);

	//Display the updated tree
	disp(head);

	//New ans for previous RangeSum query
	int tmp2 = getSum(head, lower, upper);
	cout<<"rangeSum:"<<lower<<","<<upper<<"->"<<tmp2<<endl;

	return 0;
}
