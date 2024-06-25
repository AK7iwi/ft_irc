/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 11:53:05 by mfeldman          #+#    #+#             */
/*   Updated: 2024/06/25 17:12:59 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

Client::Client(int socket_fd) :
	_socket_fd(socket_fd),
	_nickname("DEFAULT"),
	_username("DEFAULT"),
	_realname("DEFAULT"),
	_hostname("DEFAULT"),
	_valid_pass(false)
{set_prefix();}

Client::~Client() {}

/* Getter methods */

int 				Client::get_valid_pass()	const	{return (_valid_pass);}
std::string  const&	Client::get_hostname()		const	{return (_hostname);}
std::string  const&	Client::get_realname()		const	{return (_realname);}
std::string  const&	Client::get_username()		const	{return (_username);}
std::string  const&	Client::get_nickname()		const	{return (_nickname);}
std::string  const&	Client::get_prefix()		const	{return (_prefix);}
int  				Client::get_socket()		const	{return (_socket_fd);}


/* Setter method */

void 				Client::set_valid_pass()							{_valid_pass = true;}
void				Client::set_nickname(std::string const &nickname)	{_nickname = nickname;} 
void				Client::set_prefix()								{_prefix = ":" + _nickname + "!" + _username + "@" + _hostname;}



