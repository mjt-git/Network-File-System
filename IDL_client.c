/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "IDL.h"


void
nfs_fuse_9(char *host)
{
	CLIENT *clnt;
	int  *result_1;
	getattr_IDL  getattr_9_arg;
	int  *result_2;
	mkdir_IDL  mkdir_9_arg;
	int  *result_3;
	rmdir_IDL  rmdir_9_arg;
	int  *result_4;
	open_IDL  open_9_arg;
	int  *result_5;
	read_IDL  read_9_arg;
	int  *result_6;
	write_IDL  write_9_arg;
	int  *result_7;
	opendir_IDL  opendir_9_arg;
	int  *result_8;
	readdir_IDL  readdir_9_arg;

#ifndef	DEBUG
	clnt = clnt_create (host, NFS_FUSE, NFS_FUSE_VERS, "udp");
	if (clnt == NULL) {
		clnt_pcreateerror (host);
		exit (1);
	}
#endif	/* DEBUG */

	result_1 = getattr_9(&getattr_9_arg, clnt);
	if (result_1 == (int *) NULL) {
		clnt_perror (clnt, "call failed");
	}
	result_2 = mkdir_9(&mkdir_9_arg, clnt);
	if (result_2 == (int *) NULL) {
		clnt_perror (clnt, "call failed");
	}
	result_3 = rmdir_9(&rmdir_9_arg, clnt);
	if (result_3 == (int *) NULL) {
		clnt_perror (clnt, "call failed");
	}
	result_4 = open_9(&open_9_arg, clnt);
	if (result_4 == (int *) NULL) {
		clnt_perror (clnt, "call failed");
	}
	result_5 = read_9(&read_9_arg, clnt);
	if (result_5 == (int *) NULL) {
		clnt_perror (clnt, "call failed");
	}
	result_6 = write_9(&write_9_arg, clnt);
	if (result_6 == (int *) NULL) {
		clnt_perror (clnt, "call failed");
	}
	result_7 = opendir_9(&opendir_9_arg, clnt);
	if (result_7 == (int *) NULL) {
		clnt_perror (clnt, "call failed");
	}
	result_8 = readdir_9(&readdir_9_arg, clnt);
	if (result_8 == (int *) NULL) {
		clnt_perror (clnt, "call failed");
	}
#ifndef	DEBUG
	clnt_destroy (clnt);
#endif	 /* DEBUG */
}


int
main (int argc, char *argv[])
{
	char *host;

	if (argc < 2) {
		printf ("usage: %s server_host\n", argv[0]);
		exit (1);
	}
	host = argv[1];
	nfs_fuse_9 (host);
exit (0);
}
