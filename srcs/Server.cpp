/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 11:53:01 by mfeldman          #+#    #+#             */
/*   Updated: 2024/06/20 22:19:32 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

Server::Server(uint16_t port, std::string const &password) : 
    _port(port),
    _password(password),
	_networkname("AAAA"),
	_servername("BBBB"),
	_version("-5"),
	_void_str("")
{
	time_t  now = time(0);
    tm      *ltm = localtime(&now);
    char    date[32];

    strftime(date, sizeof(date), "%Y-%m-%d %H:%M:%S", ltm);
    _start_time = std::string(date);
	
	init_address_structures();
}

Server::~Server() 
{
	if (_server_socket != -1)
		close(_server_socket);

	for (std::vector<struct pollfd>::iterator it = _fds.begin(); it != _fds.end(); ++it)
        close(it->fd);
    _fds.clear();

	for (std::map<int, Client*>::iterator it = _clients.begin(); it != _clients.end(); ++it)
        delete (it->second); 
    _clients.clear(); 
}

void Server::handle_commands(int client_socket, std::string &command)
{
	command.erase(command.find_last_not_of(" \n\r\t")+1);
	const char* command_char = command.c_str();
	std::vector<std::string> s_command = split(command_char, ' ');

	if (s_command[0] == "PASS")	
		pass(client_socket, s_command[1]);
	else if (s_command[0] == "NICK")
		nick(client_socket, s_command[1]);
	else if (s_command[0] == "client")
		user(client_socket, s_command[1]);
}

void Server::handle_clients(int client_socket)
{

	std::cout << "Handle client nb :" << client_socket << std::endl << std::endl;
	
	char buffer[BUFFER_MAX];
	std::string	tmp_buffer;
	
	int valread = recv(client_socket, buffer, sizeof(buffer) - 1, 0); //check recv flag
    if (valread == -1 && errno != EWOULDBLOCK)
		return ; // Socket closed or error occurred + add error msg
	else if (valread == -1)
		return ; // couldnt read anything on this tick
	else if (valread == 0)
		return (remove_client(client_socket));
	
	buffer[valread] = '\0';

	tmp_buffer =+ buffer;

    std::vector<std::string> commands = split(tmp_buffer, '\n');
	uint8_t len_command = commands.size();
	for (uint8_t i = 0; i < len_command; ++i)
		handle_commands(client_socket, commands[i]);

	std::cout << std::endl;
}

void Server::handle_new_connections()
{
	struct sockaddr_in6 client_addr;
	memset(&client_addr, 0, sizeof(client_addr));
	socklen_t client_len = sizeof(client_addr);
    int	client_socket = accept(_server_socket, (struct sockaddr *)&client_addr, &client_len);
    if (client_socket == -1)
	{
		std::cout << "Error: accept() function failed" << std::endl;
        return ;
	}

	struct pollfd client_fd;
    client_fd.fd = client_socket;
    client_fd.events = POLLIN;
	client_fd.revents = 0;
    _fds.push_back(client_fd);
 
	_clients[client_socket] = new Client(client_socket);
}

/* Run method that loop */

void Server::run()
{
	if (poll(&_fds[0], _fds.size(), -1) == -1)
		throw (std::runtime_error("Error: poll() function failed, nobody listen to you"));

	if (_fds[0].revents & POLLIN)
        handle_new_connections();
	else
	{
		for (size_t i = 1; i < _fds.size(); ++i) 
            if (_fds[i].revents & POLLIN)
				handle_clients(_fds[i].fd);
	}
}

/* Init Server method */

void Server::init_server()
{
	_server_socket = socket(AF_INET6, SOCK_STREAM, 0);
    if (_server_socket == -1)
		throw (std::runtime_error("Error creating socket, even the server don't want to talk to you"));

	int opt = 1;
    if (setsockopt(_server_socket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1)
		throw (std::runtime_error("Error: failed to set option (SO_REUSEADDR) on socket"));
	if (fcntl(_server_socket, F_SETFL, O_NONBLOCK) == -1) 
		throw(std::runtime_error("Error: failed to set option (O_NONBLOCK) on socket"));
	if (bind(_server_socket, (struct sockaddr*)&_server_addr, sizeof(_server_addr)) == -1) 
		throw (std::runtime_error("Error binding socket"));
    if (listen(_server_socket, SOMAXCONN) == -1) 
		throw (std::runtime_error("Error listening on socket"));
	
	struct pollfd server_fd;
    server_fd.fd = _server_socket;
    server_fd.events = POLLIN;
	server_fd.revents = 0;
    _fds.push_back(server_fd);
}
