all : NFS_client NFS_server

NFS_client: IDL_clnt.c client.c IDL_xdr.c log.c
	gcc -o NFS_client $^ `pkg-config fuse --cflags --libs`

NFS_server: server.c IDL_svc.c IDL_xdr.c
	gcc -o NFS_server -lnsl $^ 

