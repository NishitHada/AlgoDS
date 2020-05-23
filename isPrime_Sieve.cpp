#include <bits/stdc++.h>
using namespace std;


class Sieve
{
public:
    int sieve_size;
    std::vector<int> s;

    Sieve(int n)
    {
        sieve_size = n;
        s.assign(sieve_size, 1);
    }

    void make_sieve()
    {
        s[0] = 0;
        s[1] = 0;
        // s[2] = 1;
        // s[3] = 1;

        for(int i = 2; i <= sieve_size; i++)
        {
            for(int j = 2*i; j <= sieve_size; j += i) s[j] = 0;
        }
    }

    void dispSieve()
    {
        for(int i = 1; i <= sieve_size; i++)
        {
            cout<< i <<" -> "<<s[i]<<endl;
        }
    }

    int isPrime(int n)
    {
        return s[n];
    }
};


int main()
{
    Sieve obj1(1000000);

    obj1.make_sieve();
    // obj1.dispSieve();

    vector<int> A = {54923, 25, 61, 905432, 999983};

    for(int i = 0; i < A.size(); i++) cout<< A[i] <<" ->"<< obj1.isPrime(A[i]) <<endl;

    return 1;
}
