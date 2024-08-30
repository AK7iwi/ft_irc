/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_utils.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 12:22:54 by mfeldman          #+#    #+#             */
/*   Updated: 2024/08/30 12:48:20 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMDS_UTILS_HPP
#define CMDS_UTILS_HPP

#include "Server.hpp"

/* Create message, reason, topic*/

std::string	create_message(std::vector<std::string> &s_command, uint8_t s_command_size);

/* Check if the channel name is valid */

bool is_valid_prefix(std::string const &channel);

/* String method */

std::vector<std::string> split(std::string const &str, char delimiter);

#endif /* CMDS_UTILS_HPP */