#include <iostream>
#include <cstdint>
#include <queue>
#include <vector>
#include <map>
#include <utility>
#include <algorithm>
#include <string>

using namespace std;

class Point {
public:
	Point() {
		x = 0;
		y = 0;
		value = 0; 
	}

	Point(int16_t a, int16_t b, int16_t v)
	{
		x = a; 
		y = b;
		value = v; 
	}
	
	Point &operator= (const Point& rhs) 
	{
		if (this == &rhs) return *this; 
		x = rhs.x; 
		y = rhs.y; 
		value = rhs.value; 

		return *this; 
	}
	bool operator== (const Point& p) const
	{
		if (x == p.x && y == p.y && value == p.value)
			return true;
		else
			return false; 
	}
	
	int16_t value;
	int16_t x;
	int16_t y;
};

ostream& operator<< (ostream& out, const Point& p)
{
	out << "(" << p.x << "," << p.y << ")" << " -- " << p.value;
	return out;
}

bool operator< (const Point &p1, const Point &p2) {
	if (p1.x == p2.x)
	{
		return p1.y < p2.y;
	}
	else
		return p1.x < p2.x;
}

#define ROW 3
#define COL 3

int16_t grid[ROW][COL] = {
	{0, 0, 0},
	{1, 0, 0},
	{0, 0, 0}
}; 

map< Point, vector<Point> > neighbours = {
	{ Point(0, 0, grid[0][0]), { Point(0, 1, grid[0][1]), Point(1, 0, grid[1][0]) } },
	{ Point(0, 1, grid[0][1]), { Point(0, 2, grid[0][2]), Point(1, 1, grid[1][1]) } }, 
	{ Point(0, 2, grid[0][2]), { Point(1, 2, grid[1][2]), Point(0, 1, grid[0][1]) } },
	   
	{ Point(1, 2, grid[1][2]), { Point(2, 2, grid[2][2]), Point(1, 1, grid[1][1]) } }, 
	{ Point(1, 1, grid[1][1]), { Point(2, 1, grid[2][1]), Point(1, 0, grid[1][0]) } }, 
	{ Point(1, 0, grid[1][0]), { Point(1, 1, grid[1][1]), Point(2, 0, grid[2][0]) } }, 

	{ Point(2, 0, grid[2][0]), { Point(2, 1, grid[2][1]), Point(1, 0, grid[1][0]) } },
	{ Point(2, 1, grid[2][1]), { Point(2, 2, grid[2][2]), Point(2, 0, grid[2][0]) } },
	{ Point(2, 2, grid[2][2]), { Point(2, 1, grid[2][1]), Point(1, 2, grid[1][2]) } }
};

void drawGrid(const vector<Point>& path )
{
	string drawing[ROW][COL]; 

	for (int16_t x = 0; x < ROW; x++)
	{
		for (int16_t y = 0; y < COL; y++)
		{
			drawing[x][y] = to_string(grid[x][y]); 
		}
	}

	for (size_t p = 0; p < path.size(); p++)
	{
		drawing[path[p].x][path[p].y] = '+';
	}

	for (int16_t x = 0; x < ROW; x++)
	{

		for (int16_t y = 0; y < COL; y++)
		{
			cout << drawing[x][y] << " ";
		}
		cout << "\n";
	}
}

bool isBlocked(const Point& p){
	return p.value == 1 ? true : false; 
}


int main()
{
	Point start_pnt = Point(0, 0, 0); 
	Point goal_pnt	= Point(2, 2, 0);

	queue<Point> visited;
	visited.push(start_pnt); 

	vector< pair<Point, Point> > came_from; 
	came_from.push_back(make_pair(start_pnt, Point(-1, -1, 0)));

	vector<Point> order; 

	int16_t step_number = 0; 
	bool been_already = false; 

	int16_t neightbour_cout = 0; 
	Point temp_neighbour = { -1, -1, 0 };
	Point last_neighbour = { -1, -1, 0 };

	while( !visited.empty() )
	{
		Point current = visited.front();
		visited.pop();

		if (current == goal_pnt)
		{
			order.push_back(goal_pnt);
			break;
		}

		neightbour_cout = 0; 

		for (Point& next : neighbours[current])
		{
			been_already = false;
			if (isBlocked(next))
			{
				continue;	// check another neighbour 
			}

			for (size_t c = 0; c < came_from.size(); c++)
			{
				if (next == came_from[c].first)
				{
					been_already = true; 
					break; 
				}
			}
			

			if (!been_already)
			{

				visited.push(next);
				neightbour_cout += 1;
				came_from.push_back(make_pair(next, current));
			}
		}

		// if the vertix has two free "neighbours"
		if (neightbour_cout == 2) 
		{
			temp_neighbour = visited.front();
			visited.pop();
			last_neighbour = visited.back(); 
			
			if (temp_neighbour.y == start_pnt.y) //	check if the column if free
			{
				if (grid[ROW-1][start_pnt.y] == 0)
				{
					visited.pop();
					visited.push(temp_neighbour);	// remove the last vertix and add the previous one 
				}
			}
			else
			{
				// choose the path if the goal cannot be reach directly 
				if (abs(temp_neighbour.y - goal_pnt.y) < abs(last_neighbour.y - goal_pnt.y))
				{
					visited.pop();
					visited.push(temp_neighbour);
				}
			}
		}

		order.push_back(current); 
		step_number += 1; 
		been_already = false;
	}

	if (!count(order.begin(), order.end(), goal_pnt))
	{
		cout << "The goal point is unreachable" << endl;
	}

	// Reduced sequence of steps
	for (size_t i = 0; i < order.size()-2; i += 1)
	{
		if (order[i].x == order[i + 2].x || order[i].y == order[i + 2].y)
		{
			step_number -= 1; 
		}
	}

	cout << "Steps number: " << step_number << endl; 
	drawGrid(order);

	return 0;
}
