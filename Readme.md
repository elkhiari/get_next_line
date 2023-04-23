## What is a File Descriptor?
    file descriptor in C is a unique integer value that identifies an open file or I/O resource within a process.    
    By default, each process systematically inherits three open file descriptors :

| File Descriptor | Name | <unistd.h> |	<stdio.h> |
| --------------- | ---- | ---------- | --------- |
| 0 | Standard Input | STDIN_FILENO | stdin |
| 1 | Standard Output | STDOUT_FILENO |	stdout |
| 2 | Standard Error | STDERR_FILENO |	stderr |