/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 11:52:27 by mfeldman          #+#    #+#             */
/*   Updated: 2024/12/02 22:58:11 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

static	void	parse_arg(int argc, char **argv)
{
	if (argc != 3)
		throw (std::invalid_argument("Usage: ./ircsrv <port> <password>"));

	int32_t port = std::atoi(argv[1]);
    if (port < 1024 || port >  65535)
		throw (std::out_of_range("Error: Invalid port number. Please provide a port number between 1024 and 65535"));

	std::string password = argv[2];
    if (password.length() < 6)
		throw (std::invalid_argument("Error: Password cannot have less than 6 char"));
}

static	void	signal_handler(int signal) 
{
    if (signal == SIGINT) 
	{
        std::cout << "\nCaught SIGINT (Ctrl+C), shutting down..." << std::endl;
		std::cout << "Server closed..." << std::endl;
    } 
	else if (signal == SIGQUIT)
	{
        (void)signal;
    }
}

int	main(int argc, char **argv)
{
	/* Catch the signals */
	std::signal(SIGINT, signal_handler); //ctrl + c
    std::signal(SIGQUIT, signal_handler); //ctrl + / 
	
	try
	{
		parse_arg(argc, argv);
		Server IRC(std::atoi(argv[1]), argv[2]);
		std::cout << "Server launch..." << std::endl;
		while (true)
			IRC.run();
	}
	catch (std::exception const &e)
	{std::cerr << e.what() << std::endl;}

	std::cout << "Server closed..." << std::endl;
	
	return (EXIT_SUCCESS);
}