#include<iostream>
using namespace std;
int matrix[100][100];//邻接矩阵
bool visited[100];//标记数组
int dist[100];//原点到i顶点的最短距离
int pre[100];//记录最短路径。pre[i]放的是i的前驱节点
int source;//源节点
int vertex_num;//顶点数
int edge_num;//边数

void Dijkstra(int source)
{
	//首先初始化
	memset(visited, 0, sizeof(visited));
	visited[source] = true;
	for (int i = 0; i < vertex_num; i++)
	{
		dist[i] = matrix[source][i];
		pre[i] = source;
	}

	int min_cost;//最短距离
	int min_cost_index;//权值最小的那个顶点的下标。（求好了）
	//主循环
	for (int i = 1; i < vertex_num; i++)
	{
		min_cost = INT_MAX;
		for (int j = 0; j < vertex_num; j++)
		{
			//注意要确保这个点没有找过。
			if (visited[j] == false && dist[j] < min_cost)
			{
				min_cost_index = j;
				min_cost = dist[j];
			}
		}

		visited[min_cost_index] = true;//找到某一个点的最短距离
		//利用该点进行dist的更新，并且调整前驱。
		for (int j = 0; j < vertex_num; j++)
		{
			//确保有连接
			if (visited[j] == false && matrix[min_cost_index][j] != INT_MAX && min_cost + matrix[min_cost_index][j] < dist[j])
			{
				dist[j] = min_cost + matrix[min_cost_index][j];
				pre[j] = min_cost_index;
			}
		}
	}
}

int main()
{
	cout << "请输入图的顶点数（<100）:";
	cin >> vertex_num;
	cout << "请输出图的边数: ";
	cin >> edge_num;
	for (int i = 0; i < vertex_num; i++)
	{
		for (int j = 0; j < vertex_num; j++)
		{
			matrix[i][j] = (i != j) ? INT_MAX : 0;
		}
	}
	cout << "请输入边的信息：\n";
	int u, v, w;
	for (int i = 0; i < edge_num; i++)
	{
		cin >> u >> v >> w;
		matrix[u - 1][v - 1] = matrix[v - 1][u - 1] = w;
	}

	cout << "请输入源点(<" << vertex_num << "): ";
	cin >> source;
	Dijkstra(source);
	for (int i = 0; i < vertex_num; i++)
	{
		if (i != source)
		{
			//路径是反的，从目标点向前不断找前驱的过程。
			cout << source << "到" << i << "最短距离： " << dist[i] << ",路径是：" << i;
			int t = pre[i];
			while (t != source)
			{
				cout << "--" << t;
				t = pre[t];
			}
			cout << "--" << source << endl;
		}
	}
	return 0;
}