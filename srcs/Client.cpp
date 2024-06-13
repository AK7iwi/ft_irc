/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 11:53:05 by mfeldman          #+#    #+#             */
/*   Updated: 2024/06/13 17:17:04 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

Client::Client(int socket_fd, const sockaddr_in6& client_addr) :
	_socket_fd(socket_fd), 
	_client_addr(client_addr) {}

Client::~Client() {}


/* Getter methods */

int  				Client::get_socket()	const	{return (_socket_fd);}
sockaddr_in6 const&	Client::get_address()	const	{return (_client_addr);}
std::string  const&	Client::get_buffer()	const	{return (_buffer);}
