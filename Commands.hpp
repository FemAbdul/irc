/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabdul-k <fabdul-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 18:57:49 by fabdul-k          #+#    #+#             */
/*   Updated: 2024/08/17 07:35:23 by fabdul-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include <iostream>
#include <sstream>

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

    


};

#endif