

struct timespec_IDL{
       long tv_sec;
       long tv_nsec;
};

struct stat_IDL{
	       uint32_t     st_dev;         /* ID of device containing file */
               uint32_t     st_ino;         /* Inode number */
               uint32_t    st_mode;        /* File type and mode */
               uint32_t   st_nlink;       /* Number of hard links */
               uint32_t     st_uid;         /* User ID of owner */
               uint32_t     st_gid;         /* Group ID of owner */
               uint32_t     st_rdev;        /* Device ID (if special file) */
               uint32_t     st_size;        /* Total size, in bytes */
               uint32_t st_blksize;     /* Block size for filesystem I/O */
               uint32_t  st_blocks;      /* Number of 512B blocks allocated */

               /* Since Linux 2.6, the kernel supports nanosecond
                  precision for the following timestamp fields.
                  For the details before Linux 2.6, see NOTES. */

               struct timespec_IDL st_atim;  /* Time of last access */
               struct timespec_IDL st_mtim;  /* Time of last modification */
               struct timespec_IDL st_ctim;  /* Time of last status change */
           };


struct fuse_file_info_IDL{
       int flags;
       unsigned int writepage;
       unsigned	int direct_io;
       unsigned	int keep_cache;
       unsigned int flush;
       unsigned	int nonseekable;
       unsigned int cache_readdir;
       unsigned int padding;
       uint64_t fh;
       uint64_t lock_owner;
       uint32_t poll_events;
};

struct getattr_IDL{
       char *path;
       struct stat_IDL *statbuf;
};

struct mkdir_IDL{
       char *path;
       uint32_t mode;
};

struct rmdir_IDL{
       char *path;
};

struct open_IDL{
       char *path;
       struct fuse_file_info_IDL *fi;
};

struct read_IDL{
       char *path;
       char *buf;
       uint32_t size;
       uint32_t offset;
       struct fuse_file_info * fi;
};

struct write_IDL{
       char *path;
       char *buf;
       uint32_t size;
       uint32_t offset;
       struct fuse_file_info * fi;
};

struct opendir_IDL{
       char *path;
       struct fuse_file_info_IDL *fi;
};

struct readdir_IDL{
       char *path;
       char  *buf;
       uint32_t offset;
       struct fuse_file_info_IDL *fi;
};

program NFS_FUSE{
	version NFS_FUSE_VERS{
		int GETATTR(getattr_IDL)=1;
		int MKDIR(mkdir_IDL)=2;
		int RMDIR(rmdir_IDL)=3;     
        	int OPEN(open_IDL)=4;
		int READ(read_IDL)=5;     
        	int WRITE(write_IDL)=6;
                int OPENDIR(opendir_IDL)=7;
                int READDIR(readdir_IDL)=8;
	} = 9;
} = 123789456;
