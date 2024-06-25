/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 11:53:05 by mfeldman          #+#    #+#             */
/*   Updated: 2024/06/25 14:00:12 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

Client::Client(int socket_fd) :
	_socket_fd(socket_fd),
	_nickname("DEFAULT"),
	_username("DEFAULT"),
	_realname("DEFAULT"),
	_hostname("DEFAULT"),
	_buffer("")
{
	set_prefix();
	// fcntl(socket_fd, F_SETFL, O_NONBLOCK);
}

Client::~Client() {}

/* Getter methods */

int  				Client::get_socket()	const	{return (_socket_fd);}
std::string  const&	Client::get_nickname()	const	{return (_nickname);}
std::string  const&	Client::get_username()	const	{return (_username);}
std::string  const&	Client::get_realname()	const	{return (_realname);}
std::string  const&	Client::get_hostname()	const	{return (_hostname);}
std::string  const&	Client::get_prefix()	const	{return (_prefix);}
// std::string  const&	Client::get_buffer()	const	{return (_buffer);}

/* Setter method */

void				Client::set_prefix()						{_prefix = ":" + _nickname + "!" + _username + "@" + _hostname;}

// void				Client::set_buffer(std::string &tmp_buffer)	{_buffer = tmp_buffer;}

