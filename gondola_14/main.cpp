#include <iostream>
#include <vector>
#include <algorithm>

#define MOD 1000000009

using namespace std;

bool valid(int n, vector<int> input_seq)
{
    int i, j, displacement;
    bool visited[250010] = {false};

    for(i=0;i<n;i++)
        if(input_seq[i] <= n)
        {
            displacement = input_seq[i] - i - 1;
            break;
        }
    if(displacement < 0)
        displacement += n;

    for(i=0;i<n;i++)
        if(visited[input_seq[i]])
            return false;
        else
            visited[input_seq[i]] = true;

    for(i=0;i<n;i++)
    {
        if(input_seq[i] > n)
            continue;
        if(input_seq[i]%n != (i+1+displacement)%n)
            return false;
    }
    return true;
}

void replacement(int n, vector<int> input_seq, vector<int> &replacement_seq)
{
    int i, j, displacement = 0;
    vector<pair<int, int> > replaced;
    int replacer = n+1;

    for(i=0;i<n;i++)
        if(input_seq[i] <= n)
        {
            displacement = input_seq[i] - i - 1;
            break;
        }
    if(displacement < 0)
        displacement += n;

    for(i=0;i<n;i++)
    {
        if(input_seq[i] > n)
        {
            if((i+1+displacement) > n)
                replaced.push_back(make_pair(input_seq[i] , (i+1+displacement)%n));
            else if((i+1+displacement) == n)
                replaced.push_back(make_pair(input_seq[i] , n));
            else
                replaced.push_back(make_pair(input_seq[i] , (i+1+displacement)));
        }
    }

    sort(replaced.begin(), replaced.end());

    for(i=0;i<replaced.size();i++)
    {
        replacement_seq.push_back(replaced[i].second);
        replaced[i].second = replacer;
        while(replaced[i].second < replaced[i].first)
        {
            replacement_seq.push_back(replaced[i].second);
            replaced[i].second++; replacer++;
        }
        replacer++;
    }
}

long long count_replacement(int n, vector<int> input_seq)
{
    int i, j, displacement = 0;
    vector<pair<int, int> > replaced;
    int replacer = n+1;

    for(i=0;i<n;i++)
        if(input_seq[i] <= n)
        {
            displacement = input_seq[i] - i - 1;
            break;
        }
    if(displacement < 0)
        displacement += n;

    for(i=0;i<n;i++)
    {
        if(input_seq[i] > n)
        {
            if((i+1+displacement) > n)
                replaced.push_back(make_pair(input_seq[i] , (i+1+displacement)%n));
            else if((i+1+displacement) == n)
                replaced.push_back(make_pair(input_seq[i] , n));
            else
                replaced.push_back(make_pair(input_seq[i] , (i+1+displacement)));
        }
    }

    sort(replaced.begin(), replaced.end());

    for(i=0;i<replaced.size();i++)
    {
        replacement_seq.push_back(replaced[i].second);
        replaced[i].second = replacer;
        while(replaced[i].second < replaced[i].first)
        {
            replacement_seq.push_back(replaced[i].second);
            replaced[i].second++; replacer++;
        }
        replacer++;
    }
}

int main()
{
    int t, i, j, n, a;
    vector<int> input_seq;

    cin >> t;
    switch(t)
    {
    case 1:
    case 2:
    case 3:
        {
        cin >> n; input_seq = vector<int> (n);
        for(i=0;i<n;i++)
            cin >> input_seq[i];

        cout << valid(n, input_seq) << '\n';
        break;
        }
    case 4:
    case 5:
    case 6:
        {
        cin >> n; input_seq = vector<int> (n);
        for(i=0;i<n;i++)
            cin >> input_seq[i];

        vector<int> replacement_seq;
        replacement(n, input_seq, replacement_seq);
        cout << replacement_seq.size() << ' ';
        for(i=0;i<replacement_seq.size();i++)
            cout << replacement_seq[i] << ' ';
        cout << '\n';
        break;
        }
    case 7:
    case 8:
    case 9:
    case 10:
        cout << -1 << '\n';
        break;
    default:
        cout << -1 << '\n';
        break;
    }

    return 0;
}
