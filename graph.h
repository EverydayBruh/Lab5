#ifndef __GRAPH__
#define __GRAPH__
typedef struct list {
	int u;
	int koord[2];
	char* info;
	struct list* next;
}list;
typedef struct Graph
{
	int size;
	list** info;
}Graph;
void printg(Graph* g);
int adde(Graph* g, char* fc, char* tc);
int addv(Graph* g, char* a, int x, int y);
int bfs(Graph* g, char* fc, char* tc, list* way);
void printl(list* a);
void freel(list* a);
void freeg(Graph* g);
int ford_bell(Graph* g, char* fc, char* tc, list* way);
int delv(Graph* g, char* vc);
int dele(Graph* g, char* fc, char* tc);
int special(Graph* g, list* topsort);
#endif

