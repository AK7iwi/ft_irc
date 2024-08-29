/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_check_and_manip.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 16:04:35 by mfeldman          #+#    #+#             */
/*   Updated: 2024/08/29 20:50:25 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmds_utils.hpp"

/* Create message */

static	std::string	create_message(std::vector<std::string> &s_command)
{
	std::string new_topic = s_command[2];
	if (new_topic[0] != ':')
		return (ERR_COLON);
	new_topic.erase(0, 1);
		
	for (size_t i = 3; i < s_command.size(); ++i)
        new_topic += " " + s_command[i];
		
	if (new_topic.empty())
		new_topic = "No topic is set";
	
	return (new_topic);
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