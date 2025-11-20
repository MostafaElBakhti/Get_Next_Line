#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

// #define BUFF_SIZE 1024



char *get_next_line(int fd)
{
    char buffer[1024] ; 
    
}


int main()
{
    char buffer[128] ; 
    int fd = open("test.txt" , O_RDONLY) ; 
    if (fd == -1)
    {
        perror("error opening file ") ; 
        return 1 ; 
    }

    ssize_t byteReaded = read(fd,buffer , 3) ; 
    if (byteReaded == -1)
    {
        perror("Error reading file") ;
        close(fd) ; 
        return 1 ; 
    }

    buffer[byteReaded] = '\0' ; 
    printf("Read from the file :\n%s\n" , buffer) ; 

    close(fd) ;
    return 0 ;  
    
}