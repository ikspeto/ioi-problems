#include <fstream>
#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <climits>

using namespace std;

long long n, k, l;
pair<long long, long long>      clock_wise[10000010];
pair<long long, long long> anti_clock_wise[10000010];
long long positions[10000010], teams[10000010];
long long its[10000010];

inline long long lmin(long long a, long long b)
{
    if(a < b)
        return a;
    return b;
}

int main()
{
    ifstream cin("input.txt");
    ios::sync_with_stdio(false);
    long long  i, j = 0;
    long long a;

    cin >> n >> k >> l;
    for(i=0;i<n;i++)
        cin >> positions[i];

    if(positions[0] != 0)
        its[0] = 0, j++;
    its[j] = positions[0];
    teams[j]++;
    for(i=1;i<n;i++)
    {
        if(positions[i] == positions[i-1])
            teams[j]++;
        else
        {
            j++;
            its[j] = positions[i];
            teams[j]++;
        }
    }
    long long N = j+1;
    long long temp, temp2, ttemp1, ttemp2;
    clock_wise[0].second = k;
    for(i=1;i<N;i++)
    {
        if(clock_wise[i-1].second != 0)
        {
            if(teams[i] <= clock_wise[i-1].second)
            {
                clock_wise[i].first = clock_wise[i-1].first + its[i]-its[i-1];
                clock_wise[i].second = clock_wise[i-1].second-teams[i];
            } else {
                clock_wise[i].first = clock_wise[i-1].first + its[i]-its[i-1];
                temp = teams[i] - clock_wise[i-1].second;
                while(temp > 0)
                {
                    clock_wise[i].first += lmin(2 * its[i], 2*(l - its[i]));
                    if(k > temp) {
                        clock_wise[i].second = k-temp;
                        temp = 0;
                    } else {
                        clock_wise[i].second = 0;
                        temp -= k;
                    }
                }
            }
            long long ttemp1, ttemp2;
            ttemp1 = clock_wise[i-1].first + lmin(its[i-1], l-its[i-1]) + lmin(its[i], l-its[i]);
            if(k > teams[i])
            {
                temp = 0;
                ttemp2 = k-teams[i];
            } else {
                temp = teams[i] - k;
                ttemp2 = 0;
            }
            while(temp > 0)
            {
                ttemp1 += lmin(2 * its[i], 2 * (l - its[i]));
                if(k > temp) {
                    ttemp2 = k - temp;
                    temp = 0;
                } else {
                    ttemp2 = 0;
                    temp -= k;
                }
            }
            if(ttemp1 < clock_wise[i].first)
            {
                clock_wise[i].first = ttemp1;
                clock_wise[i].second = ttemp2;
            }
        } else {
            clock_wise[i].first = clock_wise[i-1].first + lmin(its[i-1], l-its[i-1]) + lmin(its[i], l-its[i]);
            if(k > teams[i])
            {
                temp = 0;
                clock_wise[i].second = k-teams[i];
            } else {
                temp = teams[i] - k;
                clock_wise[i].second = 0;
            }
            while(temp > 0)
            {
                clock_wise[i].first += lmin(2 * its[i], 2*(l - its[i]));
                if(k > temp) {
                    clock_wise[i].second = k-temp;
                    temp = 0;
                } else {
                    clock_wise[i].second = 0;
                    temp -= k;
                }
            }
        }
    }
    its[N] = l; N++;
    anti_clock_wise[N-1].second = k;
    for(i=N-2;i>=1;i--)
    {
        if(anti_clock_wise[i+1].second != 0)
        {
            if(teams[i] <= anti_clock_wise[i+1].second)
            {
                anti_clock_wise[i].first = anti_clock_wise[i+1].first + its[i+1]-its[i];
                anti_clock_wise[i].second = anti_clock_wise[i+1].second-teams[i];
            } else {
                anti_clock_wise[i].first = anti_clock_wise[i+1].first + its[i+1]-its[i];
                temp = teams[i] - anti_clock_wise[i+1].second;
                while(temp > 0)
                {
                    anti_clock_wise[i].first += lmin(2 * its[i], 2 * (l - its[i]));
                    if(k > temp) {
                        anti_clock_wise[i].second = k - temp;
                        temp = 0;
                    } else {
                        anti_clock_wise[i].second = 0;
                        temp -= k;
                    }
                }
            }
            ttemp1, ttemp2;
            ttemp1 = anti_clock_wise[i+1].first + lmin(its[i+1], l-its[i+1]) + lmin(its[i], l-its[i]);
            if(k > teams[i])
            {
                temp = 0;
                ttemp2 = k-teams[i];
            } else {
                temp = teams[i] - k;
                ttemp2 = 0;
            }
            while(temp > 0)
            {
                ttemp1 += lmin(2 * its[i], 2 * (l - its[i]));
                if(k > temp) {
                    ttemp2 = k - temp;
                    temp = 0;
                } else {
                    ttemp2 = 0;
                    temp -= k;
                }
            }
            if(ttemp1 < anti_clock_wise[i].first)
            {
                anti_clock_wise[i].first = ttemp1;
                anti_clock_wise[i].second = ttemp2;
            }
        } else {
            anti_clock_wise[i].first = anti_clock_wise[i+1].first + lmin(its[i+1], l-its[i+1]) + lmin(its[i], l-its[i]);
            if(k > teams[i])
            {
                temp = 0;
                anti_clock_wise[i].second = k-teams[i];
            } else {
                temp = teams[i] - k;
                anti_clock_wise[i].second = 0;
            }
            while(temp > 0)
            {
                anti_clock_wise[i].first += lmin(2 * its[i], 2 * (l - its[i]));
                if(k > temp) {
                    anti_clock_wise[i].second = k - temp;
                    temp = 0;
                } else {
                    anti_clock_wise[i].second = 0;
                    temp -= k;
                }
            }
        }
    }

    long long best = LLONG_MAX;

    for(i=1;i<N;i++)
    {
        best = lmin(best, anti_clock_wise[i].first   + lmin(its[i], (l - its[i]))
                             + clock_wise[i-1].first + lmin(its[i-1], (l - its[i-1])));
    }

    cout << best << '\n';
    return 0;
}
