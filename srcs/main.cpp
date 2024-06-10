/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 11:52:27 by mfeldman          #+#    #+#             */
/*   Updated: 2024/06/10 16:58:05 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

// bool signal_g = false;

int	main(int argc, char **argv)
{
	/* Catch the signals */
	
	std::signal(SIGINT, signal_handler); //ctrl + c
    // std::signal(SIGQUIT, signal_handler); //ctrl + / 
	
	try
	{
		parse_arg(argc, argv);
		Server IRC(std::atoi(argv[1]), argv[2]);
		
		IRC.init_server();

		// while (true) // tmp
		// 	std::cout << "Server OK" << std::endl;
		
	}
	catch (std::exception const &e)
	{std::cerr << e.what() << std::endl;}

	return (EXIT_SUCCESS);
	
}