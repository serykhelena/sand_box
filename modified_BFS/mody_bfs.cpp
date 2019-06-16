#include <iostream>
#include <cstdint>
#include <queue>
#include <vector>
#include <set>
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
	
	Point &operator= (const Point& rhs) /* { p.x = x, p.y = y; p.value = value; }*/
	{
		if (this == &rhs) return *this; 
		x = rhs.x; 
		y = rhs.y; 
		value = rhs.value; 

		return *this; 
	}
	//bool operator== (Point& p) { return (p.x == x && p.y == y && p.value == value); }
	//friend bool operator== (const Point& p1, const Point& p2); 
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
	return true; // do not sort 
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
	{ Point(0, 1, grid[0][1]), { Point(0, 2, grid[0][2]), Point(1, 1, grid[1][1]) } }, /*Point(0, 0, grid[0][0]) } },*/
	{ Point(0, 2, grid[0][2]), { Point(1, 2, grid[1][2]), Point(0, 1, grid[0][1]) } },
	   
	{ Point(1, 2, grid[1][2]), { Point(2, 2, grid[2][2]), Point(1, 1, grid[1][1]) } }, /*Point(1, 2, grid[1][2]) } },*/
	{ Point(1, 1, grid[1][1]), { /*Point(1, 2, grid[1][2]),*/ Point(2, 1, grid[2][1]), Point(1, 0, grid[1][0]) } }, /*Point(0, 1, grid[0][1]) } },*/
	{ Point(1, 0, grid[1][0]), { Point(1, 1, grid[1][1]), Point(2, 0, grid[2][0]) } }, /*Point(0, 0, grid[0][0]) } },*/

	{ Point(2, 0, grid[2][0]), { Point(2, 1, grid[2][1]), Point(1, 0, grid[1][0]) } },
	{ Point(2, 1, grid[2][1]), { Point(2, 2, grid[2][2]), /*Point(1, 1, grid[1][1]),*/ Point(2, 0, grid[2][0]) } },
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
		//cout << "current: " << current << endl;
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
			//cout << "next is: " << next << endl;
			if (isBlocked(next))
			{
				//cout << next << " is Blocked" << endl; 
				continue;	// check another neighbour 
			}

			for (size_t c = 0; c < came_from.size(); c++)
			{
				if (next == came_from[c].first)
				{
					//cout << "already visited" << endl; 
					been_already = true; 
					break; 
				}
			}
			

			if (!been_already)
			{

				visited.push(next);
				neightbour_cout += 1;
				cout << "add to queue " << next << endl; 
				came_from.push_back(make_pair(next, current));
				
			}
		}

		if (neightbour_cout == 2) // CHECK!!!!!!!!!!!!! for x and == 
		{
			cout << "queue size: " << visited.size() << endl; 
			temp_neighbour = visited.front();
			cout << "temp: " << temp_neighbour << " "; 
			
			visited.pop();
			last_neighbour = visited.back(); 
			
			cout << "back: " << last_neighbour << endl;
			cout << "queue size: " << visited.size() << endl;

			/*while (!visited.empty())
			{
				cout << " " << visited.front();
				visited.pop();
			}*/
			
			if (temp_neighbour.y == start_pnt.y)
			{
				cout << "Temp work" << endl; 
				if (grid[ROW-1][start_pnt.y] == 0)
				{

					visited.pop();
					visited.push(temp_neighbour);
					cout << "queue: " << visited.front() << endl; 
					cout << "queue size: " << visited.size() << endl;

				}
			}
			//else if (last_neighbour.y == start_pnt.y)
			//{
			//	cout << "last work" << endl; 
			//	if (grid[ROW - 1][start_pnt.y] == 0)
			//	{
			//		break; // do nothing 
			//	}
			//}
			else
			{
				cout << "error work" << endl; 
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

	vector<Point> final_path; 

	vector<int16_t> y_ind;
	vector<int16_t> x_ind; 
	vector<int16_t> other_ind;
	vector<int16_t> all_ind; 


	for (size_t ord = 0; ord < order.size(); ord++)
	{
		if (order[ord].y == start_pnt.y)
		{
			y_ind.push_back(static_cast<int16_t>(ord));
			/*final_path.push_back(order[ord]);
			continue;*/
		}
		else if (order[ord].x == goal_pnt.x)
		{
			x_ind.push_back(static_cast<int16_t>(ord));
			/*final_path.push_back(order[ord]);
			continue;*/
		}
		else
		{
			other_ind.push_back(static_cast<int16_t>(ord));
		}
	}

	//all_ind = y_ind;

	//cout << "y size: " << y_ind.size() << " : x_size: " << x_ind.size()
	//	 << " : other size: " << other_ind.size() << endl;

	//if (y_ind.size() == ROW && x_ind.size() == COL)
	//{
	//	//all_ind = y_ind;
	//	all_ind.insert(all_ind.end(), x_ind.begin(), x_ind.end());
	//	
	//}
	//else
	//{
	//	all_ind.pop_back();
	//	cout << "all size: " << all_ind.size() << endl; 
	//	all_ind.insert(all_ind.end(), other_ind.begin(), other_ind.end());
	//	all_ind.insert(all_ind.end(), x_ind.begin(), x_ind.end());
	//}

	//cout << "all size: " << all_ind.size() << endl;
	//
	//for (size_t a = 0; a < all_ind.size(); a++)
	//{
	//	final_path.push_back(order[all_ind[static_cast<int16_t>(a)]]);
	//}


	

	/*for (size_t ord = 0; ord < order.size(); ord++)
	{
		if (order[ord].x == goal_pnt.x)
		{
			final_path.push_back(order[ord]);
			continue;
		}
	}*/





	//cout << "Full sequence of steps" << endl;
	for (size_t i = 0; i < order.size(); i++)
	{
		cout << order[i] << endl;
	}

	//cout << "Steps number: " << step_number << endl;

	//cout << "Reduced sequence of steps" << endl;
	for (size_t i = 0; i < order.size()-2; i += 1)
	{
		/*cout << i << " : " << (i+2) << " | " <<
				order[i] << " : " << order[i+2] << endl;*/

		if (order[i].x == order[i + 2].x || order[i].y == order[i + 2].y)
		{
			//cout << " - step " << endl; 
			step_number -= 1; 
		}
	}

	cout << "Steps number: " << step_number << endl; 
	//drawGrid(final_path);
	cout << "\n";
	drawGrid(order);


	

	return 0;
}
