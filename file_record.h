#include <stdlib.h>
#include <stdio.h>

struct fileNode {
	char * buf;
	unsigned int size;
	unsigned int offset;
	int fd;
	struct fileNode * next;
};
typedef struct fileNode fileNode;

struct fileRecord {
	fileNode * head;
	fileNode * tail;
};
typedef struct fileRecord fileRecord;

void addNode(fileRecord * fr, const char * buf, unsigned int size, unsigned int offset, int fd);

void deleteNode(fileRecord * fr, int fd);

fileNode * find(fileRecord * fr, int fd);
