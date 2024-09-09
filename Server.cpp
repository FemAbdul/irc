/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabdul-k <fabdul-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 07:47:05 by fabdul-k          #+#    #+#             */
/*   Updated: 2024/08/20 07:47:08 by fabdul-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "Server.hpp"
#include "User.hpp"

Server::Server(int port, string password)
{
	_port = port;
	_channelID = 0;
	_listening = 0;
	_countConnects = 1;
	_password = password;

	int i = -1;
	while (++i < MAX_CONN)
		_fds[i].fd = -1;
	_fds[0].events = POLLIN;
	_fds[0].revents = 0;
}

Server::~Server(){}

// GETTERS
int				Server::getChannelID() { return(_channelID); }
int				Server::getPort() { return(_port); }
void			Server::setListening(int socket) { _listening = socket; }
int				Server::getListening() { return(_listening); }
int				Server::getCountConnects() { return(_countConnects); }
vector<Channel>	Server::getVectorOfChannels() { return(_channels); }
vector<Channel>	&Server::getVectorOfChannelsRef() { return(_channels); }
Channel			Server::getChannel(int i) { return(_channels[i]); }
string			Server::getPassword() { return(_password); }

// SETTERS
void			Server::setPasswordPassedByUser(int i) { getUserMap(i)->second.setPasswordPassed(); }
void			Server::setNicknamePassedByUser(int i) {  getUserMap(i)->second.setNicknamePassed(); }
void			Server::setUserPassedByUser(int i) {  getUserMap(i)->second.setUserPassed(); }
void			Server::setChannelID(int id) { _channelID += id; }

void			Server::setCountConnects(int value) { _countConnects = value; }
void			Server::incrementCountConnects() { ++_countConnects; }
void			Server::decrementCountConnects() { if (_countConnects > 0) --_countConnects; }

void			Server::incrementChannelId() { ++_channelID; }
void			Server::decrementChannelId() { if (_channelID > 0) --_channelID; }

void			Server::setUsernameByUser(string username, int i) {   getUserMap(i)->second.setUsername(username); }
void			Server::setNicknameByUser(string nickname, int i) {  getUserMap(i)->second.setNickname(nickname); }
void			Server::channelsPushBack(Channel *channel) { _channels.push_back(*channel); }

void			Server::setNewChannelAdm(vector<int> &tmpIntFdsVector) { _channels[_fds[0].fd].setFdAdmin(tmpIntFdsVector[0]); }
void			Server::channelPushBackFd(int id, int fd) { _channels[id].fdsPushBack(fd); }
void			Server::channelVectorSetNew(vector<Channel> &tmpVector){ _channels = tmpVector;}
void			Server::channelSetNew(Channel &newChannel, int id) { _channels[id] = newChannel; }

void Server::addUserToChannel(int fd, string channelName)
{
	for (size_t i = 0; i < _channels.size(); i++)
	{
		if (_channels[i].getChannelName() == channelName)
		{
			_channels[i].fdsPushBack(fd);
			_channels[i].channelPrivmsgCmdExec(fd, "JOIN", channelName, _userMap.find(fd)->second.getNickname());
		}
	}

}

void Server::removeUserFromAdmin(int fd, string channelName)
{
	for (size_t i = 0; i < _channels.size(); i++)
	{
		if (_channels[i].getChannelName() == channelName)
		{
			for (size_t j = 0; j < _channels[i].getAdminFds().size(); j++)
			{
				if (_channels[i].getAdminFds()[j] == fd)
				{
					_channels[i].getAdminFds().erase(_channels[i].getAdminFds().begin() + j);
					return ;
				}
			}
		}
	}
}

void Server::removeUserFromInvited(int fd, string channelName)
{
	for (size_t i = 0; i < _channels.size(); i++)
	{
		if (_channels[i].getChannelName() == channelName)
		{
			if (_channels[i].isUserInvited(fd))
			{
				_channels[i].getInvitedFds().erase(fd);
				return ;
			}
		}
	}
}

void Server::removeUserFromChannel(int fd, string channelName)
{
	for (size_t i = 0; i < _channels.size(); i++)
	{
		if (_channels[i].getChannelName() == channelName)
		{
			if (_channels[i].checkUserInChannel(fd))
			{
				for (size_t j = 0; j < _channels[i].getFdVector().size(); j++)
				{
					if (_channels[i].getFdVector()[j] == fd)
					{
						_channels[i].getFdVector().erase(_channels[i].getFdVector().begin() + j);
						return ;
					}
				}
			}
		}
	}
}

void			Server::setChannelFlag(string channelName, string flag, bool val, string password, int userLimit)
{
	for (size_t i = 0; i < _channels.size(); i++)
	{
		if (_channels[i].getChannelName() == channelName)
		{
			if (flag == "l")
			{
				_channels[i].setUserLimitFlag(val);
				_channels[i].setUserLimit(userLimit);
			}
			else if (flag == "i")
				_channels[i].setInviteOnlyFlag(val);
			else if (flag == "t")
				_channels[i].setTopicFlag(val);
			else if (flag == "k")
			{
				_channels[i].setKeyFlag(val);
				_channels[i].setPassword(password);
			}
		}
	}
}

void Server::addUserToAdmin(int fd, string channelName)
{
	for (size_t i = 0; i < _channels.size(); i++)
	{
		if (_channels[i].getChannelName() == channelName)
		{
			if (_channels[i].isUserInChannel(fd) == false)
				return ;
		}
		else
			_channels[i].addAdmin(fd);
	}
}

void			Server::addUserToInvited(int fd, string channelName)
{
	for (size_t i = 0; i < _channels.size(); i++)
	{
		if (_channels[i].getChannelName() == channelName)
			_channels[i].addToInvited(fd);
	}
}

Channel Server::getChannelByName(string channelName)
{
	for (size_t i = 0; i < _channels.size(); i++)
	{
		if (_channels[i].getChannelName() == channelName)
			return _channels[i];
	}
	return Channel();
}

void Server::setChannelTopicName(string channelName, string topic)
{
	for (size_t i = 0; i < _channels.size(); i++)
	{
		if (_channels[i].getChannelName() == channelName)
			_channels[i].setTopic(topic);
	}
}

std::map<int, User>::iterator	Server::getUserMap(int fd)
{
	return _userMap.find(fd);
}

map<int, User>	Server::getUserMap()
{
	return _userMap;
}

map<int, User>	&Server::getUserMapRef()
{
	return _userMap;
}

int Server::getFdFromMapByNick(string nickname)
{
	for (std::map<int, User>::iterator it = _userMap.begin(); it != _userMap.end(); it++)
	{
		if (it->second.getNickname() == nickname)
			return it->first;
	}
	return -1;
}

void	Server::swapFD(std::map<int, User>::iterator it)
{
	int i, j = MAX_CONN;
	for (int z = 0; z < MAX_CONN; z++)
	{
		if (_fds[z].fd == it->first)
		{
			i = z;
			j = i + 1;
			break ;
		}
	}

	pollfd tmp;
	while (j != MAX_CONN)
	{
		tmp = _fds[i];
		_fds[i] = _fds[j];
		_fds[j] = tmp;
		i++;
		j++;
	}
}

void Server::deleteUserFromMap(std::map<int, User>::iterator it)
{
	if (it != _userMap.end())
		_userMap.erase(it->first);
}

void	Server::createNewConnection(size_t &i)
{
	if(_countConnects >= MAX_CONN)
		std::cout << "You reached the max number of connections! " << std::endl;
	else
	{
		_fds[_countConnects].fd = accept(_fds[i].fd, NULL, NULL);
		if (_fds[_countConnects].fd < 0)
		{
			std::cerr << "Failed to accept new connection" << std::endl;
			return;
		}
		_fds[_countConnects].events = POLLIN;
		_fds[_countConnects].revents = 0;
		User *user = new User(_fds[_countConnects].fd);
		_userMap.insert(std::make_pair(_fds[_countConnects].fd, *user));
		delete user;

		incrementCountConnects();

		std::cout << "A new connection has been established" << std::endl;
	}
}

void	Server::processExistedConnection(size_t &i)
{
	char buff[BUFFER_SIZE];
	memset(buff, 0, BUFFER_SIZE);
	int readed = read(_fds[i].fd, buff, BUFFER_SIZE);
	_fds[i].revents = 0;
	std::map<int, User>::iterator it = _userMap.find(_fds[i].fd);

	if (!readed)
	{
		std::cout << _fds[i].fd << "  disconnected" << std::endl;
		
		if (it != _userMap.end())
		{
			_userMap.erase(it);
			std::cout << "User with fd " << _fds[i].fd << " removed." << std::endl;
		}
		close(_fds[i].fd);
		_fds[i].fd = -1;
		decrementCountConnects();
		int j = i + 1;
		pollfd tmp;
		while (j != MAX_CONN)
		{
			tmp = _fds[i];
			_fds[i] = _fds[j];
			_fds[j] = tmp;
			i++;
			j++;
		}
	}
	buff[readed] = 0;
	if (it != _userMap.end())
	{
		it->second.parseCmd(*this, std::string(buff), _fds[i].fd);
	}
	_fds[i].revents = 0;
}

void	Server::serverSimulation()
{
	std::cout << "A new server simulation has been started!" << std::endl;
	while (true)
	{
		int COUNTFD;
		if ((COUNTFD = poll(_fds, _countConnects, -1)) < 0)
			error("Poll crash");
		for (size_t i = 0; i < static_cast<size_t>(_countConnects); i++)
		{
			if (_fds[i].fd > 0 && (_fds[i].revents & POLLIN) == POLLIN)
			{
				if (i == 0) 
					createNewConnection(i);
				else
					processExistedConnection(i);
			}
		}
	}
}

void	Server::runServer()
{
	_listening = socket(AF_INET, SOCK_STREAM, 0);
	if (_listening == -1)
		error("Error establishing connection");
	
	int flagOne = 1;
	if (setsockopt(_listening, SOL_SOCKET, SO_REUSEADDR, &flagOne, sizeof(int)) < 0)
		error("setsockpt error");
	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(_port);
	hint.sin_addr.s_addr = htonl(INADDR_ANY);
	inet_pton(AF_INET, "127.0.0.1", &hint.sin_addr);
	if (bind(_listening, (sockaddr *)&hint, sizeof(hint)) == -1)
		error("Can't bind");

	if (listen(_listening, SOMAXCONN) == -1)
		error("Can't listen");
	_fds[0].fd = _listening;
	fcntl(_fds[0].fd, F_SETFL, O_NONBLOCK);

	serverSimulation();
}
