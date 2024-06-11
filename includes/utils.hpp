/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 12:22:54 by mfeldman          #+#    #+#             */
/*   Updated: 2024/06/11 14:55:34 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
#define UTILS_HPP

#include "Server.hpp"
#include <csignal>

/* Signal handler */

void	signal_handler(int signal);

/* Parse arguments */

void	parse_arg(int argc, char **argv);

#endif /* UTILS_HPP */