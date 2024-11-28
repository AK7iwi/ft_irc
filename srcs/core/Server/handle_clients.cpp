/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_clients.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 07:00:01 by mfeldman          #+#    #+#             */
/*   Updated: 2024/11/28 07:03:49 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

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