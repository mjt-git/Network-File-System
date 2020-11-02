#include "file_record.h"
#include <string.h>

fileNode * createNode(char * path) {
	fileNode * newNode = (fileNode *)malloc(sizeof(fileNode));
	newNode->path = (char*)malloc(sizeof(char) * (strlen(path) + 1));
	strncpy(newNode->path, path, strlen(path));
	newNode->path[strlen(path)] = '\0';
	newNode->next = NULL;

	return newNode;
}

void addNode(fileRecord * fr, char * path) {
	fileNode * newNode = createNode(path);

	if(fr->head == NULL) {
		fr->head = newNode;
		fr->tail = newNode;
	} else {
		fr->tail->next = newNode;
		fr->tail = newNode;
	}
}

void deleteNode(fileRecord * fr, char * path) {
	fileNode * cur = fr->head;
	fileNode * prev = NULL;
	while(cur != NULL) {
		if(strcmp(cur->path, path) == 0) {
			if(cur == fr->head) {
				if(fr->tail == fr->head) {fr->tail = NULL;}
				fr->head = fr->head->next;
			} else if(cur == fr->tail) {
				if(fr->head == fr->tail) {fr->head = NULL;}
				fr->tail = prev;
				if(fr->tail) {fr->tail->next = NULL;}
			} else {
				prev = prev->next;
			}

			free(cur);
			break;
		} else {
			prev = cur;
			cur = cur->next;
		}
	}
}

int isInside(fileRecord * fr, char * path) {
	fileNode * cur = fr->head;
	while(cur != NULL) {
		if(strcmp(cur->path, path) == 0) {
			return 1;
		}
		cur = cur->next;
	}
	return 0;
}