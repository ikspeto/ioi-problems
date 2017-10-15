#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstring>
#include <utility>

using namespace std;

int n, m, l;
vector<pair<int, int> > adj[100010];
vector<int> components[100010];
short color[100010], n_color = 0;
bool visited[100010];
short edge_degree[100010];
int dists[100010];
short centers[100010];

/*
*   BFS variables
*/
queue<int> q;
int ci;

void find_disjoint_sets()
{
    /*
    *   Finding disjoint sets
    */

    int i, j, N;
    N = 0;
    while(N < n)
    {
        for(i=0;i<n;i++)
            if(color[i] == -1)
                break;
        if(i == n)
            break;
        q.push(i);
        while(!q.empty())
        {
            ci = q.front(); q.pop();
            color[ci] = n_color;
            components[n_color].push_back(ci);
            N++;

            for(i=0;i<adj[ci].size();i++)
            {
                if(color[adj[ci][i].first] == -1)
                    q.push(adj[ci][i].first);
            }
        }
        n_color++;
    }
}

int main()
{
    ios::sync_with_stdio(false);
    memset(color, -1, sizeof(color));
    int i, j, t, z;
    int a, b, c, N, biggest1 = 0, biggest2 = 0;
    vector<int> vdists;

    cin >> n >> m >> l;
    for(i=0;i<m;i++)
    {
        cin >> a >> b >> c;
        adj[a].push_back(make_pair(b, c));
        adj[b].push_back(make_pair(a, c));
    }
    for(i=0;i<n;i++)
        edge_degree[i] = adj[i].size();

    find_disjoint_sets();

    /*
    *   Finding centers of sets
    */

    for(i=0;i<n_color;i++)
    {
        N = 0;
        t = 0;
        while(N < components[i].size())
        {
            for(j=0;j<components[i].size();j++)
                if(edge_degree[components[i][j]] == 1 || edge_degree[components[i][j]] == 0)
                {
                    q.push(components[i][j]);
                    N++;
                    edge_degree[components[i][j]] = -1;
                }
            if(N == components[i].size())
            {
                t = q.front(); q.pop();
                if(q.empty())
                    break;
                z = q.front(); q.pop();
                for(j=0;j<adj[t].size();j++)
                    if(adj[t][j].first == z)
                        break;
                a = dists[z] + adj[t][j].second;
                b = dists[t] + adj[t][j].second;
                dists[t] = max(dists[t], a);
                dists[z] = max(dists[z], b);
                if(dists[z] < dists[t])
                    t = z;

                break;
            }
            while(!q.empty())
            {
                ci = q.front(); q.pop();
                for(j=0;j<adj[ci].size();j++)
                {
                    edge_degree[adj[ci][j].first]--;
                    dists[adj[ci][j].first] = max(dists[adj[ci][j].first], dists[ci] + adj[ci][j].second);
                }
            }
            t++;
        }
        centers[i] = t;
//        cout << dists[centers[i]] << '\n';
        vdists.push_back(dists[centers[i]]);
        if(dists[centers[i]] > biggest1)
            biggest2 = biggest1, biggest1 = dists[centers[i]];
        else if(dists[centers[i]] > biggest2)
            biggest2 = dists[centers[i]];
    }

    sort(vdists.rbegin(), vdists.rend());

    if(vdists.size() > 1)
    {
        biggest1 = vdists[0] + vdists[1] + l;
        if(vdists.size() > 2)
            biggest1 = max(biggest1, vdists[1] + vdists[2] + 2*l);
    }

//    cout << biggest1 + biggest2 + l << endl;
    cout << biggest1 << endl;
    return 0;
}
