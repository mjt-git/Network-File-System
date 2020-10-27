/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include <memory.h> /* for memset */
#include "IDL.h"

/* Default timeout can be changed using clnt_control() */
static struct timeval TIMEOUT = { 25, 0 };

struct getattr_IDL *
getattr_1000(struct getattr_IDL *argp, CLIENT *clnt)
{
	static struct getattr_IDL clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (clnt_call (clnt, GETATTR,
		(xdrproc_t) xdr_getattr_IDL, (caddr_t) argp,
		(xdrproc_t) xdr_getattr_IDL, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}

int *
mkdir_1000(mkdir_IDL *argp, CLIENT *clnt)
{
	static int clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (clnt_call (clnt, MKDIR,
		(xdrproc_t) xdr_mkdir_IDL, (caddr_t) argp,
		(xdrproc_t) xdr_int, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}

int *
rmdir_1000(rmdir_IDL *argp, CLIENT *clnt)
{
	static int clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (clnt_call (clnt, RMDIR,
		(xdrproc_t) xdr_rmdir_IDL, (caddr_t) argp,
		(xdrproc_t) xdr_int, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}

int *
open_1000(open_IDL *argp, CLIENT *clnt)
{
	static int clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (clnt_call (clnt, OPEN,
		(xdrproc_t) xdr_open_IDL, (caddr_t) argp,
		(xdrproc_t) xdr_int, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}

struct read_ret_IDL *
read_1000(read_IDL *argp, CLIENT *clnt)
{
	static struct read_ret_IDL clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (clnt_call (clnt, READ,
		(xdrproc_t) xdr_read_IDL, (caddr_t) argp,
		(xdrproc_t) xdr_read_ret_IDL, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}

struct write_IDL *
write_1000(write_IDL *argp, CLIENT *clnt)
{
	static struct write_IDL clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (clnt_call (clnt, WRITE,
		(xdrproc_t) xdr_write_IDL, (caddr_t) argp,
		(xdrproc_t) xdr_write_IDL, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}

struct opendir_ret_IDL *
opendir_1000(opendir_IDL *argp, CLIENT *clnt)
{
	static struct opendir_ret_IDL clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (clnt_call (clnt, OPENDIR,
		(xdrproc_t) xdr_opendir_IDL, (caddr_t) argp,
		(xdrproc_t) xdr_opendir_ret_IDL, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}

struct readdir_ret_IDL *
readdir_1000(readdir_IDL *argp, CLIENT *clnt)
{
	static struct readdir_ret_IDL clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (clnt_call (clnt, READDIR,
		(xdrproc_t) xdr_readdir_IDL, (caddr_t) argp,
		(xdrproc_t) xdr_readdir_ret_IDL, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}

void *
hellotest_1000(void *argp, CLIENT *clnt)
{
	static char clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (clnt_call (clnt, HELLOTEST,
		(xdrproc_t) xdr_void, (caddr_t) argp,
		(xdrproc_t) xdr_void, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return ((void *)&clnt_res);
}

int *
access_1000(access_IDL *argp, CLIENT *clnt)
{
	static int clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (clnt_call (clnt, ACCESS,
		(xdrproc_t) xdr_access_IDL, (caddr_t) argp,
		(xdrproc_t) xdr_int, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}

int *
releasedir_1000(releasedir_IDL *argp, CLIENT *clnt)
{
	static int clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (clnt_call (clnt, RELEASEDIR,
		(xdrproc_t) xdr_releasedir_IDL, (caddr_t) argp,
		(xdrproc_t) xdr_int, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}

int *
release_1000(release_IDL *argp, CLIENT *clnt)
{
	static int clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (clnt_call (clnt, RELEASE,
		(xdrproc_t) xdr_release_IDL, (caddr_t) argp,
		(xdrproc_t) xdr_int, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}

struct fgetattr_ret_IDL *
fgetattr_1000(fgetattr_IDL *argp, CLIENT *clnt)
{
	static struct fgetattr_ret_IDL clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (clnt_call (clnt, FGETATTR,
		(xdrproc_t) xdr_fgetattr_IDL, (caddr_t) argp,
		(xdrproc_t) xdr_fgetattr_ret_IDL, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}

int *
mknod_1000(mknod_IDL *argp, CLIENT *clnt)
{
	static int clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (clnt_call (clnt, MKNOD,
		(xdrproc_t) xdr_mknod_IDL, (caddr_t) argp,
		(xdrproc_t) xdr_int, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}
