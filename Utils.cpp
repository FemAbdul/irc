/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabdul-k <fabdul-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 07:31:57 by fabdul-k          #+#    #+#             */
/*   Updated: 2024/08/20 07:31:59 by fabdul-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Libs.hpp"

void	sendIrcMsg(int fd, string nickname, string username, string message)
{
	string messageToSend = ":" + nickname + "!" + username + "@127.0.0.1 " + message + "\r\n";
	send(fd, messageToSend.c_str(), messageToSend.length() + 1, 0);
}

void	error(string error)
{
	std::cout << error << std::endl;
	exit(EXIT_FAILURE);
}