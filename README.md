# Linux-System-Calls
Repository for the course LAS

# Notes on System Calls

To get more information on a particular system call : `man 2 syscall`.
 
- `open` :
    - returns a *file descriptor*, index to the system wide open file descriptors table.
    - for each open, a close has to be present.
    The system call must include an access flag, and optionnaly some other creation flags.

The  open() system call opens the file specified by pathname.  If the specified file does not exist, it may optionally (if O_CREAT is speci‐
fied in flags) be created by open().

The return value of open() is a file descriptor, a small, nonnegative integer that is an index to an entry in the process's  table  of  open
file  descriptors.   The  file  descriptor is used in subsequent system calls (read(2), write(2), lseek(2), fcntl(2), etc.)  to refer to the
open file.  The file descriptor returned by a successful call will be the  lowest-numbered  file  descriptor  not  currently  open  for  the
process.

By  default,  the  new file descriptor is set to remain open across an execve(2) (i.e., the FD_CLOEXEC file descriptor flag described in fc‐
ntl(2) is initially disabled); the O_CLOEXEC flag, described below, can be used to change this default.  The file offset is set to  the  be‐
ginning of the file (see lseek(2)).

A  call  to  open() creates a new open file description, an entry in the system-wide table of open files.  The open file description records
the file offset and the file status flags (see below).  A file descriptor is a reference to an open file description; this reference is  un‐
affected  if  pathname is subsequently removed or modified to refer to a different file.  For further details on open file descriptions, see
NOTES.
