#include <iostream>
#include <queue>
#include <utility>
#include <vector>

using namespace std;

int imap[100][100];
int rooms[100][100], room_num = 1;
int room_size[2510];
int n, m;
int is[4] =    {1, 0, -1, 0};
int js[4] =    {0, 1, 0, -1};
int walls[4] = {8, 4, 2, 1};
			//  S, E, N, W
char let[4]  = {'S', 'E', 'N', 'W'};
		  //cell,direction
vector<pair<short, pair<pair<short, short>, short> > > wall[2510];

void flood_fill(int si, int sj)
{
	queue<int> qi, qj;
	int ci, cj, ti, tj, temp, i;
	rooms[si][sj] = room_num;
	qi.push(si); qj.push(sj);
	while(!qi.empty())
	{
		ci = qi.front(); qi.pop();
		cj = qj.front(); qj.pop();
		temp = imap[ci][cj];

		for(i=0;i<4;i++)
		{
			if(walls[i] <= temp)
			{
				temp -= walls[i];
				continue;
			}

			ti = ci + is[i];
			tj = cj + js[i];
			if(ti >= 0 && ti < n && tj >= 0 && tj < m && rooms[ti][tj] == 0)
			{
				rooms[ti][tj] = room_num;
				qi.push(ti);
				qj.push(tj);
			}
		}
	}
}

int main()
{
	int i, j, ti, tj;

	cin >> m >> n;
	for(i=0;i<n;i++)
		for(j=0;j<m;j++)
			cin >> imap[i][j];

	for(i=0;i<n;i++)
		for(j=0;j<m;j++)
		{
			if(rooms[i][j] == 0)
				flood_fill(i, j), room_num++;
		}
    for(i=0;i<n;i++)
        for(j=0;j<m;j++)
            room_size[rooms[i][j]]++;

    bool are_neighbors;
	for(j=0;j<m;j++)
	{
		for(i=n-1;i>=0;i--)
		{
			for(int z=2;z>=1;z--)
			{
				ti = i + is[z];
				tj = j + js[z];
				are_neighbors = false;

				if(ti >= 0 && ti < n && tj >= 0 && tj < m && rooms[ti][tj] != rooms[i][j])
				{
//				    for(int t=0;t<wall[rooms[i][j]].size();t++)
//                        if(wall[rooms[i][j]][t].first == rooms[ti][tj])
//                        {
//                            are_neighbors = true;
//                            break;
//                        }
//                    if(are_neighbors)
//                        continue;
//					wall[min(rooms[i][j], rooms[ti][tj])].push_back(make_pair(max(rooms[i][j], rooms[ti][tj]), make_pair(make_pair(i, j), z)));
					wall[rooms[i][j]].push_back(make_pair(rooms[ti][tj], make_pair(make_pair(i, j), z)));
					wall[rooms[ti][tj]].push_back(make_pair(rooms[i][j], make_pair(make_pair(i, j), z)));
//					wall[rooms[ti][tj]][rooms[i][j]] = wall[rooms[i][j]][rooms[ti][tj]] = make_pair(make_pair(i, j), z);
				}
			}
		}
	}

	int biggest_size = 0, bi, bj, bd, largest_room = 0;

	for(i=1;i<room_num;i++)
	{
		largest_room = max(largest_room, room_size[i]);
		for(int z=0;z<wall[i].size();z++)
        {
            j = wall[i][z].first;
            if(biggest_size < room_size[i]+room_size[j])
			{
				biggest_size = room_size[i]+room_size[j];
				bi = wall[i][z].second.first.first;
				bj = wall[i][z].second.first.second;
				bd = wall[i][z].second.second;
			} else if(biggest_size == room_size[i]+room_size[j]) {
                if(bj > wall[i][z].second.first.second) {
                    bi = wall[i][z].second.first.first;
                    bj = wall[i][z].second.first.second;
                    bd = wall[i][z].second.second;
                } else if(bj == wall[i][z].second.first.second) {
                    if(bi < wall[i][z].second.first.first)
                    {
                        bi = wall[i][z].second.first.first;
                        bj = wall[i][z].second.first.second;
                        bd = wall[i][z].second.second;
                    } else if(bi == wall[i][z].second.first.first && bd == 1 && wall[i][z].second.second == 2) {
                        bd = wall[i][z].second.second;
                    }
                }
            }
        }
	}

	cout << room_num - 1 << '\n';
	cout << largest_room << '\n';
	cout << biggest_size << '\n';
	cout << bi+1 << ' ' << bj+1 << ' ' << let[bd] << '\n';
//	for(i=0;i<n;i++)
//	{
//		for(j=0;j<m;j++)
//		{
//			cout << rooms[i][j] << " ";
//		}
//		cout << endl;
//	}
	return 0;
}
