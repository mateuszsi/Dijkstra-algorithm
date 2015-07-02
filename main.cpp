#include <iostream>
#include <vector>

class edge
{
public:
	int from;
	int to;
	int distance;

	edge();
	edge(int f, int t, int d);
};

edge::edge()
{
	from = to = distance = 0;
}

edge::edge(int f, int t, int d)
{
	from = f;
	to = t;
	distance = d;
}

int GraphSize(std::vector <edge> tab)
{
	std::vector <int> vertex;

	for (int i = 0; i < tab.size(); i++)
	{
		bool tempB = false;

		for (int j = 0; j < vertex.size(); j++)
		{
			if (tab[i].from == vertex[j])
				tempB = true;
		}

		if (tempB == false)
			vertex.push_back(tab[i].from);
	}

	return vertex.size();
}

void CreateTabOfEdges(std::vector <edge> tab, int vertex, std::vector <int> visited, std::vector <edge> &tempT)
{
	for (int i = 0; i < tab.size(); i++)
	{
		if (tab[i].from == vertex)
		{
			bool tempB = false;

			for (int j = 0; j < visited.size(); j++)
			{
				if (tab[i].to == visited[j])
					tempB = true;
			}

			if (tempB == false)
				tempT.push_back(tab[i]);
		}
	}
}

void UpdateUnvisited(std::vector <edge> tempT, std::vector <int> visited, std::vector <int> &unvisited)
{
	for (int i = 0; i < tempT.size(); i++)
	{
		bool tB = false;

		for (int j = 0; j < visited.size(); j++)
		{
			if (visited[j] == tempT[i].to)
				tB = true;
		}

		if (tB == false)
			unvisited.push_back(tempT[i].to);
	}
}

void ChooseNewVertex(std::vector <int> visited, std::vector <int> unvisited, int &vertex)
{
	for (int i = 0; i < unvisited.size(); i++)
	{
		int v = unvisited[i];
		bool tB = false;

		for (int j = 0; j < visited.size(); j++)
		{
			if (visited[j] == v)
			{
				tB = true;
				break;
			}
			vertex = v;
		}

		if (tB == false)
			break;
	}
}

void Dijkstra(std::vector <edge> tab, int start, int end, std::vector <int> &path)
{
	std::vector <int> visited;
	std::vector <int> unvisited;
	int graphSize = GraphSize(tab);
	std::vector <std::vector <int> > matrix;
	int vertex = start;

	for (int i = 0; i < graphSize; i++)
	{
		std::vector <int> t;
		matrix.push_back(t);
	}

	for (int i = 0; i < graphSize; i++)
	{
		matrix[i].push_back(INT_MAX);
		if (i == start)
			matrix[i][matrix[i].size() - 1] = 0;
	}
	
	while (visited.size() < graphSize)
	{
		std::vector <edge> tempT;
		visited.push_back(vertex);

		for (int i = 0; i < graphSize; i++)
		{
			matrix[i].push_back(matrix[i][matrix[i].size() - 1]);
			if (i == start)
				matrix[i][matrix[i].size() - 1] = vertex;
		}

		CreateTabOfEdges(tab, vertex, visited, tempT);
		
		for (int i = 0; i < tempT.size(); i++)
		{
			int a = matrix[tempT[i].from][matrix[tempT[i].from].size() - 2] + tempT[i].distance;
			int b = matrix[tempT[i].to][matrix[tempT[i].to].size() - 2];
			if (a < b)
				matrix[tempT[i].to][matrix[tempT[i].to].size() - 1] = a;
		}
		
		UpdateUnvisited(tempT, visited, unvisited);
		ChooseNewVertex(visited, unvisited, vertex);
	}

	int tempI = end;
	path.push_back(end);
	
	for (int i = matrix[end].size() - 1; i > 1; i--)
	{
		if (matrix[tempI][i] < matrix[tempI][i - 1])
		{
			path.push_back(matrix[start][i]);
			tempI = matrix[start][i];
		}
	}
}

int main()
{
	std::vector <edge> tab(20);
	tab[0] = edge(0, 1, 2);
	tab[1] = edge(0, 2, 4);
	tab[2] = edge(1, 0, 2);
	tab[3] = edge(1, 3, 2);
	tab[4] = edge(1, 4, 3);
	tab[5] = edge(2, 0, 4);
	tab[6] = edge(2, 3, 2);
	tab[7] = edge(2, 5, 2);
	tab[8] = edge(3, 1, 2);
	tab[9] = edge(3, 2, 2);
	tab[10] = edge(4, 1, 3);
	tab[11] = edge(4, 6, 3);
	tab[12] = edge(4, 7, 4);
	tab[13] = edge(5, 2, 2);
	tab[14] = edge(5, 6, 3);
	tab[15] = edge(6, 4, 3);
	tab[16] = edge(6, 5, 3);
	tab[17] = edge(6, 7, 5);
	tab[18] = edge(7, 4, 4);
	tab[19] = edge(7, 6, 5);

	std::vector <int> path;

	Dijkstra(tab, 3, 7, path);

	for (int i = 0; i < path.size(); i++)
	{
		std::cout << path[i] << " ";
	}

	char a;
	std::cin >> a;

	return 0;
}