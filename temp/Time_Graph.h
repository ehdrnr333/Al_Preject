#ifndef __TIME_GRAPH_H__
#include<stdio.h>
#include<stdlib.h>
#define __TIME_GRAPH_H__
#define MAX_VERTEX 10
typedef int Record;

typedef struct {
	int n;
	int adj_mat[MAX_VERTEX][MAX_VERTEX];
}GraphType;


void initGraph(GraphType *g)
{
	int i, j;

	g->n = 0;

	for (i = 0; i < MAX_VERTEX; i++)
		for (j = 0; j < MAX_VERTEX; j++)
			g->adj_mat[i][j] = 0;
}

void insertVertex(GraphType *g, Record v)
{
	if ((g->n) + 1 > MAX_VERTEX)
	{
		fprintf(stderr, "정점 갯수 초과\n");
	}

	g->n++;
}
void insertEdge(GraphType *g, int start, int end)
{
	if (start >= g->n || end >= g->n)
	{
		fprintf(stderr, "잘못된 정점 입력\n");
		exit(-1);
	}

	g->adj_mat[start][end] = 1;
	g->adj_mat[end][start] = 1;
}

#endif
