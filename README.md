# ft_irc

An IRC server in C++ 98

## Overview 

ft_irc is a custom Internet Relay Chat (IRC) server. It is designed to handle multiple client connections and facilitate real-time communication over the IRC protocol. The server is compatible with popular IRC clients like irssi, allowing users to interact with the server through a familiar interface.

The ft_irc project consists of the following main components:

### 1) Server Core
The core of the server handles incoming client connections, manages user sessions, and processes IRC commands. It operates over TCP sockets to facilitate communication between clients and the server.

### 2) Client Management
The server tracks connected clients, each identified by a unique nickname. It manages user authentication and ensures proper handling of client commands and responses.

### 3) Channel System
Users can create and join chat channels, which serve as virtual rooms where multiple users can communicate. The server handles channel permissions, message broadcasting, and user lists.

### 4) Command Parsing and Execution
The server parses and executes standard IRC commands such as:

/NICK to set or change a user's nickname
/JOIN to join a channel
/PART to leave a channel
/PRIVMSG to send private messages to other users
/QUIT to disconnect from the server

RPL (Error Handling)
The server implements error handling to ensure proper communication between clients and to provide meaningful feedback when commands fail or users encounter issues.

Protocol Compliance
ft_irc adheres to the IRC protocol specifications, making it compatible with common IRC clients like irssi, enabling seamless interaction with users across different platforms.


