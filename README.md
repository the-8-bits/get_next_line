---
title: Get Next Line
tags:
  - "42"
  - programação
  - common_core
use: README, Documentation
languages: C
dependences:
---

<p align="center">
  <picture>
    <img alt="List_logo" src="https://drive.google.com/uc?export=view&id=1rFqWh4miOnHABWGa2X7KTe2geXDhuD2S">
  </picture>
</p>

# <p align="center">**Get Next Line**</p>
<p align="center">Reading a line from a fd is way too tedious</p>
</br>
<p align="center"> <i>Summary:</br>
      This project is about programming a function that returns a line read from a file descriptor.</br>
      Version: 11</i></br>
</p>

</br>

> [!INFO]  
> If you spot something that isn't right, please open an [Issue](https://github.com/the-8-bits/42-libft/issues/new)

</br>

<details><summary>Table of Contents 🔖</summary>

- [**Get Next Line**](#get-next-line)
  - [Important Concepts](#important-concepts)
    - [File descriptor](#file-descriptor)
    - [Static Variables](#static-variables)
  - [Mandatory part](#mandatory-part)
    - [Return Value](#return-value)
    - [Static Variables](#static-variables-1)
    - [Helper Functions](#helper-functions)
    - [Function Operation](#function-operation)
    - [Error Handling](#error-handling)
    - [Memory Management](#memory-management)
    - [Thread Safety](#thread-safety)
    - [Usage Example](#usage-example)
  - [Bonus part](#bonus-part)
    - [Return Values](#return-values)
    - [File Descriptor Data Management](#file-descriptor-data-management)
    - [Helper Functions](#helper-functions-1)
    - [Function Operation](#function-operation-1)
    - [Error Handling](#error-handling-1)
    - [Memory Management](#memory-management-1)
    - [Thread Safety](#thread-safety-1)
    - [Usage Example](#usage-example-1)

</details>

---

## Important Concepts

### File descriptor

A file descriptor **is a number that uniquely identifies an open file in a computer's operating system** i.e. an index. It is used by the OS to keep track (in the File Description Table) of::

- **files and its states**, such as its size, position, and access permissions,
- **terminal I/O**,
- **pipes**
- **sockets**
- **devices**, etc

File descriptors are created when a process opens a file. The operating system assigns a unique file descriptor to the file and returns it to the process. The process can then use the file descriptor to read from, write to, or close the file. There's a difference between file descriptors and file pointers, a file pointer is the location in memory of the file.

File descriptors are also used to redirect input and output. For example, the ` >> ` operator can be used to redirect the output of a command to a file. In this case, the file descriptor for the file is used to specify the destination of the output.

The first three file descriptors are reserved for standard input (`stdin`), standard output (`stdout`), and standard error (`stderr`). These file descriptors are used by the operating system to communicate with processes.

File descriptors are an important concept in operating systems. They provide a way for the operating system to keep track of files and their state, and they allow processes to interact with files in a consistent way.

Here are some additional things to keep in mind about file descriptors:

-   File descriptors are integers, and they are typically non-negative.
-   The number of file descriptors that a process can open is limited by the operating system.
-   File descriptors can be inherited by child processes.
-   File descriptors can be closed by the process that opened them.

> You can go to [this file](../../../../Docs/file_descriptor.md) for a more complete explanation. Or [here](https://www.youtube.com/watch?v=KM5sRWAYqaw) if you´re a video person.

### [Static Variables](../../../../Languages/C/README.md#static-variables)

A static variable is a type of variable that retains its value across multiple function calls or throughout the lifetime of a program. Unlike local variables, which are created and destroyed every time a function is called, static variables persist and maintain their value between function invocations. They are often used to store information that needs to be shared or preserved across function calls within the same scope.

## Mandatory part

The `get_next_line` function is a C function designed to read text from a file descriptor (fd) line by line. It reads the next line from the file and returns it as a null-terminated string. This function is particularly useful for reading data from files where the line lengths are variable.

The function uses a static buffer to store and accumulate data read from the file descriptor until it encounters a newline character ('\n'). Once a newline character is found, it returns the accumulated line, including the newline character, as a string. If the end of the file is reached, or if an error occurs, the function returns `NULL`.

```c
char *get_next_line(int fd);
```

- `int fd`: The file descriptor from which to read.

### Return Value

- On success, the function returns a pointer to the next line read from the file (including the newline character) as a null-terminated string.
- If the end of the file is reached, it returns `NULL`.
- If an error occurs, it also returns `NULL`.

### Static Variables

The function uses some static variables to maintain the state between successive calls.

- `static char *line_buffer`: This variable holds the accumulated data read from the file descriptor until a newline character is encountered. It is initially set to `NULL`.
  
### Helper Functions

The `get_next_line` function relies on several helper functions for its operation:

- `ft_free`

    ```c
    static void ft_free(char **str);
    ```

    This function is used to free memory allocated for strings. It checks if the input pointer is valid and not NULL before freeing the memory and setting the pointer to NULL to prevent dangling pointers.

- `ft_read`

    ```c
    static int ft_read(int fd, char **line_buffer, char *buffer);
    ```

    The `ft_read` function is responsible for reading data from the file descriptor into a buffer. It is called within the `get_next_line` function to read data from the file. The function reads up to `BUFFER_SIZE` bytes at a time and appends the read data to the `line_buffer`. It returns the number of bytes read.

### Function Operation

1. The function first performs some input validation checks. It ensures that the file descriptor (`fd`) is valid (not negative) and that `BUFFER_SIZE` is greater than zero. If any of these conditions are not met, the function returns `NULL`.

2. It allocates memory for a `buffer` to read data from the file descriptor. The size of the buffer is `BUFFER_SIZE + 1` to accommodate the null-terminator.

3. The main loop of the function continues until one of the following conditions is met:
   - A newline character ('\n') is found in the `line_buffer`.
   - The `ft_read` function returns an error (`bytes == -1`).
   - The end of the file is reached (`bytes == 0`).

4. Inside the loop, the `ft_read` function is called to read data into the `buffer`. The data read is appended to the `line_buffer`.

5. After exiting the loop, the `buffer` is freed to prevent memory leaks.

6. Finally, the function checks if the `line_buffer` is empty or if an error occurred during reading. If either of these conditions is true, it returns `NULL`. Otherwise, it duplicates the `line_buffer` using `ft_strdup`, frees the `line_buffer`, and returns the result.

### Error Handling

The function handles errors in the following ways:
- If `fd` is negative or `BUFFER_SIZE` is not greater than zero, it returns `NULL`.
- If an error occurs during the `read` operation in the `ft_read` function (`bytes == -1`), it frees the `line_buffer` and returns `NULL`.

### Memory Management

The function allocates memory for the `buffer` to read data, and it dynamically resizes the `line_buffer` to accommodate the read data. It is essential to free the allocated memory to prevent memory leaks.

### Thread Safety

The function is not thread-safe due to the use of static variables (`line_buffer`). If multiple threads call this function simultaneously with different file descriptors, they may interfere with each other's state.

### Usage Example

Here's an example of how you might use the `get_next_line` function to read lines from a file:

```c
int main() {
    int fd = open("sample.txt", O_RDONLY);
    char *line;

    while ((line = get_next_line(fd)) != NULL) {
        printf("Line: %s\n", line);
        free(line); // Don't forget to free the allocated memory
    }

    close(fd);
    return 0;
}
```

The `get_next_line` function is a useful utility for reading lines from a file descriptor. It maintains a static buffer to accumulate data, making it suitable for reading lines from files with variable line lengths. However, developers should be aware of memory management and potential thread safety issues when using this function in multi-threaded environments.

## Bonus part

The `get_next_line` function is extended in this implementation to manage data associated with each file descriptor (`fd`) separately. It reads text from a file descriptor line by line and returns the next line as a null-terminated string. This implementation addresses potential issues related to managing multiple file descriptors by introducing data structures and functions to store and manage data associated with each `fd`.

```c
static t_fd_data *get_fd_data(int fd);
static t_fd_data *create_fd_data(int fd);
static int ft_read(int fd, char **line_buffer, char *buffer);
char *get_next_line(int fd);
```


- `int fd`: The file descriptor from which to read.

### Return Values

- `t_fd_data *get_fd_data(int fd)`: Returns a pointer to the `t_fd_data` structure associated with the given `fd`. Returns `NULL` if no such structure exists.

- `t_fd_data *create_fd_data(int fd)`: Creates a new `t_fd_data` structure for the given `fd`, initializes its fields, and returns a pointer to the newly created structure. Returns `NULL` if memory allocation fails.

- `int ft_read(int fd, char **line_buffer, char *buffer)`: Reads data from the file descriptor `fd` into the `buffer`. It appends the read data to `line_buffer`. Returns the number of bytes read.

- `char *get_next_line(int fd)`: Reads the next line from the file descriptor `fd` and returns it as a null-terminated string. It manages the data associated with the `fd` to ensure that the function works correctly with multiple file descriptors.

### File Descriptor Data Management

**`t_fd_data` Structure**

A custom data structure called `t_fd_data` is introduced to manage data associated with each file descriptor. It has the following fields:

- `int fd`: The file descriptor.
- `char *left_str`: A buffer to store any remaining data from the previous read operation.
- `struct t_fd_data *next`: A pointer to the next `t_fd_data` structure in the linked list (for managing multiple file descriptors).

### Helper Functions

- `get_fd_data`

    ```c
    static t_fd_data *get_fd_data(int fd);
    ```

    This function searches for the `t_fd_data` structure associated with a given file descriptor (`fd`) in a linked list of such structures. It returns a pointer to the found structure or `NULL` if no matching structure is found.

- `create_fd_data`

    ```c
    static t_fd_data *create_fd_data(int fd);
    ```

    This function allocates memory for a new `t_fd_data` structure, initializes its fields, and adds it to the linked list of `t_fd_data` structures. It returns a pointer to the newly created structure or `NULL` if memory allocation fails.

### Function Operation

1. The `get_next_line` function performs input validation checks to ensure that the `fd` is valid (not negative) and that `BUFFER_SIZE` is greater than zero. If any of these conditions are not met, it returns `NULL`.

2. It attempts to retrieve the `t_fd_data` structure associated with the given `fd` using the `get_fd_data` function. If such a structure does not exist, it creates one using the `create_fd_data` function.

3. The main read loop within the `get_next_line` function is similar to the previous implementation. It reads data from the file descriptor into a `buffer` using the `ft_read` function and appends it to the `left_str` field of the `t_fd_data` structure.

4. If `ft_read` returns an error (`bytes_read <= 0`), the function handles the following cases:
   - If `bytes_read` is zero and there is data left in `left_str`, it returns the remaining data as a line and clears `left_str`.
   - Otherwise, it returns `NULL`.

5. If the read operation is successful, the function duplicates the `left_str` (to avoid modifying the original) and clears `left_str` for further reads. It returns the duplicated line.

### Error Handling

The function handles errors in the following ways:
- If `fd` is negative or `BUFFER_SIZE` is not greater than zero, it returns `NULL`.
- If memory allocation fails during the creation of the `t_fd_data` structure, it returns `NULL`.

### Memory Management

The function dynamically allocates and deallocates memory as needed:
- Memory is allocated for the `buffer` to read data from the file descriptor.
- Memory is allocated for the `t_fd_data` structure to manage data associated with the `fd`.
- Memory is allocated for the duplicated line that is returned to the caller.
- Memory allocated for `left_str` is freed when the line is returned or if an error occurs.

### Thread Safety

This implementation is not thread-safe due to the use of static variables and shared data structures. If multiple threads call the `get_next_line` function simultaneously with different file descriptors, they may interfere with each other's state.

### Usage Example

Here's an example of how you might use the `get_next_line` function to read lines from multiple files:

```c
int main() {
    int fd1 = open("file1.txt", O_RDONLY);
    int fd2 = open("file2.txt", O_RDONLY);
    char *line;

    while ((line = get_next_line(fd1)) != NULL) {
        printf("File 1 Line: %s\n", line);
        free(line); // Don't forget to free the allocated memory
    }

    while ((line = get_next_line(fd2)) != NULL) {
        printf("File 2 Line: %s\n", line);
        free(line); // Don't forget to free the allocated memory
    }

    close(fd1);
    close(fd2);
    return 0;
}
```

This extended implementation of the `get_next_line` function introduces data management for multiple file descriptors. It uses a custom data structure to store and manage data associated with each file descriptor, ensuring correct behavior when reading from multiple sources simultaneously. Developers should still be cautious about memory management and potential thread safety issues when using this function in multi-threaded environments.

> Malebolge