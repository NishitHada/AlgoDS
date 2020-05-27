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

class Heap{
public:
    std::vector<int> heap;

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
        // cout<<"Parent->"<< heap[idx] <<endl;;
        // cout<<"Children->"<< heap[2*idx] <<"\t"<< heap[2*idx+1]<<endl;

        int max_child_idx = (heap[2*idx] > heap[2*idx+1]) ? 2*idx : 2*idx+1;
        // cout<<"Max child @ "<< max_child_idx <<" -> "<< heap[max_child_idx] <<endl;

        if(heap[idx] < heap[max_child_idx])
        {
            swap(heap[idx], heap[max_child_idx]);
            percolateDown(heap, max_child_idx);
        }
    }

    void printHeap()
    {
        for(int i = 0; i < heap.size(); i++)
        {
            cout<<heap[i]<<" ";
        }
        cout<<endl;
    }

    void insert(int num)
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

    vector<int> buildHeap(vector<int> A)
    {
        heap = A;
        heap.insert(heap.begin(), 0);

        for(int i = A.size() - 1; i > 0; i--)
        {
            percolateDown(heap, i);
        }

        return heap;
    }

    void deleteRoot()
    {
        heap[1] = heap.back();
        heap.resize(heap.size() - 1);
        percolateDown(heap, 1);
    }

};


std::vector<int> heapSort(std::vector<int> v)
{
    std::vector<int> ans;
    Heap h;

    h.buildHeap(v);
    while(h.heap.size() > 1)
    {
        // h.printHeap();
        ans.push_back(h.heap[1]);
        // printArray(ans);
        h.deleteRoot();
    }

    return ans;
}

int main()
{
    vector<int> A = {23, 98, 12, 3, 54, 75};
    // std::vector<int> A = {5, 1, 6, 23, 12, 3};

    std::vector<int> ans = heapSort(A);
    printArray(ans);

    return 1;
}
