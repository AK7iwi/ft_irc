/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 11:53:01 by mfeldman          #+#    #+#             */
/*   Updated: 2024/11/28 08:39:03 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

Server::Server(uint16_t port, std::string const &password) : 
    _port(port),
    _password(password),
	_network_name("Black_Market"),
	_server_name("No_Rules"),
	_version("Jailbreak 1.33")
{init_server();}

Server::~Server() 
{
	for (std::vector<struct pollfd>::iterator it = _fds.begin(); it != _fds.end(); it++)
        close(it->fd);
    _fds.clear();

	for (std::map<int, Client*>::iterator it = _clients.begin(); it != _clients.end(); it++)
        delete (it->second); 
    _clients.clear();

	for (std::vector<Channel*>::iterator it = _channels.begin(); it != _channels.end(); it++)
        delete (*it); 
    _channels.clear(); 
}

void	Server::run()
{
	if (poll(&_fds[0], _fds.size(), -1) == -1)
		throw (std::runtime_error("Nobody listen to you"));

	if (_fds[0].revents & POLLIN)
        handle_new_connections();
	else
		for (size_t i = 1; i < _fds.size(); ++i) 
        	if (_fds[i].revents & POLLIN)
				handle_clients(_fds[i].fd);
}

void 	Server::init_time()
{
	time_t  now = time(0);
    tm      *ltm = localtime(&now);
    char    date[32];

    strftime(date, sizeof(date), "%Y-%m-%d %H:%M:%S", ltm);
    _start_time = std::string(date);
}

void 	Server::init_server_address()
{
    memset(&_server_addr, 0, sizeof(_server_addr));
    _server_addr.sin6_family = AF_INET6;
    _server_addr.sin6_port = htons(_port);
    _server_addr.sin6_addr = in6addr_any;
}

void	Server::init_server()
{
	std::cout << "Initialization of the server..." << std::endl;
	init_server_address();
	init_time();
	_server_socket = socket(AF_INET6, SOCK_STREAM, 0);
    if (_server_socket == -1)
		throw (std::runtime_error("Error creating socket, even the server doesn't want to talk to you"));

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
	
	std::cout << "The server is initialized..." << std::endl;
}
