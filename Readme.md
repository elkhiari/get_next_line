## What is a File Descriptor?
file descriptor in C is a unique integer value that identifies an open file or I/O resource within a process.    
By default, each process systematically inherits three open file descriptors :

| File Descriptor | Name | <unistd.h> |	<stdio.h> |
| --------------- | ---- | ---------- | --------- |
| 0 | Standard Input | STDIN_FILENO | stdin |
| 1 | Standard Output | STDOUT_FILENO |	stdout |
| 2 | Standard Error | STDERR_FILENO |	stderr |

But why use file descriptors as identifiers? An integer is much simpler to process for a computer than a long path string to a file. What’s more, the reference to a file must contain much more than its location: it must also include its permissions, access mode, size, etc… And wouldn’t it be wasteful to keep several entire references to the same file if several processes opened it?

**So how does the operating system maintain all of the information about every open file?**

## The System’s Representation of Open Files?

To represent open files, the system uses three data structures:

A **table of file descriptors** per process. Each process has its own table containing a series of indexes, each one referring to an entry in the open file table.
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
```
int main() {
    int fd1, fd2, fd3;

    // Open three files for reading
    fd1 = open("file1.txt", O_RDONLY);
    fd2 = open("file2.txt", O_RDONLY);
    fd3 = open("file3.txt", O_RDONLY);

    // Print the file descriptors
    printf("fd1 = %d\n", fd1);
    printf("fd2 = %d\n", fd2);
    printf("fd3 = %d\n", fd3);

    // Close the files
    close(fd1);
    close(fd2);
    close(fd3);

    return 0;
}
```
| **File Descriptor** | **File Name**   |
| --------------- | -----------|
| fd1             | "file1.txt"|
| fd2             | "file2.txt"|
| fd3             | "file3.txt"|