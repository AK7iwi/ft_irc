/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 12:23:39 by mfeldman          #+#    #+#             */
/*   Updated: 2024/06/10 13:08:19 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.hpp"


/*Singal handler*/


/* Parse the argument */

void	parse_arg(int argc, char **argv)
{
	if (argc != 3)
		throw (std::invalid_argument("Usage: ./ircsrv <port> <password>"));

	int port = std::atoi(argv[1]);
    if (port <= 0 || port > 65535)
		throw (std::out_of_range("Error: Invalid port number. Please provide a port number between 1 and 65535."));

	std::string password = argv[2];
	//check if mandatory
    if (password.empty())
		throw (std::invalid_argument("Error: Password cannot be empty."));
}