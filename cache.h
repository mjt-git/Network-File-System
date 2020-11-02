#include <linux/limits.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
struct cache{
  char path[PATH_MAX];
  size_t size;
  size_t offset;
  uint32_t mtime;
  char buf[4096];
  struct cache * next;
};
typedef struct cache cache;

struct cachelist{
  int length;
  struct cache * head;
  struct cache * tail;
};
typedef struct cachelist cachelist;

void create_cachelist(struct cachelist * calist);

void create_cache(struct cache * ca, char path[PATH_MAX], size_t size, size_t offset, uint32_t mtime, char buf[4096]);

void add_cache(struct cachelist * calist, struct cache * ca);

void update_cache(struct cachelist * calist, struct cache * ca, struct cache * prev, char * buf);
