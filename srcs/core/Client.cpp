/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 11:53:05 by mfeldman          #+#    #+#             */
/*   Updated: 2024/09/03 15:19:58 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

Client::Client(int socket_fd) :
	_socket_fd(socket_fd),
	_buffer(""),
	_nickname(DEFAULT),
	_username(DEFAULT),
	_hostname(DEFAULT),
	_realname(DEFAULT),
	_valid_pass(false),
	_register(false)
{set_prefix();}

Client::~Client() {}

/* Channel method */

void	Client::leave_channel(Channel *channel) 
{
	for (std::vector<Channel*>::iterator it = _channels_of_client.begin(); it != _channels_of_client.end();)
	{
		if (channel == (*it))
			it = _channels_of_client.erase(it);
		else 
			++it;
	}
}

void 							Client::add_chan_to_client(Channel *channel) 		{_channels_of_client.push_back(channel);}

/* Checker */

bool 							Client::is_registered()				const			{return (_register);}
bool 							Client::is_pass_valid()				const			{return (_valid_pass);}

/* Getter methods */

std::vector<Channel*>	const&	Client::get_channels_of_client() 	const			{return (_channels_of_client);}
std::string  			const&	Client::get_realname()				const			{return (_realname);}
std::string  			const&	Client::get_hostname()				const			{return (_hostname);}
std::string  			const&	Client::get_username()				const			{return (_username);}
std::string  			const&	Client::get_nickname()				const			{return (_nickname);}
std::string  			const&	Client::get_prefix()				const			{return (_prefix);}
int 							Client::get_socket()				const			{return (_socket_fd);}
std::string  			const&	Client::get_buffer()				const			{return (_buffer);}

/* Setter method */

void 							Client::set_register()								{_register = true;}
void							Client::set_realname(std::string const &realname)	{_realname = realname;} 
void							Client::set_hostname(std::string const &hostname)	{_hostname = hostname;} 
void							Client::set_username(std::string const &username)	{_username = username;} 
void							Client::set_prefix()								{_prefix = ":" + _nickname + "!" + _username + "@" + _hostname;}
void							Client::set_nickname(std::string const &nickname)	{_nickname = nickname;} 
void 							Client::set_pass()									{_valid_pass = true;}
void 							Client::erase_buffer()								{_buffer.erase(0, _buffer.length());}
void 							Client::set_buffer(std::string const &buffer)		{_buffer += buffer;}
