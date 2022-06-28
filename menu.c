#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
#include "Graph.h"
#include "InOut.h"
int d_addv(Graph* t) {
	char* name = read_line("How to name it?\n->");
	int x, y;
	printf("X Y?\n->");
	scanf("%d", &x);
	scanf("%d", &y);
	scanf("%*c");
	return addv(t,name,x,y);
};
int d_adde(Graph* t) {
	char* from = read_line("From?\n->");
	char* to = read_line("To?\n->");
	int k = 0;
	if (from && to) {
		k = adde(t, from, to)*adde(t,to,from);
	}
	free(from);
	free(to);
	return k;
};
int d_delv(Graph* t) {
	char* from = read_line("Wich one?\n->");
	int k = 0;
	if (from) {
		k = delv(t, from);
	}
	free(from);
	return k;
};
int d_dele(Graph* t) {
	char* from = read_line("From?\n->");
	char* to = read_line("To?\n->");
	int k = 0;
	if (from && to) {
		k = dele(t, from, to)* dele(t,to,from);
	}
	free(from);
	free(to);
	return k;
};
int d_out(Graph* t) {
	printg(t);
	return 1;
};
int d_BFS(Graph* t) {
	char* from = read_line("From?\n->");
	char* to = read_line("To?\n->");
	if (from && to) {
		list* doroga = malloc(sizeof(list));
		doroga->next = NULL;
		doroga->info = from;
		if (bfs(t, from, to, doroga)) {
			printf("Trere is the way:\n");
			printl(doroga);
			freel(doroga);
			free(to);
			return 1;
		}
		free(from);
		printf("Trere is no way\n");
		free(to);
		return 0;
	}
	return 0;
};
int d_bell(Graph* t) {
	char* from = read_line("From?\n->");
	char* to = read_line("To?\n->");
	if (from && to) {
		list* way = malloc(sizeof(list));
		way->next = NULL;
		way->info = from;
		if (ford_bell(t, from, to, way)) {
			printf("Trere is the way:\n");
			printl(way);
			freel(way);
			free(to);
			return 1;
		}
		free(from);
		printf("Trere is no way\n");
		free(to);
		return 0;
	}
	return 0;
};
int d_special(Graph* t) {
	list* way = malloc(sizeof(list));
	way->next = NULL;
	way->info = NULL;
	way->u = -1;
	way->koord[0] = 0;
	way->koord[1] = 0;
	int a = special(t,way);
	if (a) {
		printf("Trere is the ts:\n");
		printl(way->next);
		freel(way);
		return 1;
	}
	return 0;
};
int main() {
	int n;
	char* menus = "1. Add V\n2. Add E\n3. Del V\n4. Del E\n5. Print\n6. Find way\n7. Shortest way\n8. Spetial\n0. Exit\n->";
	printf("%s",menus);
	Graph* t= malloc(sizeof(Graph));
	t->size = 0;
	t->info = NULL;
	int (*fd[])(Graph*) = { NULL,d_addv,d_adde,d_delv,d_dele,d_out,d_BFS,d_bell,d_special };
	while (readint(&n)) {
		if (n <= 8) {
			if (!n) {
				break;
			}
			else {
				if (fd[n](t)) {
					printf("USPEH!\n");
				}
				else {
					printf("NOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO!!!!!\n");
				}
			}
		}
		else {
			printf("[0-8]!");
			continue;
		}
		printf("%s", menus);
	}
	freeg(t);
	printf("BY\n");
}