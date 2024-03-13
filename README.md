# Project 2: IPC

## Description

This project implements a simple calculator application with network communication capabilities. The application is divided into a client-server architecture where the server processes calculation requests sent by the client over Unix socket connections. Additionally, the server can read specific lines from a file as requested by the client.

## Included Files and Their Relationships

### Header Files

- **`calculator.h`**: Defines the namespace and functions for performing arithmetic calculations.
- **`filereader.h`**: Declares the `filereader` namespace with functions for reading specific lines from a file.
- **`socket.h`**: Contains the `Socket` class definition, providing foundational network communication functionalities.
- **`text-client.h`**: Declares the `Client` class, derived from `Socket`, for handling the client-side logic.
- **`text-server.h`**: Declares the `Server` class, also derived from `Socket`, for handling server-side operations.

### Source Files

- **`calculator.cc`**: Implements the functions declared in `calculator.h` for arithmetic operations.
- **`filereader.cc`**: Implements the functions declared in `filereader.h` for file reading operations.
- **`socket.cc`**: Implements the methods of the `Socket` class defined in `socket.h`.
- **`text-client.cc`**: Contains the `main` function for the client application, implementing the `Client` class's logic.
- **`text-server.cc`**: Contains the `main` function for the server application, implementing the `Server` class's logic.

### Class/Functionality Description

- **`Socket` Class**: Provides the base functionality for network communication, including setup, sending, and receiving messages over Unix sockets.
- **`Client` Class**: Inherits from `Socket`. It sends calculation or file reading requests to the server and processes the responses.
- **`Server` Class**: Inherits from `Socket`. It listens for connections, processes incoming requests for calculations or file reading, and sends back the results.
- **`calculator` Namespace**: Offers utilities for parsing calculation requests and performing arithmetic operations.
- **`filereader` Namespace**: Provides functionality to read specific lines from a file and return them as a response to the client.

## Usage

This application is designed to be compiled and run using `make` commands for both the server and client components. Follow the steps below to compile and run the server and client applications:

### Compiling and Running the Server

1. **Compile the Server**: Use the `make` command to compile the server application:
   ```bash
   make server
   ```
2. **Run the Server**: After compilation, run the server application by specifying a server name (Unix socket path):
   ```bash
   ./server servername
   ```

### Compiling and Running the Client

1. **Compile the Client**: Similarly, compile the client application using the `make` command:
   ```bash
   make client
   ```
2. **Run the Client**: Execute the client application by specifying the server name (Unix socket path), the path to a text file containing equations or file read requests, and a line number. Here's an example that requests reading line number 2 from the file at `./dat/equations_1.txt`:
   ```bash
   ./client servername ./dat/equations_1.txt 2
   ```

Ensure that the server application is running before starting the client. The client will send a request to the server based on the command-line arguments provided, and the server will process this request and return the result to the client.
