/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include "IDL.h"

bool_t
xdr_timespec_IDL (XDR *xdrs, timespec_IDL *objp)
{
	register int32_t *buf;

	 if (!xdr_long (xdrs, &objp->tv_sec))
		 return FALSE;
	 if (!xdr_long (xdrs, &objp->tv_nsec))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_stat_IDL (XDR *xdrs, stat_IDL *objp)
{
	register int32_t *buf;

	 if (!xdr_uint32_t (xdrs, &objp->st_dev))
		 return FALSE;
	 if (!xdr_uint32_t (xdrs, &objp->st_ino))
		 return FALSE;
	 if (!xdr_long (xdrs, &objp->st_mode))
		 return FALSE;
	 if (!xdr_uint32_t (xdrs, &objp->st_nlink))
		 return FALSE;
	 if (!xdr_uint32_t (xdrs, &objp->st_uid))
		 return FALSE;
	 if (!xdr_uint32_t (xdrs, &objp->st_gid))
		 return FALSE;
	 if (!xdr_uint32_t (xdrs, &objp->st_rdev))
		 return FALSE;
	 if (!xdr_uint32_t (xdrs, &objp->st_size))
		 return FALSE;
	 if (!xdr_uint32_t (xdrs, &objp->st_blksize))
		 return FALSE;
	 if (!xdr_uint32_t (xdrs, &objp->st_blocks))
		 return FALSE;
	 if (!xdr_timespec_IDL (xdrs, &objp->st_atim))
		 return FALSE;
	 if (!xdr_timespec_IDL (xdrs, &objp->st_mtim))
		 return FALSE;
	 if (!xdr_timespec_IDL (xdrs, &objp->st_ctim))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_fuse_file_info_IDL (XDR *xdrs, fuse_file_info_IDL *objp)
{
	register int32_t *buf;


	if (xdrs->x_op == XDR_ENCODE) {
		buf = XDR_INLINE (xdrs, 8 * BYTES_PER_XDR_UNIT);
		if (buf == NULL) {
			 if (!xdr_int (xdrs, &objp->flags))
				 return FALSE;
			 if (!xdr_u_int (xdrs, &objp->writepage))
				 return FALSE;
			 if (!xdr_u_int (xdrs, &objp->direct_io))
				 return FALSE;
			 if (!xdr_u_int (xdrs, &objp->keep_cache))
				 return FALSE;
			 if (!xdr_u_int (xdrs, &objp->flush))
				 return FALSE;
			 if (!xdr_u_int (xdrs, &objp->nonseekable))
				 return FALSE;
			 if (!xdr_u_int (xdrs, &objp->cache_readdir))
				 return FALSE;
			 if (!xdr_u_int (xdrs, &objp->padding))
				 return FALSE;

		} else {
		IXDR_PUT_LONG(buf, objp->flags);
		IXDR_PUT_U_LONG(buf, objp->writepage);
		IXDR_PUT_U_LONG(buf, objp->direct_io);
		IXDR_PUT_U_LONG(buf, objp->keep_cache);
		IXDR_PUT_U_LONG(buf, objp->flush);
		IXDR_PUT_U_LONG(buf, objp->nonseekable);
		IXDR_PUT_U_LONG(buf, objp->cache_readdir);
		IXDR_PUT_U_LONG(buf, objp->padding);
		}
		 if (!xdr_uint64_t (xdrs, &objp->fh))
			 return FALSE;
		 if (!xdr_uint64_t (xdrs, &objp->lock_owner))
			 return FALSE;
		 if (!xdr_uint32_t (xdrs, &objp->poll_events))
			 return FALSE;
		return TRUE;
	} else if (xdrs->x_op == XDR_DECODE) {
		buf = XDR_INLINE (xdrs, 8 * BYTES_PER_XDR_UNIT);
		if (buf == NULL) {
			 if (!xdr_int (xdrs, &objp->flags))
				 return FALSE;
			 if (!xdr_u_int (xdrs, &objp->writepage))
				 return FALSE;
			 if (!xdr_u_int (xdrs, &objp->direct_io))
				 return FALSE;
			 if (!xdr_u_int (xdrs, &objp->keep_cache))
				 return FALSE;
			 if (!xdr_u_int (xdrs, &objp->flush))
				 return FALSE;
			 if (!xdr_u_int (xdrs, &objp->nonseekable))
				 return FALSE;
			 if (!xdr_u_int (xdrs, &objp->cache_readdir))
				 return FALSE;
			 if (!xdr_u_int (xdrs, &objp->padding))
				 return FALSE;

		} else {
		objp->flags = IXDR_GET_LONG(buf);
		objp->writepage = IXDR_GET_U_LONG(buf);
		objp->direct_io = IXDR_GET_U_LONG(buf);
		objp->keep_cache = IXDR_GET_U_LONG(buf);
		objp->flush = IXDR_GET_U_LONG(buf);
		objp->nonseekable = IXDR_GET_U_LONG(buf);
		objp->cache_readdir = IXDR_GET_U_LONG(buf);
		objp->padding = IXDR_GET_U_LONG(buf);
		}
		 if (!xdr_uint64_t (xdrs, &objp->fh))
			 return FALSE;
		 if (!xdr_uint64_t (xdrs, &objp->lock_owner))
			 return FALSE;
		 if (!xdr_uint32_t (xdrs, &objp->poll_events))
			 return FALSE;
	 return TRUE;
	}

	 if (!xdr_int (xdrs, &objp->flags))
		 return FALSE;
	 if (!xdr_u_int (xdrs, &objp->writepage))
		 return FALSE;
	 if (!xdr_u_int (xdrs, &objp->direct_io))
		 return FALSE;
	 if (!xdr_u_int (xdrs, &objp->keep_cache))
		 return FALSE;
	 if (!xdr_u_int (xdrs, &objp->flush))
		 return FALSE;
	 if (!xdr_u_int (xdrs, &objp->nonseekable))
		 return FALSE;
	 if (!xdr_u_int (xdrs, &objp->cache_readdir))
		 return FALSE;
	 if (!xdr_u_int (xdrs, &objp->padding))
		 return FALSE;
	 if (!xdr_uint64_t (xdrs, &objp->fh))
		 return FALSE;
	 if (!xdr_uint64_t (xdrs, &objp->lock_owner))
		 return FALSE;
	 if (!xdr_uint32_t (xdrs, &objp->poll_events))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_getattr_IDL (XDR *xdrs, getattr_IDL *objp)
{
	register int32_t *buf;

	 if (!xdr_string (xdrs, &objp->path, PATH_MAX))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_getattr_ret_IDL (XDR *xdrs, getattr_ret_IDL *objp)
{
	register int32_t *buf;

	 if (!xdr_int (xdrs, &objp->res))
		 return FALSE;
	 if (!xdr_uint32_t (xdrs, &objp->st_dev))
		 return FALSE;
	 if (!xdr_uint32_t (xdrs, &objp->st_ino))
		 return FALSE;
	 if (!xdr_long (xdrs, &objp->st_mode))
		 return FALSE;
	 if (!xdr_uint32_t (xdrs, &objp->st_nlink))
		 return FALSE;
	 if (!xdr_uint32_t (xdrs, &objp->st_uid))
		 return FALSE;
	 if (!xdr_uint32_t (xdrs, &objp->st_gid))
		 return FALSE;
	 if (!xdr_uint32_t (xdrs, &objp->st_rdev))
		 return FALSE;
	 if (!xdr_uint32_t (xdrs, &objp->st_size))
		 return FALSE;
	 if (!xdr_uint32_t (xdrs, &objp->st_blksize))
		 return FALSE;
	 if (!xdr_uint32_t (xdrs, &objp->st_blocks))
		 return FALSE;
	 if (!xdr_uint32_t (xdrs, &objp->st_atim))
		 return FALSE;
	 if (!xdr_uint32_t (xdrs, &objp->st_mtim))
		 return FALSE;
	 if (!xdr_uint32_t (xdrs, &objp->st_ctim))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_fgetattr_IDL (XDR *xdrs, fgetattr_IDL *objp)
{
	register int32_t *buf;

	 if (!xdr_int (xdrs, &objp->fh))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_fgetattr_ret_IDL (XDR *xdrs, fgetattr_ret_IDL *objp)
{
	register int32_t *buf;

	 if (!xdr_int (xdrs, &objp->res))
		 return FALSE;
	 if (!xdr_uint32_t (xdrs, &objp->st_dev))
		 return FALSE;
	 if (!xdr_uint32_t (xdrs, &objp->st_ino))
		 return FALSE;
	 if (!xdr_long (xdrs, &objp->st_mode))
		 return FALSE;
	 if (!xdr_uint32_t (xdrs, &objp->st_nlink))
		 return FALSE;
	 if (!xdr_uint32_t (xdrs, &objp->st_uid))
		 return FALSE;
	 if (!xdr_uint32_t (xdrs, &objp->st_gid))
		 return FALSE;
	 if (!xdr_uint32_t (xdrs, &objp->st_rdev))
		 return FALSE;
	 if (!xdr_uint32_t (xdrs, &objp->st_size))
		 return FALSE;
	 if (!xdr_uint32_t (xdrs, &objp->st_blksize))
		 return FALSE;
	 if (!xdr_uint32_t (xdrs, &objp->st_blocks))
		 return FALSE;
	 if (!xdr_uint32_t (xdrs, &objp->st_atim))
		 return FALSE;
	 if (!xdr_uint32_t (xdrs, &objp->st_mtim))
		 return FALSE;
	 if (!xdr_uint32_t (xdrs, &objp->st_ctim))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_mkdir_IDL (XDR *xdrs, mkdir_IDL *objp)
{
	register int32_t *buf;

	 if (!xdr_string (xdrs, &objp->path, PATH_MAX))
		 return FALSE;
	 if (!xdr_uint32_t (xdrs, &objp->mode))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_rmdir_IDL (XDR *xdrs, rmdir_IDL *objp)
{
	register int32_t *buf;

	 if (!xdr_string (xdrs, &objp->path, PATH_MAX))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_open_IDL (XDR *xdrs, open_IDL *objp)
{
	register int32_t *buf;

	 if (!xdr_string (xdrs, &objp->path, PATH_MAX))
		 return FALSE;
	 if (!xdr_uint32_t (xdrs, &objp->flags))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_read_IDL (XDR *xdrs, read_IDL *objp)
{
	register int32_t *buf;

	 if (!xdr_uint32_t (xdrs, &objp->size))
		 return FALSE;
	 if (!xdr_uint32_t (xdrs, &objp->offset))
		 return FALSE;
	 if (!xdr_int (xdrs, &objp->fh))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_read_ret_IDL (XDR *xdrs, read_ret_IDL *objp)
{
	register int32_t *buf;

	int i;
	 if (!xdr_int (xdrs, &objp->count))
		 return FALSE;
	 if (!xdr_opaque (xdrs, objp->buf, 4096))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_write_IDL (XDR *xdrs, write_IDL *objp)
{
	register int32_t *buf;

	int i;
	 if (!xdr_opaque (xdrs, objp->buf, 4096))
		 return FALSE;
	 if (!xdr_uint32_t (xdrs, &objp->size))
		 return FALSE;
	 if (!xdr_uint32_t (xdrs, &objp->offset))
		 return FALSE;
	 if (!xdr_uint32_t (xdrs, &objp->fh))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_write_ret_IDL (XDR *xdrs, write_ret_IDL *objp)
{
	register int32_t *buf;

	 if (!xdr_int (xdrs, &objp->res))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_opendir_IDL (XDR *xdrs, opendir_IDL *objp)
{
	register int32_t *buf;

	 if (!xdr_string (xdrs, &objp->path, PATH_MAX))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_opendir_ret_IDL (XDR *xdrs, opendir_ret_IDL *objp)
{
	register int32_t *buf;

	 if (!xdr_int (xdrs, &objp->res))
		 return FALSE;
	 if (!xdr_int (xdrs, &objp->isvalid))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_readdir_IDL (XDR *xdrs, readdir_IDL *objp)
{
	register int32_t *buf;

	 if (!xdr_uint64_t (xdrs, &objp->fh))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_readdir_ret_IDL (XDR *xdrs, readdir_ret_IDL *objp)
{
	register int32_t *buf;

	int i;
	 if (!xdr_int (xdrs, &objp->res))
		 return FALSE;
	 if (!xdr_opaque (xdrs, objp->buf, 1024))
		 return FALSE;
	 if (!xdr_int (xdrs, &objp->length))
		 return FALSE;
	 if (!xdr_int (xdrs, &objp->count))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_access_IDL (XDR *xdrs, access_IDL *objp)
{
	register int32_t *buf;

	 if (!xdr_string (xdrs, &objp->path, PATH_MAX))
		 return FALSE;
	 if (!xdr_int (xdrs, &objp->mask))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_releasedir_IDL (XDR *xdrs, releasedir_IDL *objp)
{
	register int32_t *buf;

	 if (!xdr_int (xdrs, &objp->fh))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_release_IDL (XDR *xdrs, release_IDL *objp)
{
	register int32_t *buf;

	 if (!xdr_int (xdrs, &objp->fh))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_mknod_IDL (XDR *xdrs, mknod_IDL *objp)
{
	register int32_t *buf;

	 if (!xdr_string (xdrs, &objp->path, PATH_MAX))
		 return FALSE;
	 if (!xdr_int (xdrs, &objp->mode))
		 return FALSE;
	 if (!xdr_int (xdrs, &objp->dev))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_truncate_IDL (XDR *xdrs, truncate_IDL *objp)
{
	register int32_t *buf;

	 if (!xdr_string (xdrs, &objp->path, PATH_MAX))
		 return FALSE;
	 if (!xdr_int (xdrs, &objp->newsize))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_ftruncate_IDL (XDR *xdrs, ftruncate_IDL *objp)
{
	register int32_t *buf;

	 if (!xdr_int (xdrs, &objp->fh))
		 return FALSE;
	 if (!xdr_int (xdrs, &objp->newsize))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_unlink_IDL (XDR *xdrs, unlink_IDL *objp)
{
	register int32_t *buf;

	 if (!xdr_string (xdrs, &objp->path, PATH_MAX))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_utime_IDL (XDR *xdrs, utime_IDL *objp)
{
	register int32_t *buf;

	 if (!xdr_string (xdrs, &objp->path, PATH_MAX))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_utime_ret_IDL (XDR *xdrs, utime_ret_IDL *objp)
{
	register int32_t *buf;

	 if (!xdr_uint32_t (xdrs, &objp->actime))
		 return FALSE;
	 if (!xdr_uint32_t (xdrs, &objp->modtime))
		 return FALSE;
	 if (!xdr_int (xdrs, &objp->res))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_rename_IDL (XDR *xdrs, rename_IDL *objp)
{
	register int32_t *buf;

	 if (!xdr_string (xdrs, &objp->path, PATH_MAX))
		 return FALSE;
	 if (!xdr_string (xdrs, &objp->newpath, PATH_MAX))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_chmod_IDL (XDR *xdrs, chmod_IDL *objp)
{
	register int32_t *buf;

	 if (!xdr_string (xdrs, &objp->path, PATH_MAX))
		 return FALSE;
	 if (!xdr_uint32_t (xdrs, &objp->mode))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_chown_IDL (XDR *xdrs, chown_IDL *objp)
{
	register int32_t *buf;

	 if (!xdr_string (xdrs, &objp->path, PATH_MAX))
		 return FALSE;
	 if (!xdr_uint32_t (xdrs, &objp->uid))
		 return FALSE;
	 if (!xdr_uint32_t (xdrs, &objp->gid))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_authenticate_IDL (XDR *xdrs, authenticate_IDL *objp)
{
	register int32_t *buf;

	 if (!xdr_uint32_t (xdrs, &objp->hash))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_fdatasync_IDL (XDR *xdrs, fdatasync_IDL *objp)
{
	register int32_t *buf;

	 if (!xdr_int (xdrs, &objp->fh))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_fsync_IDL (XDR *xdrs, fsync_IDL *objp)
{
	register int32_t *buf;

	 if (!xdr_int (xdrs, &objp->fh))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_hello_IDL (XDR *xdrs, hello_IDL *objp)
{
	register int32_t *buf;

	 if (!xdr_string (xdrs, &objp->path, PATH_MAX))
		 return FALSE;
	return TRUE;
}
