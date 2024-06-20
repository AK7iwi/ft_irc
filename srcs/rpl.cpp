/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rpl.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 19:59:26 by mfeldman          #+#    #+#             */
/*   Updated: 2024/06/20 03:49:49 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rpl.hpp"

// /* 001 */
// std::string	RPL_WELCOME(Client const *client, std::string const &networkname, std::string const &servername) 
// {return (":" + _servername + " 001 " + client->get_nickname() + " :Welcome to the " + _networkname + " Network, " + client->get_nickname() + "[!" + client->get_clientname() + "@" + client->get_hostname() + "]");}

// /* 002 */
// std::string	RPL_YOURHOST(Client const *client, std::string const &servername, std::string const &version) 
// {return (":" + _servername + " 002 " + client->get_nickname() + " :Your host is "+ _servername + ", running version " + _version);}

// /* 003 */
// std::string	RPL_CREATED(Client const *client, std::string const &start_time, std::string const &servername) 
// {return (":" + _servername + " 003 " + client->get_nickname() + " :This server was created " + _start_time);}

// /* 004 */
// std::string	RPL_MYINFO(Client const *client, std::string const &servername, std::string const &version) 
// {return (":" + _servername + " 004 " + client->get_nickname() + " " + _servername + " " + _version + "\n[ -k -i -o -t -l ] [ -k -o -l ]");}

// /* 221 */
// std::string RPL_UMODEIS(const client *client, const std::vector<std::string> &reply_arg) 
// {return (client->get_prefix() + " 221 " + reply_arg[0]);}

// /* 324 */
// std::string RPL_CHANNELMODEIS(const std::vector<std::string> &reply_arg) 
// {return (reply_arg[1] + " " + reply_arg[2] + " " + reply_arg[0]);}

// /* 332 */
// std::string RPL_TOPIC(const client *client, const std::vector<std::string> &reply_arg) 
// {return (":" + client->get_hostname() + " 332 " + client->get_nickname() + " " + reply_arg[1] + " :" + reply_arg[2]);}

// /* 341 */
// std::string RPL_INVITING(const client *client, const std::vector<std::string> &reply_arg) 
// {return (client->get_prefix() + " 341 " + reply_arg[0] + " :" + reply_arg[1]);}

// /* 366 */
// std::string	RPL_ENDOFNAMES(const client *client, const std::vector<std::string> &reply_arg) 
// {return (client->get_prefix() + " 366 " + reply_arg[0] + " :End of /NAMES list");}

// /* 401 */
// std::string	ERR_NOSUCHNICK(const client *client, const std::vector<std::string> &reply_arg) 
// {return (client->get_prefix() + " 401 " + reply_arg[0] + " :No such nick/channel");}

// /* 403 */
// std::string	ERR_NOSUCHCHANNEL(const client *client, const std::vector<std::string> &reply_arg) 
// {return (client->get_prefix() + " 403 " + reply_arg[0] + " :No such channel");}

// /* 404 */
// std::string	ERR_CANNOTSENDTOCHAN(const client *client, const std::vector<std::string> &reply_arg) 
// {return (client->get_prefix() + " 404 " + reply_arg[0] + " :Cannot send to channel");}

// /* 411 */
// std::string	ERR_NORECIPIENT(const client *client, const std::vector<std::string> &reply_arg) 
// {return (client->get_prefix() + " 411 :No recipient given (" + reply_arg[0] + ")");}

// /* 412 */
// std::string	ERR_NOTEXTTOSEND(const client *client) 
// {return (client->get_prefix() + " 412 :No text to send");}

// /* 431 */
// std::string	ERR_NONICKNAMEGIVEN(const client *client) 
// {return (client->get_prefix() + " 431 :No nickname given");}

// /* 432 */
// std::string	ERR_ERRONEUSNICKNAME(const client *client, const std::vector<std::string> &reply_arg) 
// {return (client->get_prefix() + " 432 " + reply_arg[0] + " :Erroneus nickname");}

// /* 433 */
// std::string	ERR_NICKNAMEINUSE(const client *client, const std::vector<std::string> &reply_arg)
// {return (client->get_prefix() + " 433 " + reply_arg[0] + " :Nickname is already in use");}

// /* 441 */
// std::string	ERR_clientNOTINCHANNEL(const client *client, const std::vector<std::string> &reply_arg)
// {return (client->get_prefix() + " 441 " + reply_arg[0] + " " + reply_arg[1] + " :They aren't on that channel");}

// /* 442 */
// std::string	ERR_NOTONCHANNEL(const client *client, const std::vector<std::string> &reply_arg)
// {return (client->get_prefix() + " 442 " + reply_arg[0] + " :You're not on that channel");}

// /* 443 */
// std::string	ERR_clientONCHANNEL(const client *client, const std::vector<std::string> &reply_arg)
// {return (client->get_prefix() + " 443 " + reply_arg[0] + " " + reply_arg[1] + " :is already on channel");}

// /* 451 */
// std::string	ERR_NOTREGISTERED(const client *client)
// {return (client->get_prefix() + " 451 :You have not registered");}

// /* 461 */
// std::string	ERR_NEEDMOREPARAMS(const client *client, const std::vector<std::string> &reply_arg)
// {return (client->get_prefix() + " 461 " + reply_arg[0] + " :Not enough parameters");}

// /* 462 */
// std::string	ERR_ALREADYREGISTERED(const client *client)
// {return (client->get_prefix() + " 462 :You may not reregister");}

// /* 464 */
// std::string	ERR_PASSWDMISMATCH(const client *client)
// {return (client->get_prefix() + " 464 :Password incorrect");}

// /* 471 */
// std::string	ERR_CHANNELISFULL(const client *client, const std::vector<std::string> &reply_arg)
// {return (":" + client->get_hostname() + " 471 " + client->get_nickname() + " " + reply_arg[0] + " :Cannot join channel (+l)");}

// /* 473 */
// std::string	ERR_INVITEONLYCHAN(const client *client, const std::vector<std::string> &reply_arg)
// {return (":" + client->get_hostname() + " 473 " + client->get_nickname() + " " + reply_arg[0] + " :Cannot join channel (+i)");}

// /* 474 */
// std::string	ERR_BANNEDFROMCHAN(const client *client, const std::vector<std::string> &reply_arg)
// {return (client->get_prefix() + " 474 " + reply_arg[0] + " :Cannot join channel (+b)");}

// /* 475 */
// std::string	ERR_BADCHANNELKEY(const client *client, const std::vector<std::string> &reply_arg)
// {return (":" + client->get_hostname() + " 475 " + client->get_nickname() + " " + reply_arg[0] + " :Cannot join channel (+k)");}

// /* 476 */
// std::string	ERR_BADCHANMASK(const std::vector<std::string> &reply_arg)
// {return ("476 " + reply_arg[0] + " :Bad Channel Mask");}

// /* 482 */
// std::string	ERR_CHANOPRIVSNEEDED(const client *client, const std::vector<std::string> &reply_arg)
// {return (client->get_prefix() + " 482 " + reply_arg[0] + " :You're not channel operator");}

// /* 501 */
// std::string	ERR_UMODEUNKNOWNFLAG(const client *client)
// {return (client->get_prefix() + " 501 :Unknown MODE flag");}

// /* 502 */
// std::string	ERR_clientSDONTMATCH(const client *client)
// {return (client->get_prefix() + " 502 :Cant change mode for other clients");}

// /* 696 */
// std::string	ERR_INVALIDMODEPARAM(const client *client, const std::vector<std::string> &reply_arg)
// {return (client->get_prefix() + " 696 " + reply_arg[0] + " " + reply_arg[1] + " " + reply_arg[2] + " " + reply_arg[3]);}

// /* 1001 */
// std::string	PER_NICKNAMECHANGE(const std::vector<std::string> &reply_arg)
// {return (reply_arg[0] + " NICK " + reply_arg[1]);}

// /* 1002 */
// std::string	PER_SENDMESSAGETOCHANNEL(const std::vector<std::string> &reply_arg)
// {return (reply_arg[0] + " " + reply_arg[1] + " " + reply_arg[2] + " :" + reply_arg[3]);}

std::string wich_rpl(uint16_t rpl)
{
	std::string reply;
	
	switch(rpl)
	{

        // case   1: reply = CREATE_RPL_WELCOME(_users[fd], _networkname, _servername);    break;
        // case   2: reply = CREATE_RPL_YOURHOST(_users[fd], _servername, _version);       break;
        // case   3: reply = CREATE_RPL_CREATED(_users[fd], _start_time, _servername);     break;
        // case   4: reply = CREATE_RPL_MYINFO(_users[fd], _servername, _version);         break;
        // case 221: reply = CREATE_RPL_UMODEIS(_users[fd], reply_arg);                    break;
        // case 324: reply = CREATE_RPL_CHANNELMODEIS(reply_arg);                          break;
        // case 332: reply = CREATE_RPL_TOPIC(_users[fd], reply_arg);                      break;
        // case 341: reply = CREATE_RPL_INVITING(_users[fd], reply_arg);                   break;
        // case 366: reply = CREATE_RPL_ENDOFNAMES(_users[fd], reply_arg);                 break;
        // case 401: reply = CREATE_ERR_NOSUCHNICK(_users[fd], reply_arg);                 break;
        // case 403: reply = CREATE_ERR_NOSUCHCHANNEL(_users[fd], reply_arg);              break;
        // case 404: reply = CREATE_ERR_CANNOTSENDTOCHAN(_users[fd], reply_arg);           break;
        // case 411: reply = CREATE_ERR_NORECIPIENT(_users[fd], reply_arg);                break;
        // case 412: reply = CREATE_ERR_NOTEXTTOSEND(_users[fd]);                          break;
        // case 441: reply = CREATE_ERR_USERNOTINCHANNEL(_users[fd], reply_arg);           break;
        // case 442: reply = CREATE_ERR_NOTONCHANNEL(_users[fd], reply_arg);               break;
        // case 443: reply = CREATE_ERR_USERONCHANNEL(_users[fd], reply_arg);              break;
        // case 451: reply = CREATE_ERR_NOTREGISTERED(_users[fd]);                         break;
        // case 461: reply = CREATE_ERR_NEEDMOREPARAMS(_users[fd], reply_arg);             break;
        // case 462: reply = CREATE_ERR_ALREADYREGISTERED(_users[fd]);                     break;
        // case 464: reply = CREATE_ERR_PASSWDMISMATCH(_users[fd]);                        break;
        // case 431: reply = CREATE_ERR_NONICKNAMEGIVEN(_users[fd]);                       break;
        // case 432: reply = CREATE_ERR_ERRONEUSNICKNAME(_users[fd], reply_arg);           break;
        // case 433: reply = CREATE_ERR_NICKNAMEINUSE(_users[fd], reply_arg);              break;
        // case 471: reply = CREATE_ERR_CHANNELISFULL(_users[fd], reply_arg);              break;
        // case 475: reply = CREATE_ERR_BADCHANNELKEY(_users[fd], reply_arg);              break;
        // case 482: reply = CREATE_ERR_CHANOPRIVSNEEDED(_users[fd], reply_arg);           break;
        // case 473: reply = CREATE_ERR_INVITEONLYCHAN(_users[fd], reply_arg);             break;
        // case 476: reply = CREATE_ERR_BADCHANMASK(reply_arg);                            break;
        // case 501: reply = CREATE_ERR_UMODEUNKNOWNFLAG(_users[fd]);                      break;
        // case 502: reply = CREATE_ERR_USERSDONTMATCH(_users[fd]);                        break;
        // case 696: reply = CREATE_ERR_INVALIDMODEPARAM(_users[fd], reply_arg);           break;
        // case 1001: reply = CREATE_PER_NICKNAMECHANGE(reply_arg);                        break;
        // case 1002: reply = CREATE_PER_SENDMESSAGETOCHANNEL(reply_arg);                  break;
    }
	
	return (reply);
}

void Server::send_reply(int client_socket, uint16_t rpl) 
{
	std::string message = wich_rpl(rpl) + "\r\n";

    if (send(client_socket, message.c_str(), message.length(), 0) == -1)
		return ;
}