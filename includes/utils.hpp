/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 12:22:54 by mfeldman          #+#    #+#             */
/*   Updated: 2024/06/18 15:13:33 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
#define UTILS_HPP

#include "Server.hpp"
#include <csignal>
#include <iostream>
#include <vector>
#include <sstream>

/* String method */

std::vector<std::string> split(std::string const &str, char delimiter);

/* Signal handler */

void	signal_handler(int signal);

/* Parse arguments */

void	parse_arg(int argc, char **argv);

#endif /* UTILS_HPP */