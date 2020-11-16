#include "cache.h"

int CACHE_SIZE = 1000;

void create_cachelist(struct cachelist * calist){
  calist->length = 0; 
  calist->head = NULL;
  calist->tail = NULL;
}

void create_cache(struct cache * ca, char path[PATH_MAX], size_t size, size_t offset, uint32_t mtime, char buf[4096]){
  memcpy(ca->path, path, 4096);
  ca->size = size;
  ca->offset = offset;
  ca->mtime = mtime;
  memcpy(ca->buf, buf, 4096);
  ca->next = NULL;
}

void add_cache(struct cachelist * calist, struct cache * ca){
  if(calist->head == NULL){
    calist->head = ca;
    printf("cache list head path is %s\n", calist->head->path);
    printf("cache list head size is %ld\n", calist->head->size);
    printf("cache list head offset is %ld\n", calist->head->offset);
    calist->tail = ca;
    calist->length += 1;
  }
  else{
    if(calist->length < CACHE_SIZE){
      calist->tail->next = ca;
      calist->tail = ca;
      calist->length += 1;
    }
    else{
      calist->head = calist->head->next;
      calist->tail->next = ca;
      calist->tail = ca;
    }
  }
}

void update_cache(struct cachelist * calist, struct cache * ca, struct cache * prev, char * buf){
  if(buf != NULL){
    memcpy(ca->buf, buf, 4096);
  }
  if(prev == NULL){
    if(ca->next != NULL){
      calist->head = ca->next;
      calist->tail->next = ca;
      calist->tail = ca;
      ca->next = NULL;
    }
  }
  else{
    if(ca->next != NULL){
      prev->next = ca->next;
      ca->next = NULL;
      calist->tail->next = ca;
      calist->tail = ca;
    }
  }
}
