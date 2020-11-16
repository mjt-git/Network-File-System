#include <stdio.h>
#include <stdlib.h> 
#include <unistd.h>   

unsigned int BKDRHash(char *str)
{
    unsigned int seed = 131; // 31 131 1313 13131 131313 etc..
    unsigned int hash = 0;
 
    while (*str)
    {
        hash = hash * seed + (*str++);
    }
 
    return (hash & 0x7FFFFFFF);
}


int main() {
    FILE *fptr;
    if ((fptr = fopen("password", "w+")) == NULL) {
        printf("Error! cannot open the password file\n");
        exit(1);
    }
    printf("Please type in the password given by NFS server:\n");
    char * password;
    password = getpass("Enter Password: \n");
    unsigned int hashvalue = BKDRHash(password);
    printf("Sucessfully saved the hash value of the password to password file!\n");
    fprintf(fptr,"%d",hashvalue);
    fclose(fptr);
    return 0;
}