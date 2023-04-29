# Minitalk
Minitalk is a project from the 42 School that consists of creating a client-server program that allows two processes to communicate via Unix signals.

The server program is responsible for receiving messages, while the client program must send messages to the server using its PID and a signal. The server then displays the received message.

The project is composed of two parts: the client and the server. Each must be implemented using the same codebase but compiles into separate programs.

## Usage
To use Minitalk, you must first compile the client and server programs using `make`.

Next, you can start the server program by using the command `./server`. This will launch the server, which will wait for client connections.

To send a message to the server, you can run the client program using the command `./client [PID] [message]`, where `[PID]` is the process ID of the server and `[message]` is the message you want to send.

The client sends a signal for each bit of the message, and the server reconstructs the message from these signals.

## Example
To run Minitalk follow these steps:

1. Open two terminals.
2. In the first terminal, compile the program using the command `make`.
3. In the first terminal, execute the server program using `./server`.
4. Note the PID of the server (it is displayed when the server starts).
5. In the second terminal, execute the client using `./client [PID] "Hello, world!"`. Replace [PID] with the PID of the server displayed in step 4.
6. Check that the message "Hello, world!" was received and displayed in the first terminal.

## Conclusion
Minitalk is an interesting project that allows you to become familiar with Unix signals and inter-process communication.
This project can be implemented using different strategies, so feel free to explore different approaches to find the best solution.
