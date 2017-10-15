/*
AUTHOR: Mihail Denkovski
DATE: 13.05.2016
PROG: The Wall, IOI 2014
*/

#include <iostream>
#include <cstring>
#include <climits>

#define TREE_SIZE 4200000

using namespace std;

int n, min_tree[TREE_SIZE], max_tree[TREE_SIZE];

void add_bricks(int l, int r, int val, int i = 0, int j = n-1, int node = 1)
{
	if(i > r || j < l)
		return;
	if(i >= l && j <= r)
	{
		min_tree[node] = max(min_tree[node], val);
		max_tree[node] = max(max_tree[node], val);
	}
	else
	{
		// Update children
		if(min_tree[node] != 0)
        {
            min_tree[node*2] = max(min_tree[node*2], min_tree[node]);
            max_tree[node*2] = max(max_tree[node*2], min_tree[node]);
            min_tree[node*2+1] = max(min_tree[node*2+1], min_tree[node]);
            max_tree[node*2+1] = max(max_tree[node*2+1], min_tree[node]);
            min_tree[node] = 0;
		}
		if(max_tree[node] != INT_MAX)
		{
            max_tree[node*2] = min(max_tree[node*2], max_tree[node]);
            max_tree[node*2+1] = min(max_tree[node*2+1], max_tree[node]);
            max_tree[node] = INT_MAX;
		}

		add_bricks(l, r, val, i, (i+j)/2, node*2);
		add_bricks(l, r, val, (i+j)/2+1, j, node*2+1);
	}
}

void remove_bricks(int l, int r, int val, int i = 0, int j = n-1, int node = 1)
{
	if(i > r || j < l)
		return;
	if(i >= l && j <= r)
		max_tree[node] = min(max_tree[node], val);
	else
	{
		// Update children
		if(min_tree[node] != 0)
        {
            min_tree[node*2] = max(min_tree[node*2], min_tree[node]);
            max_tree[node*2] = max(max_tree[node*2], min_tree[node]);
            min_tree[node*2+1] = max(min_tree[node*2+1], min_tree[node]);
            max_tree[node*2+1] = max(max_tree[node*2+1], min_tree[node]);
            min_tree[node] = 0;
		}
		if(max_tree[node] != INT_MAX)
		{
            max_tree[node*2] = min(max_tree[node*2], max_tree[node]);
            max_tree[node*2+1] = min(max_tree[node*2+1], max_tree[node]);
            max_tree[node] = INT_MAX;
		}

		remove_bricks(l, r, val, i, (i+j)/2, node*2);
		remove_bricks(l, r, val, (i+j)/2+1, j, node*2+1);
	}
}

void print_leaves(int i = 0, int j = n-1, int node = 1)
{
	if(i > j)
		return;
	if(i == j)
	{
		cout << min(max_tree[node], min_tree[node]) << '\n';
	} else {
		// Update children
		if(min_tree[node] != 0)
        {
            min_tree[node*2] = max(min_tree[node*2], min_tree[node]);
            max_tree[node*2] = max(max_tree[node*2], min_tree[node]);
            min_tree[node*2+1] = max(min_tree[node*2+1], min_tree[node]);
            max_tree[node*2+1] = max(max_tree[node*2+1], min_tree[node]);
            min_tree[node] = 0;
		}
		if(max_tree[node] != INT_MAX)
		{
            max_tree[node*2] = min(max_tree[node*2], max_tree[node]);
            max_tree[node*2+1] = min(max_tree[node*2+1], max_tree[node]);
            max_tree[node] = INT_MAX;
		}

		print_leaves(i, (i+j)/2, node*2);
		print_leaves((i+j)/2+1, j, node*2+1);
	}
}

int main()
{
	ios::sync_with_stdio(false);
//	memset(max_tree, INT_MAX, sizeof(max_tree));
    int i, m, opr, a, b, val;
    for(i=0;i<TREE_SIZE;i++)
        max_tree[i] = INT_MAX;

	cin >> n >> m;
	for(i=0;i<m;i++)
	{
		cin >> opr >> a >> b >> val;
		if(opr == 1)
			add_bricks(a, b, val);
		else
			remove_bricks(a, b, val);
	}
	print_leaves();
    return 0;
}
