/*
  Big Brother File System
  Copyright (C) 2012 Joseph J. Pfeiffer, Jr., Ph.D. <pfeiffer@cs.nmsu.edu>

  This program can be distributed under the terms of the GNU GPLv3.
  See the file COPYING.

  This code is derived from function prototypes found /usr/include/fuse/fuse.h
  Copyright (C) 2001-2007  Miklos Szeredi <miklos@szeredi.hu>
  His code is licensed under the LGPLv2.
  A copy of that code is included in the file fuse.h
  
  The point of this FUSE filesystem is to provide an introduction to
  FUSE.  It was my first FUSE filesystem as I got to know the
  software; hopefully, the comments in this code will help people who
  follow later to get a gentler introduction.

  This might be called a no-op filesystem:  it doesn't impose
  filesystem semantics on top of any other existing structure.  It
  simply reports the requests that come in, and passes them to an
  underlying filesystem.  The information is saved in a logfile named
  bbfs.log, in the directory from which you run bbfs.
*/
#define _FILE_OFFSET_BITS  64
#include "params.h"
#include "IDL.h"

#include <ctype.h>
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <fuse.h>
#include <libgen.h>
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <time.h>

#ifdef HAVE_SYS_XATTR_H
#include <sys/xattr.h>
#endif

#include "log.h"
#include "cache.h"
#include "file_record.h"

const int useReadCache = 0; // use to determine if we use read cache
const int useWriteCache = 0;  // use to determine if we use write cache

const char * host = "10.148.54.199";
const int password_expiration=20; //second
//  All the paths I see are relative to the root of the mounted
//  filesystem.  In order to get to the underlying filesystem, I need to
//  have the mountpoint.  I'll save it away early on in main(), and then
//  whenever I need a path for something I'll call this to constructd
//  it.
struct cachelist cachlist;
struct cachelist * calist = & cachlist;

fileRecord fr;
fileRecord * frP = &fr;
// frP->head = NULL;
// frP->tail = NULL; 
// fr.head = NULL;
// fr.tail = NULL; 

time_t last_activate;

// BKDR Hash Function
unsigned int BKDRHash(char *str)
{
    unsigned int seed = 131; // 31 131 1313 13131 131313 etc..
    unsigned int hash = 0;
 
    while (*str)
    {
        hash = hash * seed + (*str++);
    }
 
    return (hash & 0x7FFFFFFF);
}

int user_authenticate(){
    char * password = (char *)malloc(sizeof(char)* 128); //128 == length of plain password
    fprintf(stdout,"Please type in the password given by NFS server:\n");
    fscanf(stdin,"%s",password);
    unsigned int hashvalue = BKDRHash(password);

    struct authenticate_IDL * new_authenticate = (struct authenticate_IDL *)malloc(sizeof(struct authenticate_IDL));
    new_authenticate -> hash = hashvalue;
    
    CLIENT * clnt = clnt_create(host, NFS_FUSE, NFS_FUSE_VERS, "udp");
    if(clnt==NULL){
        clnt_pcreateerror (host);
        exit (1);
    }
    int * result = authenticate_1000(new_authenticate,clnt);
    clnt_destroy (clnt);
    free(new_authenticate);
    return *result;
}

CLIENT * createclient() {
    CLIENT * clnt;
    clnt = clnt_create (host, NFS_FUSE, NFS_FUSE_VERS, "udp");
    if (clnt == NULL) {
        clnt_pcreateerror (host);
        exit (1);
    }
    return clnt;
}

void destroyclient(CLIENT * clnt){
  clnt_destroy(clnt);
}

static void bb_fullpath(char fpath[PATH_MAX], const char *path)
{   
    strcpy(fpath, BB_DATA->rootdir);
    strncat(fpath, path, PATH_MAX); // ridiculously long paths will
				    // break here

    log_msg("    bb_fullpath:  rootdir = \"%s\", path = \"%s\", fpath = \"%s\"\n",
	    BB_DATA->rootdir, path, fpath);
}

void print_getattr_IDL(getattr_ret_IDL res) {
    printf("\n");
    printf("************************\n");
    printf("result.res: %d\n", res.res);
    printf("result.st_dev: %u\n", res.st_dev);
    printf("result.st_ino: %u\n", res.st_ino);
    printf("result.st_mode: %ld\n", res.st_mode);
    printf("result.st_nlink: %u\n", res.st_nlink);
    printf("result.st_uid: %u\n", res.st_uid);
    printf("result.st_gid: %u\n", res.st_gid);
    printf("result.st_rdev: %u\n", res.st_rdev);
    printf("result.st_size: %u\n", res.st_size);
    printf("result.st_blksize: %u\n", res.st_blksize);
    printf("result.st_blocks: %u\n", res.st_blocks);
    printf("result.st_atim: %u\n", res.st_atim);
    printf("result.st_mtim: %u\n", res.st_mtim);
    printf("result.st_ctim: %u\n", res.st_ctim);
    printf("************************\n");
    printf("\n");
}

///////////////////////////////////////////////////////////
//
// Prototypes for all these functions, and the C-style comments,
// come from /usr/include/fuse.h
//
/** Get file attributes.
 *
 * Similar to stat().  The 'st_dev' and 'st_blksize' fields are
 * ignored.  The 'st_ino' field is ignored except if the 'use_ino'
 * mount option is given.
 */
int bb_getattr(const char *path, struct stat *statbuf)
{   
    int retstat;
    char fpath[PATH_MAX];
    
    log_msg("\nbb_getattr(path=\"%s\", statbuf=0x%08x)\n",
      path, statbuf);
    
    CLIENT * clnt = createclient();
    
    getattr_ret_IDL * result;
    getattr_IDL * new_getattr = (struct getattr_IDL*)malloc(sizeof(struct getattr_IDL));
    new_getattr->path = (char*)malloc(sizeof(char) * (strlen(path) + 1));
    strncpy(new_getattr->path, path, strlen(path));
    new_getattr->path[strlen(path)] = '\0';

    // log_msg("original path: %s\n", path);
    // log_msg("strlen result: %u\n", strlen(path));
    // log_msg("new_getattr->path: %s\n", new_getattr->path);
    log_msg("before getattr\n");
    result = getattr_1000(new_getattr, clnt);
    print_getattr_IDL(*result);
    log_msg("after getattr\n");
    // log_msg("mode recv is %3o\n", new_getattr->st_mode);
    log_msg("result.st_dev: %d\n", result->st_dev);
    statbuf->st_dev = result->st_dev;
    statbuf->st_ino = result->st_ino;
    statbuf->st_mode = result->st_mode;
    statbuf->st_nlink = result->st_nlink;
    statbuf->st_uid = result->st_uid;
    statbuf->st_gid = result->st_gid;
    statbuf->st_rdev = result->st_rdev;
    statbuf->st_size = result->st_size;
    statbuf->st_blksize = result->st_blksize;
    statbuf->st_blocks = result->st_blocks;
    statbuf->st_atime = result->st_atim;
    statbuf->st_mtime = result->st_mtim;
    statbuf->st_ctime = result->st_ctim;
    log_msg("mode returned is %3o\n", statbuf->st_mode);

    free(new_getattr->path);
    free(new_getattr);
    log_stat(statbuf);
    destroyclient(clnt);
    return result->res;
}



/** Read the target of a symbolic link
 *
 * The buffer should be filled with a null terminated string.  The
 * buffer size argument includes the space for the terminating
 * null character.  If the linkname is too long to fit in the
 * buffer, it should be truncated.  The return value should be 0
 * for success.
 */
// Note the system readlink() will truncate and lose the terminating
// null.  So, the size passed to to the system readlink() must be one
// less than the size passed to bb_readlink()
// bb_readlink() code by Bernardo F Costa (thanks!)
int bb_readlink(const char *path, char *link, size_t size)
{   
    int retstat;
    char fpath[PATH_MAX];
    
    log_msg("\nbb_readlink(path=\"%s\", link=\"%s\", size=%d)\n",
	  path, link, size);
    bb_fullpath(fpath, path);

    retstat = log_syscall("readlink", readlink(fpath, link, size - 1), 0);
    if (retstat >= 0) {
	link[retstat] = '\0';
	retstat = 0;
	log_msg("    link=\"%s\"\n", link);
    }
    
    return retstat;
}

/** Create a file node
 *
 * There is no create() operation, mknod() will be called for
 * creation of all non-directory, non-symlink nodes.
 */
// shouldn't that comment be "if" there is no.... ?
int bb_mknod(const char *path, mode_t mode, dev_t dev)
{
    log_msg("\nbb_mknod(path=\"%s\", mode=0%3o, dev=%lld)\n",
	  path, mode, dev);
    CLIENT * clnt = createclient();
    mknod_IDL * new_mknod = (mknod_IDL *)malloc(sizeof(mknod_IDL));
    new_mknod->path = (char*)malloc(sizeof(char) * (strlen(path) + 1));
    strncpy(new_mknod->path, path, strlen(path));
    new_mknod->path[strlen(path)] = '\0';
    new_mknod->mode = mode;
    new_mknod->dev = dev;

    int * pRes;
    pRes = mknod_1000(new_mknod, clnt);

    free(new_mknod->path);
    free(new_mknod);
    destroyclient(clnt);

    return *pRes;
}

/** Create a directory */
int bb_mkdir(const char *path, mode_t mode)
{
    char fpath[PATH_MAX];
    
    log_msg("\nbb_mkdir(path=\"%s\", mode=0%3o)\n",
	    path, mode);
    CLIENT * clnt = createclient();
    struct mkdir_IDL * new_mkdir = (struct mkdir_IDL*)malloc(sizeof(struct mkdir_IDL));
    new_mkdir->path = (char*)malloc(sizeof(char) * (strlen(path) + 1));
    strncpy(new_mkdir->path, path, strlen(path));
    new_mkdir->path[strlen(path)] = '\0';
    log_msg("path sent %s\n", new_mkdir->path);
    new_mkdir->mode = mode;
    int result;                                                                                                 
    int * p = &result;
    p = (int*)mkdir_1000(new_mkdir, clnt);
    destroyclient(clnt);
    free(new_mkdir->path);
    free(new_mkdir);
    return *p;
}

/** Remove a file */
int bb_unlink(const char *path)
{   
    log_msg("bb_unlink(path=\"%s\")\n", path);
    CLIENT * clnt = createclient();
    struct unlink_IDL * new_unlink = (struct unlink_IDL*)malloc(sizeof(struct unlink_IDL));
    new_unlink -> path =  (char*)malloc(sizeof(char) * (strlen(path) + 1));
    strncpy(new_unlink->path, path, strlen(path));
    printf("new_unlink->path=%s",new_unlink->path);
    int * result = unlink_1000(new_unlink, clnt);
    destroyclient(clnt);
    free(new_unlink->path);
    free(new_unlink);
    return *result;
}

/** Remove a directory */
int bb_rmdir(const char *path)
{
    char fpath[PATH_MAX];
    
    log_msg("bb_rmdir(path=\"%s\")\n",
	    path);
    CLIENT * clnt = createclient();
    struct rmdir_IDL * new_rmdir = (struct rmdir_IDL*)malloc(sizeof(struct rmdir_IDL));
    new_rmdir->path = (char*)malloc(sizeof(char) * (strlen(path) + 1));
    strncpy(new_rmdir->path, path, strlen(path));
    new_rmdir->path[strlen(path)] = '\0';
    int result;
    int * p = &result;
    p = rmdir_1000(new_rmdir, clnt);
    destroyclient(clnt);
    free(new_rmdir->path);
    free(new_rmdir);
    return *p;
    }

/** Create a symbolic link */
// The parameters here are a little bit confusing, but do correspond
// to the symlink() system call.  The 'path' is where the link points,
// while the 'link' is the link itself.  So we need to leave the path
// unaltered, but insert the link into the mounted directory.
int bb_symlink(const char *path, const char *link)
{
    char flink[PATH_MAX];
    
    log_msg("\nbb_symlink(path=\"%s\", link=\"%s\")\n",
	    path, link);
    bb_fullpath(flink, link);

    return log_syscall("symlink", symlink(path, flink), 0);
}

/** Rename a file */
// both path and newpath are fs-relative
int bb_rename(const char *path, const char *newpath)
{
    log_msg("\nbb_rename(fpath=\"%s\", newpath=\"%s\")\n", path, newpath);
    CLIENT * clnt = createclient();
    int * result;

    rename_IDL * new_rename = (rename_IDL *)malloc(sizeof(rename_IDL));
    new_rename->path = (char*)malloc(sizeof(char) * (strlen(path) + 1));
    strncpy(new_rename->path, path, strlen(path));
    new_rename->path[strlen(path)] = '\0';

    new_rename->newpath = (char*)malloc(sizeof(char) * (strlen(newpath) + 1));
    strncpy(new_rename->newpath, newpath, strlen(newpath));
    new_rename->newpath[strlen(newpath)] = '\0';

    result = rename_1000(new_rename, clnt);
    destroyclient(clnt);
    free(new_rename->newpath);
    free(new_rename->path);
    free(new_rename);
    return *result;
}

/** Create a hard link to a file */
int bb_link(const char *path, const char *newpath)
{
    char fpath[PATH_MAX], fnewpath[PATH_MAX];
    
    log_msg("\nbb_link(path=\"%s\", newpath=\"%s\")\n",
	    path, newpath);
    bb_fullpath(fpath, path);
    bb_fullpath(fnewpath, newpath);

    return log_syscall("link", link(fpath, fnewpath), 0);
}

/** Change the permission bits of a file */
int bb_chmod(const char *path, mode_t mode)
{
    log_msg("\nbb_chmod(fpath=\"%s\", mode=0%03o)\n", path, mode);
    CLIENT * clnt = createclient();
    int * result;

    chmod_IDL * new_chmod = (chmod_IDL *)malloc(sizeof(chmod_IDL));
    new_chmod->path = (char*)malloc(sizeof(char) * (strlen(path) + 1));
    strncpy(new_chmod->path, path, strlen(path));
    new_chmod->path[strlen(path)] = '\0';
    new_chmod->mode = mode;

    result = chmod_1000(new_chmod, clnt);
    destroyclient(clnt);
    free(new_chmod->path);
    free(new_chmod);

    return *result;
}

/** Change the owner and group of a file */
int bb_chown(const char *path, uid_t uid, gid_t gid)
{
    log_msg("\nbb_chown(path=\"%s\", uid=%d, gid=%d)\n", path, uid, gid);
    CLIENT * clnt = createclient();
    int * result;

    chown_IDL * new_chown = (chown_IDL *)malloc(sizeof(chown_IDL));
    new_chown->path = (char*)malloc(sizeof(char) * (strlen(path) + 1));
    strncpy(new_chown->path, path, strlen(path));
    new_chown->path[strlen(path)] = '\0';
    new_chown->uid = uid;
    new_chown->gid = gid;

    result = chown_1000(new_chown, clnt);
    destroyclient(clnt);
    free(new_chown->path);
    free(new_chown);

    return *result;
}

/** Change the size of a file */
int bb_truncate(const char *path, off_t newsize)
{
    char fpath[PATH_MAX];
    int * result;
    log_msg("\nbb_truncate(path=\"%s\", newsize=%lld)\n",
	    path, newsize);
    //bb_fullpath(fpath, path);
    struct truncate_IDL * newtruncate = (struct truncate_IDL * )malloc(sizeof(truncate_IDL));
    newtruncate->path = (char*)malloc(sizeof(char) * (strlen(path) + 1));
    strncpy(newtruncate->path, path, strlen(path));
    newtruncate->path[strlen(path)] = '\0';
    newtruncate->newsize = newsize;
    CLIENT * clnt = createclient();
    result = truncate_1000(newtruncate, clnt);
    destroyclient(clnt);
    free(newtruncate->path);
    free(newtruncate);
    return *result;
    //return log_syscall("truncate", truncate(fpath, newsize), 0);
}

/** Change the access and/or modification times of a file */
/* note -- I'll want to change this as soon as 2.6 is in debian testing */
int bb_utime(const char *path, struct utimbuf *ubuf)
{
    log_msg("\nbb_utime(path=\"%s\", ubuf=0x%08x)\n", path, ubuf);
    utime_ret_IDL * result;
    CLIENT * clnt = createclient();

    utime_IDL * new_utime = (utime_IDL *)malloc(sizeof(utime_IDL));
    new_utime->path = (char*)malloc(sizeof(char) * (strlen(path) + 1));
    strncpy(new_utime->path, path, strlen(path));
    new_utime->path[strlen(path)] = '\0';

    result = (utime_ret_IDL *)utime_1000(new_utime, clnt);
    ubuf->actime = result->actime;
    ubuf->modtime = result->modtime;

    free(new_utime->path);
    free(new_utime);
    destroyclient(clnt);

    return result->res;
}

/** File open operation
 *
 * No creation, or truncation flags (O_CREAT, O_EXCL, O_TRUNC)
 * will be passed to open().  Open should check if the operation
 * is permitted for the given flags.  Optionally open may also
 * return an arbitrary filehandle in the fuse_file_info structure,
 * which will be passed to all file operations.
 *
 * Changed in version 2.2
 */
int bb_open(const char *path, struct fuse_file_info *fi)
{
    int retstat = 0;
    int * p;
    
    log_msg("\nbb_open(path\"%s\", fi=0x%08x)\n",
	    path, fi);

    CLIENT * clnt = createclient();
    
    struct open_IDL * newopen = (struct open_IDL*)malloc(sizeof(struct open_IDL));
    newopen->path = (char*)malloc(sizeof(char) * (strlen(path) + 1));
    strncpy(newopen->path, path, strlen(path));
    newopen->path[strlen(path)] = '\0';
    newopen->flags = fi->flags;

    log_msg("newopen->flags: %d\n", newopen->flags);

    p = open_1000(newopen, clnt);
    log_msg("open_10 return value *p: %d\n", *p);
    if (*p < 0)
	   retstat = log_error("open");
	
    fi->fh = *p;

    log_fi(fi);
    destroyclient(clnt);
    free(newopen->path);
    free(newopen);
    return retstat;
}

/** Read data from an open file
 *
 * Read should return exactly the number of bytes requested except
 * on EOF or error, otherwise the rest of the data will be
 * substituted with zeroes.  An exception to this is when the
 * 'direct_io' mount option is specified, in which case the return
 * value of the read system call will reflect the return value of
 * this operation.
 *
 * Changed in version 2.2
 */
// I don't fully understand the documentation above -- it doesn't
// match the documentation for the read() system call which says it
// can return with anything up to the amount of data requested. nor
// with the fusexmp code which returns the amount of data also
// returned by read.
int bb_read(const char *path, char *buf, size_t size, off_t offset, struct fuse_file_info *fi)
{
    size_t rest_len;
    log_msg("\nbb_read(path=\"%s\", buf=0x%08x, size=%d, offset=%lld, fi=0x%08x)\n", path, buf, size, offset, fi);
    int total_length = 0;

    if(useReadCache == 0){
      while(size > 0){
      size_t this_size = size <= 4096 ? size : 4096;
      CLIENT * clnt = createclient();
      struct read_IDL * newread = (struct read_IDL*)malloc(sizeof(struct read_IDL));
      newread->size = size <= 4096 ? size : 4096;
      newread->offset = offset;
      newread->fh = fi->fh;
      struct read_ret_IDL * result;
      result = read_1000(newread, clnt);
      int length_readed = result->count;
      log_msg("length_readed: %d\n", length_readed);
      if(length_readed == 0) {
        break;
      }
      memcpy(buf, result->buf, length_readed);
      buf += this_size;
      offset += this_size;
      size -= this_size;
      total_length += length_readed;
      free(newread);
      destroyclient(clnt);
      }
    }
    else{
    while(size > 0) {
        struct stat *statbuf = (struct stat*)malloc(sizeof(struct stat));
	//if use read cache, then getattr to get timestamp
	bb_getattr(path, statbuf);
	log_msg("\npresent stat->mtime is %d\n", statbuf->st_mtime);
    	struct cache * curr = calist->head;
    	struct cache * prev = NULL;
    	int find_cache = 0;//0 = no cache; 1 = valid cache; 2 = invalid cache
    	size_t this_size = size <= 4096 ? size : 4096;
    	while(curr != NULL){
	  //make sure if not use read cache, no need to check cache
          log_msg("curr cache: size is %ld, offset is %ld, path is %s\n", curr->size, curr->offset, curr->path);
          log_msg("requested content: size is %ld, offset is %ld, path is %s\n", this_size, offset, path);
    	  if(strncmp(path, curr->path, strlen(path) + 1) == 0 && curr->size == this_size && curr->offset == offset){
    	    if(curr->mtime == statbuf->st_mtime){
    	      find_cache = 1;
    	      break;
    	    }
    	    else{
    	      find_cache = 2;
    	      break;
    	    }
    	  }
    	  prev = curr;
    	  curr = curr->next;
    	}
        log_msg("find cache state is %d\n", find_cache);
    	if (find_cache == 0 || find_cache == 2){
                CLIENT * clnt = createclient();
                struct read_IDL * newread = (struct read_IDL*)malloc(sizeof(struct read_IDL));
                newread->size = size <= 4096 ? size : 4096;
                newread->offset = offset;
                newread->fh = fi->fh;
                struct read_ret_IDL * result;
                result = read_1000(newread, clnt);
                int length_readed = result->count;
                log_msg("length_readed: %d\n", length_readed);
                if(length_readed == 0) {
                    break;
                }
                memcpy(buf, result->buf, length_readed);
                //log_msg("current buf: \n%s\n", buf);
		//update cache only when using it
		if(find_cache == 0){//if cache miss, add a new one to cache list
		    log_msg("start add new cache");
		    struct cache * newcache = (struct cache *)malloc(sizeof(struct cache));
		    newcache->size = 4096;
		    newcache->offset = newread->offset;
		    newcache->next = NULL;
		    memset(newcache->path, '\0', PATH_MAX);
		    memcpy(newcache->path, path, strlen(path));
		    newcache->mtime = statbuf->st_mtime;
		    memset(newcache->buf, '\0', 4096);
		    memcpy(newcache->buf, result->buf, length_readed);
		    add_cache(calist, newcache);
		}
		else{//if cache invalid, update it
		    curr->mtime = statbuf->st_mtime;
    	      //memcpy(curr->buf, result->buf, length_readed);
		    update_cache(calist, curr, prev, result->buf);
		}
		buf += this_size;
		offset += this_size;
		size -= this_size;
		total_length += length_readed;
		free(newread);
		destroyclient(clnt);
	
	}
    	else{//if cache valid
    	    log_msg("cache hit, return cached buf");
    	    memcpy(buf, curr->buf, this_size);
    	    update_cache(calist, curr, prev, NULL);
            buf += this_size;
            offset += this_size;
            size -= this_size;
            total_length += this_size;
    	}
    }
    }
    return total_length;
}

// this function will write content in cache with "fd" to server
void write_helper(int fd) {
    fileNode * target = find(frP, fd);
    if(target == NULL) {
        log_msg("Inside write_helper, nothing in write back cache with fd: %d\n", fd);
    } else {
        while(target != NULL) {
            char * buf = target->buf;
            unsigned int size = target->size;
            unsigned int offset = target->offset;
            int total_length = 0;

            log_msg("\nwrite_helper(buf=0x%08x, size=%d, offset=%lld)\n", buf, size, offset);

            // start write to server
            while(size > 0){
              CLIENT * clnt = createclient();
              struct write_IDL * newwrite = (struct write_IDL*)malloc(sizeof(struct write_IDL));
              newwrite->size = size <= 4096 ? size : 4096;
              newwrite->offset = offset;
              newwrite->fh = fd;
              //newwrite->buf = (char*)malloc(sizeof(char) * newwrite->size);
              memset(newwrite->buf, '\0', 4096);
              memcpy(newwrite->buf, buf, newwrite->size);
              int * single_length;
              single_length = write_1000(newwrite, clnt);
              log_msg("single_length written is %d\n", *single_length);
              total_length += *single_length;
              size -= newwrite->size;
              log_msg("size - newwrite->size is: %d\n", size);
              offset += newwrite->size;
              buf += newwrite->size;
              log_msg("before free");
              //free(newwrite->buf);
              free(newwrite);
              destroyclient(clnt);
              printf("end of loop\n");
            }
            log_msg("total_length written is %d\n", total_length);

            // delete this node
            deleteNode(frP, fd);
            target = find(frP, fd);
        }
    }
}

/** Write data to an open file
 *
 * Write should return exactly the number of bytes requested
 * except on error.  An exception to this is when the 'direct_io'
 * mount option is specified (see read operation).
 *
 * Changed in version 2.2
 */
// As  with read(), the documentation above is inconsistent with the
// documentation for the write() system call.
int bb_write(const char *path, const char *buf, size_t size, off_t offset,
	     struct fuse_file_info *fi)
{
    if(useWriteCache == 1) {
        size_t rest_len;
        log_msg("\nbb_write(path=\"%s\", buf=0x%08x, size=%d, offset=%lld, fi=0x%08x)\n",
            path, buf, size, offset, fi
            );
        
        log_msg("before addNode in bb_write\n");
        addNode(frP, buf, size, offset, fi->fh);
        log_msg("after addNode in bb_write\n");
        
        return size;
    } else {
        size_t rest_len;
        int total_length = 0;
        log_msg("\nbb_write(path=\"%s\", buf=0x%08x, size=%d, offset=%lld, fi=0x%08x)\n",
            path, buf, size, offset, fi
            );
        // no need to get fpath on this one, since I work from fi->fh not the
        while(size > 0){
          CLIENT * clnt = createclient();
          struct write_IDL * newwrite = (struct write_IDL*)malloc(sizeof(struct write_IDL));
          newwrite->size = size <= 4096 ? size : 4096;
          newwrite->offset = offset;
          newwrite->fh = fi->fh;
          //newwrite->buf = (char*)malloc(sizeof(char) * newwrite->size);
          memset(newwrite->buf, '\0', 4096);
          memcpy(newwrite->buf, buf, newwrite->size);
          int * single_length;
          single_length = write_1000(newwrite, clnt);
          log_msg("single_length written is %d\n", *single_length);
          total_length += *single_length;
          size -= newwrite->size;
          log_msg("size - newwrite->size is: %d\n", size);
          offset += newwrite->size;
          buf += newwrite->size;
          log_msg("before free");
          //free(newwrite->buf);
          free(newwrite);
          destroyclient(clnt);
          printf("end of loop\n");
        }
        log_msg("total_length written is %d\n", total_length);
        return total_length;
    }
}

/** Get file system statistics
 *
 * The 'f_frsize', 'f_favail', 'f_fsid' and 'f_flag' fields are ignored
 *
 * Replaced 'struct statfs' parameter with 'struct statvfs' in
 * version 2.5
 */
int bb_statfs(const char *path, struct statvfs *statv)
{
    int retstat = 0;
    char fpath[PATH_MAX];
    
    log_msg("\nbb_statfs(path=\"%s\", statv=0x%08x)\n",
	    path, statv);
    bb_fullpath(fpath, path);
    
    // get stats for underlying filesystem
    retstat = log_syscall("statvfs", statvfs(fpath, statv), 0);
    
    log_statvfs(statv);
    
    return retstat;
}

/** Possibly flush cached data
 *
 * BIG NOTE: This is not equivalent to fsync().  It's not a
 * request to sync dirty data.
 *
 * Flush is called on each close() of a file descriptor.  So if a
 * filesystem wants to return write errors in close() and the file
 * has cached dirty data, this is a good place to write back data
 * and return any errors.  Since many applications ignore close()
 * errors this is not always useful.
 *
 * NOTE: The flush() method may be called more than once for each
 * open().  This happens if more than one file descriptor refers
 * to an opened file due to dup(), dup2() or fork() calls.  It is
 * not possible to determine if a flush is final, so each flush
 * should be treated equally.  Multiple write-flush sequences are
 * relatively rare, so this shouldn't be a problem.
 *
 * Filesystems shouldn't assume that flush will always be called
 * after some writes, or that if will be called at all.
 *
 * Changed in version 2.2
 */
// this is a no-op in BBFS.  It just logs the call and returns success
int bb_flush(const char *path, struct fuse_file_info *fi)
{
    log_msg("\nbb_flush(path=\"%s\", fi=0x%08x)\n", path, fi);
    // no need to get fpath on this one, since I work from fi->fh not the path
    log_fi(fi);

    if(useWriteCache == 1) {
        log_msg("before calling write_helper\n");
        write_helper(fi->fh);
        log_msg("after calling write_helper\n");
    }
    return 0;
}

/** Release an open file
 *
 * Release is called when there are no more references to an open
 * file: all file descriptors are closed and all memory mappings
 * are unmapped.
 *
 * For every open() call there will be exactly one release() call
 * with the same flags and file descriptor.  It is possible to
 * have a file opened more than once, in which case only the last
 * release will mean, that no more reads/writes will happen on the
 * file.  The return value of release is ignored.
 *
 * Changed in version 2.2
 */
int bb_release(const char *path, struct fuse_file_info *fi)
{
    log_msg("\nbb_release(path=\"%s\", fi=0x%08x)\n",
	  path, fi);
    log_fi(fi);

    // We need to close the file.  Had we allocated any resources
    // (buffers etc) we'd need to free them here as well.
    CLIENT * clnt = createclient();
    release_IDL new_release;
    new_release.fh = fi->fh;
    int * pRes;
    pRes = release_1000(&new_release, clnt);
    log_msg("close function result: %d\n", *pRes);
    destroyclient(clnt);
    return *pRes;
}

/** Synchronize file contents
 *
 * If the datasync parameter is non-zero, then only the user data
 * should be flushed, not the meta data.
 *
 * Changed in version 2.2
 */
int bb_fsync(const char *path, int datasync, struct fuse_file_info *fi)
{   
    log_msg("\nbb_fsync(path=\"%s\", datasync=%d, fi=0x%08x)\n",
	    path, datasync, fi);
    log_fi(fi);
    
    // some unix-like systems (notably freebsd) don't have a datasync call
#ifdef HAVE_FDATASYNC
    if (datasync){
        CLIENT * clnt = createclient();
        struct fdatasync_IDL * newfdatasync = (struct fdatasync_IDL *)malloc(sizeof(struct fdatasync_IDL));
	newfdatasync->fh = fi->fh;
	int * result;
	result = fdatasync_1000(newfdatasync, clnt);
	free(newfdatasync);
	return *result;}
    else
	{
      CLIENT * clnt = createclient();
        struct fsync_IDL * newfsync = (struct fsync_IDL *)malloc(sizeof(struct fsync_IDL));
        newfsync->fh = fi->fh;
        int * result;
        result = fsync_1000(newfsync, clnt);
	free(newfsync);
        return *result;
      }
#endif
}

#ifdef HAVE_SYS_XATTR_H
/** Note that my implementations of the various xattr functions use
    the 'l-' versions of the functions (eg bb_setxattr() calls
    lsetxattr() not setxattr(), etc).  This is because it appears any
    symbolic links are resolved before the actual call takes place, so
    I only need to use the system-provided calls that don't follow
    them */

/** Set extended attributes */
int bb_setxattr(const char *path, const char *name, const char *value, size_t size, int flags)
{
    char fpath[PATH_MAX];
    
    log_msg("\nbb_setxattr(path=\"%s\", name=\"%s\", value=\"%s\", size=%d, flags=0x%08x)\n",
	    path, name, value, size, flags);
    bb_fullpath(fpath, path);

    return log_syscall("lsetxattr", lsetxattr(fpath, name, value, size, flags), 0);
}

/** Get extended attributes */
int bb_getxattr(const char *path, const char *name, char *value, size_t size)
{
    int retstat = 0;
    char fpath[PATH_MAX];
    
    log_msg("\nbb_getxattr(path = \"%s\", name = \"%s\", value = 0x%08x, size = %d)\n",
	    path, name, value, size);
    bb_fullpath(fpath, path);

    retstat = log_syscall("lgetxattr", lgetxattr(fpath, name, value, size), 0);
    if (retstat >= 0)
	log_msg("    value = \"%s\"\n", value);
    
    return retstat;
}

/** List extended attributes */
int bb_listxattr(const char *path, char *list, size_t size)
{
    int retstat = 0;
    char fpath[PATH_MAX];
    char *ptr;
    
    log_msg("\nbb_listxattr(path=\"%s\", list=0x%08x, size=%d)\n",
	    path, list, size
	    );
    bb_fullpath(fpath, path);

    retstat = log_syscall("llistxattr", llistxattr(fpath, list, size), 0);
    if (retstat >= 0) {
	log_msg("    returned attributes (length %d):\n", retstat);
	if (list != NULL)
	    for (ptr = list; ptr < list + retstat; ptr += strlen(ptr)+1)
		log_msg("    \"%s\"\n", ptr);
	else
	    log_msg("    (null)\n");
    }
    
    return retstat;
}

/** Remove extended attributes */
int bb_removexattr(const char *path, const char *name)
{
    char fpath[PATH_MAX];
    
    log_msg("\nbb_removexattr(path=\"%s\", name=\"%s\")\n",
	    path, name);
    bb_fullpath(fpath, path);

    return log_syscall("lremovexattr", lremovexattr(fpath, name), 0);
}
#endif

/** Open directory
 *
 * This method should check if the open operation is permitted for
 * this  directory
 *
 * Introduced in version 2.3
 */
int bb_opendir(const char *path, struct fuse_file_info *fi)
{
    log_msg("\nbb_opendir(path=\"%s\", fi=0x%08x)\n",
	  path, fi);

    CLIENT * clnt = createclient();
    opendir_IDL * new_opendir = (opendir_IDL *)malloc(sizeof(opendir_IDL));
    new_opendir->path = (char*)malloc(sizeof(char) * (strlen(path) + 1));
    strncpy(new_opendir->path, path, strlen(path));
    new_opendir->path[strlen(path)] = '\0';

    opendir_ret_IDL * pRes;   // field of isvalid determine if opendir call on server side is successful, 1 -> success; 0 ->fail
    pRes = (opendir_ret_IDL *)opendir_1000(new_opendir, clnt);
    log_msg("pRes->res: %d", pRes->res);
    log_msg("pRes->isvalid: %d", pRes->isvalid);

    fi->fh = pRes->res;
    log_fi(fi);
    if(pRes->isvalid == 0) {
        int retstat = log_error("bb_opendir opendir");
        return retstat;
    }
    return 0;

  
}

/** Read directory
 *
 * This supersedes the old getdir() interface.  New applications
 * should use this.
 *
 * The filesystem may choose between two modes of operation:
 *
 * 1) The readdir implementation ignores the offset parameter, and
 * passes zero to the filler function's offset.  The filler
 * function will not return '1' (unless an error happens), so the
 * whole directory is read in a single readdir operation.  This
 * works just like the old getdir() method.
 *
 * 2) The readdir implementation keeps track of the offsets of the
 * directory entries.  It uses the offset parameter and always
 * passes non-zero offset to the filler function.  When the buffer
 * is full (or an error happens) the filler function will return
 * '1'.
 *
 * Introduced in version 2.3
 */

int bb_readdir(const char *path, void *buf, fuse_fill_dir_t filler, off_t offset,
           struct fuse_file_info *fi)
{
    log_msg("\nbb_readdir(path=\"%s\", buf=0x%08x, filler=0x%08x, offset=%lld, fi=0x%08x)\n",
        path, buf, filler, offset, fi);

    CLIENT * clnt = createclient();
    struct readdir_IDL *new_readdir = (struct readdir_IDL*)malloc(sizeof(struct  readdir_IDL));
    log_msg("fi->fh=%ld\n",fi->fh);
    new_readdir -> fh = fi->fh;
    log_msg("new_readdir->fh=%ld\n",new_readdir->fh);

    struct readdir_ret_IDL * ans; 
    ans = (readdir_ret_IDL*)readdir_1000(new_readdir, clnt);
    log_msg("ans count: %d\n", ans->count);
    int offs = 0;
    for(int i = 0; i < ans->count; i++){
      if (filler(buf, ans->buf + offs, NULL, 0) != 0) {
            log_msg("    ERROR bb_readdir filler:  buffer full");
            return -ENOMEM;
      }
      log_msg("ans->buf + offs: %s\n", ans->buf + offs);
      offs += strlen(ans->buf + offs) + 1;
    }
    destroyclient(clnt);
    free(new_readdir);    
    return ans->res;
}
/** Release directory
 *
 * Introduced in version 2.3
 */
int bb_releasedir(const char *path, struct fuse_file_info *fi)
{
    log_msg("\nbb_releasedir(path=\"%s\", fi=0x%08x)\n",
	    path, fi);
    log_fi(fi);

    CLIENT * clnt = createclient();
    releasedir_IDL new_releasedir;
    new_releasedir.fh = fi->fh;
    int * pRes;
    pRes = releasedir_1000(&new_releasedir, clnt);
    destroyclient(clnt);
    return *pRes;
}

/** Synchronize directory contents
 *
 * If the datasync parameter is non-zero, then only the user data
 * should be flushed, not the meta data
 *
 * Introduced in version 2.3
 */
// when exactly is this called?  when a user calls fsync and it
// happens to be a directory? ??? >>> I need to implement this...
int bb_fsyncdir(const char *path, int datasync, struct fuse_file_info *fi)
{
    int retstat = 0;
    
    log_msg("\nbb_fsyncdir(path=\"%s\", datasync=%d, fi=0x%08x)\n",
	    path, datasync, fi);
    log_fi(fi);
    
    return retstat;
}

/**
 * Initialize filesystem
 *
 * The return value will passed in the private_data field of
 * fuse_context to all file operations and as a parameter to the
 * destroy() method.
 *
 * Introduced in version 2.3
 * Changed in version 2.6
 */
// Undocumented but extraordinarily useful fact:  the fuse_context is
// set up before this function is called, and
// fuse_get_context()->private_data returns the user_data passed to
// fuse_main().  Really seems like either it should be a third
// parameter coming in here, or else the fact should be documented
// (and this might as well return void, as it did in older versions of
// FUSE).
void *bb_init(struct fuse_conn_info *conn)
{
    log_msg("\nbb_init()\n");
    
    //log_conn(conn);
    //log_fuse_context(fuse_get_context());
    
    return BB_DATA;
}

/**
 * Clean up filesystem
 *
 * Called on filesystem exit.
 *
 * Introduced in version 2.3
 */
void bb_destroy(void *userdata)
{
    log_msg("\nbb_destroy(userdata=0x%08x)\n", userdata);
}

/**
 * Check file access permissions
 *
 * This will be called for the access() system call.  If the
 * 'default_permissions' mount option is given, this method is not
 * called.
 *
 * This method is not called under Linux kernel versions 2.4.x
 *
 * Introduced in version 2.5
 */
int bb_access(const char *path, int mask)
{  
    log_msg("\nbb_access(path=\"%s\", mask=0%o)\n",
	    path, mask);

    CLIENT * clnt = createclient();
    int * pRes;
    access_IDL * new_access = (access_IDL *)malloc(sizeof(access_IDL));
    new_access->path = (char*)malloc(sizeof(char) * (strlen(path) + 1));
    strncpy(new_access->path, path, strlen(path));
    new_access->path[strlen(path)] = '\0';
    new_access->mask = mask;

    pRes = (int*)access_1000(new_access, clnt);
    
    if (*pRes < 0){
	   log_error("bb_access access");
    }
    free(new_access->path);
    free(new_access);
    destroyclient(clnt);
    return *pRes;
}

/**
 * Create and open a file
 *
 * If the file does not exist, first create it with the specified
 * mode, and then open it.
 *
 * If this method is not implemented or under Linux kernel
 * versions earlier than 2.6.15, the mknod() and open() methods
 * will be called instead.
 *
 * Introduced in version 2.5
 */
// Not implemented.  I had a version that used creat() to create and
// open the file, which it turned out opened the file write-only.

/**
 * Change the size of an open file
 *
 * This method is called instead of the truncate() method if the
 * truncation was invoked from an ftruncate() system call.
 *
 * If this method is not implemented or under Linux kernel
 * versions earlier than 2.6.15, the truncate() method will be
 * called instead.
 *
 * Introduced in version 2.5
 */
int bb_ftruncate(const char *path, off_t offset, struct fuse_file_info *fi)
{
    int retstat = 0;
    
    log_msg("\nbb_ftruncate(path=\"%s\", offset=%lld, fi=0x%08x)\n",
	    path, offset, fi);
    log_fi(fi);
    
    //char fpath[PATH_MAX];
    int * result;
    log_msg("\nbb_truncate(path=\"%s\", newsize=%lld), fi->fh=%d\n",
            path, offset, fi->fh);
    //bb_fullpath(fpath, path);                                                                                                               
    struct ftruncate_IDL * newftruncate = (struct ftruncate_IDL * )malloc(sizeof(ftruncate_IDL));
    //newtruncate->path = (char*)malloc(sizeof(char) * (strlen(path) + 1));
    //strncpy(newtruncate->path, path, strlen(path));
    //newtruncate->path[strlen(path)] = '\0';
    newftruncate->newsize = offset;
    newftruncate->fh = fi->fh;
    CLIENT * clnt = createclient();
    result = ftruncate_1000(newftruncate, clnt);
    destroyclient(clnt);
    //free(newtruncate->path);
    free(newftruncate);
    return *result;

}

/**
 * Get attributes from an open file
 *
 * This method is called instead of the getattr() method if the
 * file information is available.
 *

 * Currently this is only called after the create() method if that
 * is implemented (see above).  Later it may be called for
 * invocations of fstat() too.
 *
 * Introduced in version 2.5
 */
int bb_fgetattr(const char *path, struct stat *statbuf, struct fuse_file_info *fi)
{
    
    int retstat = 0;
    
    log_msg("\nbb_fgetattr(path=\"%s\", statbuf=0x%08x, fi=0x%08x)\n",
	    path, statbuf, fi);
    log_fi(fi);

    // On FreeBSD, trying to do anything with the mountpoint ends up
    // opening it, and then using the FD for an fgetattr.  So in the
    // special case of a path of "/", I need to do a getattr on the
    // underlying root directory instead of doing the fgetattr().
    if (!strcmp(path, "/"))
	return bb_getattr(path, statbuf);

    CLIENT * clnt = createclient();
    fgetattr_IDL new_fgetattr;
    new_fgetattr.fh = fi->fh;
    fgetattr_ret_IDL * result = (fgetattr_ret_IDL *)fgetattr_1000(&new_fgetattr, clnt);

    retstat = result->res;
    if (retstat < 0){
        retstat = log_error("bb_fgetattr fstat");    
    }
    
    statbuf->st_dev = result->st_dev;
    statbuf->st_ino = result->st_ino;
    statbuf->st_mode = result->st_mode;
    statbuf->st_nlink = result->st_nlink;
    statbuf->st_uid = result->st_uid;
    statbuf->st_gid = result->st_gid;
    statbuf->st_rdev = result->st_rdev;
    statbuf->st_size = result->st_size;
    statbuf->st_blksize = result->st_blksize;
    statbuf->st_blocks = result->st_blocks;
    statbuf->st_atime = result->st_atim;
    statbuf->st_mtime = result->st_mtim;
    statbuf->st_ctime = result->st_ctim;

    log_stat(statbuf);
    destroyclient(clnt);
    
    return retstat;
}

struct fuse_operations bb_oper = {
  .getattr = bb_getattr,
  .readlink = bb_readlink,
  // no .getdir -- that's deprecated
  .getdir = NULL,
  .mknod = bb_mknod,
  .mkdir = bb_mkdir,
  .unlink = bb_unlink,
  .rmdir = bb_rmdir,
  .symlink = bb_symlink,
  .rename = bb_rename,
  .link = bb_link,
  .chmod = bb_chmod,
  .chown = bb_chown,
  .truncate = bb_truncate,
  .utime = bb_utime,
  .open = bb_open,
  .read = bb_read,
  .write = bb_write,
  /** Just a placeholder, don't set */ // huh???
  .statfs = bb_statfs,
  .flush = bb_flush,
  .release = bb_release,
  .fsync = bb_fsync,
  
#ifdef HAVE_SYS_XATTR_H
  .setxattr = bb_setxattr,
  .getxattr = bb_getxattr,
  .listxattr = bb_listxattr,
  .removexattr = bb_removexattr,
#endif
  
  .opendir = bb_opendir,
  .readdir = bb_readdir,
  .releasedir = bb_releasedir,
  .fsyncdir = bb_fsyncdir,
  .init = bb_init,
  .destroy = bb_destroy,
  .access = bb_access,
  .ftruncate = bb_ftruncate,
  .fgetattr = bb_fgetattr
};

void bb_usage()
{
    fprintf(stderr, "usage:  ./NFS_client [options] <mount directory>\n");
    exit(1);
}

// test rpc hello
void test_hello() {
    CLIENT * clnt;
    clnt = clnt_create (host, NFS_FUSE, NFS_FUSE_VERS, "udp");
    if (clnt == NULL) {
        clnt_pcreateerror (host);
        exit (1);
    }
    hellotest_1000(NULL, clnt);
    clnt_destroy (clnt);
}

int main(int argc, char *argv[])
{
    int fuse_stat;
    struct bb_state *bb_data;
    test_hello();
    fprintf(stderr, "Sucessfully connecting to server(%s)\n",host);

    //first log in authenticate 
    int auth_res=1;
    while(auth_res==1){
        auth_res = user_authenticate();
    }

    //update last activate time
    time(&last_activate);

    if ((getuid() == 0) || (geteuid() == 0)) {
    	fprintf(stderr, "Running BBFS as root opens unnacceptable security holes\n");
    	return 1;
    }

    // See which version of fuse we're running
    fprintf(stderr, "Fuse library version %d.%d\n", FUSE_MAJOR_VERSION, FUSE_MINOR_VERSION);
    
    // Perform some sanity checking on the command line:  make sure
    // there are enough arguments, and that neither of the last two
    // start with a hyphen (this will break if you actually have a
    // rootpoint or mountpoint whose name starts with a hyphen, but so
    // will a zillion other programs)

    if (argc < 2 || (argv[argc-1][0] == '-')) {
        bb_usage();    
        abort();
    }

    bb_data = malloc(sizeof(struct bb_state));
    if (bb_data == NULL) {
    	perror("main calloc");
    	abort();
    }

    // Pull the rootdir out of the argument list and save it in my
    // internal data
    //bb_data->rootdir = realpath(argv[argc-2], NULL);
    //argv[argc-2] = argv[argc-1];
    //argv[argc-1] = NULL;
    //argc--;
    
    bb_data->logfile = log_open();
    
    // turn over control to fuse
    fprintf(stderr, "about to call fuse_main\n");
    fuse_stat = fuse_main(argc, argv, &bb_oper, bb_data);
    fprintf(stderr, "fuse_main returned %d\n", fuse_stat);
    //calist = (struct cachelist *)malloc(sizeof(struct cachelist));
    create_cachelist(calist);
    return fuse_stat;
}
