
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <errno.h>
#include <sys/stat.h>
#include <string.h>

int printAll(char directory[], int indentation){
    //first, scan the current directory
    struct stat buffer;
    struct dirent **nameList;
    int n;
    n = scandir(directory, &nameList, NULL, alphasort);
    if (n == -1){
        printf("scandir failed for directory: %s\n", directory);
        exit(EXIT_FAILURE);
    }

    //iterate through items in directory

    for(int i = 2; i < n; i++){
        //print indentation
        for(int i = 0; i < indentation; i++){
            printf("%s", "   ");
        }

        //we print each element in the directory as we visit it
        printf("%s\n", nameList[i]->d_name);

        //if the element is a directory, enter it
        
        //if i remove this line, the program thinks tuls is a directory even though it's not
        stat(nameList[i]->d_name, &buffer);

        //using strings to build the new directory path
        char newDirectory[50];
        //add the current directory to the string (already contains a / at the end)
        strcpy(newDirectory, directory);
        char dirAddition[50];
        //add the element name that we are entering to the string
        strcpy(dirAddition, nameList[i]->d_name);
        //add the forward slash
        strcat(dirAddition, "/");
        //put everything together
        strcat(newDirectory, dirAddition);
        //printf("\nnew directory is: %s\n", newDirectory);
        
        stat(newDirectory, &buffer);
        if (S_ISDIR(buffer.st_mode) != 0){ //not zero if it's a directory
            //printf("%s is a directory\n", newDirectory);
            
            //since it's a directory, call the recursive function and increase the indentation by 1
            printAll(newDirectory, indentation+1);
        }
        

    }
    return 0;
}

int main(int argc, char **argv){
    if(argc > 2){ //more than 2 elements - error
        puts("error, too many arguments provided");
        exit(EXIT_FAILURE);
    }

    if(argc == 1){ //zero elements -- list items in cwd
        struct dirent **nameList;
        int n;
        n = scandir(".",&nameList,NULL,alphasort); //scan directory and store elements in nameList
        //printf("Number Files %d\n", n);
        if (n == -1) { //if scandir call is not successful
            perror("scandir");
            exit(EXIT_FAILURE);
        }
        for(int i = 2; i < n; i++){ //iterate starting at 2 to avoid "." and ".."
            printf("%s\n", nameList[i]->d_name);
        }
    } else if (argc == 2){ //one element -- recursion

    //building the first directory to recursively scan through, which is the parent directory of the directory
    char parentDir[50];

    //add a "/../" to the directory to go to the parent directory
    strcpy(parentDir, argv[1]);
    strcat(parentDir, "/../");

    //initial call to the recursive function, 0 represents 0 indentations to start
    printAll(parentDir, 0);

    }



    return 0;
}