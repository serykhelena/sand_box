#include <iostream>
#include <cstdint>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <set>
#include <map>

using namespace std;

class RandomGraph {
public:
	RandomGraph(int16_t n)
	{
		v_number = n; 
		cout << "INITIAL GRAPH" << endl; 
		
		// graph.push_back({0, 1, 1, 0});
		// graph.push_back({1, 0, 0, 1});
		// graph.push_back({1, 0, 0, 1});
		// graph.push_back({0, 1, 1, 0});


		for (int16_t x = 0; x < n; x++)
		{
			graph.push_back({ });
			for (int16_t y = 0; y < n; y++)
			{
				graph[x].push_back(rand() % 2); 
				if (x == y) graph[x][y] = 0;
				
				cout << graph[x][y] << " ";	// DON'T FORGET TO REMOVE!! 
			}
			cout << "\n";					// DON'T FORGET TO REMOVE!! 
		}
		cout << "MODIFIED GRAPH" << endl; 
		for( int16_t x = 0; x < n; x++ )
		{
			for( int16_t y = 0; y < n; y++ )
			{
				if( x != y )
				{
					if( graph[x][y] != graph[y][x] )
					{
						graph[y][x] = graph[x][y] = 1; 
					}
				}

				if (graph[x][y] != 0)
				{
					edges[x + 1].push_back(y + 1); 
				}
				cout << graph[x][y] << " ";
			}
			cout << "\n";					// DON'T FORGET TO REMOVE!! 
		}

		cout << "EDGES" << endl; 
		for( auto item : edges )
		{
			cout << item.first << " : "; 
			for( int16_t i = 0; i < item.second.size(); i++)
			{
				cout << item.second[i] << " ";
			}
			cout << "\n";
		}


	}

	int16_t v_number; 
	vector<vector<int16_t>> graph; 
	map<int16_t, vector<int16_t>> edges; 

};

set<int16_t> marked_v; 

void dfs(int16_t& cur_v, RandomGraph& g)
{
	marked_v.insert(cur_v);
	for (size_t i = 0; i < g.edges[cur_v].size(); i++) 
	{
		cout << "dfs i: " << i << " | cur_v: " << cur_v
			 << " next v: " << cur_v + 1 << endl; 
		int16_t next = g.edges[cur_v][i];	
		if (!marked_v.count(next) /*&& g.graph[cur_v - 1][i] == 1*/)	// if we don't check this vertix 
		{
			cout << "dfs recursive - ok " << endl;
			dfs(next, g);
		}
	}
}

int16_t connected_comps_count( RandomGraph& g)
{
	int16_t comp_count = 0; 
	for (int16_t i = 1; i <= g.v_number; i++)	// check all vertxes 
	{
		cout << "v: " << i << " | count: " << comp_count << endl;
		if (!marked_v.count(i))
		{
			dfs(i, g);
			cout << "comp ++ " << endl;
			if( i != g.v_number) comp_count += 1; 
		}
	}
	return comp_count; 
}

int main()
{

	// cin << n; 
	const int16_t n = 4;

	RandomGraph g(n); 

	cout << connected_comps_count(g) << endl; 
	
	return 0;
}

