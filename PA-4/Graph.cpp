#ifndef GRAPH__CPP
#define GRAPH__CPP
#include "Graph.h"

//
// Add your constructor code here. It takes the filename and loads
// the graph from the file, storing into your representation of the
// graph. MAKE SURE you use the addEdge function here, and pass the
// flag to it too.
//
Graph::Graph(string filename, bool flag)
{
	// TODO
	ifstream read;
	read.open(filename);
	string check;

	read >> check;
	read >> check;

	int n = stoi(check);

	for (int i = 0; i < n; i++)
	{
		vector<shared_ptr<Edge>> temp;
		for (int j = 0; j < n; j++)
		{
			shared_ptr<Edge> temp2 = make_shared<Edge>();
			temp2->origin = i2c(i);
			temp2->dest = i2c(j);
			temp2->weight = -1;
			temp.push_back(temp2);
		}
		graph.push_back(temp);
	}

	read >> check;
	read >> check;

	int c = stoi(check);
	read >> check;

	while (!read.eof())
	{
		char start = check[0];
		read >> check;
		char end = check[0];
		read >> check;
		int weight = stoi(check);
		addEdge(start, end, weight, flag);
		read >> check;
	}
}

//
// Adds an edge to the graph. Useful when loading the graph from file.
// The flag determines whether the edges will be added according to a
// directed or undirected graph.
//
void Graph::addEdge(char start, char end, int weight, bool flag)
{
	// TODO
	int i = c2i(start);
	int j = c2i(end);

	if (flag)
	{
		graph[i][j]->weight = weight;
	}
	else
	{
		graph[i][j]->weight = weight;
		graph[j][i]->weight = weight;
	}

	return;
}

//
// Returns the display of the graph as a string. Make sure
// you follow the same output as given in the manual.
//
string Graph::display()
{
	// TODO
	string s = "";

	for (int i = 0; i < graph.size(); i++)
	{
		for (int j = 0; j < graph.size(); j++)
		{
			if (graph[i][j]->weight != -1)
			{
				s = s + "(" + graph[i][j]->origin + "," + graph[i][j]->dest + "," + to_string(graph[i][j]->weight) + ") ";
			}
		}
		s += "\n";
	}

	return s;
}

// Returns whether the destination city is reachable from the
// origin city or not.
//
bool Graph::Reachable(char start, char end)
{
	vector<char> visited;
	vector<char> queue;
	queue.push_back(start);

	while (!queue.empty())
	{
		int i = c2i(queue[0]);
		visited.push_back(queue[0]);
		queue.erase(queue.begin());
		for (int j = 0; j < graph.size(); j++)
		{
			if (graph[i][j]->weight != -1)
			{
				if (j == c2i(end))
				{
					return true;
				}
				bool check = true;
				for (int k = 0; k < visited.size(); k++)
				{
					if (i2c(j) == visited[k])
					{
						check = false;
					}
				}
				if (check)
				{
					queue.push_back(i2c(j));
				}
			}
		}
	}

	return false;
}

//
// Returns the weight of shortest path between origin and destination cities.
// Return -1 if no path exists.
//
int Graph::Dijkstra(char start, char dest)
{
	// TODO
	if (!Reachable(start, dest))
	{
		return -1;
	}

	vector<char> queue;
	queue.push_back(start);
	vector<int> distance;
	for (int i = 0; i < graph.size(); i++)
	{
		distance.push_back(-1);
	}
	distance[c2i(start)] = 0;

	while (!queue.empty())
	{
		int i = c2i(queue[0]);
		queue.erase(queue.begin());
		for (int j = 0; j < graph.size(); j++)
		{
			if (graph[i][j]->weight != -1)
			{
				if (distance[j] == -1)
				{
					distance[j] = distance[i] + graph[i][j]->weight;
					queue.push_back(i2c(j));
				}
				else
				{
					int temp = distance[i] + graph[i][j]->weight;
					if (temp < distance[j])
					{
						distance[j] = temp;
					}
				}
			}
		}
	}

	return distance[c2i(dest)];
}

//
// Implement topological sort on the graph and return the string of the sorted cities
//
string Graph::topoSort()
{
	//TODO
	vector<char> visited;
	vector<char> stack;

	for (int i = 0; i < graph.size(); i++)
	{
		bool check = true;
		for (int k = 0; k < visited.size(); k++)
		{
			if (i2c(i) == visited[k])
			{
				check = false;
			}
		}
		if (check)
		{
			_helper(visited, stack, i2c(i));
		}
	}

	string s = "";
	while (!stack.empty())
	{
		s = s + stack[stack.size() - 1];
		stack.pop_back();
	}

	return s;
}

int Graph::c2i(char x)
{
	return x - 65;
}

char Graph::i2c(int x)
{
	return x + 65;
}

void Graph::_helper(vector<char> &v, vector<char> &s, char x)
{
	v.push_back(x);

	for (int i = 0; i < graph.size(); i++)
	{
		if (graph[c2i(x)][i]->weight != -1)
		{
			bool check = true;
			for (int k = 0; k < v.size(); k++)
			{
				if (i2c(i) == v[k])
				{
					check = false;
				}
			}
			if (check)
			{
				_helper(v, s, i2c(i));
			}
		}
	}

	s.push_back(x);
}

//

#endif
