#include "graph.h"
#include "InOut.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
int in_list(list* a, int u, char* info, int x, int y) {
	list* b = malloc(sizeof(list));
	list* lol = a;
	while (lol){
		if (lol->info&&strcmp(info,lol->info) == 0) {
			free(b);
			return 0;
		}
		lol = lol->next;
	}
	if (b) {
		b->next = a->next;
		a->next = b;
		b->info = info;
		b->u = u;
		b->koord[0] = x;		
		b->koord[1] = y;
		return 1;
	}
	return 0;
}
int findv(Graph* g, char* s) {
	if (s == NULL) {
		return -1;
	}
	for (int i = 0; i < g->size; i++) {
		if (g->info[i]&&strcmp(g->info[i]->info, s) == 0) {
			return g->info[i]->u;
		}
	}
	return -1;
}
void freel(list* a) {
	if (a) {
		free(a->info);
		list* b = a;
		while (a) {
			a = a->next;
			free(b);
			b = a;
		}
	}
}
int dele(Graph* g, char* fc, char* tc) {
	int to = findv(g, tc);
	int from = findv(g, fc);
	if (to == -1 || from == -1) {
		return 0;
	}
	list* a = g->info[from];
	while (a->next && a->next->u != to) {
		a = a->next;
	}
	if (a->next) {
		list* b = a->next;
		a->next = a->next->next;
		free(b);
		return 1;
	}return 0;
}
int delv(Graph* g, char* vc) {
	int v = findv(g, vc);
	if (v == -1) {
		return 0;
	}
	for (int i = 0; i < g->size; i++) {
		if (g->info[i]) {
			dele(g, g->info[i]->info, vc);
		}
	}
	freel(g->info[v]);
	g->info[v] = NULL;
	return 1;
}
int addv(Graph* g, char*a,int x,int y) {
	if (findv(g, a) != -1) {
		free(a);
		return 0;
	}
	for (int i = 0; i < g->size; i++) {
		if (g->info[i]==NULL) {
			g->info[i] = malloc(sizeof(list));
			g->info[i]->next = NULL;
			g->info[i]->u = i;
			g->info[i]->info = a;
			g->info[i]->koord[0] = x;
			g->info[i]->koord[1] = y;
			return 1;
		}
	}
	g->info = realloc(g->info, sizeof(list*) * (g->size+1));
	g->info[g->size] = malloc(sizeof(list));
	g->info[g->size]->next = NULL;
	g->info[g->size]->u = g->size;
	g->info[g->size]->info = a;
	g->info[g->size]->koord[0] = x;
	g->info[g->size]->koord[1] = y;
	g->size++;
	return 1;
}
void freeg(Graph* g) {
	for (int i = 0; i < g->size; i++) {
		freel(g->info[i]);
	}
	free(g->info);
	free(g);
}

int adde(Graph* g, char* uc, char* vc) {
	int to = findv(g,vc);
	int from = findv(g,uc);
	if (to !=-1&&from!=-1) {
		return in_list(g->info[from], to, g->info[to]->info,g->info[to]->koord[0], g->info[to]->koord[1]);
	}
	return 0;
}


void printl(list* a) {
	if (a) {
		printf("%s(%d), x=%d, y=%d -> ", a->info, a->u,a->koord[0],a->koord[1]);
		printl(a->next);
	}
	else {
		printf("NONE\n");
	}
}
void printg(Graph* g) {
	for (int i = 0; i < g->size; i++) {
		if (g->info[i]) {
			printf("vertex: %s(%d), x=%d, y=%d\n list of connected: ", g->info[i]->info, g->info[i]->u, g->info[i]->koord[0], g->info[i]->koord[1]);
			printl(g->info[i]->next);
		}
	}
}
typedef struct item {
	int el;
	struct item* next;
}item;
typedef struct qeue{
	item* head;
	item* tail;
}queue;
void push(queue* q, int el) {
	item* a = malloc(sizeof(item));
	a->el = el;
	a->next = NULL;
	if (q->tail) {
		q->tail->next = a;
		q->tail = a;
	}
	else {
		q->tail = a;
		q->head = a;
	}
}
int pop(queue* q) {
	item* lol = q->head;
	if (q->head != q->tail) {
		q->head = q->head->next;
	}
	else {
		q->head = NULL;
		q->tail = NULL;
	}
	int a = lol->el;
	free(lol);
	return a;
}
float leight(Graph* g, int u, int v) {
	int d_x = g->info[u]->koord[0]- g->info[v]->koord[0];
	int d_y = g->info[u]->koord[1] - g->info[v]->koord[1];
	return sqrtf(d_x * d_x + d_y * d_y);
}
int bfs(Graph* g,char* fc, char* tc,list* way) {
	int from = findv(g, fc);
	int to = findv(g, tc);
	if (to == -1 || from == -1) {
		return 0;
	}
	way->u = from;
	way->koord[0] = g->info[from]->koord[0];
	way->koord[1] = g->info[from]->koord[1];
	if (from == to) {
		return 1;
	}
	int* pred = malloc(g->size*sizeof(int));
	for (int i = 0; i < g->size; i++) {
		pred[i] = -1;
	}
	queue q;
	q.head = NULL;
	q.tail = NULL;
	push(&q, from);
	while (q.head) {
		int v = pop(&q);
		for (list* uv = g->info[v]->next; uv; uv = uv->next) {
			int u = uv->u;
			if (pred[u] == -1) {
				pred[u] = v;
				push(&q, u);
			}
		}
	}
	if (pred[to] != -1) {
		while (to != from) {
			in_list(way, to, g->info[to]->info, g->info[to]->koord[0], g->info[to]->koord[1]);
			to = pred[to];
		}
		free(pred);
		return 1;
	}
	else {
		free(pred);
		return 0;
	}
}
int ford_bell(Graph* g, char* fc, char* tc, list* way) {
	int n = g->size;
	int from = findv(g, fc);
	int to = findv(g, tc);
	if (to == -1 || from == -1) {
		return 0;
	}
	way->u = from;
	way->koord[0] = g->info[from]->koord[0];
	way->koord[1] = g->info[from]->koord[1];
	if (from == to) {
		return 1;
	}
	int* pred = malloc(g->size*sizeof(int));
	float* d = malloc(g->size*sizeof(int));
	for (int i = 0; i < g->size; i++) {
		pred[i] = -1;
		d[i] = -1;
	}
	d[from] = 0;
	for (int i = 0; i < n - 1; i++) {
		for (int j = 0; j < n; j++) {
			if(d[j]!=-1)
			for (list* el = g->info[j]->next; el; el = el->next) {
				if (d[el->u]==-1||d[el->u] > d[j] + leight(g, j, el->u)) {
					d[el->u] = d[j] + leight(g, j, el->u);
					pred[el->u] = j;
				}
			}
		}
	}
	if (pred[to] != -1) {
		while (to != from) {
			in_list(way, to, g->info[to]->info, g->info[to]->koord[0], g->info[to]->koord[1]);
			to = pred[to];
		}
		free(pred);
		free(d);
		return 1;
	}
	free(d);
	free(pred);
	return 0;
}
int dfs(Graph* g, int v, int par, int* used, queue* topsort) {
	used[v] = 1;
	for (list* el = g->info[v]->next; el; el = el->next) {
		if (el->u!=par&&used[el->u]) {
			return 0;
		}
		else if (used[el->u] == 0) {
			int a = dfs(g,el->u,v,used,topsort );
			if (a == 0) return 0;
		}
	}
	push(topsort, v);
	return 1;
}
int special(Graph* g, list* topsort) {
	int* used = malloc(g->size * sizeof(int));
	int n = g->size;
	for (int i = 0; i < g->size; i++) {
		used[i] = 0;
	}
	queue ts = { NULL,NULL };
	for (int i = 0; i < n; i++) {
		if (used[i] == 0) {
			int a = dfs(g, i,-1, used, &ts);
			if (a == 0) return 0;
		}
	}
	while (ts.head) {
		int to = pop(&ts);
		in_list(topsort, to, g->info[to]->info, g->info[to]->koord[0],g->info[to]->koord[1]);
	}
	free(used);
	return 1;
}
