#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <climits>

using namespace std;

//
//int moves[][] = {
//    {0, 1, 3, 4},
//    {0, 1, 2},
//    {1, 2, 4, 5},
//    {0, 3, 6},
//    {1, 3, 4, 5, 7},
//    {2, 5, 8},
//    {3, 4, 6, 7},
//    {6, 7, 8},
//    {2, 5, 8},
//    {4, 5, 7, 8}
//};

string moves[] = {"ABDE", "ABC", "BCEF", "ADG", "BDEFH", "CFI", "DEGH", "GHI", "EFHI"};
int clocks[9];
stack<int> order;
string final_rez;
int moves_done[40], j_move = 0;


bool rec(int i_move)
{
    /// Check if all clocks are at 12
    bool are_set = true;
    for(int i=0;i<9;i++)
        if(clocks[i] != 0)
        {
            are_set = false;
            break;
        }
    if(are_set)
    {
        string rez = "";
        for(int i=0;i<j_move;i++)
        {
            rez += (char(moves_done[i]+'0'+1));
            rez += " ";
        }
        final_rez = min(final_rez, rez);
        return true;
    }
    /// End of check
    if(i_move > 8)
        return false;
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<moves[i_move].size();j++)
        {
            clocks[moves[i_move][j]-'A'] += 3;
            clocks[moves[i_move][j]-'A'] %= 12;
        }
        moves_done[j_move] = i_move;
        j_move++;
        rec(i_move+1);
    }
    for(int i=0;i<3;i++)
    {
        j_move--;
        for(int j=0;j<moves[i_move].size();j++)
        {
            clocks[moves[i_move][j]-'A'] -= 3;
            if(clocks[moves[i_move][j]-'A'] < 0)
                clocks[moves[i_move][j]-'A'] += 12;
        }
    }
    rec(i_move+1);
}

int main()
{
    int i, j, a;
    for(i=0;i<9*4;i++)
        final_rez += "9 ";
    for(i=0;i<9;i++)
        cin >> clocks[i], clocks[i] %= 12;

    rec(0);
    cout << final_rez << '\n';
    return 0;
}
