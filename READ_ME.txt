The exec functions in C are a family of functions used to execute a program from within a C program. These functions are defined in the unistd.h header file in a Unix-based operating system, or in the process.h header file in a Windows-based operating system.

Some of the most commonly used exec functions in C are:

	execvp: This function executes the program specified by the file name passed as an argument, and searches the PATH environment variable to locate the file.

	execv: This function executes the program specified by the file name passed as an argument, and takes the full path to the file as a parameter.

	execl: This function is similar to execvp, but it takes the arguments to the program as a list of separate parameters.

	execlp: This function is similar to execl, but it searches the PATH environment variable to locate the file.

The exec functions replace the current process image with a new process image specified by the file name, and return only if there is an error in the execution of the new program.


///////////////

int execvp(const char *file, char *const argv[]);
int execv(const char *path, char *const argv[]);
int execl(const char *path, const char *arg, ... /* (char *) NULL */);
int execlp(const char *file, const char *arg, ... /* (char *) NULL */);

The ellipsis (...) in the prototypes of execl and execlp indicates that a variable number of arguments can be passed to these functions.

The arguments should be specified as a list of pointers to strings, terminated by a NULL pointer.

//

If the execution of the new process image is successful, the exec function does not return. Instead, the new process image replaces the current process image and starts executing.

If there is an error in executing the new process image, the exec function returns a non-zero value.


//
open: This function is used to open a file and return a file descriptor,
which is an integer representing the file.
The file descriptor can be used to perform various operations on the file,
such as reading or writing.

int fd = open("file.txt", O_RDONLY);
int fd = open("file.txt", O_RDWR | O_CREAT | O_TRUNC, 0666);

O_RDONLY: Open for reading only.
O_WRONLY: Open for writing only.
O_RDWR: Open for reading and writing.
O_APPEND: Write to the end of the file, appending new data.
O_TRUNC: Truncate the file to zero length if it exists and is opened for writing.
Note that oflags can be combined using the bitwise OR operator (|), for example:
O_CREAT: Create the file if it doesn't exist.


