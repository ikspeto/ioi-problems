#include <iostream>
#include <vector>
#include <stack>

using namespace std;

int schedule[60], schedule_2[60], n;
vector<pair<int, int> > buses;
stack<int> order;
bool finished = false;

void make_schedule(int i = 0)
{
    if(i >= buses.size() || finished || order.size() >= 17)
        return;

    finished = true;

    for(int i=0;i<60;i++)
        if(schedule[i] != 0)
        {
            finished = false;
            break;
        }

    if(finished)
    {
        cout << order.size() << endl;
        while(!order.empty())
        {
            cout << buses[order.top()].first << ' ' << buses[order.top()].second << '\n';
            order.pop();
        }
        finished = true;
        return;
    }
    int num = 9999999;
    for(int j=buses[i].first;j<60;j+=buses[i].second) /// Check whether current line fits
        if(schedule[j] == 0)
        {
            make_schedule(i+1); /// Don't use current bus line
            return;
        } else {
            num = min(num, schedule[j]);
        }
    for(int t=1;t<=num;t++)
    {
        for(int j=buses[i].first;j<60;j+=buses[i].second) /// Add current line
                schedule[j]--;
        order.push(i);

        make_schedule(i+1); /// Use current bus line
    }
    if(finished)
        return;
    for(int j=buses[i].first;j<60;j+=buses[i].second) /// Remove current line
        schedule[j] += num;
    for(int j=0;j<num;j++)
        order.pop();
    make_schedule(i+1); /// Don't use current bus line
}

int main()
{
    int i, j, t, temp, num;
    bool exists;

    cin >> n;
    for(i=0;i<n;i++)
    {
        cin >> temp;
        schedule[temp]++;
    }

    for(i=1;i<30;i++) /// Interval
    {
        for(j=0;j<i;j++) /// Starting time
        {
            exists = true;
            num = 9999999;
            for(t=j;t<60;t+=i)
                if(schedule[t] == 0)
                {
                    exists = false;
                    break;
                } else {
                    num = min(num, schedule[t]);
                }
            if(exists)
            {
//                for(t=j;t<60;t+=i)
//                    hour[t] -= num;
                for(t=0;t<num;t++)
                    buses.push_back(make_pair(j, i));
//                break;
            }
        }
    }
    make_schedule();
//    cout << buses.size() << '\n';
//    for(i=0;i<buses.size();i++)
//        cout << buses[i].first << ' ' << buses[i].second << '\n';
    return 0;
}
