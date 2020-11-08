#include <stdio.h>
#include <stdlib.h> 


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
    char password[128]={'\0'};
    scanf("%s",password);
    printf("plain_password is %s\n",password);
    unsigned int hashvalue = BKDRHash(password);
    printf("hash value is %d\n",hashvalue);
    fprintf(fptr,"%d",hashvalue);
    fclose(fptr);

    return 0;
}