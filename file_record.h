#include <stdlib.h>
#include <stdio.h>

struct fileNode {
	char * path;
	struct fileNode * next;
};
typedef struct fileNode fileNode;

struct fileRecord {
	fileNode * head;
	fileNode * tail;
};
typedef struct fileRecord fileRecord;

void addNode(fileRecord * fr, char * path);

void deleteNode(fileRecord * fr, char * path);

int isInside(fileRecord * fr, char * path);