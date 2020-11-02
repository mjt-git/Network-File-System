/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include "IDL.h"
#include <stdio.h>
#include <stdlib.h>
#include <rpc/pmap_clnt.h>
#include <string.h>
#include <memory.h>
#include <sys/socket.h>
#include <netinet/in.h>

#ifndef SIG_PF
#define SIG_PF void(*)(int)
#endif

static void
nfs_fuse_1000(struct svc_req *rqstp, register SVCXPRT *transp)
{
	union {
		struct getattr_IDL getattr_1000_arg;
		mkdir_IDL mkdir_1000_arg;
		rmdir_IDL rmdir_1000_arg;
		open_IDL open_1000_arg;
		read_IDL read_1000_arg;
		write_IDL write_1000_arg;
		opendir_IDL opendir_1000_arg;
		readdir_IDL readdir_1000_arg;
		access_IDL access_1000_arg;
		releasedir_IDL releasedir_1000_arg;
		release_IDL release_1000_arg;
		fgetattr_IDL fgetattr_1000_arg;
		mknod_IDL mknod_1000_arg;
		truncate_IDL truncate_1000_arg;
		unlink_IDL unlink_1000_arg;
		utime_IDL utime_1000_arg;
		rename_IDL rename_1000_arg;
		chmod_IDL chmod_1000_arg;
		chown_IDL chown_1000_arg;
	} argument;
	char *result;
	xdrproc_t _xdr_argument, _xdr_result;
	char *(*local)(char *, struct svc_req *);

	switch (rqstp->rq_proc) {
	case NULLPROC:
		(void) svc_sendreply (transp, (xdrproc_t) xdr_void, (char *)NULL);
		return;

	case GETATTR:
		_xdr_argument = (xdrproc_t) xdr_getattr_IDL;
		_xdr_result = (xdrproc_t) xdr_getattr_ret_IDL;
		local = (char *(*)(char *, struct svc_req *)) getattr_1000_svc;
		break;

	case MKDIR:
		_xdr_argument = (xdrproc_t) xdr_mkdir_IDL;
		_xdr_result = (xdrproc_t) xdr_int;
		local = (char *(*)(char *, struct svc_req *)) mkdir_1000_svc;
		break;

	case RMDIR:
		_xdr_argument = (xdrproc_t) xdr_rmdir_IDL;
		_xdr_result = (xdrproc_t) xdr_int;
		local = (char *(*)(char *, struct svc_req *)) rmdir_1000_svc;
		break;

	case OPEN:
		_xdr_argument = (xdrproc_t) xdr_open_IDL;
		_xdr_result = (xdrproc_t) xdr_int;
		local = (char *(*)(char *, struct svc_req *)) open_1000_svc;
		break;

	case READ:
		_xdr_argument = (xdrproc_t) xdr_read_IDL;
		_xdr_result = (xdrproc_t) xdr_read_ret_IDL;
		local = (char *(*)(char *, struct svc_req *)) read_1000_svc;
		break;

	case WRITE:
		_xdr_argument = (xdrproc_t) xdr_write_IDL;
		_xdr_result = (xdrproc_t) xdr_int;
		local = (char *(*)(char *, struct svc_req *)) write_1000_svc;
		break;

	case OPENDIR:
		_xdr_argument = (xdrproc_t) xdr_opendir_IDL;
		_xdr_result = (xdrproc_t) xdr_opendir_ret_IDL;
		local = (char *(*)(char *, struct svc_req *)) opendir_1000_svc;
		break;

	case READDIR:
		_xdr_argument = (xdrproc_t) xdr_readdir_IDL;
		_xdr_result = (xdrproc_t) xdr_readdir_ret_IDL;
		local = (char *(*)(char *, struct svc_req *)) readdir_1000_svc;
		break;

	case HELLOTEST:
		_xdr_argument = (xdrproc_t) xdr_void;
		_xdr_result = (xdrproc_t) xdr_void;
		local = (char *(*)(char *, struct svc_req *)) hellotest_1000_svc;
		break;

	case ACCESS:
		_xdr_argument = (xdrproc_t) xdr_access_IDL;
		_xdr_result = (xdrproc_t) xdr_int;
		local = (char *(*)(char *, struct svc_req *)) access_1000_svc;
		break;

	case RELEASEDIR:
		_xdr_argument = (xdrproc_t) xdr_releasedir_IDL;
		_xdr_result = (xdrproc_t) xdr_int;
		local = (char *(*)(char *, struct svc_req *)) releasedir_1000_svc;
		break;

	case RELEASE:
		_xdr_argument = (xdrproc_t) xdr_release_IDL;
		_xdr_result = (xdrproc_t) xdr_int;
		local = (char *(*)(char *, struct svc_req *)) release_1000_svc;
		break;

	case FGETATTR:
		_xdr_argument = (xdrproc_t) xdr_fgetattr_IDL;
		_xdr_result = (xdrproc_t) xdr_fgetattr_ret_IDL;
		local = (char *(*)(char *, struct svc_req *)) fgetattr_1000_svc;
		break;

	case MKNOD:
		_xdr_argument = (xdrproc_t) xdr_mknod_IDL;
		_xdr_result = (xdrproc_t) xdr_int;
		local = (char *(*)(char *, struct svc_req *)) mknod_1000_svc;
		break;

	case TRUNCATE:
		_xdr_argument = (xdrproc_t) xdr_truncate_IDL;
		_xdr_result = (xdrproc_t) xdr_int;
		local = (char *(*)(char *, struct svc_req *)) truncate_1000_svc;
		break;

	case UNLINK:
		_xdr_argument = (xdrproc_t) xdr_unlink_IDL;
		_xdr_result = (xdrproc_t) xdr_int;
		local = (char *(*)(char *, struct svc_req *)) unlink_1000_svc;
		break;

	case UTIME:
		_xdr_argument = (xdrproc_t) xdr_utime_IDL;
		_xdr_result = (xdrproc_t) xdr_utime_ret_IDL;
		local = (char *(*)(char *, struct svc_req *)) utime_1000_svc;
		break;

	case RENAME:
		_xdr_argument = (xdrproc_t) xdr_rename_IDL;
		_xdr_result = (xdrproc_t) xdr_int;
		local = (char *(*)(char *, struct svc_req *)) rename_1000_svc;
		break;

	case CHMOD:
		_xdr_argument = (xdrproc_t) xdr_chmod_IDL;
		_xdr_result = (xdrproc_t) xdr_int;
		local = (char *(*)(char *, struct svc_req *)) chmod_1000_svc;
		break;

	case CHOWN:
		_xdr_argument = (xdrproc_t) xdr_chown_IDL;
		_xdr_result = (xdrproc_t) xdr_int;
		local = (char *(*)(char *, struct svc_req *)) chown_1000_svc;
		break;

	default:
		svcerr_noproc (transp);
		return;
	}
	memset ((char *)&argument, 0, sizeof (argument));
	if (!svc_getargs (transp, (xdrproc_t) _xdr_argument, (caddr_t) &argument)) {
		svcerr_decode (transp);
		return;
	}
	result = (*local)((char *)&argument, rqstp);
	if (result != NULL && !svc_sendreply(transp, (xdrproc_t) _xdr_result, result)) {
		svcerr_systemerr (transp);
	}
	if (!svc_freeargs (transp, (xdrproc_t) _xdr_argument, (caddr_t) &argument)) {
		fprintf (stderr, "%s", "unable to free arguments");
		exit (1);
	}
	return;
}

int
main (int argc, char **argv)
{
	register SVCXPRT *transp;

	pmap_unset (NFS_FUSE, NFS_FUSE_VERS);

	transp = svcudp_create(RPC_ANYSOCK);
	if (transp == NULL) {
		fprintf (stderr, "%s", "cannot create udp service.");
		exit(1);
	}
	if (!svc_register(transp, NFS_FUSE, NFS_FUSE_VERS, nfs_fuse_1000, IPPROTO_UDP)) {
		fprintf (stderr, "%s", "unable to register (NFS_FUSE, NFS_FUSE_VERS, udp).");
		exit(1);
	}

	transp = svctcp_create(RPC_ANYSOCK, 0, 0);
	if (transp == NULL) {
		fprintf (stderr, "%s", "cannot create tcp service.");
		exit(1);
	}
	if (!svc_register(transp, NFS_FUSE, NFS_FUSE_VERS, nfs_fuse_1000, IPPROTO_TCP)) {
		fprintf (stderr, "%s", "unable to register (NFS_FUSE, NFS_FUSE_VERS, tcp).");
		exit(1);
	}

	svc_run ();
	fprintf (stderr, "%s", "svc_run returned");
	exit (1);
	/* NOTREACHED */
}
