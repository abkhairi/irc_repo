/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamsate <shamsate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 21:27:55 by shamsate          #+#    #+#             */
/*   Updated: 2024/12/16 16:24:11 by shamsate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <poll.h>
#include <fcntl.h>
#include "../include/Server.hpp"

//********************************************************************************************************************
Server::Server(int port, std::string pass)
{
    _portNum = port;
    _password = pass;
    _socketFd = 0;
    idx = 0;
};

//********************************************************************************************************************
void index_Of_Begin(Server src){
	std::cout<<"#-- ---------------------------- --#"<< std::endl;
	std::cout<<"#  Port    : "<<src.getPort()<< std::endl;
	std::cout<<"#  Password: "<<src.getPassWd()<< std::endl;
	std::cout<<"#-- ---------------------------- --#" << std::endl;
};
//********************************************************************************************************************
std::string &Server::getPassWd() {
	return (_password);
};
//********************************************************************************************************************
unsigned int  Server::getPort() {
	return ((_portNum));
};
//********************************************************************************************************************
int	Server::getSkFd()
{
	return (_socketFd);
};
//********************************************************************************************************************
int checkPort(std::string port, std::string pass){
	std::stringstream ss(port);
	int portNum;
	ss >> portNum;
	if ((portNum < 1024 || portNum > 65535 || port.empty()))
		return 1;
	if (pass.empty())
		return 2;
	if (port[0] == '+' || port[0] == '-')
		return 1;
	for (size_t i = 0; i < port.size(); i++) {
		if (port[i] < '0' || port[i] > '9')
			return 1;
	}
	return (0);
	};
//********************************************************************************************************************
void serverCheckRequirements(int argc, char *port, char *pass) {
	if (argc != 3) {
		std::cerr << "Usage: ./ircserv [port] [password] :( " << std::endl;
		exit(EXIT_FAILURE);
	}
	if (checkPort(port, pass) != 0) {
		if (checkPort(port, pass) == 2)
			std::cerr << "ERROR: '" << pass << "' : check Password then try again... :( \n";
		else
			std::cerr << "ERROR: '" << port << "' : check Port then try again... :( \n";
		exit(EXIT_FAILURE);
	}
};
//********************************************************************************************************************
pollFdVec&	Server::getPollfdVec()
{
	return (_pollFd);
};
//********************************************************************************************************************
void Server::setClient(Client cli) {
	_clients.push_back(cli);
};
//********************************************************************************************************************
void Server::rmvClient(int idx) {
		_clients.erase(_clients.begin() + idx);
};
//********************************************************************************************************************
Client &Server::getClientByFd(int idx) {
	for(size_t i = 0; i < _clients.size(); i++) {
		if (_clients[i].getClientFd() == idx)
			return (_clients[i]);
	}
	return (_clients[0]);
};
//********************************************************************************************************************
Client&	Server::getCliByIdx(int id)
{
    return _clients[id];
}
//********************************************************************************************************************
void	sendMsgToClient(int cli_sock_fd, std::string msg) {
	ssize_t x = send(cli_sock_fd, msg.c_str(), msg.size(), 0);
	if (x == -1)
		perror("send : ");
};
//********************************************************************************************************************
void Server::broadcastMsg(Channel _chan, std::string msg, int cli_sock_fd) {
	mapUsers &users = _chan.getUsersMap();
	for (auto it = users.begin(); it != users.end(); it++) {
		if (it->second.getClientFd() != cli_sock_fd) {
			sendMsgToClient(it->second.getClientFd(), msg);
		}
	}
};
//********************************************************************************************************************

void sockAddssInfo(struct sockaddr_in& addss, int port_n)
{
    memset(&addss, 0, sizeof(addss));
    addss.sin_family = PF_INET;
    addss.sin_addr.s_addr = htonl(INADDR_ANY);
    addss.sin_port = htons(port_n);
};
//********************************************************************************************************************
void    Server::setSockAddss()
{
    memset(&_addss, 0, sizeof(_addss));
    _addss.sin_family = PF_INET;
    _addss.sin_addr.s_addr = htonl(INADDR_ANY);
    _addss.sin_port = htons(_portNum);
};
//********************************************************************************************************************
void    Server::setSocketFd(int sock_fd)
{
    _socketFd = sock_fd;
};
//********************************************************************************************************************
void Server::runServ(){
	_socketFd =socket(PF_INET, SOCK_STREAM, 0);
	if (_socketFd == -1){
		std::cerr <<"Error: Socket Creation failed :( \n";
		exit(1);
	}
	if (fcntl(_socketFd, F_SETFL, O_NONBLOCK) , 0){
		perror("fcntl");
		close(_socketFd);
		exit(EXIT_FAILURE);
	}
	int valOpt = 1;
	if (setsockopt(_socketFd, SOL_SOCKET, SO_REUSEADDR, &valOpt, sizeof(valOpt)) == -1){
		std::cerr << " Error setsockopt() failed :( \n";
		close (_socketFd);
		exit(1);
	}
	if (bind(_socketFd, (struct sockaddr *) &_addss, sizeof(_addss)) == -1){
		std::cerr <<"Error : bind() failed :( \n ";
		close(_socketFd);
		exit(1);
	}
	if (listen(_socketFd, 10) ==  -1){
		std::cerr <<"Error listen() failed :( \n";
		close(_socketFd);
		exit(1);
	}
	index_Of_Begin(*this);
};
//********************************************************************************************************************
Client &Server::getCli(std::string nick){
	clientVec::iterator it = _clients.begin();
	for(; it != _clients.end(); it++){
		if (it->getNickNm() == nick)
			return *it;
	}
	throw "no user found";
};
//********************************************************************************************************************
Server::~Server(){};
//********************************************************************************************************************
