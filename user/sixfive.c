#include "kernel/types.h"
#include "kernel/fcntl.h"
#include "user/user.h"

char buf[512];

void
sixfive(int fd)
{
  int n;
  char token[32];
  int len = 0;

  while ((n = read(fd, buf, sizeof(buf))) > 0) {
    for (int i = 0; i <= n; i++) {
      char c = buf[i];
      if (strchr(" -\r\t\n.,", c) == 0){
        token[len] = c;
        len++;
      } else {
        len++;
        token[len] = '\0';
        int num = atoi(token);
        if ((num % 5) == 0 || (num % 6 ) == 0){
          printf("%d\n", num);
        }
        memset(token, 0, sizeof token);
        len = 0;
      }
    }
  }
  if (n < 0) {
    fprintf(2, "sixfive: read error\n");
    exit(1);
  }
}


int
main(int argc, char *argv[])
{
  int fd, i;

  if (argc <= 1) {
    sixfive(0);
    exit(0);
  }

  for (i = 1; i < argc; i++) {
    if ((fd = open(argv[i], O_RDONLY)) < 0) {
      fprintf(2, "sixfive: cannot open %s\n", argv[i]);
      exit(1);
    }
    sixfive(fd);
    close(fd);
  }
  exit(0);
}

