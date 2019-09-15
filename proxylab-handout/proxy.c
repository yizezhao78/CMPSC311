#include <stdio.h>
#include "csapp.h"

#define MAX_OBJECT_SIZE 7204056
/* You won't lose style points for including this long line in your code */
static const char *user_agent_header = "User-Agent: Mozilla/5.0 (X11; Linux x86_64; rv:10.0.3) Gecko/20120305 Firefox/10.0.3\r\n";



void doit(int fd);
void read_requesthdrs(rio_t *rp);
void parse_uri(char *uri, char *host, char *port, char *path);

void build_request_header(char* request_header, char* host,
                  char* port,char* path, rio_t* rio);
void clienterror(int fd, char *cause, char *errnum,
                      char *shortmsg, char *longmsg);

int main(int argc, char **argv)
{
  int listenfd, connfd;
  char host[MAXLINE], port[MAXLINE];
  socklen_t clientlen;
  struct sockaddr_storage clientaddr;

  /* Check command line args */
  if (argc != 2) {
    fprintf(stderr, "usage: %s <port>\n", argv[0]);
    exit(1);
  }

  Signal(SIGPIPE, SIG_IGN);
  listenfd = Open_listenfd(argv[1]);
  while (1) {
    clientlen = sizeof(clientaddr);
    connfd = Accept(listenfd, (SA *)&clientaddr, &clientlen);
    Getnameinfo((SA *) &clientaddr, clientlen, host, MAXLINE,
        port, MAXLINE, 0);
    printf("Accepted connection from (%s, %s)\n", host, port);
    printf("%s\n", "????????");
    doit(connfd);
    printf("%s\n", "!!!!!!!");
    Close(connfd);
  }
}






void doit(int fd)
{
  int serverfd;
  char buf[MAXLINE], method[MAXLINE], uri[MAXLINE], version[MAXLINE];
  char host[MAXLINE], path[MAXLINE], port[MAXLINE], request_header[MAXLINE];
  rio_t rio, server_rio;
  // Read request line and headers
  rio_readinitb(&rio, fd);
  if (!rio_readlineb(&rio, buf, MAXLINE))
    return;
  printf("%s", buf);
  sscanf(buf, "%s %s %s", method, uri, version);
  printf("%s\n", "start parsing");
  if (strcasecmp(method, "GET")) {
          clienterror(fd, method, "501", "Not Implemented",
                      "Tiny does not implement this method");
          return;
      }
  // Parse URI from GET request
  parse_uri(uri, host, port, path);
  printf("%s %s %s\n", host,port, path);

  // Build the request header
  build_request_header(request_header, host, port, path, &rio);
  printf("%s\n", request_header);
  printf("%s\n", "!@#$%");

  // Connect to server
  printf("host: %s\n", host);
  printf("p:%s\n", port);
  serverfd = Open_clientfd(host, port);
  if(serverfd < 0){
      printf("connection failed\n");
      return;
  }
  printf("%s\n", "!!!!!!!");
  // Write the http header to server
  Rio_readinitb(&server_rio, serverfd);
  Rio_writen(serverfd, request_header, strlen(request_header));


  // receive message from server and send to the client
  size_t n;
  while((n = Rio_readnb(&server_rio, buf, MAXLINE)) != 0)
  {
      // printf("proxy received %zu bytes,then send\n",n);
      Rio_writen(fd, buf, n);
  }
  Close(serverfd);
}


void parse_uri(char *uri, char *host, char *port, char *path){
  char *start = uri;

  // when uri not start with http://
  if (strstr(uri, "http://")){
    start += 7;
  }
  // printf("%s\n", start);
  char *colon = strstr(start, ":");

  // When there is no port
  if (colon == NULL){
    *port = 80;
    char *slash = strstr(start, "/");
    // Also no path
    if (slash == NULL){
      sscanf(start, "%s", host);
      sscanf("/","%s",path);
      // printf("!!!!:%s",path);
    }
    // With path
    else{
      sscanf(slash, "%s", path);
      // printf("@@@@@: %s\n", path);
      *slash = '\0';
      sscanf(start, "%s", host);
      // printf("%s",host);
      // *slash = '/';
      // sscanf(slash, "%s", path);
    }
  }
  // with port
  else{
    char *slash = strstr(start, "/");

    //When no "/", set path as default "/"
    if (slash == NULL){
      char *port_start = colon +1;
      *colon = '\0';
      // printf("start ghhgh: %s\n", start);
      // printf("host ghhgh: %s\n", host);
      strcpy(host, start);
      // printf("host: %s\n",host);
      // printf("start: %s\n",port_start);
      strcpy(port, port_start);
      // printf("port: %s\n",port);
      // sscanf(colon, "%s", port);
      printf("host: %s\n", host);
      printf("port: %s\n", port);
      sscanf("/","%s",path);
      printf("path: %s\n", path);
    }

    //Or find the path behind "/"
    else{
      char *port_start = colon +1;
      *colon = '\0';
      // printf("start ghhgh: %s\n", start);
      // printf("host ghhgh: %s\n", host);
      strcpy(host, start);
      // printf("host: %s\n",host);
      // printf("start: %s\n",port_start);
      sscanf(slash, "%s", path);
      *slash = '\0';
      strcpy(port, port_start);
      // printf("port: %s\n",port);
      // sscanf(colon, "%s", port);
      printf("host: %s\n", host);
      printf("port: %s\n", port);
      printf("path: %s\n", path);
    }
  }
  return;
}



void build_request_header(char* request_header, char* host,
              char* port, char* path, rio_t* rio)
{
    char buf[MAXLINE], host_header[MAXLINE], other_header[MAXLINE];
    strcpy(host_header, "\0");
    printf("path :1243%s\n", path);
    sprintf(request_header, "GET %s HTTP/1.0\r\n", path);
    printf("abc  : %s\n", request_header);

    //Get other header from client rio and then change it
    while(Rio_readlineb(rio,buf,MAXLINE)>0){
      // printf("buf: !! %s\n", buf);
        if(strncmp(buf,"\r\n",4)==0) break;
        if(!strncasecmp(buf,"Host",strlen("Host"))){
          // printf("!!!!!%s\n", host);
          // printf("buf%s\n", buf);
            strncpy(host_header,buf,sizeof(host)+7);
            strcat(host_header, "\r\n");
            // printf("jlkjj%s\n", host_header);
            continue;
        }
        //when this line is not  proxy_connection header or connection header
        //or user-agent:
        if(!strncasecmp(buf,"Connection",strlen("Connection"))
                &&!strncasecmp(buf,"User-Agent",strlen("User-Agent"))
                &&!strncasecmp(buf,"User-Agent",strlen("User-Agent")))
            strcat(other_header,buf);
    }
    if(strlen(host_header) == 0){
        sprintf(host_header, "Host: %s\r\n", host);
    }
    //Build the request_header body
    strcat(request_header, host_header);
    // printf("2: %s\n", request_header);
    strcat(request_header, user_agent_header);
    // printf("3: %s\n", request_header);
    strcat(request_header, other_header);
    // printf("4: %s\n", request_header);
    strcat(request_header, "Connection: close\r\n");
    strcat(request_header, "Proxy-Connection: close\r\n");
    // printf("%s\n", host);
    // printf("%s\n", port);
    // printf("%s\n", path);
    // printf("%s\n", request_header);
    strcat(request_header, "\r\n");
}

void clienterror(int fd, char *cause, char *errnum,
    char *shortmsg, char *longmsg)
{
  char buf[MAXLINE], body[MAXBUF];

  /* Build the HTTP response body */
  sprintf(body, "<html><title>Tiny Error</title>");
  sprintf(body, "%s<body bgcolor=""ffffff"">\r\n", body);
  sprintf(body, "%s%s: %s\r\n", body, errnum, shortmsg);
  sprintf(body, "%s<p>%s: %s\r\n", body, longmsg, cause);
  sprintf(body, "%s<hr><em>The Tiny Web server</em>\r\n", body);

  /* Print the HTTP response */
  sprintf(buf, "HTTP/1.0 %s %s\r\n", errnum, shortmsg);
  sprintf(buf, "%sContent-type: text/html\r\n", buf);
  sprintf(buf, "%sContent-length: %d\r\n\r\n", buf, (int)strlen(body));
  rio_writen(fd, buf, strlen(buf));
  rio_writen(fd, body, strlen(body));
}
