/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#ifndef _IDL_H_RPCGEN
#define _IDL_H_RPCGEN

#include <rpc/rpc.h>


#ifdef __cplusplus
extern "C" {
#endif


struct timespec_IDL {
	long tv_sec;
	long tv_nsec;
};
typedef struct timespec_IDL timespec_IDL;

struct stat_IDL {
	uint32_t st_dev;
	uint32_t st_ino;
	long st_mode;
	uint32_t st_nlink;
	uint32_t st_uid;
	uint32_t st_gid;
	uint32_t st_rdev;
	uint32_t st_size;
	uint32_t st_blksize;
	uint32_t st_blocks;
	struct timespec_IDL st_atim;
	struct timespec_IDL st_mtim;
	struct timespec_IDL st_ctim;
};
typedef struct stat_IDL stat_IDL;

struct fuse_file_info_IDL {
	int flags;
	u_int writepage;
	u_int direct_io;
	u_int keep_cache;
	u_int flush;
	u_int nonseekable;
	u_int cache_readdir;
	u_int padding;
	uint64_t fh;
	uint64_t lock_owner;
	uint32_t poll_events;
};
typedef struct fuse_file_info_IDL fuse_file_info_IDL;

struct getattr_IDL {
	int res;
	char *path;
	uint32_t st_dev;
	uint32_t st_ino;
	long st_mode;
	uint32_t st_nlink;
	uint32_t st_uid;
	uint32_t st_gid;
	uint32_t st_rdev;
	uint32_t st_size;
	uint32_t st_blksize;
	uint32_t st_blocks;
	uint32_t st_atim;
	uint32_t st_mtim;
	uint32_t st_ctim;
};
typedef struct getattr_IDL getattr_IDL;

struct fgetattr_IDL {
	int fh;
};
typedef struct fgetattr_IDL fgetattr_IDL;

struct fgetattr_ret_IDL {
	int res;
	uint32_t st_dev;
	uint32_t st_ino;
	long st_mode;
	uint32_t st_nlink;
	uint32_t st_uid;
	uint32_t st_gid;
	uint32_t st_rdev;
	uint32_t st_size;
	uint32_t st_blksize;
	uint32_t st_blocks;
	uint32_t st_atim;
	uint32_t st_mtim;
	uint32_t st_ctim;
};
typedef struct fgetattr_ret_IDL fgetattr_ret_IDL;

struct mkdir_IDL {
	char *path;
	uint32_t mode;
};
typedef struct mkdir_IDL mkdir_IDL;

struct rmdir_IDL {
	char *path;
};
typedef struct rmdir_IDL rmdir_IDL;

struct open_IDL {
	char *path;
	uint32_t flags;
};
typedef struct open_IDL open_IDL;

struct read_IDL {
	uint32_t size;
	uint32_t offset;
	int fh;
};
typedef struct read_IDL read_IDL;

struct read_ret_IDL {
	int count;
	char buf[4096];
};
typedef struct read_ret_IDL read_ret_IDL;

struct write_IDL {
	char *path;
	char buf[4096];
	uint32_t size;
	uint32_t offset;
	uint32_t fh;
};
typedef struct write_IDL write_IDL;

struct write_ret_IDL {
	int res;
};
typedef struct write_ret_IDL write_ret_IDL;

struct opendir_IDL {
	char *path;
};
typedef struct opendir_IDL opendir_IDL;

struct opendir_ret_IDL {
	int res;
	int isvalid;
};
typedef struct opendir_ret_IDL opendir_ret_IDL;

struct readdir_IDL {
	uint64_t fh;
};
typedef struct readdir_IDL readdir_IDL;

struct readdir_ret_IDL {
	int res;
	char buf[1024];
	int length;
	int count;
};
typedef struct readdir_ret_IDL readdir_ret_IDL;

struct access_IDL {
	char *path;
	int mask;
};
typedef struct access_IDL access_IDL;

struct releasedir_IDL {
	int fh;
};
typedef struct releasedir_IDL releasedir_IDL;

struct release_IDL {
	int fh;
};
typedef struct release_IDL release_IDL;

struct mknod_IDL {
	char *path;
	int mode;
	int dev;
};
typedef struct mknod_IDL mknod_IDL;

#define NFS_FUSE 123789456
#define NFS_FUSE_VERS 1000

#if defined(__STDC__) || defined(__cplusplus)
#define GETATTR 1
extern  struct getattr_IDL * getattr_1000(struct getattr_IDL *, CLIENT *);
extern  struct getattr_IDL * getattr_1000_svc(struct getattr_IDL *, struct svc_req *);
#define MKDIR 2
extern  int * mkdir_1000(mkdir_IDL *, CLIENT *);
extern  int * mkdir_1000_svc(mkdir_IDL *, struct svc_req *);
#define RMDIR 3
extern  int * rmdir_1000(rmdir_IDL *, CLIENT *);
extern  int * rmdir_1000_svc(rmdir_IDL *, struct svc_req *);
#define OPEN 4
extern  int * open_1000(open_IDL *, CLIENT *);
extern  int * open_1000_svc(open_IDL *, struct svc_req *);
#define READ 5
extern  struct read_ret_IDL * read_1000(read_IDL *, CLIENT *);
extern  struct read_ret_IDL * read_1000_svc(read_IDL *, struct svc_req *);
#define WRITE 6
extern  struct write_IDL * write_1000(write_IDL *, CLIENT *);
extern  struct write_IDL * write_1000_svc(write_IDL *, struct svc_req *);
#define OPENDIR 7
extern  struct opendir_ret_IDL * opendir_1000(opendir_IDL *, CLIENT *);
extern  struct opendir_ret_IDL * opendir_1000_svc(opendir_IDL *, struct svc_req *);
#define READDIR 8
extern  struct readdir_ret_IDL * readdir_1000(readdir_IDL *, CLIENT *);
extern  struct readdir_ret_IDL * readdir_1000_svc(readdir_IDL *, struct svc_req *);
#define HELLOTEST 9
extern  void * hellotest_1000(void *, CLIENT *);
extern  void * hellotest_1000_svc(void *, struct svc_req *);
#define ACCESS 10
extern  int * access_1000(access_IDL *, CLIENT *);
extern  int * access_1000_svc(access_IDL *, struct svc_req *);
#define RELEASEDIR 11
extern  int * releasedir_1000(releasedir_IDL *, CLIENT *);
extern  int * releasedir_1000_svc(releasedir_IDL *, struct svc_req *);
#define RELEASE 12
extern  int * release_1000(release_IDL *, CLIENT *);
extern  int * release_1000_svc(release_IDL *, struct svc_req *);
#define FGETATTR 13
extern  struct fgetattr_ret_IDL * fgetattr_1000(fgetattr_IDL *, CLIENT *);
extern  struct fgetattr_ret_IDL * fgetattr_1000_svc(fgetattr_IDL *, struct svc_req *);
#define MKNOD 14
extern  int * mknod_1000(mknod_IDL *, CLIENT *);
extern  int * mknod_1000_svc(mknod_IDL *, struct svc_req *);
extern int nfs_fuse_1000_freeresult (SVCXPRT *, xdrproc_t, caddr_t);

#else /* K&R C */
#define GETATTR 1
extern  struct getattr_IDL * getattr_1000();
extern  struct getattr_IDL * getattr_1000_svc();
#define MKDIR 2
extern  int * mkdir_1000();
extern  int * mkdir_1000_svc();
#define RMDIR 3
extern  int * rmdir_1000();
extern  int * rmdir_1000_svc();
#define OPEN 4
extern  int * open_1000();
extern  int * open_1000_svc();
#define READ 5
extern  struct read_ret_IDL * read_1000();
extern  struct read_ret_IDL * read_1000_svc();
#define WRITE 6
extern  struct write_IDL * write_1000();
extern  struct write_IDL * write_1000_svc();
#define OPENDIR 7
extern  struct opendir_ret_IDL * opendir_1000();
extern  struct opendir_ret_IDL * opendir_1000_svc();
#define READDIR 8
extern  struct readdir_ret_IDL * readdir_1000();
extern  struct readdir_ret_IDL * readdir_1000_svc();
#define HELLOTEST 9
extern  void * hellotest_1000();
extern  void * hellotest_1000_svc();
#define ACCESS 10
extern  int * access_1000();
extern  int * access_1000_svc();
#define RELEASEDIR 11
extern  int * releasedir_1000();
extern  int * releasedir_1000_svc();
#define RELEASE 12
extern  int * release_1000();
extern  int * release_1000_svc();
#define FGETATTR 13
extern  struct fgetattr_ret_IDL * fgetattr_1000();
extern  struct fgetattr_ret_IDL * fgetattr_1000_svc();
#define MKNOD 14
extern  int * mknod_1000();
extern  int * mknod_1000_svc();
extern int nfs_fuse_1000_freeresult ();
#endif /* K&R C */

/* the xdr functions */

#if defined(__STDC__) || defined(__cplusplus)
extern  bool_t xdr_timespec_IDL (XDR *, timespec_IDL*);
extern  bool_t xdr_stat_IDL (XDR *, stat_IDL*);
extern  bool_t xdr_fuse_file_info_IDL (XDR *, fuse_file_info_IDL*);
extern  bool_t xdr_getattr_IDL (XDR *, getattr_IDL*);
extern  bool_t xdr_fgetattr_IDL (XDR *, fgetattr_IDL*);
extern  bool_t xdr_fgetattr_ret_IDL (XDR *, fgetattr_ret_IDL*);
extern  bool_t xdr_mkdir_IDL (XDR *, mkdir_IDL*);
extern  bool_t xdr_rmdir_IDL (XDR *, rmdir_IDL*);
extern  bool_t xdr_open_IDL (XDR *, open_IDL*);
extern  bool_t xdr_read_IDL (XDR *, read_IDL*);
extern  bool_t xdr_read_ret_IDL (XDR *, read_ret_IDL*);
extern  bool_t xdr_write_IDL (XDR *, write_IDL*);
extern  bool_t xdr_write_ret_IDL (XDR *, write_ret_IDL*);
extern  bool_t xdr_opendir_IDL (XDR *, opendir_IDL*);
extern  bool_t xdr_opendir_ret_IDL (XDR *, opendir_ret_IDL*);
extern  bool_t xdr_readdir_IDL (XDR *, readdir_IDL*);
extern  bool_t xdr_readdir_ret_IDL (XDR *, readdir_ret_IDL*);
extern  bool_t xdr_access_IDL (XDR *, access_IDL*);
extern  bool_t xdr_releasedir_IDL (XDR *, releasedir_IDL*);
extern  bool_t xdr_release_IDL (XDR *, release_IDL*);
extern  bool_t xdr_mknod_IDL (XDR *, mknod_IDL*);

#else /* K&R C */
extern bool_t xdr_timespec_IDL ();
extern bool_t xdr_stat_IDL ();
extern bool_t xdr_fuse_file_info_IDL ();
extern bool_t xdr_getattr_IDL ();
extern bool_t xdr_fgetattr_IDL ();
extern bool_t xdr_fgetattr_ret_IDL ();
extern bool_t xdr_mkdir_IDL ();
extern bool_t xdr_rmdir_IDL ();
extern bool_t xdr_open_IDL ();
extern bool_t xdr_read_IDL ();
extern bool_t xdr_read_ret_IDL ();
extern bool_t xdr_write_IDL ();
extern bool_t xdr_write_ret_IDL ();
extern bool_t xdr_opendir_IDL ();
extern bool_t xdr_opendir_ret_IDL ();
extern bool_t xdr_readdir_IDL ();
extern bool_t xdr_readdir_ret_IDL ();
extern bool_t xdr_access_IDL ();
extern bool_t xdr_releasedir_IDL ();
extern bool_t xdr_release_IDL ();
extern bool_t xdr_mknod_IDL ();

#endif /* K&R C */

#ifdef __cplusplus
}
#endif

#endif /* !_IDL_H_RPCGEN */
