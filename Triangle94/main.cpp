#include <iostream>

using namespace std;

int triangle[110][110];
int dp[110][110];

int main()
{
    int i, j, n;

    cin >> n;
    for(i=0;i<n;i++)
        for(j=0;j<=i;j++)
            cin >> triangle[i][j];
    dp[0][0] = triangle[0][0];
    for(i=0;i<n-1;i++)
    {
    	for(j=0;j<=i;j++)
    	{
    	    dp[i+1][j] = max(dp[i+1][j], triangle[i+1][j] + dp[i][j]);
    	    dp[i+1][j+1] = max(dp[i+1][j+1], triangle[i+1][j+1] + dp[i][j]);
    	}
    }
    int best = 0;
    for(i=0;i<n;i++)
    	best = max(best, dp[n-1][i]);
    cout << best << endl;
    return 0;
}
