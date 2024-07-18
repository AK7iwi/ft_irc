// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   kick.cpp                                           :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2024/07/17 12:03:19 by mfeldman          #+#    #+#             */
// /*   Updated: 2024/07/18 14:07:09 by mfeldman         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "Server.hpp"

// void 	Server::kicked(int client_socket, Channel *channel, std::vector<std::string> &s_command, std::vector<std::string> &reply_arg)
// {
// 	std::string comment = "";
	
// 	if (s_command.size() >= 4) 
// 	{
// 		comment = s_command[3];
// 		if (comment[0] != ':')
// 		{
// 			std::cerr << "You should set the reason with a "":"" before bro, be rigorous please" << std::endl;
// 			return ;
// 		}
// 		comment.erase(0, 1);
		
// 		for (size_t i = 4; i < s_command.size(); ++i)
//         	comment += " " + s_command[i];
// 	}
// 	reply_arg.push_back(comment);
	
// 	std::vector <Client*> cpy = channel->get_clients_of_chan();
// 	for (size_t i = 0; i <  cpy.size(); ++i)
// 		send_reply(cpy[i]->get_socket(), 4444, reply_arg);
	
// 	reply_arg.erase(reply_arg.begin() + 3);
// 	(void)channel;
// 	(void)client_socket;
// 	// channel->remove_from_chan(client_socket); /
// 	// _clients[client_socket]->leave_channel(channel);
// }
// void 	Server::kick(int client_socket, std::vector<std::string> &s_command)
// {	
// 	std::vector<std::string>    reply_arg;
	
// 	reply_arg.push_back(s_command[0]);
// 	reply_arg.push_back(_clients[client_socket]->get_prefix());

// 	if (!_clients[client_socket]->is_registered())
// 		return (send_reply(client_socket, 451, reply_arg)); 
// 	else if (s_command.size() < 3)
// 		return (send_reply(client_socket, 461, reply_arg));

// 	reply_arg.push_back(s_command[1]);
// 	std::vector<std::string> clients_list = split(s_command[2], ',')

// 	bool chan_found = false;
	
// 	for (size_t i = 0; i < _channels.size(); ++i)
// 	{	
// 		if (s_command[1] == _channels[i]->get_chan_name())
// 		{
// 			chan_found = true;
// 			bool client_found = false;
				
// 			std::vector <Client*> cpy = _channels[i]->get_clients_of_chan();
// 			for (size_t j = 0; j < cpy.size(); ++j)
// 			{	
// 				if (client_socket == cpy[j]->get_socket())
// 				{
// 					client_found = true;
// 					bool client_target = false;
					
// 					for (size_t k = 0; k < clients_list.size(); ++k)
// 					{
// 						if (clients_list[k]->get_nickname())
// 						{
// 							client_target = true;
// 							kicked(client_socket, _channels[i], s_command, reply_arg);
// 							break ; 
// 						}
// 					}
// 					if (!client_target)
// 					{
// 						reply_arg.push_back(s_command[2]);
// 						send_reply(client_socket, 441, reply_arg);
// 						reply_arg.erase(reply_arg.begin() + 3);
// 					}
// 					break;
// 				}					
// 			}
			
// 			if (!client_found)
// 				send_reply(client_socket, 442, reply_arg);
// 			break;
// 		}
// 	}
		
// 	if (!chan_found)
// 		send_reply(client_socket, 403, reply_arg);
// }