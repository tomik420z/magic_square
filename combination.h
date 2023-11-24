#pragma once 

#include <iostream>
#include <iterator>
#include <vector>
#include <cstdlib>

using namespace std;

struct combinations
{
    typedef vector<long long> combination_t;

    // initialize status
    combinations(size_t N, size_t R) :
       completed(N < 1 || R > N),
       generated(0),
       N(N), R(R)
    {
        curr.reserve(R);

        for (size_t c = 1; c <= R; ++c) {
            curr.push_back(c);
        }
    }

   // true while there are more solutions
   bool completed;

   // count how many generated
   size_t generated;

   // get current and compute next combination
   combination_t next()
   {
       combination_t ret = curr;

       // find what to increment
       completed = true;
       for (long long i = R - 1; i >= 0; --i)
           if (curr[i] < N - R + i + 1)
           {
               int j = curr[i] + 1;
               while (i <= R-1)
                   curr[i++] = j++;
               completed = false;
               ++generated;
               break;
           }

       return ret;
   }
private:

   size_t N, R;
   combination_t curr;
};
/*
int main(int argc, char **argv)
{
    int N = 6;
    int R = 3;
    combinations cs(N, R);
    while (!cs.completed)
    {
        combinations::combination_t c = cs.next();
        std::cout << "[ ";
        for(auto num : c) {
            std::cout << num << " ";
        }
        std::cout << ']' << std::endl;
        //copy(c.begin(), c.end(), ostream_iterator<int>(cout, ","));
        cout << endl;
    }
    return cs.generated;
}*/