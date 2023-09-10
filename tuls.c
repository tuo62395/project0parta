
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <errno.h>

int main(int argc, char **argv){
    printf("number of elements: %d\n", argc);

    struct dirent **nameList;
    int n;
    n = scandir(".",&nameList,NULL,alphasort);
    printf("Number Files %d\n", n);
    if (n == -1) {
        perror("scandir");
        exit(EXIT_FAILURE);
    }
    for(int i = 0; i < n; i++){
        printf("%s\n", nameList[i]->d_name);
    }
 



    //DIR *dp = opendir(".");

    //if (dp == NULL){
    //    perror("cannot open.");
    //    exit(1);
    //}



    return 0;
}