/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 16:30:03 by mfeldman          #+#    #+#             */
/*   Updated: 2024/06/27 20:05:24 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include "Server.hpp"

class Channel 
{
	public:
		Channel();
		~Channel();

		/* Getter methods */
		std::string 	const	&get_chan_name() const;

	private:
		std::string 	_name;
		std::string 	_topic;

		// std::map<int, Client*> 		_clients_chan;


};


#endif /* CHANNEL_HPP */