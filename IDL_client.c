/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "IDL.h"


void
nfs_fuse_1000(char *host)
{
	CLIENT *clnt;
	struct getattr_ret_IDL  *result_1;
	struct getattr_IDL  getattr_1000_arg;
	int  *result_2;
	mkdir_IDL  mkdir_1000_arg;
	int  *result_3;
	rmdir_IDL  rmdir_1000_arg;
	int  *result_4;
	open_IDL  open_1000_arg;
	struct read_ret_IDL  *result_5;
	read_IDL  read_1000_arg;
	int  *result_6;
	write_IDL  write_1000_arg;
	struct opendir_ret_IDL  *result_7;
	opendir_IDL  opendir_1000_arg;
	struct readdir_ret_IDL  *result_8;
	readdir_IDL  readdir_1000_arg;
	void  *result_9;
	char *hellotest_1000_arg;
	int  *result_10;
	access_IDL  access_1000_arg;
	int  *result_11;
	releasedir_IDL  releasedir_1000_arg;
	int  *result_12;
	release_IDL  release_1000_arg;
	struct fgetattr_ret_IDL  *result_13;
	fgetattr_IDL  fgetattr_1000_arg;
	int  *result_14;
	mknod_IDL  mknod_1000_arg;
	int  *result_15;
	truncate_IDL  truncate_1000_arg;
	int  *result_16;
	unlink_IDL  unlink_1000_arg;
	struct utime_ret_IDL  *result_17;
	utime_IDL  utime_1000_arg;
	int  *result_18;
	rename_IDL  rename_1000_arg;
	int  *result_19;
	chmod_IDL  chmod_1000_arg;
	int  *result_20;
	chown_IDL  chown_1000_arg;
	int  *result_21;
	authenticate_IDL  authenticate_1000_arg;
	int  *result_22;
	ftruncate_IDL  ftruncate_1000_arg;
	int  *result_23;
	fdatasync_IDL  fdatasync_1000_arg;
	int  *result_24;
	fsync_IDL  fsync_1000_arg;

#ifndef	DEBUG
	clnt = clnt_create (host, NFS_FUSE, NFS_FUSE_VERS, "udp");
	if (clnt == NULL) {
		clnt_pcreateerror (host);
		exit (1);
	}
#endif	/* DEBUG */

	result_1 = getattr_1000(&getattr_1000_arg, clnt);
	if (result_1 == (struct getattr_ret_IDL *) NULL) {
		clnt_perror (clnt, "call failed");
	}
	result_2 = mkdir_1000(&mkdir_1000_arg, clnt);
	if (result_2 == (int *) NULL) {
		clnt_perror (clnt, "call failed");
	}
	result_3 = rmdir_1000(&rmdir_1000_arg, clnt);
	if (result_3 == (int *) NULL) {
		clnt_perror (clnt, "call failed");
	}
	result_4 = open_1000(&open_1000_arg, clnt);
	if (result_4 == (int *) NULL) {
		clnt_perror (clnt, "call failed");
	}
	result_5 = read_1000(&read_1000_arg, clnt);
	if (result_5 == (struct read_ret_IDL *) NULL) {
		clnt_perror (clnt, "call failed");
	}
	result_6 = write_1000(&write_1000_arg, clnt);
	if (result_6 == (int *) NULL) {
		clnt_perror (clnt, "call failed");
	}
	result_7 = opendir_1000(&opendir_1000_arg, clnt);
	if (result_7 == (struct opendir_ret_IDL *) NULL) {
		clnt_perror (clnt, "call failed");
	}
	result_8 = readdir_1000(&readdir_1000_arg, clnt);
	if (result_8 == (struct readdir_ret_IDL *) NULL) {
		clnt_perror (clnt, "call failed");
	}
	result_9 = hellotest_1000((void*)&hellotest_1000_arg, clnt);
	if (result_9 == (void *) NULL) {
		clnt_perror (clnt, "call failed");
	}
	result_10 = access_1000(&access_1000_arg, clnt);
	if (result_10 == (int *) NULL) {
		clnt_perror (clnt, "call failed");
	}
	result_11 = releasedir_1000(&releasedir_1000_arg, clnt);
	if (result_11 == (int *) NULL) {
		clnt_perror (clnt, "call failed");
	}
	result_12 = release_1000(&release_1000_arg, clnt);
	if (result_12 == (int *) NULL) {
		clnt_perror (clnt, "call failed");
	}
	result_13 = fgetattr_1000(&fgetattr_1000_arg, clnt);
	if (result_13 == (struct fgetattr_ret_IDL *) NULL) {
		clnt_perror (clnt, "call failed");
	}
	result_14 = mknod_1000(&mknod_1000_arg, clnt);
	if (result_14 == (int *) NULL) {
		clnt_perror (clnt, "call failed");
	}
	result_15 = truncate_1000(&truncate_1000_arg, clnt);
	if (result_15 == (int *) NULL) {
		clnt_perror (clnt, "call failed");
	}
	result_16 = unlink_1000(&unlink_1000_arg, clnt);
	if (result_16 == (int *) NULL) {
		clnt_perror (clnt, "call failed");
	}
	result_17 = utime_1000(&utime_1000_arg, clnt);
	if (result_17 == (struct utime_ret_IDL *) NULL) {
		clnt_perror (clnt, "call failed");
	}
	result_18 = rename_1000(&rename_1000_arg, clnt);
	if (result_18 == (int *) NULL) {
		clnt_perror (clnt, "call failed");
	}
	result_19 = chmod_1000(&chmod_1000_arg, clnt);
	if (result_19 == (int *) NULL) {
		clnt_perror (clnt, "call failed");
	}
	result_20 = chown_1000(&chown_1000_arg, clnt);
	if (result_20 == (int *) NULL) {
		clnt_perror (clnt, "call failed");
	}
	result_21 = authenticate_1000(&authenticate_1000_arg, clnt);
	if (result_21 == (int *) NULL) {
		clnt_perror (clnt, "call failed");
	}
	result_22 = ftruncate_1000(&ftruncate_1000_arg, clnt);
	if (result_22 == (int *) NULL) {
		clnt_perror (clnt, "call failed");
	}
	result_23 = fdatasync_1000(&fdatasync_1000_arg, clnt);
	if (result_23 == (int *) NULL) {
		clnt_perror (clnt, "call failed");
	}
	result_24 = fsync_1000(&fsync_1000_arg, clnt);
	if (result_24 == (int *) NULL) {
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
	nfs_fuse_1000 (host);
exit (0);
}
