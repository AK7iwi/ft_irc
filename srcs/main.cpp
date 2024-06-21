/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 11:52:27 by mfeldman          #+#    #+#             */
/*   Updated: 2024/06/21 14:19:21 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

static bool is_running = true;

/* Signal handler */

void	signal_handler(int signal) 
{
    if (signal == SIGINT) 
	{
		is_running = false;
        std::cout << "\nCaught SIGINT (Ctrl+C), shutting down..." << std::endl;
		std::cout << "Server closed..." << std::endl;
		
    } 
	else if (signal == SIGQUIT) //doesn't work
	{
		is_running = false;
        std::cout << "\nCaught SIGQUIT (Ctrl+/), shutting down..." << std::endl;
		std::cout << "Server closed..." << std::endl;
    }
}

int	main(int argc, char **argv)
{
	/* Catch the signals */
	
	std::signal(SIGINT, signal_handler); //ctrl + c
    // std::signal(SIGQUIT, signal_handler); //ctrl + / 
	
	try
	{
		parse_arg(argc, argv);
		Server IRC(std::atoi(argv[1]), argv[2]);
		
		std::cout << "Initialization of the server..." << std::endl;
		IRC.init_server();
		std::cout << "The server is initialized..." << std::endl;
		std::cout << "Server launch..." << std::endl;
		while (is_running)
			IRC.run();
	}
	catch (std::exception const &e)
	{std::cerr << e.what() << std::endl;}

	std::cout << "Server closed..." << std::endl;
	
	return (EXIT_SUCCESS);
	
}