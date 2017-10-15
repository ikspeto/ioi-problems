#include <iostream>

using namespace std;

long long r, l, b;
long long xi[100010], s[100010];

int main()
{
    int i, j, p;
    long long best = 0, cost;
    bool ok;

    cin >> r >> l >> b;
    for(i=1;i<=r;i++)
    {
        cin >> xi[i];
        s[i] = s[i-1] + xi[i-1];
    }
    s[i] += s[i-1] + xi[i-1];

    int l_b = 1, r_b = r, middle;

    while(true)
    {
        middle = (l_b + r_b) / 2 + (l_b + r_b) % 2;
        ok = false;

        for(i=1;i<=r-middle+1;i++)
        {
            j = i + middle - 1;
            p = (i + j) / 2 + (i + j) % 2;

            cost = ((p - i) * xi[p] - (s[p] - s[i]));
            cost +=  ((s[j+1] - s[p+1]) - (j - p) * xi[p]);

            if(cost <= b)
            {
                best = middle;
                ok = true;
                break;
            }
        }
        if(l_b == r_b)
            break;
        if(ok)
            l_b = middle;
        else
            r_b = middle-1;
    }

    cout << best << '\n';
    return 0;
}
