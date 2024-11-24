/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 11:53:01 by mfeldman          #+#    #+#             */
/*   Updated: 2024/11/24 17:36:51 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

Server::Server(uint16_t port, std::string const &password) : 
    _port(port),
    _password(password),
	_network_name("Black_Market"),
	_server_name("No_Rules"),
	_version("Jailbreak 1.33")
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

void 	Server::remove_channel(Channel *channel)
{
	for (std::vector<Channel*>::iterator it = _channels.begin(); it != _channels.end();)
	{
		if (channel == (*it))
		{
			delete (*it);
			it = _channels.erase(it);
		}
		else 
			++it;
	}
}

void	Server::remove_client(int client_socket)
{
	std::cout << "Get out of here " << _clients[client_socket]->get_nickname() << std::endl;
	
	join_zero(client_socket);
    close(client_socket);

	for (std::vector<struct pollfd>::iterator it = _fds.begin(); it != _fds.end(); ++it) 
	{
        if (it->fd == client_socket)
		{
            _fds.erase(it);
            break;
        }
    }

	delete (_clients[client_socket]);
    _clients.erase(_clients.find(client_socket));
}

bool	Server::handle_commands(int client_socket, std::string &command)
{
	command.erase(command.find_last_not_of(" \n\r\t") + 1);
	const char* command_char = command.c_str();
	std::vector<std::string> s_command = split(command_char, ' ');

	if (s_command.empty())
		return (0);
	else if (s_command[0][0] == '/')
		s_command[0].erase(0, 1);
	
	if (s_command[0] == "CAP")
		std::cout << "CAP LS" << std::endl;
	else if (s_command[0] == "PASS")
		return (pass(client_socket, s_command), 1);
	else if (s_command[0] == "NICK")
		return (nick(client_socket, s_command), 1);
	else if (s_command[0] == "USER")
		return (user(client_socket, s_command), 1);
	else if (s_command[0] == "JOIN")
		return (join(client_socket, s_command), 1);
	else if (s_command[0] == "PING")
		return (ping(client_socket, s_command), 1);
	else if (s_command[0] == "PONG")
		return (pong(), 1);
	else if (s_command[0] == "PART")
		return (part(client_socket, s_command), 1);
	else if (s_command[0] == "TOPIC")
		return (topic(client_socket, s_command), 1);
	else if (s_command[0] == "INVITE")
		return (invite(client_socket, s_command), 1);
	else if (s_command[0] == "KICK")
		return (kick(client_socket, s_command), 1);
	else if (s_command[0] == "PRIVMSG")
		return (privmsg(client_socket, s_command), 1);
	else if (s_command[0] == "MODE")
		return (mode(client_socket, s_command), 1);
	else
		std::cout << "Unknow command" << std::endl;

	return (0);
}

void	Server::handle_clients(int client_socket)
{	
	char buffer[BUFFER_MAX];
	
	int valread = recv(client_socket, buffer, sizeof(buffer) - 1, 0);
    if (valread == -1)
	{
		std::cout << "valread == -1" << std::endl;
		if (errno != EWOULDBLOCK)
			std::cout << "EWOULDBLOCK" << std::endl;
		return ; 
	}
	else if (valread == 0)
		return (remove_client(client_socket));
	
	buffer[valread] = '\0';
	
	_clients[client_socket]->set_buffer(buffer);

	std::cout << "Client Buffer: \n" << _clients[client_socket]->get_buffer() << std::endl;
	
    std::vector<std::string> commands = split(_clients[client_socket]->get_buffer(), '\n');
	for (uint8_t i = 0; i < commands.size(); i++)
		if (handle_commands(client_socket, commands[i])) // || _clients[client_socket]->get_buffer() == 4096 protect buffer 
			_clients[client_socket]->erase_buffer();
}

void	Server::handle_new_connections()
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

void	Server::init_server()
{
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
}

void 	Server::init_address_structures()
{
    memset(&_server_addr, 0, sizeof(_server_addr));
    _server_addr.sin6_family = AF_INET6;
    _server_addr.sin6_port = htons(_port);
    _server_addr.sin6_addr = in6addr_any;
}
