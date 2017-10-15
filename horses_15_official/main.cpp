#include <iostream>
#include <cstring>

using namespace std;

int n, *confidence;
int *host, *protocol;
/*
*   0 - I am your friend
*   1 - My friends are your friends
*   2 - We are your friends
*/
int *used, *unused;

int main()
{
    ios::sync_with_stdio(false);
    int i, j;

    cin >> n;

    confidence = new int[n];
    host = new int[n]; protocol = new int[n];
    used = new int[n]; unused = new int[n];

    memset(used, 0, sizeof(int[n]));
    memset(unused, 0, sizeof(int[n]));

    for(i=0;i<n;i++)
        cin >> confidence[i], used[i] = confidence[i];
    for(i=1;i<n;i++)
        cin >> host[i] >> protocol[i];

    for(i=n-1;i>=1;i--)
    {
//        if(used[i] == 0)
//            used[i] = confidence[i], unused[i] = 0;
        switch(protocol[i])
        {
        case 0:
            used[host[i]] += unused[i];
            unused[host[i]] = max(unused[host[i]] + used[i], unused[host[i]] + unused[i]);
            break;
        case 1:
            used[host[i]] = max(used[host[i]] + used[i], max(unused[host[i]] + used[i], used[host[i]] + unused[i]));
            unused[host[i]] += unused[i];
            break;
        case 2:
            used[host[i]] = max(unused[host[i]] + used[i], used[host[i]] + unused[i]);
            unused[host[i]] += unused[i];
            break;
        }
    }
    cout << max(used[0], unused[0]) << '\n';
    return 0;
}
