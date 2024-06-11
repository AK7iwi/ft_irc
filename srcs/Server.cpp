/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 11:53:01 by mfeldman          #+#    #+#             */
/*   Updated: 2024/06/11 16:16:55 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

Server::Server(uint16_t port, std::string const &password) : 
    _port(port),
    _password(password)
{init_address_structures();}

Server::~Server() 
{
	if (_server_socket != -1)
		close(_server_socket);
}

void Server::handle_client(int client_socket)
{
	char buffer[1024];
	int valread = recv(client_socket, buffer, sizeof(buffer) - 1, 0);

    if (valread == -1)
		return ; // Socket closed or error occurred

	buffer[valread] = '\0';
	std::string command(buffer);
    std::vector<std::string> cmd_splited = split(command, '\n');
}

void Server::handle_new_connections()
{
	struct sockaddr_in6 client_addr;
	memset(&client_addr, 0, sizeof(client_addr));
	socklen_t client_len = sizeof(client_addr);
    int	client_socket = accept(_server_socket, (struct sockaddr *)&client_addr,&client_len);
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

	Client new_client(client_socket, client_addr);
	// _clients.push_back(new_client);
}

void Server::run()
{
	while (true)
	{
		if (poll(&_fds[0], _fds.size(), -1) == -1)
			throw (std::runtime_error("Error: poll() function failed"));

		if (_fds[0].revents & POLLIN)
            handle_new_connections();
		else
		{
			for (size_t i = 1; i < _fds.size(); ++i) 
            	if (_fds[i].revents & POLLIN)
					handle_client(_fds[i].fd);
		}
		
	}
}

/* Init Server method */

void Server::init_server()
{
	_server_socket = socket(AF_INET6, SOCK_STREAM, 0);
    if (_server_socket == -1)
		throw (std::runtime_error("Error creating socket"));

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

/* Init struct address*/

void Server::init_address_structures()
{
    memset(&_server_addr, 0, sizeof(_server_addr));
    _server_addr.sin6_family = AF_INET6;
    _server_addr.sin6_port = htons(_port);
    _server_addr.sin6_addr = in6addr_any;
}