#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <pwd.h>
#include <grp.h>
#include <unistd.h>
//This function is for Step 4
char * time2str(const time_t * when, long ns) {
  char * ans = malloc(128 * sizeof(*ans));
  char temp1[64];
  char temp2[32];
  const struct tm * t= localtime(when);
  strftime(temp1,512,"%Y-%m-%d %H:%M:%S",t);  
  strftime(temp2,32,"%z",t);
  snprintf(ans,128,"%s.%09ld %s", temp1, ns, temp2);
  return ans;
}

// BEGIN
//Step1 : make mystat accept exactly 1 filename as a command line argument,
// and print out the first 3 lines of output that "stat" would print 
int main (int argc, char *argv[]) {
  if (argc != 2) {
    fprintf(stderr, "Usage: %s <pathname>\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  struct stat sb;
  if (stat(argv[1], &sb) == -1) {
    perror("stat");
    exit(EXIT_FAILURE);
  }


  
  printf("  File: '%s'\n", argv[1]);
  printf("  Size: %-10lu\tBlocks: %-10lu IO Block: %-6lu", (long unsigned)sb.st_size, (long unsigned)sb.st_blocks, (long unsigned)sb.st_blksize);
  switch (sb.st_mode & S_IFMT) {
  case S_IFBLK: printf(" block special file\n");
    break;
  case S_IFCHR: printf(" character special file\n");
    break;
  case S_IFDIR: printf(" directory\n");
    break;
  case S_IFIFO: printf(" fifo\n");
    break;
  case S_IFLNK: printf(" symbolic link\n");
    break;
  case S_IFREG: printf(" regular file\n");
    break;
  default: printf(" socket\n");
    break;
  }

  printf("Device: %lxh/%lud\tInode: %-10lu  Links: %lu\n", (unsigned long)sb.st_dev, (long unsigned)sb.st_dev, (long unsigned)sb.st_ino, (long unsigned)sb.st_nlink);
  return EXIT_SUCCESS;
}
