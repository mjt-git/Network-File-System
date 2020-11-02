all : IDL_target NFS_client NFS_server

IDL_target: IDL.x
	rpcgen -a -C IDL.x

NFS_client: IDL_clnt.c cache.c client.c IDL_xdr.c log.c
	gcc -g3 -o NFS_client $^ `pkg-config fuse --cflags --libs`

NFS_server: server.c IDL_svc.c IDL_xdr.c file_record.c
	gcc -g3 -o NFS_server -lnsl $^ 

clean:
	rm NFS_client NFS_server IDL.h IDL_* Makefile.IDL
