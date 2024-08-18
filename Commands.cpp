/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabdul-k <fabdul-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 18:58:33 by fabdul-k          #+#    #+#             */
/*   Updated: 2024/08/17 07:41:11 by fabdul-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

Commands::Commands(std::string message, int fd, std::string nickname, std::string username):_message(message), _fd(fd), _nickname(nickname), _username(username)
{
    if (!message.empty())
    {
        std::istringstream input(message);
        std::string inputsplit;

        while (std::getline(input, inputsplit, ' ') && inputsplit != " ")
            args.push_back(inputsplit);
        _command = args[0];
        args.erase(args.begin());
        _command.erase(std::remove(_command.begin(), _command.end(), '\r'), _command.end());
        _command.erase(std::remove(_command.begin(), _command.end(), '\n'), _command.end());
        for(std::vector<std::string>::iterator it = args.begin(); it != args.end(); it++)
        {
            args.erase(std::remove(args.begin(),args.end(), '\r'),args.end());
            args.erase(std::remove(args.begin(),args.end(), '\n'),args.end());
        }
    }
}

Commands::~Commands(){}

int Commands::ExecuteCommand()
{
    
}