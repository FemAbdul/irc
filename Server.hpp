/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabdul-k <fabdul-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 07:47:16 by fabdul-k          #+#    #+#             */
/*   Updated: 2024/08/20 07:47:19 by fabdul-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Libs.hpp"
#include "User.hpp"
#include "Command.hpp"
#include "Channel.hpp"

class User;

class Server
{
	private:
		int				_port;
		int				_channelID;
		int				_listening;
		int				_countConnects;
		string			_password;

		struct pollfd 	_fds[MAX_CONN];
		map<int, User>	_userMap;
		vector<Channel>	_channels;

		Server();

	public:
		Server(int port, string password);
		~Server();

		// GETTERS
		std::map<int, User>::iterator getUserMap(int fd);
		map<int, User>	getUserMap();
		map<int, User>	&getUserMapRef();
		int				getChannelID();
		int				getPort();
		int				getListening();
		int				getCountConnects();
		vector<Channel>	getVectorOfChannels();
		vector<Channel>	&getVectorOfChannelsRef();
		int				getFdFromMapByNick(string nickname);
		Channel			getChannel(int i);
		string			getPassword();
		
		// SETTERS
		void			setUsernameByUser(string username, int i);
		void			setNicknameByUser(string username, int i);
		void			setPasswordPassedByUser(int i);
		void			setNicknamePassedByUser(int i);
		void			setUserPassedByUser(int i);
		void			setChannelID(int id);
		void			setListening(int socket);
		void			setCountConnects(int value);
		
		void			channelsPushBack(Channel *channel);
		void			channelSetNew(Channel &newChannel, int id);
		void			channelVectorSetNew(vector<Channel> &tmpVector);
		void			channelPushBackFd(int id, int fd);
		void			swapFD(std::map<int, User>::iterator it);
		
		// SERVER
		void			setNewChannelAdm(vector<int> &fdVector);
		void			incrementCountConnects();
		void			decrementCountConnects();
		void 			incrementChannelId();
		void			decrementChannelId();
		void			runServer();
		void 			serverSimulation();
		void			createNewConnection(size_t &i);
		void			processExistedConnection(size_t &i);
		void			deleteUserFromMap(std::map<int, User>::iterator it);
		Channel			getChannelByName(string channelName);
		void			setChannelTopicName(string channelName, string topic);
		void			setChannelFlag(string channelName, string flag, bool val, string password, int userLimit);
		void			addUserToChannel(int fd, string channelName);
		void 			addUserToInvited(int fd, string channelName);
		void			addUserToAdmin(int fd, string channelName);
		void			removeUserFromAdmin(int fd, string channelName);
		void			removeUserFromInvited(int fd, string channelName);
		void			removeUserFromChannel(int fd, string channelName);
	
};

void	error(string error);