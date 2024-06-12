/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 11:53:01 by mfeldman          #+#    #+#             */
/*   Updated: 2024/06/12 18:22:47 by mfeldman         ###   ########.fr       */
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

	// for (size_t i = 0; i < _fds.size(); ++i)
    //     close(_fds[i].fd);
    // _fds.clear();
}

void Server::handle_clients(int client_socket)
{
	// static std::map<int , std::string> clients;
	char buffer[BUFFER_MAX];
	int valread = recv(client_socket, buffer, sizeof(buffer) - 1, MSG_DONTWAIT);

    if (valread == -1 && errno != EWOULDBLOCK)
		return ; // Socket closed or error occurred + add error msg
	else if (valread == -1)
		return ; // couldnt read anything on this tick
	else if (valread == 0)
		return ; // client is leaving must close
	
	buffer[valread] = '\0';
	
	// clients[client_socket] += buffer;

	// std::string command(buffer);
	// std::cout << "command:\n " << command;

    std::vector<std::string> cmd_splited = split(command, '\n');
	// for (std::vector<std::string >::iterator it = cmd_splited.begin(); it != cmd_splited.end(); ++it)
	// 	std::cout << *it;
	
	std::cout << "cmd_splited[0]: " << cmd_splited[0] << std::endl;
	// cmd_splited[0].erase(cmd_splited[0].find_last_not_of(" \n\r\t")+1);
	// if (cmd_splited[0] == "CAP LS")
	// 	std::cout << "CAP LS OK" << std::endl;

	std::cout << "cmd_splited[1]: " << cmd_splited[1] << std::endl;
	// cmd_splited[1].erase(cmd_splited[1].find_last_not_of(" \n\r\t")+1);
	// if (cmd_splited[1] == "PASS")
	// 	std::cout << "PASS OK" << std::endl;

	// std::cout << "cmd_splited[2]:" << cmd_splited[2] << std::endl;
	// cmd_splited[2].erase(cmd_splited[2].find_last_not_of(" \n\r\t")+1);
	// if (cmd_splited[2] == "NICK")
	// 	std::cout << "NICK OK" << std::endl;

	// std::cout << "cmd_splited[3]:" << cmd_splited[3] << std::endl;
	// cmd_splited[3].erase(cmd_splited[3].find_last_not_of(" \n\r\t")+1);
	// if (cmd_splited[3] == "USER LS")
	// 	std::cout << "USER OK" << std::endl;

	// std::cout << "cmd_splited[1]size:" << cmd_splited[1].size() << std::endl;
	// std::cout << "PASS1: " << pass_string[0] << std::endl;
	// std::vector<std::string> pass_string = split(cmd_splited[1], ' ');
	// std::cout << "PASS2: " << pass_string[1] << std::endl;
	
	// std::vector<std::string> nick_string = split(cmd_splited[2], ' ');
	// std::cout << "NICK1: " << nick_string[0] << std::endl;
	// std::cout << "NICK2: " << nick_string[1] << std::endl;

	// std::vector<std::string> user_string = split(cmd_splited[3], ' ');
	// std::cout << "USER1: " << user_string[0] << std::endl;
	// std::cout << "USER2: " << user_string[1] << std::endl;
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

	// Client new_client(client_socket, client_addr);
	// _clients.push_back(new_client);
}

/* Run method that loop */

void Server::run()
{
	//readapt this fct for fds_active, not iter with _fds[i]
	
	ssize_t fds_active = poll(&_fds[0], _fds.size(), -1);
	if (fds_active == -1)
		throw (std::runtime_error("Error: poll() function failed"));

	if (_fds[0].revents & POLLIN)
        handle_new_connections();
	else
	{
		for (ssize_t i = 1; i < fds_active; ++i) 
            if (_fds[i].revents & POLLIN)
				handle_clients(_fds[i].fd);
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