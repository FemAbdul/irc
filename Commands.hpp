/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabdul-k <fabdul-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 18:57:49 by fabdul-k          #+#    #+#             */
/*   Updated: 2024/08/20 07:38:01 by fabdul-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include "Libs.hpp"
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>

class User;
class Server;
class Channel;
class Commands
{
    private:
    int _fd;
    std::string _message;
    std::string _username;
    std::string _nickname;
    std::string _command;

    std::vector<std::string> args;
    Commands();

    public:
    Commands(std::string message, int fd, std::string nickname, std::string username);
    ~Commands();

    int ExecuteCommand(Server &server);
    void execQuitcmd(Server &server);
    void execPrivmsgcmd(Server &server);
};

#endif