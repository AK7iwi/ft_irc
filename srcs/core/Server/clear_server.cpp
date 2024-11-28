/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_server.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 06:59:09 by mfeldman          #+#    #+#             */
/*   Updated: 2024/11/28 07:04:25 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

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