/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 12:23:39 by mfeldman          #+#    #+#             */
/*   Updated: 2024/08/29 10:39:23 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.hpp"

/* Create message */

/* Send mesage to all client of a channel */

// void Server::send_rpl_to_channel(Channel *channel, std::vector<std::string> &reply_arg)
// {
	// std::vector <Client*> cpy = channel->get_clients_of_chan();
	// 	for (size_t i = 0; i <  cpy.size(); ++i)
// 		send_reply(cpy[i]->get_socket(), 2222, reply_arg);
// }
	
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

/* Check if the channel name is valid */

bool is_valid_prefix(std::string const &channel) 
{return (channel[0] == '#' || channel[0] == '&');}

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
