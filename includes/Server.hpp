/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 11:53:10 by mfeldman          #+#    #+#             */
/*   Updated: 2024/07/16 10:39:54 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

#include "utils.hpp"
#include "Client.hpp"
#include "Channel.hpp"
#include <iostream>
#include <stdlib.h>
#include <stdint.h>
#include <cstring>
#include <fcntl.h>
#include <vector>
#include <map>
#include <string>
#include <errno.h>
#include <poll.h>
#include <netinet/in.h>


#define BUFFER_MAX	4096
#define CLIENT_MAX 5

class Client;
class Channel;

class Server 
{
	public:
		Server(uint16_t port, std::string const &password);
		~Server();
		
		/* Main loop */
		void		run();

		/* Init the Server */
		void		init_server();

	private:
		/////////////////// Member variable ///////////////////
		
		/* Server infos */
		uint16_t 					_port;
    	std::string					_password;
		std::string					_networkname;
		std::string					_servername;
		std::string					_version;
		std::string             	_start_time;

		/* Struct for init server */
		struct sockaddr_in6					_server_addr;
		
		/* Socket of the server */
		int 								_server_socket;

		/* Vector of fds */
		std::vector<struct pollfd>			_fds;

		/* Map of clients */
		std::map<int, Client*> 				_clients;
		
		/* Map of channels */
		std::vector<Channel*>				_channels;

		//////////////////// Methods ////////////////////////////
		
		/* Remove client method */
		void		remove_client(int client_socket);
		
		/* Send response to the client */
		std::string	wich_rpl(Client *client, uint16_t rpl, std::vector<std::string> const &reply_arg);
		void		send_reply(int client_socket, uint16_t rpl, std::vector<std::string> const &reply_arg); 
		
		/* Commands */
		void		topic(int client_socket, std::vector<std::string> &s_command);
		void		part(int client_socket, std::vector<std::string> &s_command);
		void		pong();
		void		ping(int client_socket, std::vector<std::string> &s_command);
		void		join(int client_socket, std::vector<std::string> &s_command);
		void 		user(int client_socket, std::vector<std::string> &s_command);
		void 		nick(int client_socket, std::vector<std::string> &s_command);
		void		pass(int client_socket, std::vector<std::string> &s_command);
		
		/* Handle commands */
		void 		handle_commands(int client_socket, std::string &command);
		
		/* Handle client method */
		void		handle_clients(int client_cocket);
		void		handle_new_connections();
		
		/////////////////// Utils methods for Server///////////////
		
		/* Topic utils */
		void 								send_topic(int client_socket, Channel *channel, std::vector<std::string> &reply_arg);
		/* Part utils */
		void 								leave(int client_socket, Channel *channel, std::vector<std::string> &reply_arg, std::vector<std::string> &s_command);
		/* Join utils */
		void 								add_client(int client_socket, Channel *channel, std::vector<std::string> &reply_arg);
		std::map<std::string, std::string>	create_channel_map(int client_socket, std::vector<std::string> &s_command, std::vector<std::string> &reply_arg);
		/* Init struct address */
		void		init_address_structures();
};

#endif /* SERVER_HPP */