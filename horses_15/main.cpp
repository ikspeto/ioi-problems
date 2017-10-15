#include <iostream>

using namespace std;

class node
{
public:
    int total_product;
    int best_profit;
    node *left, *right;

    node()
    {
        total_product = 1;
        best_profit = 0;
        left = NULL;
        right = NULL;
    }
};

node root;
node *head;

void build(int *x, int *y, node *cur, int l = 0, int r)
{
    if(l > r)
        return;
    if(l == r)
    {
        cur->total_product *= x[l];
    }
}
int main()
{
    int n, m;
    int *x ,*y;
    int i, j, a, b, val;

    cin >> n;
    x = new int[n];
    y = new int[n];
    for(i=0;i<n;i++)
        cin >> x[i];
    for(i=0;i<n;i++)
        cin >> y[i];

    build();

    cin >> m;
    for(i=0;i<m;i++)
    {
        cin >> a >> b >> val;
        if(a == 1) /// X
            x[b] = val;
        else /// Y
            y[b] = val;
        update(b);
    }
    return 0;
}
