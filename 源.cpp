#include<iostream>
using namespace std;
int matrix[100][100];//�ڽӾ���
bool visited[100];//�������
int dist[100];//ԭ�㵽i�������̾���
int pre[100];//��¼���·����pre[i]�ŵ���i��ǰ���ڵ�
int source;//Դ�ڵ�
int vertex_num;//������
int edge_num;//����

void Dijkstra(int source)
{
	//���ȳ�ʼ��
	memset(visited, 0, sizeof(visited));
	visited[source] = true;
	for (int i = 0; i < vertex_num; i++)
	{
		dist[i] = matrix[source][i];
		pre[i] = source;
	}

	int min_cost;//��̾���
	int min_cost_index;//Ȩֵ��С���Ǹ�������±ꡣ������ˣ�
	//��ѭ��
	for (int i = 1; i < vertex_num; i++)
	{
		min_cost = INT_MAX;
		for (int j = 0; j < vertex_num; j++)
		{
			//ע��Ҫȷ�������û���ҹ���
			if (visited[j] == false && dist[j] < min_cost)
			{
				min_cost_index = j;
				min_cost = dist[j];
			}
		}

		visited[min_cost_index] = true;//�ҵ�ĳһ�������̾���
		//���øõ����dist�ĸ��£����ҵ���ǰ����
		for (int j = 0; j < vertex_num; j++)
		{
			//ȷ��������
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
	cout << "������ͼ�Ķ�������<100��:";
	cin >> vertex_num;
	cout << "�����ͼ�ı���: ";
	cin >> edge_num;
	for (int i = 0; i < vertex_num; i++)
	{
		for (int j = 0; j < vertex_num; j++)
		{
			matrix[i][j] = (i != j) ? INT_MAX : 0;
		}
	}
	cout << "������ߵ���Ϣ��\n";
	int u, v, w;
	for (int i = 0; i < edge_num; i++)
	{
		cin >> u >> v >> w;
		matrix[u - 1][v - 1] = matrix[v - 1][u - 1] = w;
	}

	cout << "������Դ��(<" << vertex_num << "): ";
	cin >> source;
	Dijkstra(source);
	for (int i = 0; i < vertex_num; i++)
	{
		if (i != source)
		{
			//·���Ƿ��ģ���Ŀ�����ǰ������ǰ���Ĺ��̡�
			cout << source << "��" << i << "��̾��룺 " << dist[i] << ",·���ǣ�" << i;
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