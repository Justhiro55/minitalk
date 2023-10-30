# minitalk
The purpose of this project is to code a small data exchange program using UNIX signals.

## Getting Started
Run the following commands:

### Compiling
Run the following commands:
- To compile
  ```shell
  $ make
  ```
- To remove objects:
  ```shell
  $ make clean
  ```
- To remove objects and binary file (program):
  ```shell
  $ make fclean
  ```
- To re-compile:
  ```shell
  $ make re
  ```

## Usage
To test the program you just need to launch the "server" and the "client" in different shell tabs with the following:

```shell
$ ./server
```

This will display your PID, which is necessary for the client to function, and will remain in a listening state to receive a message from the "client."

```shell
$ ./client "PID" "Your message string"
```
