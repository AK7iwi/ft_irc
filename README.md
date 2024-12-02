# ft_irc

An IRC server in C++ 98

## Overview 

ft_irc is a custom Internet Relay Chat (IRC) server. It is designed to handle multiple client connections and facilitate real-time communication over the IRC protocol. It adheres to the IRC protocol specifications, making it compatible with common IRC clients like irssi, allowing users to interact with the server through a familiar interface.

## Usage

1) Launch the server: 

```bash
make
./ircserv <port> <password> 
```
2) You can connect to the server with common IRC clients like irssi or with netcat command: 
 
a) Connection with irssi

```irssi
irssi
```
In irssi: 

```irssi
/connect localhost <port> <password> 
```
or: 

```irssi
/connect localhost <port> <pasword> <username>
```

b) Connection with netcat

```bash
nc -C localhost <port> <password>
/PASS <passsword>
/NICK <nickname>
/USER <username> <servername> <hostname> <realname>
```
## How does it work?

The ft_irc project consists of the following main components:

### 1) Server Core
The core of the server handles incoming client connections, manages user sessions, and processes IRC commands. It operates over TCP sockets to facilitate communication between clients and the server.

### 2) Client Management
The server tracks connected clients, each identified by a unique nickname. It manages user authentication and ensures proper handling of client commands and responses.

### 3) Channel System
Users can create and join chat channels, which serve as virtual rooms where multiple users can communicate. The server handles channel permissions, message broadcasting, and user lists.

### 4) Command Parsing and Execution
The server parses and executes standard IRC commands such as:

- /PASS : Used to provide a connection password if the server requires one
- /NICK : Set or change a user's nickname
- /USER : Registers a new user with the server, providing basic information like  username, hostname, and real name
- /PING : Sent by the server to check if the client is still connected
- /PONG : Response to a /PING command
- /JOIN : Join a channel
- /INVITE : Invites a user to join a specific channel
- /KICK : Removes a user from a channel
- /TOPIC : Sets or retrieves the topic of a channel
- /PART : Leave a channel
- /PRIVMSG : Send private messages to other users
- /MODE : Sets or queries the mode of a user or channel

### 5) RPL (Error Handling)
The server implements error handling to ensure proper communication between clients and to provide meaningful feedback when commands fail or users encounter issues.

----------------------------------------------------------------------------------------------------------------------------------

### 1) Server Core

TCP (Transmission Control Protocol) is a reliable communication protocol used to send data between devices over a network. It works with sockets, which are endpoints that allow applications to connect and exchange data.

- How TCP Works? 

a) Connection Setup (Three-Way Handshake):

TCP first establishes a connection between two devices (client and server) using a socket.
The client and server "shake hands" to agree on how to communicate.

b) Data Transfer:

TCP breaks the data into smaller pieces, called segments.
Each segment is sent through the socket and arrives in order.
If any data is lost, TCP automatically resends it.

c) Connection Close (Four-Way Handshake):

Once the data is sent, TCP closes the connection by ending the socket communication.

- Why Use TCP?

a) Reliable: 

Ensures all data is received correctly and in order.

b) Error Checking: 

Detects and fixes any errors in data transmission.


c) Connection-Based: 

Establishes a stable connection before sending data.


- Common TCP Socket Use Cases

a) Web Browsing: Loading web pages (HTTP/HTTPS).

b) File Transfer: Downloading or uploading files (FTP).

c) Email: Sending and receiving emails (SMTP, IMAP).

d) Remote Access: Securely connecting to another computer (SSH).

In simple terms, TCP ensures data sent through a socket arrives safely and correctly.

#### I) Port and password
First, the server sets up a port and a password. The port should be between 1024 and 65535 because ports below 1024 are reserved for system services, while ports above 1024 are available for user applications. 
The maximum port number is 65535 because ports are represented using a 16-bit unsigned integer in the TCP and UDP protocol headers. The password should be longer than 5 characters.

#### II) Initialization of the server

##### a) Initialization of the server address

The initialized server_addr structure is used in the bind system call to bind the server socket to the specified address and port.

```C++
#include <netinet/in.h>
struct sockaddr_in6			_server_addr;
```

The struct sockaddr_in6 (IPv6): 

```C++
struct sockaddr_in6 
{
    uint16_t        sin6_family;   /* AF_INET6 */
    uint16_t        sin6_port;     /* port number */
    uint32_t        sin6_flowinfo; /* IPv6 flow information */
    struct in6_addr sin6_addr;     /* IPv6 address */
    uint32_t        sin6_scope_id; /* Scope ID (new in 2.4) */
};
```

How to initialize the struct: 

```C++
memset(&_server_addr, 0, sizeof(_server_addr));
_server_addr.sin6_family = AF_INET6;
_server_addr.sin6_port = htons(_port);
_server_addr.sin6_addr = in6addr_any;
```


How it works: 

```C++
memset(&server_addr, 0, sizeof(server_addr));
```

This clears the server_addr structure to ensure there are no residual values from previous operations.


```C++
server_addr.sin_family = AF_INET6;
```

This sets the address family to IPv6. For IPv4, you would use AF_INET.


```C++
server_addr.sin_port = htons(_port);
```

This sets the port number the server will listen on. 
The htons function converts the port number from host byte order to network byte order, which is required for correct communication over the network.


```C++
server_addr.sin_addr.s_addr = in6addr_any;
```

This allows the server to accept connections on any of the host’s IP addresses. in6addr_any is typically used in servers to listen on all available interfaces.


##### b) Initialization of the time

Time must be initialized for server info and RPL.


##### c) Initialization of communication and connection for the server

```C++
socket(int domain, int type, int protocol);
```

a) Use: 

Creates an endpoint for communication and returns a file descriptor representing the socket.

b) Parameters:

- domain (or address family)

Specifies the address family for the socket.

AF_INET: The socket will use the IPv4 protocol.

AF_INET6: The socket will use the IPv6 protocol.

- type

Specifies the socket type. 

Common values:

SOCK_STREAM: Provides sequenced, reliable, two-way, connection-based byte streams (typically used for TCP connections).

SOCK_DGRAM: Provides connectionless, unreliable messages of a fixed maximum length (used for UDP).

SOCK_RAW: Provides raw network protocol access.

- protocol

Specifies the protocol to be used with the socket. 0 means that the system should choose the default protocol for the given combination of domain and type. For AF_INET/AF_INET6 and SOCK_STREAM, this usually means the TCP protocol.

- Return Value

The function returns a file descriptor (an integer) that represents the socket of the server. If the socket creation fails, it returns -1.
It return the server socket.

```C++
setsockopt(int sockfd, int level, int optname, const void *optval, socklen_t optlen);
```

a) Use: 

Sets options on a socket to configure its behavior.

b) Parameters:

- sockfd

The file descriptor of the socket on which to set the option.

- level

Specifies the protocol level at which the option resides.

Common values:

SOL_SOCKET: Set options at the socket level.

IPPROTO_TCP: Set options at the TCP protocol level.

- optname

The name of the option to set. 

Common options:

SO_REUSEADDR: Allows the socket to be bound to an address that is already in use.

SO_KEEPALIVE: Enables keepalive messages for the socket.

- optval

A pointer to the option value. For example, to enable SO_REUSEADDR, this would point to an integer set to 1.

- optlen

The size of the option value in bytes.

- Return Value

Returns 0 on success and -1 on failure.

```C++
fcntl(int fd, int cmd, ...);
```

a) Use: 

Performs various control operations on a file descriptor, such as setting it to non-blocking mode.

b) Parameters:

- fd

The file descriptor on which to perform the operation (e.g., a socket or file descriptor).

- cmd

Specifies the command to perform.

Common commands:

F_SETFL: Set file status flags.

F_GETFL: Get file status flags.

- Additional Arguments

Depending on the command, additional arguments may be required, such as setting non-blocking mode (O_NONBLOCK).

What is a non-blocking socket ?

Non-blocking I/O means that the I/O operations (such as reading from or writing to a socket) do not cause the program to wait if the operation cannot be completed immediately. 
Instead, the function returns immediately with an indication that the operation could not be completed right now. 
This is useful for high-performance servers that need to handle many connections simultaneously without being blocked by any single operation.

- Return Value

Returns a new descriptor on success or -1 on failure

```C++
bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
```

a) Use: 

Associates a socket with a specific local address and port (struct sockaddr_in6).

b) Parameters:

- sockfd

The file descriptor of the socket to bind.

- addr

A pointer to a sockaddr structure (e.g., sockaddr_in for IPv4 or sockaddr_in6 for IPv6) that specifies the address to bind to.

- addrlen

The size of the address structure in bytes.

- Return Value

Returns 0 on success and -1 on failure.

```C++
listen(int sockfd, int backlog);
```

a) Use:

Marks a socket as passive, indicating that it will accept incoming connection requests.

b) Parameters:

- sockfd

The file descriptor of the socket to mark as a passive socket (i.e., to listen for incoming connections).

- backlog

The maximum number of pending connections that can be queued for acceptance.

- Return Value

Returns 0 on success and -1 on failure.

```C++
struct pollfd server_fd;
```

```C++
struct pollfd
{
	int   fd;         /* file descriptor */
    short events;     /* requested events */
    short revents;    /* returned events */
};
```

a) Use:

The struct pollfd is used with the poll() system call in C++ to monitor multiple file descriptors (e.g., sockets, pipes, or files) for events such as readiness for reading or writing.

b) Parameters: 

- int fd (File Descriptor)

The file descriptor you want to monitor.

- short events (Requested Events)

Specifies the events you want to monitor for this file descriptor.

Common event flags:

POLLIN: Data is available to read.

POLLOUT: The file descriptor is ready for writing.

POLLERR: An error occurred.

POLLHUP: The connection was closed (hang-up).

POLLPRI: There is urgent data to read (out-of-band data).


- short revents (Returned Events)

After calling poll(), this field contains the events that actually occurred on the file descriptor.

The value in revents is a subset of the flags from events, plus additional flags such as:

POLLNVAL: The file descriptor is invalid.

POLLERR: An error occurred on the file descriptor.

POLLHUP: The connection was closed.


#### III) Handle connections and clients

```C++
poll(struct pollfd *fds, nfds_t nfds, int timeout);
```

a) Use:

Monitors multiple file descriptors to see if any of them are ready for I/O operations (e.g., reading or writing).


b) Parameters:

- fds

A pointer to an array of struct pollfd structures, each specifying a file descriptor to monitor and the events to watch for.

- nfds

The number of file descriptors in the fds array.

- timeout

The maximum time to wait in milliseconds:

0: Returns immediately (non-blocking).
-1: Waits indefinitely (blocking).
Positive value: Waits for the specified number of milliseconds.

- Return Value

Returns the number of file descriptors with events, 0 if the timeout expires, or -1 on failure.

### 2) Client Management 

#### I) Handle new connection

##### a) Initialization of the client address


struct sockaddr_in6 client_addr;
memset(&client_addr, 0, sizeof(client_addr));
socklen_t client_len = sizeof(client_addr);

##### b) Create connection for clients

```C++
accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
```

a) Use:

Accepts a connection request on a listening socket and returns a new socket file descriptor for the connection.

b) Parameters:

- sockfd

The file descriptor of the listening socket (created with socket() and set to listen with listen()).

- addr

A pointer to a sockaddr structure where the address of the connecting client will be stored.

- addrlen

A pointer to a variable containing the size of the addr structure. It will be updated with the actual size of the client address.

- Return Value

Returns a new file descriptor for the accepted connection on success or -1 on failure.

#### II) Handle client requests

```C++
recv(int sockfd, void *buf, size_t len, int flags);
```

a) Use:

Receives data from a connected socket.

b) Parameters:

- sockfd

The file descriptor of the socket from which to receive data.

- buf

A pointer to a buffer where the received data will be stored.

- len

The size of the buffer in bytes.

- flags

Specifies how the call is made. 

Common flags:

0: Standard blocking receive.

MSG_DONTWAIT: Non-blocking receive.

MSG_PEEK: Peek at the incoming data without removing it from the queue.

- Return Value

Returns the number of bytes received on success, 0 if the connection is closed, or -1 on failure.


### 3) Channel System

### 4) Command Parsing and Execution

### 5) RPL (Error handling)



