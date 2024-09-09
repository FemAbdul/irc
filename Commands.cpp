/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabdul-k <fabdul-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 18:58:33 by fabdul-k          #+#    #+#             */
/*   Updated: 2024/08/20 08:06:51 by fabdul-k         ###   ########.fr       */
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
            (*it).erase(std::remove((*it).begin(), (*it).end(), '\r'),(*it).end());
        }

        for(std::vector<std::string>::iterator it = args.begin(); it != args.end(); it++)
        {
            (*it).erase(std::remove((*it).begin(), (*it).end(), '\n'), (*it).end());
        }
    }
}

Commands::~Commands(){}

int Commands::ExecuteCommand(Server &server)
{
    if (_command == "QUIT") execQuitcmd(server);
	else if (_command == "PRIVMSG") execPrivmsgcmd(server);
	// else if (_command == "JOIN") joinCmdExec(server);
	// else if (_command == "KICK") kickCmdExec(server);
	// else if (_command == "MODE") modeCmdExec(server);
	// else if (_command == "INVITE") inviteCmdExec(server);
	// else if (_command == "TOPIC") topicCmdExec(server);
    else return 0;
    
    return 1;
}

void Commands::execQuitcmd(Server &server)
{
    std::map<int, User> tempuserMap = server.getUserMap();
    std::map<int, User>::iterator it = tempuserMap.find(_fd);

	server.swapFD(it);
	server.deleteUserFromMap(it);
	server.decrementCountConnects();

	std::cout << _fd << "  disconnectedQUIT" << std::endl;
	close(_fd);
	_fd = -1;
}

void	Commands::execPrivmsgcmd(Server &server)
{
    if (args.size() < 2)
    {
        send(_fd, ERR_NEEDMOREPARAMS(string("PRIVMSG")).c_str(), ERR_NEEDMOREPARAMS(string("PRIVMSG")).length() + 1, 0);
        return ;
    }

    bool user = false;
    int user_fd;
    std::map<int, User> tempusermap = server.getUserMapRef();
    for (std::map<int, User>::iterator it = tempusermap.begin(); it != tempusermap.end(); it++)
    {
        if (it->second.getNickname() == args[0])
        {
            user = true;
            user_fd = it->second.getSockFd();
            break;
        }
    }

    bool channel = false;
    Channel tempChannel;
	vector<Channel> tmpVector = server.getVectorOfChannels();
	for(vector<Channel>::iterator it = tmpVector.begin(); it != tmpVector.end(); it++)
	{
		if ((*it).getChannelName() == args[0])
		{
			channel = true;
			tempChannel = (*it);
			break;
		}
	}

    if (user)
        sendIrcMsg(user_fd, _nickname, _username, _message);
    else if(channel)
        tempChannel.channelPrivmsgExec(_fd, _message, _nickname, _username);
    else
    {
        send(_fd, ERR_NORECIPIENT(string("PRIVMSG")).c_str(), ERR_NORECIPIENT(string("PRIVMSG")).length() + 1, 0);
		return ;
    }    
}

