#include "file_record.h"
#include <string.h>
#include <stdio.h>

fileNode * createNode(const char * buf, unsigned int size, unsigned int offset, int fd) {
	fileNode * newNode = (fileNode *)malloc(sizeof(fileNode));
	newNode->buf = (char*)malloc(sizeof(char) * size);
	//printf("\n--------****************-------\n");
	//printf("strlen(buf): %d\n", size);
	//printf("\n--------****************-------\n");
	memcpy(newNode->buf, buf, size);

	newNode->size = size;
	newNode->offset = offset;
	newNode->fd = fd;
	newNode->next = NULL;

	return newNode;
}

void addNode(fileRecord * fr, const char * buf, unsigned int size, unsigned int offset, int fd) {
	fileNode * newNode = createNode(buf, size, offset, fd);

	if(fr->head == NULL) {
		fr->head = newNode;
		fr->tail = newNode;
	} else {
		fr->tail->next = newNode;
		fr->tail = newNode;
	}
}

void deleteNode(fileRecord * fr, int fd) {
	fileNode * cur = fr->head;
	fileNode * prev = NULL;
	while(cur != NULL) {
		if(cur->fd == fd) {
			if(cur == fr->head) {
				if(fr->tail == fr->head) {fr->tail = NULL;}
				fr->head = fr->head->next;
			} else if(cur == fr->tail) {
				if(fr->head == fr->tail) {fr->head = NULL;}
				fr->tail = prev;
				if(fr->tail) {fr->tail->next = NULL;}
			} else {
				prev->next = cur->next;
			}

			free(cur->buf);
			free(cur);
			break;
		} else {
			prev = cur;
			cur = cur->next;
		}
	}
}

fileNode * find(fileRecord * fr, int fd) {
	fileNode * cur = fr->head;
	while(cur != NULL) {
		if(cur->fd == fd) {
			return cur;
		}
		cur = cur->next;
	}
	return NULL;
}
