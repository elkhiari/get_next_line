## What is a File Descriptor?
    file descriptor in C is a unique integer value that identifies an open file or I/O resource within a process.
    
    By default, each process systematically inherits three open file descriptors :

| File Descriptor | Name | Developer | Developer |
| ----------------| ---- | --------- | --------- |
| 0 | 1991 | Guido van Rossum |
| 1 | 1995 | Brendan Eich |
| 2 | 1995 | James Gosling |
		<unistd.h>	<stdio.h>

        0	Standard Input	STDIN_FILENO	stdin
1	Standard Output	STDOUT_FILENO	stdout
2	Standard Error	STDERR_FILENO	stderr


| File Descriptor | Name | <unistd.h> |	<stdio.h> |
| --------------- | ---- | ---------- | --------- |
| 0 | Standard Input | STDIN_FILENO | stdin |
| 1 | Standard Output | STDOUT_FILENO |	stdout |
| 2 | Standard Error | STDERR_FILENO |	stderr |