/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 13:35:41 by mfeldman          #+#    #+#             */
/*   Updated: 2024/07/13 09:16:37 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void 	Server::leave(int client_socket, Channel *channel, std::vector<std::string> &reply_arg)
{
	channel->remove_from_chan(client_socket);
	_clients[client_socket]->leave_channel(channel);
	
	std::vector <Client*> cpy_clients_of_chan = channel->get_clients_of_chan();
	for (size_t i = 0; i <  cpy_clients_of_chan.size(); ++i)
		send_reply(cpy_clients_of_chan[i]->get_socket(), 4444, reply_arg);
}

std::string	Server::find_reason(std::vector<std::string> &s_command)
{
	std::string reason = "";

    size_t pos = std::string::npos; //0

	std::cout << "First loop: " << std::endl;
	
    for (size_t i = 0; i < s_command.size(); ++i) 
	{
		std::cout << "s_command[i]: " << s_command[i] << std::endl;
        if ((pos = s_command[i].find(":")) != std::string::npos) 
		{
            reason = s_command[i].substr(pos + 1);
            s_command[i] = s_command[i].substr(0, pos);
			
            for (size_t j = i + 1; j < s_command.size(); ++j)
                reason += " " + s_command[j];
			
            s_command.erase(s_command.begin() + i + 1, s_command.end());
            break;
        }
    }

	std::cout << "Second loop: " << std::endl;
	for (size_t i = 0; i < s_command.size(); ++i)
		std::cout << "s_command[i]: " << s_command[i] << std::endl;
	
	return (reason);
}

void	Server::part(int client_socket, std::vector<std::string> &s_command)
{
	std::vector<std::string>    reply_arg;
	
	reply_arg.push_back(s_command[0]);
	reply_arg.push_back(_clients[client_socket]->get_prefix());
	
	if (s_command.size() < 2)
		return (send_reply(client_socket, 461, reply_arg));
	
	// std::string reason = find_reason(s_command);

	std::string reason = "oui";

	std::cout << "Reason: " << reason << std::endl;
	
	for (size_t i = 0; i < s_command.size(); ++i)
	{	
		bool chan_found = false;
		std::cout << "s_command[1]" << s_command[1] << std::endl;
		reply_arg.push_back(s_command[i]);
		
		for (size_t j = 0; j < _channels.size(); ++j)
		{	
			if (s_command[i] == _channels[j]->get_chan_name())
			{
				chan_found = true;
				bool client_found = false;
				
				std::vector <Client*> cpy_clients_of_chan = _channels[j]->get_clients_of_chan();
				for (size_t k = 0; k < cpy_clients_of_chan.size(); ++k)
				{	
					if (client_socket == cpy_clients_of_chan[k]->get_socket())
					{
						client_found = true;
						reply_arg.push_back(reason);
						leave(client_socket, _channels[j], reply_arg);
						reply_arg.erase(reply_arg.begin() + 3);
						
						break;
					}
				}
				
				if (!client_found)
					send_reply(client_socket, 442, reply_arg);
				
				break;
			}
		}
			
		if (!chan_found)
			send_reply(client_socket, 403, reply_arg);

		reply_arg.erase(reply_arg.begin() + 2);
	}
}