# ft_irc

An IRC server in C++ 98

## Overview 

ft_irc is a custom Internet Relay Chat (IRC) server. It is designed to handle multiple client connections and facilitate real-time communication over the IRC protocol. It adheres to the IRC protocol specifications, making it compatible with common IRC clients like irssi, allowing users to interact with the server through a familiar interface.

## Usage



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
- /PING Sent by the server to check if the client is still connected
- /PONG Response to a /PING command
- /JOIN Join a channel
- /INVITE Invites a user to join a specific channel
- /KICK Removes a user from a channel
- /TOPIC Sets or retrieves the topic of a channel
- /PART Leave a channel
- /PRIVMSG Send private messages to other users
- /MODE Sets or queries the mode of a user or channel

### 5) RPL (Error Handling)
The server implements error handling to ensure proper communication between clients and to provide meaningful feedback when commands fail or users encounter issues.

### 1) Server Core

### 2) Client management

### 3) Channel System

### 4) Command Parsing and Execution

### 5) RPL (Error handling)


