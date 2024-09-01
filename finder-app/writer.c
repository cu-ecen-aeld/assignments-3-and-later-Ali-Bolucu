#include <stdio.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

#include <syslog.h>

# define LNX_ERR (-1)

// TODO
// -----------------------
// 1. Firts argument is full path to file $writefile
// 2. Second argument ıs text string to write $writestr
// 3. Handle errors correctly
// 4. Writer dont create dir
// 5. Setup syslog for all things
// 6. Write a message “Writing <string> to <file>” 
//    where <string> is the text string written to file (second argument) and <file> is the file created by the script.
//     This should be written with LOG_DEBUG level.


int main(int argc, char **argv)
{

  openlog("Log_Main", LOG_CONS | LOG_PERROR | LOG_PID, LOG_USER);
  syslog(LOG_INFO,"You have entered %d arguments:\n", argc);

  if(argc != 3) {
    syslog(LOG_ERR, "write_path and write_str must be given as argument\n");
    closelog();
    return 1;
  }

  syslog(LOG_INFO,"Writing %s to %s", argv[2], argv[1]);
  const char *writePath = argv[1];
  const char *writeStr = argv[2];

  int fd = open(writePath, O_CREAT |O_WRONLY | O_TRUNC, S_IRWXU);
  if (fd == LNX_ERR) {
  syslog(LOG_ERR, "File could not be opened: %s\n Error: %s", writePath, strerror(errno));
    closelog();
    return 1;
  }
  
  // not socket so no while loop for partial write
  // nr = number of bytes
  int nr = write(fd, writeStr, strlen(writeStr));
  if (nr == LNX_ERR) {
    syslog(LOG_ERR, "write error. Error: %s", strerror(errno));
    closelog();
    return 1;
  }

  if (close(fd) == LNX_ERR) {
    syslog(LOG_ERR, "File could not be closed");
    closelog();
    return 1;
  }

  closelog();

  return 0;  
}