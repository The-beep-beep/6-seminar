#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#define max_word 1000

int main(int argc, char *argv[]) {
  
  int fd1, fd2;
  char resstring[max_word];
  char file_name1[] = "a.fifo";
  char file_name2[] = "b.fifo";
  
  (void)umask(0);
  
    if (mknod(file_name1, S_IFIFO | 0666, 0) < 0) {
      printf("Cant\'t create 1FIFO\n");
      exit(-1);
    }
    if (mknod(file_name2, S_IFIFO | 0666, 0) < 0) {
      printf("Cant\'t create 2FIFO\n");
      exit(-1);
    }

  if (atoi(argv[1]) == 1) {
      
      if ((fd1 = open(file_name1, O_WRONLY)) < 0) {
          printf("Can\'t open FIFO for writing\n");
          exit(-1);
      }
      if ((fd2 = open(file_name2, O_RDONLY)) < 0) {
          printf("Can\'t open FIFO for reading\n");
          exit(-1);
      }
      
      while (1) {
          pid_t pid = fork();
          
          if (pid == 0) {
              read(fd2, resstring, max_word);
              printf("%s", resstring);
          }
          else {
              fgets(resstring, max_word, stdin);
              write(fd1, resstring, strlen(resstring) + 1);
          }
          
      }
      
  }
  else if (atoi(argv[1]) == 2) {
      if ((fd1 = open(file_name1, O_RDONLY)) < 0) {
          printf("Can\'t open FIFO for reading\n");
          exit(-1);
      }
      if ((fd2 = open(file_name2, O_WRONLY)) < 0) {
          printf("Can\'t open FIFO for writing\n");
          exit(-1);
      }
      while(1) {
          pid_t pid = fork();
          if (pid == 0) {
              read(fd1, resstring, max_word);
              printf("%s", resstring);
          }
          else {
              fgets(resstring, max_word, stdin);
              write(fd2, resstring, strlen(resstring) + 1);
          }
          
      }
      
  }

return 0;
}
