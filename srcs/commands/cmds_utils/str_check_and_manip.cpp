/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_check_and_manip.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 16:04:35 by mfeldman          #+#    #+#             */
/*   Updated: 2024/09/02 21:48:49 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmds_utils.hpp"

/* Basic check */

// bool	Server::

/* Create message, reason, topic, comment*/
std::string	create_message(std::vector<std::string> &s_command, uint8_t s_command_size)
{
	std::string message = "";
	
	if (s_command.size() >= s_command_size) 
	{
		message = s_command[s_command_size - 1];
		if (message[0] != ':')
			return (ERR_COLON);
		message.erase(0, 1);
		
		for (size_t i = s_command_size; i < s_command.size(); ++i)
        	message += " " + s_command[i];
	}
	
	return (message);
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