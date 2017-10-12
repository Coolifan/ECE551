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

/*Step 1 : print out the first 3 lines of output that "stat" would print */
void regularfile(struct stat sb) {
  if (sb.st_size == 0 && sb.st_blocks == 0) {
    printf(" regular empty file\n");
  }
  else {
    printf(" regular file\n");
  }
}
void printfirst3lines(char *filename, struct stat sb) {

  if (S_ISLNK(sb.st_mode)) {
    char linktarget[256];
    ssize_t len = readlink(filename, linktarget, 256);
    if (len < 0) {
      perror("lstat");
      exit(EXIT_FAILURE);
    }
    linktarget[len] = '\0';
    printf("  File: '%s' -> '%s'\n", filename, linktarget);
  }
  else if (!S_ISLNK(sb.st_mode)) {
    printf("  File: '%s'\n", filename);
  }
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
  case S_IFREG: regularfile(sb); 
    break;
  case S_IFSOCK: printf(" socket\n");
    break;
  default: printf(" unknown?\n");
  }

  /*Step 6: fix the discrepancy of line 3*/
  if (S_ISCHR(sb.st_mode) || S_ISBLK(sb.st_mode)) {
    printf("Device: %lxh/%lud\tInode: %-10lu  Links: %-5lu Device type: %x,%x\n", (unsigned long)sb.st_dev, (unsigned long)sb.st_dev, (unsigned long)sb.st_ino,
	   (unsigned long)sb.st_nlink, major(sb.st_rdev), minor(sb.st_rdev));
  }
  else {
    printf("Device: %lxh/%lud\tInode: %-10lu  Links: %lu\n", (unsigned long)sb.st_dev, (long unsigned)sb.st_dev, (long unsigned)sb.st_ino,
	   (long unsigned)sb.st_nlink);
  }
}
/* Step 2 : add part of the 4th line of output from stat*/
void printline4(char *filename, struct stat sb) {
  printf("Access: (%04o/", sb.st_mode & (~S_IFMT));

  switch (sb.st_mode & S_IFMT) {
  case S_IFBLK: printf("b");
    break;
  case S_IFCHR: printf("c");
    break;
  case S_IFDIR: printf("d");
    break;
  case S_IFIFO: printf("p");
    break;
  case S_IFLNK: printf("l");
    break;
  case S_IFREG: printf("-");
    break;
  case S_IFSOCK: printf("s");
    break;
  }
  
  if ((sb.st_mode & S_IRUSR) != 0) {
    printf("r");
  }
  else {
    printf("-");
  }

  if ((sb.st_mode & S_IWUSR) != 0) {
    printf("w");
  }
  else {
    printf("-");
  }

  if ((sb.st_mode & S_ISUID) != 0 && (sb.st_mode & S_IXUSR) != 0) {
    printf("s");
  }
  else if ((sb.st_mode & S_ISUID) != 0  && (sb.st_mode & S_IXUSR) == 0) {
    printf("S");
  }
  else if ((sb.st_mode & S_ISUID) == 0 && (sb.st_mode & S_IXUSR) != 0) { 
    printf("x");
  }
  else {
    printf("-");
  }
  
  if ((sb.st_mode & S_IRGRP) != 0) {
    printf("r");
  }
  else {
    printf("-");
  }

  if ((sb.st_mode & S_IWGRP) != 0) {
    printf("w");
  }
  else {
    printf("-");
  }

  if ((sb.st_mode & S_ISGID) != 0 && (sb.st_mode & S_IXGRP) != 0) {
    printf("s");
  }
  else if ((sb.st_mode & S_ISGID) != 0 && (sb.st_mode & S_IXGRP) == 0) {
    printf("S");
  }
  else if ((sb.st_mode & S_ISGID) == 0 && (sb.st_mode & S_IXGRP) != 0) {
    printf("x");
  }
  else {
    printf("-");
  }

  if ((sb.st_mode & S_IROTH) != 0) {
    printf("r");
  }
  else {
    printf("-");
  }

  if ((sb.st_mode & S_IWOTH) != 0) {
    printf("w");
  }
  else {
    printf("-");
  }
  

  if ((sb.st_mode & S_ISVTX) != 0 && (sb.st_mode & S_IXOTH) != 0) {
    printf("t");
  }
  else if ((sb.st_mode & S_ISVTX) != 0 && (sb.st_mode & S_IXOTH) == 0) {
    printf("T");
  }
  else if ((sb.st_mode & S_ISVTX) == 0 && (sb.st_mode & S_IXOTH) != 0) {
    printf("x");
  }
  else {
    printf("-");
  }
  
  printf(")  ");

  /* Step 3: finish the 4th line*/
  struct passwd * pw = getpwuid(sb.st_uid);
  struct group * grp = getgrgid(sb.st_gid);

  if (pw == NULL) {
    perror("getpwuid");
    exit(EXIT_FAILURE);
  }
  if (grp == NULL) {
    perror("getgrgid");
    exit(EXIT_FAILURE);
  }	
  
  printf("Uid: (%5d/%8s)   Gid: (%5d/%8s)\n", sb.st_uid, pw->pw_name, sb.st_gid, grp->gr_name);
}
/* Step 4: add the last 4 lines of output */
void printlast4lines(char *filename, struct stat sb) {
  char *Atimestr = time2str(&sb.st_atime, sb.st_atim.tv_nsec);
  char *Mtimestr = time2str(&sb.st_mtime, sb.st_mtim.tv_nsec);
  char *Ctimestr = time2str(&sb.st_ctime, sb.st_ctim.tv_nsec);

  printf("Access: %s\n", Atimestr);
  printf("Modify: %s\n", Mtimestr);
  printf("Change: %s\n", Ctimestr);

  printf(" Birth: -\n");
  
  free(Atimestr);
  free(Mtimestr);
  free(Ctimestr);
}

int main (int argc, char *argv[]) {
  if (argc < 2) {
    fprintf(stderr, "stat: missing operand\n");
    exit(EXIT_FAILURE);
  }

  struct stat sb;
  for (int i = 1; i < argc; i++) {
    if (lstat(argv[i], &sb) == -1) {
      fprintf(stderr, "stat: cannot stat '%s': No such file or directory\n", argv[i]);
      //exit(EXIT_FAILURE);
      continue;
    }
    
    printfirst3lines(argv[i], sb); 
    printline4(argv[i], sb); 
    printlast4lines(argv[i], sb); 
  }
  return EXIT_SUCCESS;
}
