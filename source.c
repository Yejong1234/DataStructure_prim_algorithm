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

struct heap_node {//거리와 원래 키 값을 보존하기 위한 구조체 선언
	int vertices;
	int key;//거리
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

int Extract_Min() {//정렬값이 0인 걸 return 한다.
	int min;
	int i;
	for (i = 0; i < MAX_VERTICES; i++) {
		if ((selected[i] == FALSE)) {//queue에서 제거되지 않고 가장 작은 최소의 수
			min = dist[i].vertices;
			break;
		}
	}
	return min;
}

void Decrease_key_min_heap(int i, int key) {//i에 있는 key값을 더 작게 만들도록
	if (key >= dist[i].key)
		printf("error new key is not smaller thatn current key\n");

	dist[i].key = key;

	int parent;

	while (i != 1) {//i=1이면 가장 높은 노드이기 때문에
		parent = i / 2;//parent노드를 찾고
		if (dist[i].key < dist[parent].key) {//만약 parent보다 작은 경우에는 바꿔준다
			dist[MAX_VERTICES] = dist[i];
			dist[i] = dist[parent];
			dist[parent] = dist[MAX_VERTICES];
		}
		i = parent;//그리고 비교대상을 위로 올려준다.
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
		u = Extract_Min;//dist heap에서 가장 작은 것의 vertices 값을 추출
		selected[u] = TRUE;//그 vertice에 true저장.

		printf("%d", u);
		for (v = 0; v < n; v++) {
			if (weight[u][v] != INF)
				if (!selected) {
					for (j = 0; j < MAX_VERTICES; j++) {//heap node안에 있는 vertices가 v인것을 찾아내야함.
						if (dist[j].vertices == v)
							break;
					}
					if (weight[u][v] < dist[j].key) {
						Decrease_key_min_heap(j, weight[u][v]);//현재 heap 에서 j번째로 정렬되어있는 것을 바꿔준다.
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
