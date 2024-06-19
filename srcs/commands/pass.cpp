/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 16:50:12 by mfeldman          #+#    #+#             */
/*   Updated: 2024/06/19 17:07:27 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"


void Server::pass(std::string &password)
{
	std::cout << "Enter into pass fct" << std::endl;
	if (password != _password)
		std::cout << "RPL" << std::endl;
}