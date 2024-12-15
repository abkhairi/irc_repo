/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamsate <shamsate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 21:25:15 by shamsate          #+#    #+#             */
/*   Updated: 2024/12/15 14:06:39 by shamsate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <cstring>
#include <sstream>
#include  <poll.h>
#include "Client.hpp"
#include "Channel.hpp"
#include "rep.hpp"

typedef std::vector<std::string> joinVec;
typedef std::vector<struct pollfd> pollFdVec;
typedef std::vector<Client> clientVec;
typedef std::map<std::string, Channel> channelMap;

class Server {
    private :
            int _portNum;
            std::string _host;
            std::string _password;
            int _socketFd;
            joinVec _rslt;
            joinVec _args;
            clientVec _clients;
            sockaddr_in _servAddr;
            channelMap  _channels;
            pollFdVec _pollFd;
            std::vector<std::pair<std::string, std::string> >_mod;
            Server();

        public :
            ~Server();
            Server(int portNum, std::string password);
            size_t idx;
            std::string &getPassWd();
            unsigned int getPort();
            int	getSkFd();
            void setSocketaddr();
            void setSocketFd(int socketFd);
            void runServ();
            void rmvClient(int idx);
            void rmvFromCh(int idx);
            void index_Of_Begin(Server src);
            pollFdVec&	getPollfdVec();
            void Server::broadcastMsg(Channel _chan, std::string msg, int cli_sock_fd);
            Client &Server::getClientByFd(int idx);
            void Server::setClient(Client cli);
            void    eventOnServSock();
            void    eventOnCliSock();
};
void    serverCheckRequirements(int argc, char *port, char *pass);
int     checkPort(std::string port, std::string pass);
void    handle_sig(int sig);
void	sendMsgToClient(int cli_sock_fd, std::string msg);
