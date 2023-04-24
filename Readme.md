# What is a File Descriptor?
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
```
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

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



An **open file table**, shared between all processes. Each entry in this table contains, among other things, the access mode, an offset describing the current location within the file, and a pointer to the corresponding entry in the inode table. This table also keeps count of the number references there are to this file in all of the file descriptor tables of all processes. When a process closes the file, this reference count is decremented and if it gets to 0, the entry is deleted from the table.


| Entry | File Path    | Access Mode | Offset | Reference Count |
|-------|--------------|-------------|---------|---------------------|
| 0     | example.txt | read/write  | 0         | 2                      |




An **inode (index node) table** which is also shared between all processes. Each entry in the inode table describes the file in detail: the path to its location on the disk, its size, its permissions, etc.

| Inode Number | File Path     | Permissions  | Owner  | Group   | Size     | Last Modified         |
| ------------| ------------ | ------------ | ------ | ------- | --------| --------------------- |
| 100         | file1.txt    | rw-r--r--    | user1  | group1  | 1024 KB | 2022-04-22 12:30:00   |
| 101         | file2.txt    | rwxr-x---    | user2  | group2  | 512 KB  | 2022-04-21 10:45:00   |
| 102         | directory1/  | rwxr-xr-x    | user1  | group1  | --      | 2022-04-22 13:00:00   |
| 103         | file3.txt    | rw-------    | user3  | group3  | 2048 KB | 2022-04-20 08:15:00   |


<center>
    <img src="https://www.codequoi.com/wp-content/uploads/2022/10/file_descriptors_en.drawio.png" />
</center>


# Memory Layout in C

* Variables declared without using malloc() are typically stored on the stack.
* Variables allocated with malloc() are stored on the heap.
* Static variables are stored in a special area of memory called the data segment, which is separate from both the stack and the heap. The data segment is a region of memory where initialized global and static variables are stored.
* Global variables are also stored in the data segment.
So in C, there are three main types of memory allocation:

1. Stack allocation - used for local variables declared within functions
2. Heap allocation - used for variables allocated with malloc() and other dynamic memory allocation functions
3. Data segment allocation - used for static and global variables.

The choice of memory allocation depends on the specific requirements of your program, and each type of allocation has its own advantages and disadvantages.


The memory layout for C program can be shown below:

<img src="https://static.javatpoint.com/cpages/images/memory-layout-in-c.png" />


## There are several differences between stack allocation, heap allocation, and data segment allocation:

* Lifetime: Variables allocated on the stack have a lifetime that is limited to the scope in which they are declared. When the function in which they are declared returns, the stack frame is destroyed and the memory used by those variables is reclaimed. Variables allocated on the heap, on the other hand, have a lifetime that persists beyond the function in which they are declared, until they are explicitly deallocated using free(). Static and global variables have a lifetime that persists throughout the entire execution of the program.

* Size: The amount of memory available for stack allocation is limited, typically to a few megabytes. Heap allocation, on the other hand, can allocate a much larger amount of memory, limited only by the amount of available system memory. Data segment allocation is typically limited by the size of the data segment, which is fixed at compile time.

* Access: Stack-allocated variables can be accessed faster than heap-allocated variables because stack access involves simply changing the value of the stack pointer. Heap-allocated variables, on the other hand, require the use of pointers to access the memory they occupy. Static and global variables can be accessed in a similar manner to stack-allocated variables, but they may be located further away from the stack, which could impact performance.

* Allocation and deallocation: Stack allocation and deallocation are managed automatically by the compiler and the operating system. Heap allocation and deallocation, on the other hand, are managed explicitly by the programmer using functions such as malloc() and free(). Static and global variables are allocated at program startup and deallocated at program shutdown.

* Fragmentation: Heap allocation can suffer from memory fragmentation, where free memory is split into small blocks, making it difficult to allocate larger blocks. Stack allocation does not suffer from this problem, as it only allocates contiguous blocks of memory. Data segment allocation does not suffer from fragmentation either, as the size of the data segment is fixed at compile time.

These are some of the main differences between stack allocation, heap allocation, and data segment allocation. The choice of allocation method depends on the specific requirements of the program and the type of data being stored.


1. Text Segment or Code Segment: This is where the compiled program code is stored. It is read-only and typically contains the machine code instructions for the executable program.
2. Data Segment: This area is used to store initialized global and static variables. It can be further divided into two sub-sections: read-only data section (contains constants) and read-write data section (contains global and static variables).
3. Heap Segment: This area is used for dynamic memory allocation. It is used to store variables that are allocated at run-time using functions like malloc(), calloc(), and realloc(). The heap is managed by the programmer, who is responsible for allocating and freeing memory as needed.
4. Stack Segment: This area is used for storing local variables and function call frames. It grows downward from higher memory addresses to lower memory addresses. When a function is called, a new stack frame is created and pushed onto the top of the stack. When the function returns, the stack frame is popped off the stack.