/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 12:23:39 by mfeldman          #+#    #+#             */
/*   Updated: 2024/06/13 13:19:49 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.hpp"

std::vector<std::string> split(std::string const &str, char delimiter) 
{
    std::vector<std::string> tokens;
    std::stringstream ss(str);
    std::string token; 

    while (std::getline(ss, token, delimiter))
        tokens.push_back(token);

    return (tokens);
}

/* Signal handler */

void	signal_handler(int signal) 
{
    if (signal == SIGINT) 
	{
        std::cout << "\nCaught SIGINT (Ctrl+C), shutting down..." << std::endl;
		std::cout << "Server closed..." << std::endl;
        exit(EXIT_SUCCESS);
    } 
	else if (signal == SIGQUIT) //doesn't work
	{
        std::cout << "\nCaught SIGQUIT (Ctrl+/), shutting down..." << std::endl;
		std::cout << "Server closed..." << std::endl;
        exit(EXIT_SUCCESS);
    }
}

/* Parse the argument */

void	parse_arg(int argc, char **argv)
{
	if (argc != 3)
		throw (std::invalid_argument("Usage: ./ircsrv <port> <password>"));

	int port = std::atoi(argv[1]);
    if (port <= 0 || port > 65535)
		throw (std::out_of_range("Error: Invalid port number. Please provide a port number between 1 and 65535"));

	std::string password = argv[2];
    if (password.length() < 6)
		throw (std::invalid_argument("Error: Password cannot have less than 6 char"));
}