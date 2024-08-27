/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 12:23:39 by mfeldman          #+#    #+#             */
/*   Updated: 2024/08/27 15:39:00 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.hpp"

/* Check if client is in invite client list */

bool	Server::is_client_in_invite_list(int client_socket, Channel *channel)
{
	bool found_client = false;
	
	std::vector <Client*> cpy = channel->get_invited_clients_of_chan();
	for (size_t j = 0; j < cpy.size(); ++j)
		if (client_socket == cpy[j]->get_socket())
			found_client = true;

	return (found_client);
}

/* Split method */

std::vector<std::string> split(std::string const &str, char delimiter) 
{
    std::vector<std::string> tokens;
    std::stringstream ss(str);
    std::string token; 

    while (std::getline(ss, token, delimiter))
        tokens.push_back(token);

    return (tokens);
}

/* Parse the argument */

void	parse_arg(int argc, char **argv)
{
	if (argc != 3)
		throw (std::invalid_argument("Usage: ./ircsrv <port> <password>"));

	int port = std::atoi(argv[1]);
    if (port < 1024 || port > 49551)
		throw (std::out_of_range("Error: Invalid port number. Please provide a port number between 1 and 65535"));

	std::string password = argv[2];
    if (password.length() < 6)
		throw (std::invalid_argument("Error: Password cannot have less than 6 char"));
}
