# Building My own shell ( A simple Unix command line interpreter).
# Simple Shell

**view**
![shell](/shell.png)

## Table of contents
 - **What is the shell?**
 - **About this project**
 - **Features**
 - **USAGE**
 - **Example of Usage**
 ****
 ## What is the shell?
The shell is a program that takes commands from the keyboard via the terminal, and gives them to the operating system to perform.\
**To better understand how the shell actually works, you can read our [Article].**

## About this project
This project is a simple version of the linux shell made for [ALX (Holberton School)] taking part of the "Low-level programming & Algorithm - Linux and Unix system programming" projects.\
It is created using the **C programming Language** and it can do many functionalities that a real shell does.

## Features

### 1. Command Execution

The shell can execute both built-in commands and external commands using fork and execve.

### 2. Change Directory (cd)

The "cd" command is implemented, allowing users to navigate through directories.

### 4. Environment Variables (env)

The "env" command is supported, displaying the current environment variables.

### 5. Error Handling

The shell provides error handling for various scenarios, such as fork failures and command execution errors.

### 6. Modular Structure

The code is organized into modular functions, enhancing readability, and maintainability.

## USAGE
follo these steps:
> **Step 1:** Clone our repository using this command, (you need to have git installed on your machine first)
````
git clone https://github.com/AhmedHenawy11/simple_shell
````
> **Step 2:** Change directory to simple_shell:
````
cd simple_shell
````
> **Step 4:** Run the shell
````
./shell
````
**Exiting the shell**
When you want to exit the shell, you can use one of the following methods:
> **1: Type the command "exit"**
````
exit
````
> **2: Press on Ctrl + D**

## Example of Usage
````
(Henawy's_shell)$ ls -l
total 208
-rwxrwxrwx 1 spider spider    824 Nov 14 10:44 README.md
-rwxrwxrwx 1 spider spider    891 Nov 14 10:37 chdir.c
-rwxrwxrwx 1 spider spider    781 Nov 14 10:33 command-path.c
-rwxrwxrwx 1 spider spider    721 Nov 14 10:27 exe-cmd.c
-rwxrwxrwx 1 spider spider   1024 Nov 14 10:20 execution_process.c
-rwxrwxrwx 1 spider spider    656 Nov 14 10:15 finding_path-1.c
-rwxrwxrwx 1 spider spider    409 Nov 14 10:10 finding_path-2.c
-rwxrwxrwx 1 spider spider    760 Nov 14 10:07 finding_path.c
-rwxrwxrwx 1 spider spider    326 Nov  7 20:56 git
-rwxrwxrwx 1 spider spider    202 Nov 14 09:59 handle_env.c
-rwxrwxrwx 1 spider spider   1171 Nov 14 09:13 input_spliting.c
-rwxrwxrwx 1 spider spider    589 Nov 14 09:24 main.c
-rwxrwxrwx 1 spider spider    884 Nov 14 09:59 main.h
-rwxrwxrwx 1 spider spider  18072 Nov 14 10:37 shell
-rwxrwxrwx 1 spider spider 148616 Nov 14 10:50 shell.png
-rwxrwxrwx 1 spider spider    276 Nov 14 09:50 sympol_and_exit-status.c
-rwxrwxrwx 1 spider spider    447 Nov 14 09:05 user_input_line.c
(Henawy's_shell)$ exit

````
## Authors:
- only me.