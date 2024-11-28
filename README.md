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
You can connect to the server with common IRC clients like irssi or with netcat command: 

2) Connection with irssi

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

3) Connection with netcat

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

#### I) Port and password
First, the server sets up a port and a password. The port should be between 1024 and 65535 because ports below 1024 are reserved for system services, while ports above 1024 are available for user applications. The maximum port number is 65535 because ports are represented using a 16-bit unsigned integer in the TCP and UDP protocol headers. The password should be longer than 5 characters.

#### II) Initialization of the server

##### a) Initialization of the server address

The initialized server_addr structure is used in the bind system call to bind the server socket to the specified address and port.

```C
#include <netinet/in.h>
struct sockaddr_in6			_server_addr;
```

The struct sockaddr_in6: 

```C
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

```C
memset(&_server_addr, 0, sizeof(_server_addr));
_server_addr.sin6_family = AF_INET6;
_server_addr.sin6_port = htons(_port);
_server_addr.sin6_addr = in6addr_any;
```

How it works: 

```memset(&server_addr, 0, sizeof(server_addr)); ```

This clears the server_addr structure to ensure there are no residual values from previous operations.


```server_addr.sin_family = AF_INET6; ```

This sets the address family to IPv6. For IPv4, you would use AF_INET.


```server_addr.sin_port = htons(_port); ```

This sets the port number the server will listen on. 
The htons function converts the port number from host byte order to network byte order, which is required for correct communication over the network.


```server_addr.sin_addr.s_addr = in6addr_any; ```

This allows the server to accept connections on any of the host’s IP addresses. in6addr_any is typically used in servers to listen on all available interfaces.


##### b) Initialization of the time

Time must be initialized for server info and RPL.


##### c) Initialization of the communication and connection for the server

```socket(int domain, int type, int protocol); ```

- domain (or address family)

Specifies the address family for the socket. AF_INET means the socket will use the IPv4 protocol.
For IPv6, you would use AF_INET6.

- type

Specifies the socket type. SOCK_STREAM indicates that the socket will provide sequenced, reliable, two-way, connection-based byte streams. This is typically used for TCP connections.
Other options include SOCK_DGRAM for datagram-based connections (UDP), SOCK_RAW for raw sockets, etc.

- protocol

Specifies the protocol to be used with the socket. 0 means that the system should choose the default protocol for the given combination of domain and type. For AF_INET and SOCK_STREAM, this usually means the TCP protocol.

- Return Value

The function returns a file descriptor (an integer) that represents the socket of the server. If the socket creation fails, it returns -1.
It return the server socket.

```setsockopt(int sockfd, int level, int optname, const void *optval, socklen_t optlen); ```

- sockfd
The file descriptor of the socket on which to set the option.

- level
Specifies the protocol level at which the option resides.

Common values:
SOL_SOCKET: Set options at the socket level.
IPPROTO_TCP: Set options at the TCP protocol level.

- optname
The name of the option to set. 

Some common options include:
SO_REUSEADDR: Allows the socket to be bound to an address that is already in use.
SO_KEEPALIVE: Enables keepalive messages for the socket.

- optval
A pointer to the option value. For example, to enable SO_REUSEADDR, this would point to an integer set to 1.

- optlen
The size of the option value in bytes.

- Return Value
Returns 0 on success and -1 on failure.

```fcntl(int fd, int cmd, ...); ```

- fd
The file descriptor on which to perform the operation (e.g., a socket or file descriptor).

- cmd
Specifies the command to perform. Common commands include:

F_SETFL: Set file status flags.
F_GETFL: Get file status flags.

- Additional Arguments
Depending on the command, additional arguments may be required, such as setting non-blocking mode (O_NONBLOCK).

- Return Value
Returns a new descriptor on success or -1 on failure

```bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen); ```

- sockfd
The file descriptor of the socket to bind.

- addr
A pointer to a sockaddr structure (e.g., sockaddr_in for IPv4 or sockaddr_in6 for IPv6) that specifies the address to bind to.

- addrlen
The size of the address structure in bytes.

- Return Value
Returns 0 on success and -1 on failure.

```listen(int sockfd, int backlog); ```

- sockfd
The file descriptor of the socket to mark as a passive socket (i.e., to listen for incoming connections).

- backlog
The maximum number of pending connections that can be queued for acceptance.

- Return Value
Returns 0 on success and -1 on failure.

```struct pollfd server_fd ```

struct pollfd
{
	int   fd;         /* file descriptor */
    short events;     /* requested events */
    short revents;    /* returned events */
};


What is a non-blocking socket ?

Non-blocking I/O means that the I/O operations (such as reading from or writing to a socket) do not cause the program to wait if the operation cannot be completed immediately. 
Instead, the function returns immediately with an indication that the operation could not be completed right now. 
This is useful for high-performance servers that need to handle many connections simultaneously without being blocked by any single operation.

#### III) Handle connections and clients

- poll
- accept
- recv 


### 2) Client management

### 3) Channel System

### 4) Command Parsing and Execution

### 5) RPL (Error handling)



