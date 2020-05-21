#include <iostream>
#include "mylib.h"
using namespace std;

struct st
{
	int l;
	int r;
	int curr_min;
	st* left;
	st* right;
};

st* buildTree(vector <int> &A, int lower, int upper)
{
	if(lower > upper) return NULL;

	std::cout << "New call:" << lower <<" "<< upper << '\n';
	st* tmp = new st();
	tmp->l = lower;
	tmp->r = upper;

	if(lower == upper)
	{
		tmp->curr_min = A[lower];
		tmp->left = NULL;
		tmp->right = NULL;
	}
	else
	{
		int mid = lower + (upper-lower)/2;
		tmp->left = buildTree(A, lower, mid);
		tmp->right = buildTree(A, mid+1, upper);

		tmp->curr_min = min(tmp->left->curr_min, tmp->right->curr_min);
	}
	return tmp;
}

void disp(st* root)
{
    queue<st*> tmp;
    st* lb = new st();
    tmp.push(root);
    tmp.push(lb);
    while(!tmp.empty())
    {
        if(tmp.front() == lb)
        {
            if(tmp.size() == 1) break;
            cout<<endl<<endl;
            tmp.push(lb);
            tmp.pop();
        }
        cout<<tmp.front()->curr_min<<"  ("<<tmp.front()->l<<","<<tmp.front()->r<<")\t\t";
        if(tmp.front()->left) tmp.push(tmp.front()->left);
        if(tmp.front()->right) tmp.push(tmp.front()->right);
        tmp.pop();
    }
}

void preorder(st* root)
{
	if(root == NULL) return;

	std::cout << root->l<<","<<root->r<<" -> " <<root->curr_min << '\n';
	preorder(root->left);
	preorder(root->right);
}

int main()
{
	cout<<"Hello!!"<<endl;

	vector<int> A = {5, 8, 1, 2, 8, 10, 7};
	printArray(A);
	// st* head = NULL;
	st* head = buildTree(A, 0, A.size() - 1);

	preorder(head);
	disp(head);

	return 0;
}
