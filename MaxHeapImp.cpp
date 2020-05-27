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

void percolateDown(vector<int> &heap, int idx)
{
    if(2*idx >= heap.size()) return;

    //Case of only one child in last node
    if(2*idx == heap.size() - 1)
    {
        if( heap[2*idx] < heap[idx] ) return;
        else
        {
            swap(heap[idx], heap[2*idx]);
            return;
        }
    }

    cout<<"Parent->"<< heap[idx] <<endl;;
    cout<<"Children->"<< heap[2*idx] <<"\t"<< heap[2*idx+1]<<endl;

    int max_child_idx = (heap[2*idx] > heap[2*idx+1]) ? 2*idx : 2*idx+1;
    cout<<"Max child @ "<< max_child_idx <<" -> "<< heap[max_child_idx] <<endl;

    if(heap[idx] < heap[max_child_idx])
    {
        swap(heap[idx], heap[max_child_idx]);
        percolateDown(heap, max_child_idx);
    }
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

void insert(vector<int> &heap, int num)
{
    if(heap.empty())
    {
        heap.push_back(0);
        heap.push_back(num);
        return;
    }

    heap.push_back(num);
    percolateUp(heap, heap.size() - 1);
}

int main()
{
    // vector<int> v = {1, 2, 3, 4, 5};
    vector<int> v = { 40, 15, 50, 40, 10, 100, 55 };
    vector<int> heap =  buildHeap(v);
    cout<<"Initial Heap:";
    printArray(heap);

    cout<<"Updation of root to 53"<<endl;
    heap[1] = 53;
    percolateDown(heap, 1);

    cout<<"Final Heap:"<<endl;
    printArray(heap);

    //Build Heap using insert only, as an ONLINE DS
    vector<int> heap2;
    for(int i = 0; i < v.size(); i++)
    {
        insert(heap2, v[i]);
    }
    cout<<"Heap built using insert only->"<<endl;
    printArray(heap2);

    return 1;
}
