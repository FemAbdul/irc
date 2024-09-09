/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Libs.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabdul-k <fabdul-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 07:31:09 by fabdul-k          #+#    #+#             */
/*   Updated: 2024/08/20 07:31:13 by fabdul-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/uio.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <vector>
#include <algorithm>
#include <stdio.h>
#include <string>
#include <poll.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sstream>
#include <arpa/inet.h>
#include <map>
#include <set>
#include <sstream>


using std::string;
using std::vector;
using std::map;
using std::set;

#define BUFFER_SIZE 512
#define MAX_CONN 10

// COMMON ERRORS
#define ERR_NOTREGISTERED "451 *  :You have not registered\r\n"
#define ERR_UNKNOWNCOMMAND(command) ("421 *  " + command + " :Unknown command")
#define ERR_NEEDMOREPARAMS(command) ("461 *  " + command + " :Not enough parameters\n")

// PASS ERRORS
#define ERR_PASSWDMISMATCH "464 *  :Password incorrect\n"
#define ERR_ALREADYREGISTRED "462 *  :You may not reregister\n"

// NICK ERRORS
#define ERR_ERRONEUSNICKNAME(nick) ("432 *  " + nick + " :Erroneus nickname\r\n")
#define ERR_NICKNAMEINUSE(nick) ("433 *  " + nick + " :Nickname is already in use\r\n")

// PRIVMSG ERRORS
#define ERR_NORECIPIENT(command) ("411 * :No recipient given " + command + "\n")
#define ERR_NOTEXTTOSEND "412 *  :No text to send\n"
#define ERR_CANNOTSENDTOCHAN(channel) ("404 *  " + channel " :Cannot send to channel\n")
#define ERR_NOSUCHNICK(nick) ("401 *  " + nick + " :No such nick/channel\n")

// JOIN ERRORS
#define ERR_CHANNELISFULL(channel) ("471 *  " + channel + " :Cannot join channel (+l)\r\n")
#define ERR_TOOMANYCHANNELS(channel) ("405 *  " + channel + " :You have joined too many channels\r\n")
#define ERR_BADCHANNELKEY(channel) ("475 * " + channel + " :Cannot join channel (+k)\r\n")
#define ERR_INVITEONLYCHAN(channel) ("473 *  " + channel + " :Cannot join channel (+i)\r\n")

// PART and KICK ERRORS
#define ERR_NOSUCHCHANNEL(channel) ("403 *  " + channel + " :No such channel\n")
#define ERR_NOTONCHANNEL(channel) ("442 *  " + channel + " :You're not on that channel\r\n")
#define ERR_CHANOPRIVSNEEDED(channel) ("482 *  " + channel " :You're not channel operator\n")
#define	ERR_USER_NOT_IN_CHANNEL send(fd, "441 ERR_USERNOTINCHANNEL \r\n", 28, 0)


// MODE ERRORS
#define ERR_KEYSET(channel) ("467 *  " + channel + " :Channel key already set\r\n")
#define ERR_BADCHANMASK(channel) ("476 *  " + channel + " :Bad Channel Mask\r\n")
#define ERR_UNKNOWNMODE(mode) ("472 *  " + mode + " :is unknown mode char to me\r\n")
#define ERR_UMODEUNKNOWNFLAG(mode) ("501 *  " + mode + " :Unknown MODE flag\r\n")

// INVITE ERRORS
#define ERR_USERONCHANNEL(user, channel)("443 *  " + user + "" + channel " :is already on channel\r\n")

// GET_PASSED
#define NEW_USER(nickname, username) ("001 * Welcome to the Internet Relay Network " + nickname + "!" + username +"@127.0.0.1\r\n")
#define GET_USER_PASSED server.getUserMap(fd)->second.getUserPassed()
#define GET_NICK_PASSED server.getUserMap(fd)->second.getNickPassed()


// DEFINES
#define SEND_ABOUT_NEW_USER std::cout << "NEW USER! NICKNAME: " << "[" << server.getUserMap(fd)->second.getNickname() << "]" << " USERNAME: " << "[" << server.getUserMap(fd)->second.getUsername() << "]" << " FD " << "[" << server.getUserMap(fd)->second.getSockFd() << "]" << std::endl;
#define RPL_CHANNELMODEIS(channel, mode) ("324 * " + channel + " +" + mode + "\r\n")
void	sendIrcMsg(int fd, string nickname, string username, string message);
void	error(string error);