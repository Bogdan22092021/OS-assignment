#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

#define MAX_LINE_SIZE 1024

int is_regular_file(const char *path) {
    struct stat path_stat;
    if (stat(path, &path_stat) != 0) {
        return 0;
    }
    return S_ISREG(path_stat.st_mode);
}
int isSymbolicLink(const char *path)
{
    struct stat path_stat;
    if (lstat(path, &path_stat) != 0) {
        return 0; // failed to get file status
    }
    return S_ISLNK(path_stat.st_mode);
}
int checkValidity(char* options, int j, int type) {
    // check if there are any non-whitespace characters before the dash
    for(int i = 0; i < j; i++) {
        if(!isspace(options[i])) {
            return 0;
        }
    }

    // check if there are invalid options and if so ask for the input again
    for (int i = j + 1; i < strlen(options); i++)
    {
        if (options[i] != 'n' && options[i] != 'l' && options[i] != 'd' && options[i] != 't' && options[i] != 'a' && type == 1)
        {
            return 0;
        } else if (options[i] != 'n' && options[i] != 'd' && options[i] != 'h' && options[i] != 'm' && options[i] != 'a' && options[i] != 'l' && type == 0)
        {
            return 0;
        }
        
    }

    return 1;
}
void regularFileMenu(char* file) {
    char options[N];
    struct stat st;
    printf("---- Menu ----\n");
    printf("  * n: display file name\n");
    printf("  * d: display file size\n");
    printf("  * h: display hard link count\n");
    printf("  * m: display time of last modification\n");
    printf("  * a: display access rights\n");
    printf("  * l: create symbolic link\n");
    printf("Please enter your options\n\n");
    printf("STANDARD INPUT:");
    fgets(options, N, stdin);
    // if we get here it means that the input is valid
        // we compute the operations received from the input
        for (int i = 0; i < strlen(options); i++)
        {
            switch (options[i])
            {
            case 'n':
                printf("File name: %s\n", file);
                break;
            case 'd':
                 printf("File size: %ld bytes\n", (long)st.st_size);
                break;
            case 'h':
                printf("Hard link count: %ld\n", (long)st.st_nlink);
                break;
            case 'm':
                printf("Time of last modification: %s", ctime(&st.st_mtime));
                break;
            case 'a':
                printf("Access rights: \n");
                    printf("User:\n");
                    st.st_mode & S_IRUSR ? printf("Read - yes\n") : printf("Read - no\n");
                    st.st_mode & S_IWUSR ? printf("Write - yes\n") : printf("Write - no\n");
                    st.st_mode & S_IXUSR ? printf("Execute - yes\n") : printf("Execute - no");
                    
                break;
            case 'l':
                char link_name[256];
                printf("Enter name of the link: ");
                scanf("%s", link_name);
                // create symbolic link
                if (symlink(file, link_name) < 0) {
                    printf("Error: Cannot create symbolic link '%s'\n", link_name);
                }
                break;
            default:
                break;
            }
        }
        
        
    } else {
        printf("Error: Invalid input\n");
    }
}


void symbolicLinkMenu(char* file) {
    char options[N];
    struct stat st;
    printf("---- Menu ----\n");
    printf("  * n: display file name\n");
    printf("  * l: delete symbolic link\n");
    printf("  * d: size of symbolic link\n");
    printf("  * t: size of target file\n");
    printf("  * a: access rights\n");
    printf("Please enter your options\n\n");
    printf("STANDARD INPUT:");
    fgets(options, N, stdin);
}

int main(int argc, char *argv[]) {

}
