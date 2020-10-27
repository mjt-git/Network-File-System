

struct timespec_IDL{
       long tv_sec;
       long tv_nsec;
};

struct stat_IDL{
	       uint32_t     st_dev;         /* ID of device containing file */
         uint32_t     st_ino;         /* Inode number */
         long         st_mode;        /* File type and mode */
         uint32_t     st_nlink;       /* Number of hard links */
         uint32_t     st_uid;         /* User ID of owner */
         uint32_t     st_gid;         /* Group ID of owner */
         uint32_t     st_rdev;        /* Device ID (if special file) */
         uint32_t     st_size;        /* Total size, in bytes */
         uint32_t     st_blksize;     /* Block size for filesystem I/O */
         uint32_t     st_blocks;      /* Number of 512B blocks allocated */

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
      int res;   

      string path<PATH_MAX>;

      uint32_t     st_dev;         /* ID of device containing file */
      uint32_t     st_ino;         /* Inode number */
      long        st_mode;        /* File type and mode */
      uint32_t   st_nlink;       /* Number of hard links */
      uint32_t     st_uid;         /* User ID of owner */
      uint32_t     st_gid;         /* Group ID of owner */
      uint32_t    st_rdev;        /* Device ID (if special file) */
      uint32_t    st_size;        /* Total size, in bytes */
      uint32_t st_blksize;     /* Block size for filesystem I/O */
      uint32_t  st_blocks;      /* Number of 512B blocks allocated */

      uint32_t st_atim;  /* Time of last access */
      uint32_t st_mtim;  /* Time of last modification */
      uint32_t st_ctim;
};

struct fgetattr_IDL {
  int fh;
};

struct fgetattr_ret_IDL {
  int res;
  uint32_t     st_dev;         /* ID of device containing file */
  uint32_t     st_ino;         /* Inode number */
  long        st_mode;        /* File type and mode */
  uint32_t   st_nlink;       /* Number of hard links */
  uint32_t     st_uid;         /* User ID of owner */
  uint32_t     st_gid;         /* Group ID of owner */
  uint32_t    st_rdev;        /* Device ID (if special file) */
  uint32_t    st_size;        /* Total size, in bytes */
  uint32_t st_blksize;     /* Block size for filesystem I/O */
  uint32_t  st_blocks;      /* Number of 512B blocks allocated */

  uint32_t st_atim;  /* Time of last access */
  uint32_t st_mtim;  /* Time of last modification */
  uint32_t st_ctim;
};

struct mkdir_IDL{
       string path<PATH_MAX>;
       uint32_t mode;
};

struct rmdir_IDL{
       string path<PATH_MAX>;
};

struct open_IDL{
       string path<PATH_MAX>;
       uint32_t flags;
};

struct read_IDL{
       uint32_t size;
       uint32_t offset;
       int fh;
};

struct read_ret_IDL {
  int count;
  opaque buf[4096];
};

struct write_IDL{
       string path<PATH_MAX>;
       opaque buf[4096];
       uint32_t size;
       uint32_t offset;
       uint32_t fh;
};

struct write_ret_IDL{
       int res;
};

struct opendir_IDL{
       string path<PATH_MAX>;
};

struct opendir_ret_IDL{
  int res;
  int isvalid;
};

struct readdir_IDL{
  uint64_t  fh;
};

struct readdir_ret_IDL{
       int res;
       opaque buf[1024];
       int length;
       int count;
};

struct access_IDL{
  string path<PATH_MAX>;
  int mask;
};

struct releasedir_IDL {
  int fh;
};

struct release_IDL {
  int fh;  
};

struct mknod_IDL {
  string path<PATH_MAX>;
  int mode;
  int dev;
};

program NFS_FUSE{
	version NFS_FUSE_VERS{
		struct getattr_IDL GETATTR(struct getattr_IDL)=1;
		int MKDIR(mkdir_IDL)=2;
		int RMDIR(rmdir_IDL)=3;     
  	int OPEN(open_IDL)=4;
		struct read_ret_IDL READ(read_IDL)=5;     
  	struct write_IDL WRITE(write_IDL)=6;
    struct opendir_ret_IDL OPENDIR(opendir_IDL)=7;
    struct readdir_ret_IDL READDIR(readdir_IDL)=8;
		void HELLOTEST()=9;
    int ACCESS(access_IDL)=10;
    int RELEASEDIR(releasedir_IDL)=11;
    int RELEASE(release_IDL)=12;
    struct fgetattr_ret_IDL FGETATTR(fgetattr_IDL)=13;
    int MKNOD(mknod_IDL)=14;
	} = 1000;
} = 123789456;
