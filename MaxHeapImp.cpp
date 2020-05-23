#include <bits/stdc++.h>
using namespace std;

void printArray(vector<int> &A)
{
    for(int i = 0; i < A.size(); i++)
    {
        cout<<A[i]<<" ";
    }
    cout<<endl;
}

void percolateUp(vector<int> &heap, int idx)
{
    if(idx <= 1) return;

    if( heap[idx] > heap[ idx/2 ] )
    {
        swap(heap[idx], heap[idx/2]);
        percolateUp(heap, idx/2);
    }
}

void percolateDown(vector<int> &heap)
{

}

vector<int> buildHeap(vector<int> A)
{
    vector<int> heap( A.size() + 1 );
    int heap_idx = 1;

    for(int i = 0; i < A.size(); i++, heap_idx++)
    {
        heap[heap_idx] = A[i];
        percolateUp(heap, heap_idx);
        printArray(heap);
    }

    return heap;
}

int main()
{
    vector<int> v = {1, 2, 3, 4, 5};

    vector<int> heap =  buildHeap(v);
    cout<<"Final Heap:";
    printArray(heap);

    return 1;
}
