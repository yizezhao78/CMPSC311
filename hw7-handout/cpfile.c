#include "csapp.h"

int main(int argc, char **argv)
{
  int n;
  rio_t rio;
  char buf[MAXLINE];
  int fd;

  if(argc > 1){
    //when there are more than one command in command line:
    //open a read only file descriptor and duplicate it to STDIN_FILENO
    fd = open(argv[1], O_RDONLY);
    dup2(fd, STDIN_FILENO);
    close(fd);
  }


  Rio_readinitb(&rio, STDIN_FILENO);
  while((n = Rio_readlineb(&rio, buf, MAXLINE)) != 0)
    Rio_writen(STDOUT_FILENO, buf, n);

  return 0;
}
