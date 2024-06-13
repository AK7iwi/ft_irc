/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 11:53:01 by mfeldman          #+#    #+#             */
/*   Updated: 2024/06/13 18:02:30 by mfeldman         ###   ########.fr       */
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

	for (size_t i = 0; i < _fds.size(); ++i)
        close(_fds[i].fd);
    _fds.clear();
}

void Server::handle_clients(int client_socket)
{
	char buffer[BUFFER_MAX];
	std::string	tmp_buffer;
	
	int valread = recv(client_socket, buffer, sizeof(buffer) - 1, 0); //check recv flag
    if (valread == -1 && errno != EWOULDBLOCK)
		return ; // Socket closed or error occurred + add error msg
	else if (valread == -1)
		return ; // couldnt read anything on this tick
	else if (valread == 0)
		return ; // client is leaving must close
	
	buffer[valread] = '\0';

	tmp_buffer = _clients[client_socket]->get_buffer();
	tmp_buffer =+ buffer;

	// std::cout << "TMPbuff:" << tmp_buffer << std::endl;
	
	// if (buffer < BUFFER_MAX)
	// 	_clients[client_socket] += buffer;
	// else 


	/* Replace buffer by tmp_buffer */
    // std::vector<std::string> command = split(buffer, '\n');
	
	// command[0].erase(command[0].find_last_not_of(" \n\r\t")+1);
	// std::cout << command[0] << std::endl;
	// command[1].erase(command[1].find_last_not_of(" \n\r\t")+1);
	// std::cout << command[1] << std::endl;
	// command[2].erase(command[2].find_last_not_of(" \n\r\t")+1);
	// std::cout << command[2] << std::endl;
	// command[3].erase(command[3].find_last_not_of(" \n\r\t")+1);
	// std::cout << command[3] << std::endl;

	// if (command[0] == "CAP LS")
	// 	std::cout << "Trop cool mon reuf" << std::endl;
}

void Server::handle_new_connections()
{
	struct sockaddr_in6 client_addr;
	memset(&client_addr, 0, sizeof(client_addr));
	socklen_t client_len = sizeof(client_addr);
    int	client_socket = accept(_server_socket, (struct sockaddr *)&client_addr, &client_len);
	std::cout << "client socket:" << client_socket << std::endl;
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
 
	_clients[client_socket] = new Client(client_socket, client_addr);
	std::cout << "get_socket test:" << _clients[client_socket]->get_socket() << std::endl;
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

/* Init struct address*/

void Server::init_address_structures()
{
    memset(&_server_addr, 0, sizeof(_server_addr));
    _server_addr.sin6_family = AF_INET6;
    _server_addr.sin6_port = htons(_port);
    _server_addr.sin6_addr = in6addr_any;
}