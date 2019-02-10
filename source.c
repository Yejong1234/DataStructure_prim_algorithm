#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 8
#define INF 1000L

int weight[MAX_VERTICES][MAX_VERTICES] =
{ {0,3,INF,INF,INF,INF,INF,12},
{3,0,8,INF,INF,INF,INF,10},
{INF,8,0,15,2,INF,INF,INF},
{INF,INF,15,0,INF,INF,INF,INF},
{INF,INF,2,INF,0,9,4,5},
{INF,INF,INF,INF,9,0,INF,INF},
{INF,INF,INF,INF,4,INF,0,6},
{14,10,INF,INF,5,INF,6,0} };

int selected[MAX_VERTICES];
int parent[MAX_VERTICES];

struct heap_node {//�Ÿ��� ���� Ű ���� �����ϱ� ���� ����ü ����
	int vertices;
	int key;//�Ÿ�
}dist[MAX_VERTICES + 1];

void build_min_heap(void) {
	int i = 1;
	int length = MAX_VERTICES;
	int child, parent;
	int temp;

	while (i != length / 2) {
		child = i * 2;
		if (dist[child].key < dist[child - 1].key) {
			child = child + 1;
		}
		if (dist[i - 1].key < dist[child - 1].key) {
			dist[MAX_VERTICES] = dist[i - 1];
			dist[i - 1] = dist[child - 1];
			dist[child - 1] = dist[MAX_VERTICES];
		}
		i++;
	}
}

int Extract_Min() {//���İ��� 0�� �� return �Ѵ�.
	int min;
	int i;
	for (i = 0; i < MAX_VERTICES; i++) {
		if ((selected[i] == FALSE)) {//queue���� ���ŵ��� �ʰ� ���� ���� �ּ��� ��
			min = dist[i].vertices;
			break;
		}
	}
	return min;
}

void Decrease_key_min_heap(int i, int key) {//i�� �ִ� key���� �� �۰� ���鵵��
	if (key >= dist[i].key)
		printf("error new key is not smaller thatn current key\n");

	dist[i].key = key;

	int parent;

	while (i != 1) {//i=1�̸� ���� ���� ����̱� ������
		parent = i / 2;//parent��带 ã��
		if (dist[i].key < dist[parent].key) {//���� parent���� ���� ��쿡�� �ٲ��ش�
			dist[MAX_VERTICES] = dist[i];
			dist[i] = dist[parent];
			dist[parent] = dist[MAX_VERTICES];
		}
		i = parent;//�׸��� �񱳴���� ���� �÷��ش�.
	}
}


void prim(int s, int n)
{
	int i, u, v, j;
	for (u = 0; u < n; u++) {
		dist[u].key = INF;
		dist[u].vertices = u;
		selected[u] = FALSE;
	}

	dist[s].key = 0;

	for (i = 0; i < n; i++) {
		u = Extract_Min;//dist heap���� ���� ���� ���� vertices ���� ����
		selected[u] = TRUE;//�� vertice�� true����.

		printf("%d", u);
		for (v = 0; v < n; v++) {
			if (weight[u][v] != INF)
				if (!selected) {
					for (j = 0; j < MAX_VERTICES; j++) {//heap node�ȿ� �ִ� vertices�� v�ΰ��� ã�Ƴ�����.
						if (dist[j].vertices == v)
							break;
					}
					if (weight[u][v] < dist[j].key) {
						Decrease_key_min_heap(j, weight[u][v]);//���� heap ���� j��°�� ���ĵǾ��ִ� ���� �ٲ��ش�.
						parent[v] = u;
					}

				}
		}

	}

}

void print_prim() {
	int i;
	for (i = 0; i < MAX_VERTICES; i++) {
		printf("Vertices %d --> parent %d\n", dist[i].vertices, parent[dist[i].vertices]);
	}
}
int main() {
	prim(0, MAX_VERTICES);

	print_prim();

}
