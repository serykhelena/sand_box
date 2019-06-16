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
		for (int16_t x = 0; x < n; x++)
		{
			graph.push_back({ });
			for (int16_t y = 0; y < n; y++)
			{
				graph[x].push_back(rand() % 2); 
				if (x == y) graph[x][y] = 0;
			}
		}
		// to make from random array -> adjacency matrix
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
				// fill set of vertexes 
				if (graph[x][y] != 0)
				{
					edges[x + 1].push_back(y + 1); 
				}
			}
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
		int16_t next = g.edges[cur_v][i];	
		if ( !marked_v.count(next) ) // if we don't check this vertex 
		{
			dfs(next, g);
		}
	}
}

int16_t connected_comps_count( RandomGraph& g)
{
	int16_t comp_count = 0; 
	for (int16_t i = 1; i <= g.v_number; i++)	// check all vertexes 
	{
		if (!marked_v.count(i))
		{
			dfs(i, g);
			if( i != g.v_number) comp_count += 1; 
		}
	}
	return comp_count; 
}

int main()
{
	const int16_t n = 4;

	RandomGraph g(n); 

	cout <<"The number of connected components: " << connected_comps_count(g) << endl; 
	
	return 0;
}

