/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 17:44:58 by mfeldman          #+#    #+#             */
/*   Updated: 2024/07/19 17:11:47 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

//invite nickname channel
void 	Server::invite(int client_socket, std::vector<std::string> &s_command)
{
	std::vector<std::string>    reply_arg;
	
	reply_arg.push_back(s_command[0]);
	reply_arg.push_back(_clients[client_socket]->get_prefix());

	std::cout << "INVIIIIIIIIITE" << std::endl;
	if (!_clients[client_socket]->is_registered())
		return (send_reply(client_socket, 451, reply_arg)); 
	else if (s_command.size() < 3)
		return (send_reply(client_socket, 461, reply_arg));

	reply_arg.push_back(s_command[2]); //channel_name
	reply_arg.push_back(s_command[1]); // client_to_invite

	std::cout << "s_command[2]: " << s_command[2] << std::endl;
	Channel *channel = is_client_in_a_valid_chan(client_socket, s_command[2], reply_arg);
	if (!channel)
		return ;
	
	std::cout << "ouiiiii" << std::endl;
	std::vector <Client*> cpy = channel->get_clients_of_chan();
	for (size_t i = 0; i < cpy.size(); ++i)
	{
		if (s_command[1] == cpy[i]->get_nickname())
			return (send_reply(client_socket, 443, reply_arg));
	}
	send_reply(client_socket, 341, reply_arg);
	// send_reply(,341, reply_arg);
}