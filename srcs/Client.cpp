/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 11:53:05 by mfeldman          #+#    #+#             */
/*   Updated: 2024/07/01 14:53:20 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

Client::Client(int socket_fd) :
	_socket_fd(socket_fd),
	_nickname("DEFAULT"),
	_username("DEFAULT"),
	_realname("DEFAULT"),
	_hostname("DEFAULT"),
	_valid_pass(false),
	_register(false)
{set_prefix();}

Client::~Client() {}

/* Checker */

bool 				Client::is_registered()		const	{return (_register);}
bool 				Client::is_valid_pass()		const	{return (_valid_pass);}

/* Getter methods */

std::string  const&	Client::get_hostname()		const	{return (_hostname);}
std::string  const&	Client::get_realname()		const	{return (_realname);}
std::string  const&	Client::get_username()		const	{return (_username);}
std::string  const&	Client::get_nickname()		const	{return (_nickname);}
std::string  const&	Client::get_prefix()		const	{return (_prefix);}
uint16_t  			Client::get_socket()		const	{return (_socket_fd);}

/* Setter method */

void 				Client::set_register()								{_register = true;}
void 				Client::set_valid_pass()							{_valid_pass = true;}
void				Client::set_hostname(std::string const &hostname)	{_hostname = hostname;} 
void				Client::set_realname(std::string const &realname)	{_realname = realname;} 
void				Client::set_username(std::string const &username)	{_username = username;} 
void				Client::set_nickname(std::string const &nickname)	{_nickname = nickname;} 
void				Client::set_prefix()								{_prefix = ":" + _nickname + "!" + _username + "@" + _hostname;}



