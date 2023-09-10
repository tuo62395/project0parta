
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <errno.h>
#include <sys/stat.h>
#include <string.h>

int printAll(char directory[]){
    //first, scan the current directory
    struct stat buffer;
    struct dirent **nameList;
    int n;
    n = scandir(directory, &nameList, NULL, alphasort);
    if (n == -1){
        puts("failed");
        exit(EXIT_FAILURE);
    }

    //iterate through items in directory

    for(int i = 2; i < n; i++){
        printf("%s\n", nameList[i]->d_name);

        //if the item is a directory, enter it
        stat(nameList[i]->d_name, &buffer);
        char newDirectory[50];
        strcpy(newDirectory, directory);
        char dirAddition[50];
        strcpy(dirAddition, nameList[i]->d_name);
        strcat(dirAddition, "/");
        strcat(newDirectory, dirAddition);
        //printf("\nnew directory is: %s\n", newDirectory);
        
        stat(newDirectory, &buffer);
        if (S_ISDIR(buffer.st_mode) != 0){ //not zero if it's a directory
            puts("this is a directory");
            printAll(newDirectory);
        }
        

    }
    return 0;
}

int main(int argc, char **argv){
    printf("number of elements: %d\n", argc);

    
    if(argc == 1){ //zero elements -- list items in cwd
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
    } else if (argc == 2){ //one element -- recursion
    char parentDir[50];
    strcpy(parentDir, argv[1]);
    strcat(parentDir, "/../");
    printAll(parentDir);

    }





    return 0;
}