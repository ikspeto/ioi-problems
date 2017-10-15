#include <iostream>
#include <numeric>
#include <algorithm>
#include <set>

using namespace std;

int table[5][5];
int sums[2][5], nums[2][5];
int sum;
                    //i, j, prev
set<int> possibles[5][10];

bool primes[100000];

bool is_prime(int n)
{
    if(n == 1)
        return false;
    if(n == 2)
        return false;
    if(n == 3)
        return true;
    if(n%2 == 0)
        return false;
    for(int i=3;i<=sqrt(n);i+=2)
        if(n%i == 0)
            return false;
    return true;
}

void rec(int ci, int cj)
{
    if(ci == 5) {
        for(int i=0;i<5;i++)
        {
            if(sums[1][i] != sum || !primes[nums[1][i]])
                return;
        }
        for(int i=0;i<5;i++)
        {
            for(int j=0;j<5;j++)
                cout << table[i][j];
            cout << '\n';
        }
        cout << '\n';
        int temp;
        cin >> temp;
        return;
    }
    if(cj == 5)
    {
        if(sums[0][ci] != sum || !primes[nums[0][ci]])
            return;
        rec(ci+1, 0);
        return;
    }
    int startj = 0, starti;
    if(cj == 0)
        startj = 0;
    else
        startj = table[ci][cj-1];
    if(ci == 0)
        starti = 0;
    else
        starti = table[ci-1][cj];
    int temp = -1;
    for(auto i:possibles[cj][startj])
    {
        temp = -1;
        for(auto j : possibles[ci][starti])
            if(j == i) {
                temp = j;
                break;
            }

        if(temp == i)
        {
            table[ci][cj] = temp;
            sums[0][ci] += temp;
            sums[1][cj] += temp;
            nums[0][ci] *= 10; nums[0][ci] += temp;
            nums[1][cj] *= 10; nums[1][cj] += temp;
            rec(ci, cj+1);
            sums[0][ci] -= temp;
            sums[1][cj] -= temp;
            nums[0][ci] /= 10;
            nums[1][cj] /= 10;
        }
    }
}

int main()
{
    int i, j, temp, d, a, b;

    cin >> sum >> table[0][0];
    sums[0][0] = table[0][0];
    sums[1][0] = table[0][0];
    nums[0][0] = table[0][0];
    nums[1][0] = table[0][0];
    for(i=10001;i<100000;i+=2) {
        if(is_prime(i))
        {
            primes[i] = true;
            d = 10000; a = 0;
            temp = 0;
            for(j=0;j<5;j++)
            {
               a = (i/d)%10;
               temp += a;
               d /= 10;
            }
            if(temp == sum) {
                d = 10000; a = 0;
                for(j=0;j<5;j++)
                {
                    b = a;
                    a = (i/d)%10;
                    possibles[j][b].insert(a);
                    d /= 10;
                }
            }
        }
    }
    rec(0, 1);

    return 0;
}
