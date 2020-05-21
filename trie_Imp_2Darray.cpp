// #include "mylib.h"
#include <bits/stdc++.h>
using namespace std;

int trie[100000][28];       //Size will be (isWord + 26 alpha +  count)(len of longest word)*(no of words)
int next_available;

void insert(string word)
{
  cout <<endl<< "New Call:" << word << '\n';
  int curr_pos = 0;

  for(int i = 0; i < word.size(); i++)
  {
    int idx = word[i] - 'a' + 1;
    cout<<"index of:"<<word[i]<<" @ "<<curr_pos<<" -> "<<trie[curr_pos][idx]<<endl;

    if( trie[curr_pos][idx] == -1)
    {
      //Allocate next next_available idx for this alphabet
      trie[curr_pos][idx] = next_available;   //Link this node to new char idx
      curr_pos = next_available;
      next_available++;

      cout<<"New Node allocated @ "<<curr_pos<<" for "<<word[i]<<endl;

      trie[curr_pos][27] = 1; //Initialize count to 1
    }
    else
    {
        curr_pos = trie[curr_pos][idx];
      trie[curr_pos][27]++;// = trie[curr_pos][27] + 1;   //Increase the count
      // cout<<"Updated Count of "<<word[i]<<" traversal:"<<trie[curr_pos][27]<<endl;
      // curr_pos = trie[curr_pos][idx];
    }

    cout<<"Updated Count of "<<word[i]<<" traversal:"<<trie[curr_pos][27]<<endl;
  }

  trie[curr_pos][0] = 1; //Set isWord to true
}

void traverse(string word)
{
    std::cout <<endl<< "New Call:" << word << '\n';
    int curr_pos = 0;

    for(int i = 0; i < word.size(); i++)
    {
        int idx = word[i] - 'a' + 1;
        curr_pos = trie[curr_pos][idx];

        cout<<word[i]<<" @ "<<curr_pos<<endl;
        cout<<"Count @ this char:"<<trie[curr_pos][27]<<" ";
        cout<<"isWord:"<<trie[curr_pos][0]<<endl;
    }
}

void dispEveryWord(int curr_pos, string word)
{
    if(trie[curr_pos][0] == 1) cout<<word<<endl;

    for(int i = 1; i <= 26; i++)
    {
        if(trie[curr_pos][i] != -1)
        {
            string tmp = word;
            char ch = (char) ('a' + (i-1) );
            tmp += ch;
            dispEveryWord(trie[curr_pos][i], tmp);
        }
    }
}

void dispPrefix(int curr_pos, string word)
{
    if(trie[curr_pos][27] == 1)
    {
        if(word.size() > 1)
        {
            word.pop_back();
            cout<<word<<endl;
        }
        return;
     }

    for(int i = 1; i <= 26; i++)
    {
        if(trie[curr_pos][i] != -1)
        {
            string tmp = word;
            char ch = (char) ('a' + (i-1) );
            tmp += ch;
            dispPrefix(trie[curr_pos][i], tmp);
        }
    }

}

void deleteInTrie(string word)
{
    int curr_pos = 0;
    int prev_pos = 0;

    int flag = 0;
    int delete_idx = -1, delete_pos = -1;
    vector<int> deleteList;

    for(int i = 0; i < word.size(); i++)
    {
        int idx = word[i] - 'a' + 1;
        prev_pos = curr_pos;
        curr_pos = trie[curr_pos][idx];

        //Count of curr node = 1
        if(trie[curr_pos][27] == 1)
        {
            if(flag == 0)
            {
                flag = 1;
                delete_pos = prev_pos;
                delete_idx = idx;
            }
            deleteList.push_back(curr_pos);
        }
        else trie[curr_pos][27]--;
    }

    trie[curr_pos][0] = -1; //Set isWord for last char to -1

    // cout<< delete_pos <<" -> "<< delete_idx <<endl;
    if(delete_pos != -1) trie[delete_pos][delete_idx] = -1;

    for(int i = 0; i < deleteList.size(); i++)
    {
        // std::cout << deleteList[i] << '\n';
        for(int j = 0; j < 28; j++) trie[ deleteList[i] ][j] = -1;
    }
}

int main()
{
  //Initialization - to avoid garbage value in case of multiple queries
  memset(trie, -1, sizeof(trie));
  next_available = 1;

  vector<string> lex = {"abra", "du", "cat", "dog", "duck", "catch"};
  // vector<string> lex = {"cat", "catch"};
  string word;

  for(auto x:lex)
  {
    insert(x);
  }
  cout<<endl<<endl;

  // for(auto x:lex)
  // {
  //     traverse(x);
  // }
  // cout<<endl<<endl;

  cout<<endl<<"All common Prefixes ->"<<endl;
  dispPrefix(0, word);
  cout<<endl;


  cout<<endl<<"All words in trie->"<<endl;
  dispEveryWord(0, word);
  cout<<endl;

  // traverse("dog");

  std::cout << "Deletion Query" << '\n';
  deleteInTrie("abra");
  deleteInTrie("cat");
  deleteInTrie("du");

  // traverse("dog");

  cout<<endl<<"All words in trie after DELETION->"<<endl;
  dispEveryWord(0, word);
  cout<<endl;


  return 1;
}
