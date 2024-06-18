/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 12:23:39 by mfeldman          #+#    #+#             */
/*   Updated: 2024/06/18 16:12:02 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.hpp"

void Server::remove_client(int client_socket)
{
    close(client_socket); ///close a int???

	for (std::vector<struct pollfd>::iterator it = _fds.begin(); it != _fds.end(); ++it) 
	{
        if (it->fd == client_socket)
		{
            _fds.erase(it);
            break;
        }
    }

    std::map<int, Client*>::iterator it = _clients.find(client_socket);
    if (it != _clients.end()) 
	{
        delete (it->second);
        _clients.erase(it);
    }

	// std::cout << "Bouge de la" << _clients[client_socket]->get_nickname <<std::endl;
	std::cout << "Bouge de la " << client_socket << std::endl;
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

/* Signal handler */

void	signal_handler(int signal) 
{
    if (signal == SIGINT) 
	{
        std::cout << "\nCaught SIGINT (Ctrl+C), shutting down..." << std::endl;
		std::cout << "Server closed..." << std::endl;
        exit(EXIT_SUCCESS);
    } 
	else if (signal == SIGQUIT) //doesn't work
	{
        std::cout << "\nCaught SIGQUIT (Ctrl+/), shutting down..." << std::endl;
		std::cout << "Server closed..." << std::endl;
        exit(EXIT_SUCCESS);
    }
}