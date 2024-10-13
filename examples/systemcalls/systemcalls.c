#include "systemcalls.h"
#include <stdlib.h>

// Fork
#include <unistd.h> 
// Waitpid
#include <sys/types.h>
#include <sys/wait.h>

// File IO
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

/**
 * @param cmd the command to execute with system()
 * @return true if the command in @param cmd was executed
 *   successfully using the system() call, false if an error occurred,
 *   either in invocation of the system() call, or if a non-zero return
 *   value was returned by the command issued in @param cmd.
*/
bool do_system(const char *cmd)
{
    printf("[do_system] Starting... \n");

    int ret = system(cmd);
    if ((ret != 0)) {
        
        return false;
    }

    return true;
}

/**
* @param count -The numbers of variables passed to the function. The variables are command to execute.
*   followed by arguments to pass to the command
*   Since exec() does not perform path expansion, the command to execute needs
*   to be an absolute path.
* @param ... - A list of 1 or more arguments after the @param count argument.
*   The first is always the full path to the command to execute with execv()
*   The remaining arguments are a list of arguments to pass to the command in execv()
* @return true if the command @param ... with arguments @param arguments were executed successfully
*   using the execv() call, false if an error occurred, either in invocation of the
*   fork, waitpid, or execv() command, or if a non-zero return value was returned
*   by the command issued in @param arguments with the specified arguments.
*/
bool do_exec(int count, ...)
{
    va_list args;
    va_start(args, count);
    char * command[count+1];
    int i;
    for(i=0; i<count; i++)
    {
        command[i] = va_arg(args, char *);
    }
    command[count] = NULL;
    // this line is to avoid a compile warning before your implementation is complete
    // and may be removed
    command[count] = command[count];

    va_end(args);

/*
 * TODO:
 *   Execute a system command by calling fork, execv(),
 *   and wait instead of system (see LSP page 161).
 *   Use the command[0] as the full path to the command to execute
 *   (first argument to execv), and use the remaining arguments
 *   as second argument to the execv() command.
 *
*/

    printf("[do_exec] Starting... \n");
    fflush(stdout);

    pid_t pid = fork();
    if (pid == -1) {
        perror("fork failed");
        return false;
    }

    if (pid == 0) { // this block is for CHILD process
        int ret = execv(command[0], command);
        if (ret == -1) {
            perror("execv");
            exit(EXIT_FAILURE);
        }
    } 
    else { // this block is for PARENT process
        int status;
        if (waitpid(pid, &status, 0) == -1) {
            perror("waitpid");
            return false;
        }
        else if (WIFEXITED(status)) {
            printf("WEXITSTATUS = %d \n", WEXITSTATUS(status));
                int exit_status = WEXITSTATUS(status);
                if (exit_status == 0) {
                    printf("Command executed successfully.\n");
                } else if (exit_status == 1) {
                    printf("Command failed with a general error.\n");
                    return false;
                } else {
                    printf("Command exited with status: %d\n", exit_status);
                }
        }
        else {
            printf("Child did not exit normally\n");
            return false;
        }
    }

    return true;
}

/**
* @param outputfile - The full path to the file to write with command output.
*   This file will be closed at completion of the function call.
* All other parameters, see do_exec above
*/
bool do_exec_redirect(const char *outputfile, int count, ...)
{
    va_list args;
    va_start(args, count);
    char * command[count+1];
    int i;
    for(i=0; i<count; i++)
    {
        command[i] = va_arg(args, char *);
    }
    command[count] = NULL;
    // this line is to avoid a compile warning before your implementation is complete
    // and may be removed
    command[count] = command[count];

/*
 * TODO
 *   Call execv, but first using https://stackoverflow.com/a/13784315/1446624 as a refernce,
 *   redirect standard out to a file specified by outputfile.
 *   The rest of the behaviour is same as do_exec()
 *
*/
    printf("[do_exec_redirect] Starting... \n");
    fflush(stdout);

    pid_t pid = fork();
    if (pid == -1) {
        perror("fork failed");
        return false;
    }

    if (pid == 0) { // this block is for CHILD process
        int fd = open(outputfile, O_WRONLY|O_TRUNC|O_CREAT, 0644);
        dup2(fd, 1);

        int ret = execv(command[0], command);
        if (ret == -1) {
            perror("execv");
            close(fd);
            exit(EXIT_FAILURE);
        }
        close(fd);
    }
    else { // this block is for PARENT process
        int status;
        if (waitpid(pid, &status, 0) == -1) {
            return false;
        }
        else if (WIFEXITED(status)) { // Bu komut her zaman succesful
            printf("WEXITSTATUS = %d \n", WEXITSTATUS(status));
                int exit_status = WEXITSTATUS(status);
                if (exit_status == 0) {
                    printf("Command executed successfully.\n");
                } else if (exit_status == 1) {
                    printf("Command failed with a general error.\n");
                    return false;
                } else {
                    printf("Command exited with status: %d\n", exit_status);
                }
        }
        else {
            printf("Child did not exit normally\n");
            return false;
        }
    }
    
    return true;
}
