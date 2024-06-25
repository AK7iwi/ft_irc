/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rpl.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 01:54:19 by mfeldman          #+#    #+#             */
/*   Updated: 2024/06/25 16:33:15 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPL_HPP
#define RPL_HPP

#include "Client.hpp"
#include <string>
#include <stdint.h>
#include <vector>

class Server;
class Client;

/* 431 */
std::string	ERR_NONICKNAMEGIVEN(Client const *client);
/* 432 */
std::string	ERR_ERRONEUSNICKNAME(Client const *client, std::string const &nick);
/* 433 */
std::string	ERR_NICKNAMEINUSE(Client const *client, std::string const &nick);
/* 461 */
std::string	ERR_NEEDMOREPARAMS(Client const *client);
/* 462 */
std::string	ERR_ALREADYREGISTERED(Client const *client);
/* 464 */
std::string	ERR_PASSWDMISMATCH(Client const *client);

#endif /* RPL_HPP */