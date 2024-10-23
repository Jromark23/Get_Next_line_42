
# GNL - Get Next Line
###     Reading a Line from a File Descriptor is Too Boring 

This project from 42 Madrid challenges you to implement a function that reads a line from a file descriptor in an efficient and non-boring way.

# 📖 Introduction
Reading a line from a file descriptor (fd) may seem easy, but doing it efficiently and correctly is an art. The get_next_line function aims to provide a reliable way to read lines one at a time from any given file descriptor, whether it's a file or the standard input.

# 🎯 Objectives
Line-by-Line Reading: Implement a function that reads and returns one line at a time from a file descriptor.

Efficient Buffer Management: Optimize reading by using a buffer of variable size determined at compile time.

Memory Management: Handle dynamic memory allocation responsibly to avoid leaks and ensure stability.

Versatility: Ensure the function works with files, standard input, and handles different edge cases gracefully.

# 🚀 Features
Dynamic Buffer Size: The buffer size can be adjusted at compile time using the -D BUFFER_SIZE=n flag.

Static Variable Usage: Utilizes static variables to retain information between function calls without using global variables.

No Global Variables: Adheres to best practices by avoiding the use of global variables.

Error Handling: Robust error checking to handle unexpected scenarios gracefully.
![image](https://github.com/user-attachments/assets/d085ca1f-8aae-4a7d-955c-acaef47fdddd)
