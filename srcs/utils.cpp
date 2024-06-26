/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 12:23:39 by mfeldman          #+#    #+#             */
/*   Updated: 2024/06/26 17:23:07 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.hpp"

bool	contains_invalid_chars(std::string const &nickname)
{
	if (nickname[0] == '$' || nickname[0] == ':' || nickname[0] == '#')
		return (true);

	std::string invalid_chars = " ,*?!@.";
	if (nickname.find_first_of(invalid_chars) != std::string::npos)
		return (true);
	
    return (false);
}

void Server::remove_client(int client_socket)
{
	std::cout << "Bouge de la " << _clients[client_socket]->get_nickname() <<std::endl;
	
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

std::vector<std::string> split(std::string const &str, char delimiter) 
{
    std::vector<std::string> tokens;
    std::stringstream ss(str);
    std::string token; 

    while (std::getline(ss, token, delimiter))
        tokens.push_back(token);

    return (tokens);
}

/* Init struct address*/

void Server::init_address_structures()
{
    memset(&_server_addr, 0, sizeof(_server_addr));
    _server_addr.sin6_family = AF_INET6;
    _server_addr.sin6_port = htons(_port);
    _server_addr.sin6_addr = in6addr_any;
}

/* Parse the argument */

void	parse_arg(int argc, char **argv)
{
	if (argc != 3)
		throw (std::invalid_argument("Usage: ./ircsrv <port> <password>"));

	int port = std::atoi(argv[1]);
    if (port <= 0 || port > 65535)
		throw (std::out_of_range("Error: Invalid port number. Please provide a port number between 1 and 65535"));

	std::string password = argv[2];
    if (password.length() < 6)
		throw (std::invalid_argument("Error: Password cannot have less than 6 char"));
}
