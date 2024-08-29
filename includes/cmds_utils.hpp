/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_utils.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 12:22:54 by mfeldman          #+#    #+#             */
/*   Updated: 2024/08/29 16:43:35 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMDS_UTILS_HPP
#define CMDS_UTILS_HPP

#include "Server.hpp"

/* Check if the channel name is valid */

bool is_valid_prefix(std::string const &channel);

/* String method */

std::vector<std::string> split(std::string const &str, char delimiter);

#endif /* CMDS_UTILS_HPP */