/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_server.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 13:55:04 by mfeldman          #+#    #+#             */
/*   Updated: 2024/08/27 16:38:47 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

Channel*	Server::is_client_in_a_valid_chan(int client_socket, std::string &channel, std::vector<std::string> &reply_arg)
{
	Channel *null_chan = NULL;
	for (size_t i = 0; i < _channels.size(); ++i)
	{	
		if (channel == _channels[i]->get_channel_name())
		{
			std::vector <Client*> cpy = _channels[i]->get_clients_of_chan();
			for (size_t j = 0; j < cpy.size(); ++j)
				if (client_socket == cpy[j]->get_socket())
					return (_channels[i]);
			
			return (send_reply(client_socket, 442, reply_arg), null_chan);
		}
	}
		
	return (send_reply(client_socket, 403, reply_arg), null_chan);
}

void	Server::remove_client(int client_socket)
{
	std::cout << "Move fast " << _clients[client_socket]->get_nickname() <<std::endl;
	
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

	//PART from the chan also (leave_channels)
}

/* Init struct address*/ //utils??
void 	Server::init_address_structures()
{
    memset(&_server_addr, 0, sizeof(_server_addr));
    _server_addr.sin6_family = AF_INET6;
    _server_addr.sin6_port = htons(_port);
    _server_addr.sin6_addr = in6addr_any;
}