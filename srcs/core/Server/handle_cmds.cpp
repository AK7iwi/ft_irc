/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cmds.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 06:59:50 by mfeldman          #+#    #+#             */
/*   Updated: 2024/11/28 07:04:07 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

bool	Server::handle_commands(int client_socket, std::string &command)
{
	command.erase(command.find_last_not_of(" \n\r\t") + 1);
	const char* command_char = command.c_str();
	std::vector<std::string> s_command = split(command_char, ' ');

	if (s_command.empty())
		return (0);
	else if (s_command[0][0] == '/')
		s_command[0].erase(0, 1);
	
	if (s_command[0] == "CAP")
		std::cout << "CAP LS" << std::endl;
	else if (s_command[0] == "PASS")
		return (pass(client_socket, s_command), 1);
	else if (s_command[0] == "NICK")
		return (nick(client_socket, s_command), 1);
	else if (s_command[0] == "USER")
		return (user(client_socket, s_command), 1);
	else if (s_command[0] == "JOIN")
		return (join(client_socket, s_command), 1);
	else if (s_command[0] == "PING")
		return (ping(client_socket, s_command), 1);
	else if (s_command[0] == "PONG")
		return (pong(), 1);
	else if (s_command[0] == "PART")
		return (part(client_socket, s_command), 1);
	else if (s_command[0] == "TOPIC")
		return (topic(client_socket, s_command), 1);
	else if (s_command[0] == "INVITE")
		return (invite(client_socket, s_command), 1);
	else if (s_command[0] == "KICK")
		return (kick(client_socket, s_command), 1);
	else if (s_command[0] == "PRIVMSG")
		return (privmsg(client_socket, s_command), 1);
	else if (s_command[0] == "MODE")
		return (mode(client_socket, s_command), 1);
	else
		std::cout << "Unknow command" << std::endl;

	return (0);
}