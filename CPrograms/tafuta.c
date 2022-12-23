// This is a C program that searches for a file recursively from a given path#
// It also prints the execution time for the search
// It also provides file information such as file size, creation date, path, time of last modification
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/dir.h>
#include<dirent.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>
#include<limits.h>
#include<sys/stat.h>
#include<time.h>
#include<glob.h>
#include <signal.h>

//Declaring functions to be used in program
void searchInDirectory(char *filename, char *dirname, char *string);
void wildcards(char* wildfile,char* dir, char *string);
int Search_in_File(char *fname, char *str);
void trimleadingandTrailing(char *s);

//Variables used for searchInDirectory Function
int result;

//Function to remove whitespace in file
void trimleadingandTrailing(char *s)
{
	int  i,j;
 
	for(i=0;s[i]==' '||s[i]=='\t';i++);
		
	for(j=0;s[i];i++)
	{
		s[j++]=s[i];
	}
	s[j]='\0';
	for(i=0;s[i]!='\0';i++)
	{
		if(s[i]!=' '&& s[i]!='\t')
				j=i;
	}
	s[j+1]='\0';
}

int Search_in_File(char *fname, char *str) {
	FILE *fp;
	int find_result = 0;
	char temp[10000];
	
    // confirm file can be opened
	if((fp = fopen(fname, "r")) == NULL) {
        perror("Error");
		exit(1);
	}

	while(fgets(temp, 10000, fp) != NULL) {
		if((strstr(temp, str)) != NULL) {
            trimleadingandTrailing(temp);
			printf("%s\n", temp);
			find_result++;
		}
	}
	
	//Close the file.
	if(fp) {
		fclose(fp);
	}
   	return find_result;
}

// Function to check incase user inputs wildcards
void wildcards(char* wildfile,char* dirname, char *string){
    char **found; 
    glob_t gstruct;
    int r;
    
    r = glob(wildfile, GLOB_ERR | GLOB_NOSORT , NULL, &gstruct);
    
    // check for errors
    if( r!=0 )
    {
        if( r==GLOB_NOMATCH )
            fprintf(stderr,"No matches\n");
        else
            fprintf(stderr,"Undefined error. Refer to glob() documentation\n");
        exit(1);
    }
    // success, output found filenames
    found = gstruct.gl_pathv;
    while(*found)
    {
        //printf("%s\n",*found);
        searchInDirectory(*found, dirname, string);
        found++;
    }
}

//Function to search in given directory
void searchInDirectory(char *filename, char *dirname, char *string){
    struct stat st; //Creating structure to use in stat function to determine type of file

    DIR *dir; //Declaring dir 
    struct dirent *dirp; //Structure to be used
    
    // Opening the file and navigating to it
    dir=opendir(dirname);


    //Confirm input in supplied in correct order
    if (!dir){
        fprintf(stderr,"Use program correctly\n");
        printf("Usage: ./tafuta \"filename\" directory string");
        exit(1);   
    }

    chdir(dirname);

    // Looping through all items in the directory
    while((dirp=readdir(dir))!=NULL){
        stat(dirp->d_name, &st); //Passing each file to stat

        if((S_ISDIR(st.st_mode)) != 0){ //Checking if file is a directory
            if(strcmp(dirp->d_name, ".")==0 || strcmp(dirp->d_name, "..")==0){
                continue;
            }
            searchInDirectory(filename, dirp->d_name, string);
        }
        else if((S_ISREG(st.st_mode)) != 0 && (string)){ //Checking if file is a regular file and if string is set
            if((strcmp(dirp->d_name, filename)==0) && (Search_in_File(dirp->d_name, string) != 0) ){ //Checking filename and string inside
                char buf[PATH_MAX]; // PATH_MAX has already been defined limits.h header file
                char *res = realpath(dirp->d_name, buf); //Getting the full path of the file
                printf("Path: %s.\n", buf);
                printf("Size: %zu bytes.\n", st.st_size);
                //printf("Creation Date: %s.\n", ctime(&st.st_birthtime));
                printf("Last Access: %s", ctime(&st.st_atime));
                printf("Time of Last Modification: %s", ctime(&st.st_mtime));
                printf("\n");
            }
        }
        else if((S_ISREG(st.st_mode)) != 0 && (!string)){ //Checking if file is a regular file
            if((strcmp(dirp->d_name, filename)==0)) { //Checking filename only
                char buf[PATH_MAX]; // PATH_MAX has already been defined limits.h header file
                char *res = realpath(dirp->d_name, buf); //Getting the full path of the file
                printf("Path: %s.\n", buf);
                printf("Size: %zu bytes.\n", st.st_size);
                //printf("Creation Date: %s.\n", ctime(&st.st_birthtime));
                printf("Last Access: %s", ctime(&st.st_atime));
                printf("Time of Last Modification: %s", ctime(&st.st_mtime));
                printf("\n");
            }
        }
        else { // Incase file is anything else other than regular file or directory e.g. block special files.
            continue;
        }
    }
    chdir("..");
    closedir(dir);
}
int main( int argc, char *argv[] )  {
    if ( argc < 3 ) {
err:
        printf("Usage: ./tafuta \"filename\" directory(full path) string");
        return 0;
    }
    // Variables used to calculate execution time
    int h,m,s;
    double second = 0.0;
    clock_t begin = clock();
    

    
    // Check if user has provided "/" at the end of directory.
    // If not put, then it is appended.
    if (strcmp( &(argv[2][strlen(argv[2])-1] ), "/") != 0 ){
        strcat(argv[2], "/");
    }

    switch ( argc ){
        case 4:
        for (int i = 0, n = strlen(argv[1]); i < n; i++) { 
            if (argv[1][i] == '*'|| argv[1][i] == '[' || argv[1][i] == '?' || 
                argv[1] == "*" || argv[1] == "["  || argv[1] == "?") {
                
                wildcards(argv[1], argv[2], argv[3]);
            } else{
                goto next; //Defaults in the case of no wildcards
            }
        }
        searchInDirectory( argv[1], argv[2], argv[3]);
        break;
        
next:
        case 3:
        for (int i = 0, n = strlen(argv[1]); i < n; i++) { 
            if (argv[1][i] == '*'|| argv[1][i] == '[' || argv[1][i] == '?' || 
                argv[1] == "*" || argv[1] == "["  || argv[1] == "?") {
                
                wildcards(argv[1], argv[2], argv[3]);
            }
        }
        searchInDirectory( argv[1], argv[2], argv[3]);
        break;
        
        default:
        goto err;
        break;
    }


    clock_t end = clock();
    second += (double)(end - begin) / CLOCKS_PER_SEC;
    h = (second/3600);
    m = (second - (3600 *h))/60;
    s = (second - (3600*h) - (m* 60));
    if (s < 1){
        printf("Execution time: Less than 1 second");
        exit (0);
    } else if ( s >= 1 && m < 0){
        printf("Execution time: %d seconds", s);
    }
    if (m > 0){
        printf("Execution time: %d minutes and %d seconds", m, s);
    }
    if ( h > 0){
        printf("Execution time: %d hours %d minutes and %d seconds", h, m, s);
    }
    return 0;
}