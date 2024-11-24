/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 11:53:10 by mfeldman          #+#    #+#             */
/*   Updated: 2024/11/24 16:51:44 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

#include <csignal>
#include <sstream>
#include <iostream>
#include <vector>
#include "cmds_utils.hpp"
#include <stdlib.h>
#include <stdint.h>
#include <stdlib.h>
#include <cstring>
#include <fcntl.h>
#include <map>
#include <string>
#include <errno.h>
#include <poll.h>
#include <netinet/in.h>
#include <unistd.h>
#include "Client.hpp"
#include "Channel.hpp"

#define BUFFER_MAX	4096
#define ERR_COLON 	"You should set the reason with a ""':'"""

/* Modes */
#define MODE_L		1
#define MODE_I		2
#define MODE_K		3
#define MODE_T		4
#define MODE_O		5

class Client;
class Channel;

class Server 
{
	public:
		/* Constructors and destructors */
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
		std::string					_network_name;
		std::string					_server_name;
		std::string					_version;
		std::string             	_start_time;
		/* Struct for init server */
		struct sockaddr_in6			_server_addr;
		/* Socket of the server */
		int 						_server_socket;
		/* Vector of fds */
		std::vector<struct pollfd>	_fds;
		/* Map of clients */
		std::map<int, Client*> 		_clients;
		/* Map of channels */
		std::vector<Channel*>		_channels;

		//////////////////// Methods ////////////////////////////
		
		/* Utils methods for cmds */
		
		/* Send rpl to the all channel */
		void 		send_rpl_to_channel(Channel *channel, int rpl, std::vector<std::string> &reply_arg);
		/* Check if the channel exist and the client is in method */
		Channel*	is_client_in_a_valid_chan(int client_socket, std::string &channel, std::vector<std::string> &reply_arg);
		/* Check prerequisites*/
		bool		check_prerequisites(int client_socket, std::vector<std::string> &s_command, std::vector<std::string> &reply_arg);

		/* RPL methods */
		std::string	wich_rpl(Client *client, uint16_t rpl, std::vector<std::string> const &reply_arg);
		void		send_reply(int client_socket, uint16_t rpl, std::vector<std::string> const &reply_arg);
		
		/* Commands methods*/
		
		/* Mode */
		void 								mode_O(int client_socket, Channel *channel, uint8_t mode, std::string const &param_mode, std::vector<std::string> &reply_arg);
		void 								mode_T(Channel *channel, uint8_t mode);
		void 								mode_K(int client_socket, Channel *channel, uint8_t mode, std::string const &param_mode, std::vector<std::string> &reply_arg);
		void 								mode_I(Channel *channel, uint8_t mode);
		void 								mode_L(int client_socket, Channel *channel, uint8_t mode, std::string const &param_mode, std::vector<std::string> &reply_arg);
		void								handle_modes(int client_socket, Channel *channel, int8_t mode, std::string &param_mode, std::vector<std::string> &reply_arg);
		int8_t								parse_mode(std::string &mode);
		/* Invite */
		void 								handle_invite(int client_socket, Channel *channel, std::vector<std::string> &s_command, std::vector<std::string> &reply_arg);
		/* Kick */
		void 								kicked(int client_socket_to_kick, Channel *channel, std::vector<std::string> &reply_arg);
		void								handle_kick(int client_socket, Channel *channel, std::vector<std::string> &s_command, std::vector<std::string> &reply_arg);
		/* Part */
		void 								goodbye(int client_socket, Channel *channel, std::vector<std::string> &reply_arg);
		void								handle_part(int client_socket, std::vector<std::string> potential_channels, std::vector<std::string> &s_command, std::vector<std::string> &reply_arg);
		/* Topic */
		void 								set_new_topic(int client_socket, Channel *channel, std::vector<std::string> &s_command, std::vector<std::string> &reply_arg);
		void 								return_topic(int client_socket, Channel *channel, std::vector<std::string> &reply_arg);
		/* Privsmsg */
		void								send_message(int client_socket, std::string &target, std::vector<std::string> &reply_arg);
		/* Join */
		void								join_zero(int client_socket);
		void 								create_new_channel(int client_socket, std::string const &channel_name, std::string const &key, std::vector<std::string> &reply_arg);
		void 								add_client(int client_socket, Channel *channel, std::vector<std::string> &reply_arg);
		bool 								check_client_access(int client_socket, Channel *channel, std::string const &key, std::vector<std::string> &reply_arg);
		void								handle_join(int client_socket, std::map<std::string, std::string> m_channel_key, std::vector<std::string> &reply_arg);
		std::map<std::string, std::string>	create_channel_map(std::vector<std::string> const &valid_channels, std::vector<std::string> &s_command);
		std::vector<std::string> 			get_valid_channels(int client_socket, std::string const &potential_new_channels, std::vector<std::string> &reply_arg);

		/* Commands */
		
		void 		kick(int client_socket, std::vector<std::string> &s_command);
		void 		invite(int client_socket, std::vector<std::string> &s_command);
		void		topic(int client_socket, std::vector<std::string> &s_command);
		void		part(int client_socket, std::vector<std::string> &s_command);
		void		mode(int client_socket, std::vector<std::string> &s_command);
		void 		privmsg(int client_socket, std::vector<std::string> &s_command);
		void		pong();
		void		ping(int client_socket, std::vector<std::string> &s_command);
		void		join(int client_socket, std::vector<std::string> &s_command);
		void 		user(int client_socket, std::vector<std::string> &s_command);
		void 		nick(int client_socket, std::vector<std::string> &s_command);
		void		pass(int client_socket, std::vector<std::string> &s_command);

		/* Server methods */

		/* Remove channel*/
		void 		remove_channel(Channel *channel);
		/* Remove client method */
		void		remove_client(int client_socket);
		/* Handle commands */
		bool 		handle_commands(int client_socket, std::string &command);
		/* Handle client method */
		void		handle_clients(int client_cocket);
		void		handle_new_connections();
		/* Init struct address */
		void		init_address_structures();
};

#endif /* SERVER_HPP */