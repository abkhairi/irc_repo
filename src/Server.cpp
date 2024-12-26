/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamsate <shamsate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 20:58:54 by r4v3n             #+#    #+#             */
/*   Updated: 2024/12/26 01:42:16 by shamsate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/Server.hpp"

Server::Server(int port, std::string pass){
    _port = port;
    _pass = pass;
};

Server::~Server(){};

Client& Server::getCliByIdx(size_t idx){
    return (cliVec[idx]);
};
std::string Server::getHostIp(){
    return (_hostIp);
};
void    Server::display(){
    for (std::vector<struct pollfd>::iterator it = pollFdVec.begin(); it != pollFdVec.end(); it++)
    {
        std::cout << "Struct  Fd  = " << it->fd << std::endl;
        std::cout << "Struct Event  = " << it->events << std::endl;
        std::cout << "Struct Revent  = " << it->revents << std::endl;
    }
};
void  Server::rmvCli(int id){
    cliVec.erase(cliVec.begin() +id);
};
std::string Server::timee() {
    time_t now = time(0);
    char buffer[30];
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", std::localtime(&now));
    return std::string(buffer) + " (" + std::to_string(now) + ")";
};
Client & Server::getCliOrg(int sockcli){
    for (size_t i = 0 ; cliVec.size() > i; i++){
        if (cliVec[i].getCliFd() == sockcli)
            return(cliVec[i]);
    }
    return (cliVec[0]);
};
int  Server::getFdSockServ(){
    return (_fdSockServ);
};



void    Server::init_serv(int  port, std::string pass, size_t &i)
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);

    int opt = 1;// setsockopt : function in network programming is used to configure options on a socket.
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    fcntl(sockfd, F_SETFL, O_NONBLOCK);
    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    bind(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr)); // bound [ip and port] to server socket
    listen(sockfd, 10);
    std::cout << "\033[32m+:::::::::[FT_IRC]:::::::::+\033[0m" << std::endl <<"\033[32m+\033[0m";
    std::cout << "\033[31m The Server listen in ==> " <<"\033[32m+" << std::endl;
    std::cout << "\033[32m+ Port :\033[0m              " << port << "\033[32m +\033[0m"<< std::endl;
    std::cout << "\033[32m+ Pass :\033[0m              " << pass << "\033[32m +\033[0m"<<std::endl;
    std::cout << "\033[32m++++++++++++++++++++++++++++\033[0m" << std::endl;
    setFdSockServ(sockfd);
    struct pollfd poolfd;
    poolfd.fd = getFdSockServ();
    poolfd.events = POLLIN;
    pollFdVec.push_back(poolfd);
    while (1){
        int res = poll(pollFdVec.data(), pollFdVec.size(), -1);
        if (res == -1){
            std::cout << "error poll\n";
            return ;}
        for (i = 0; pollFdVec.size() > i; i++){
            if (POLLIN & pollFdVec[i].revents){
                if (pollFdVec[i].fd == getFdSockServ()){
                    // is a server here : is a handle new connction for client
                    struct sockaddr_in cli_addr;
                    socklen_t len = sizeof(cli_addr);
                    int cli_fd = accept(getFdSockServ(), (struct sockaddr*)&cli_addr, &len);
                    setNonBlocking(cli_fd);
                    struct pollfd poollfd;
                        poollfd.fd = cli_fd;
                        poollfd.events = POLLIN | POLLOUT;
                        poollfd.revents = 0;
                    pollFdVec.push_back(poollfd);
                    std::string ipAddrCli = inet_ntoa(cli_addr.sin_addr);
                    Client obj_client(cli_fd, ipAddrCli);
                    cliVec.push_back(obj_client);
                    std::cout << "New connection accepted: " << cli_fd << std::endl;
                }
                else
                {
                    // is a client here : is a handle new msg
                    int sockcli = pollFdVec[i].fd;
                    std::string cmd = recvCmd(sockcli, i);
                    // std::cout << "cmd = " << cmd << std::endl;
                    // std::cout << "Message from client " << socket_client << ": " << cmd << std::endl;
                    Client &cliref = getCliOrg(sockcli);
                    cliref.setDataRec(cmd);
                    authCli(cmd, sockcli, cliref, i);  
                }
            }
        }
    }
};

void Server::setFdSockServ(int fd){
    _fdSockServ = fd;
};

bool Server::isMember(int fdcli, Channels ch){
    std::map<std::pair<bool,int>, Client > user_map = ch.getMapUser();
    for(std::map<std::pair<bool,int>, Client >::iterator it = user_map.begin(); it != user_map.end(); it++)
    {
        if (fdcli == it->second.getCliFd())
            return  true;
    }
    return false;
};

void    Server::broadCastMsg(Channels ch, std::string msg, int clifd){
    std::map<std::pair<bool, int>, Client> mapOfClients = ch.getMapUser();
    std::map<std::pair<bool, int>, Client>::iterator iter;
    for(iter = mapOfClients.begin(); iter != mapOfClients.end(); iter++)
    {
        if (iter->second.getCliFd() != clifd)
            sendMsgToCli(iter->second.getCliFd(), msg);
    }
};

void Server::isRegistred(Client &cli, std::string time){
    sendMsgToCli(cli.getCliFd(),RPL_WELCOME(cli.getNickNm(), cli.getIpAddrCli()));
    sendMsgToCli(cli.getCliFd(),RPL_YOURHOST(cli.getNickNm(), cli.getIpAddrCli()));
    sendMsgToCli(cli.getCliFd(),RPL_CREATED(cli.getNickNm(), cli.getIpAddrCli(), time));
    sendMsgToCli(cli.getCliFd(),RPL_MYINFO(cli.getNickNm(), cli.getIpAddrCli()));
};

void    Server::authCli(std::string cmd, int socket_client, Client &clienteref, size_t &_index_client)
{
    (void)socket_client;
    for (size_t i = 0; i < cmd.size(); i++)
        cmd[i] = std::tolower(cmd[i]);
    // pass abc
    std::stringstream ss(cmd);
    int i = 0;
    while (ss >> cmd)
    {
        cmdVec.push_back(cmd);
        i++;
    }
    if (strstr(clienteref.getRecLn().c_str(), "\n"))
    {
        size_t position = clienteref.getRecLn().find_first_of("\n");
        if (position > clienteref.getRecLn().size())
            return;
        // std::cout << "position = " << position << std::endl;
        std::string cmd_final = clienteref.getRecLn().substr(0 , position + 1);
        std::cout << "cmd_final = " << cmd_final << std::endl;
        handleAuthCmd(cmd_final, _index_client);
    }
    else
        return ;
}
std::string Server::recvCmd(int fdcli, size_t &idxcli)
{
    char buffer[1024];
    memset(buffer, 0, 1024);
    ssize_t bytes_received = recv(fdcli, buffer, sizeof(buffer) - 1, 0);
    if (bytes_received <= 0)
    {
        if (bytes_received == 0)
        {
            std::cout << "Client disconnected: " << fdcli << std::endl;
            pollFdVec.erase(pollFdVec.begin() + idxcli);
            idxcli--;
        }
        else
            perror("recv");
        close(fdcli); // close the socket if not present program infinite loop infoi click sur c
        // removeClient(fd_client);
        return "";
    }
    buffer[bytes_received] = '\0'; // add null terminator if not present => display garbej value
    std::string message(buffer);
    if (message == "\n")
        return "";
    return message;
};

std::string to_lower(std::string str){
    for (size_t i =0; str.size() > i; i++)
        str[i] = tolower(str[i]);
    return (str);
};

Channels & Server::getChannel(std::string channel){
    std::map<std::string, Channels>::iterator it = channels.find(to_lower(channel));
    if (it == channels.end())
        throw "No channel found";
    return it->second;
};

void    Server::SendToAll(Channels ch, std::string msg)
{
    std::map<std::pair<bool, int>, Client> mapOfClients = ch.getMapUser();
    std::map<std::pair<bool, int>, Client>::iterator iter;
    for(iter = mapOfClients.begin(); iter != mapOfClients.end(); iter++)
        sendMsgToCli(iter->second.getCliFd(), msg);
        // send_msg_to_clinet(iter->first.second, _message);
};

