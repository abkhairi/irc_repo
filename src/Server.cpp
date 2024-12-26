/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamsate <shamsate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 20:58:54 by r4v3n             #+#    #+#             */
/*   Updated: 2024/12/26 02:22:52 by shamsate         ###   ########.fr       */
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
void Server::handleAuthCmd(std::string cmdf, size_t &idxcli){

std::vector<std::string> &cmdvec = cmdVec;
    // ft_gethostname();
    char hostnm[256]; // Buffer to store the hostname
    (void)cmdf;
    if (gethostname(hostnm, sizeof(hostnm)) != 0)
        std::cerr << "Error retrieving hostname: " << strerror(errno) << std::endl;
    _hostIp = hostnm;

    Client &cli = getCliByIdx(idxcli - 1);
    std::string nick = cli.getNickNm();

    // std::cout << "size of vector = " << vec_of_commande.size() << std::endl;
    // ici segfault if nc localhost 4545 after click sur entre hhhhhh
    if (cli.getAuth() == false)
    {
        if (cmdvec.size() <= 1)
        {
            if (cmdvec[0] == "nick")
                sendMsgToCli(cli.getCliFd(), ERR_NONICKNAMEGIVEN(nick, _hostIp));
            else if (cmdvec[0] != "nick" || cmdvec.size() == 0)
                sendMsgToCli(cli.getCliFd(), ":IRC ==> 461 :Not enough parameters\r\n");
            cmdvec.clear();
            return ;
        }
        if (cmdvec[0] == "pass" && cmdvec[1] == _pass && cli.getFlgPass() == false)
        {
            if (cmdvec.size() == 2)
            {
                // std::cout << "is a pass cmd" << std::endl;
                cli.setFlgPass(true);
                cli.setPass(cmdvec[1]);
            }
            else
                sendMsgToCli(cli.getCliFd(), ":IRC ==> 464 :Password incorrect\r\n");
            cmdvec.clear();
            return ;
        }
        else if (cmdvec[0] == "pass" && cmdvec[1] != _pass && cli.getFlgPass() == false)
        {
            sendMsgToCli(cli.getCliFd(), ":IRC ==> 464 :Password incorrect\r\n");
            cmdvec.clear();
            return ;
        }
        if (cmdvec[0] == "nick" && cmdvec.size() == 2 && cli.getFlgNick() == false)
        {
            // check if any client in vector has the same nickname ft_check_nickname()
            cli.setFlgNick(true);
            cli.setNickNm(cmdvec[1]);
            cmdvec.clear();
            return ;
        }
        else if (cmdvec[0] == "nick" && cmdvec.size() > 2 && cli.getFlgNick() == false)
        {
            sendMsgToCli(cli.getCliFd(), ":IRC ==> 432 :Erroneous nickname\r\n");
            cmdvec.clear();
            return ;
        }
        if (cmdVec[0] == "user" && cli.getFlgNick() && cli.getFlgPass())
        {
            // std::cout << "herre fi user\n";
            if (cmdvec.size() > 5 || cmdvec[1].empty())
            {
                sendMsgToCli(cli.getCliFd(), ":irc.abkhairi.chat 461 :Need more parameters\r\n");
                cmdvec.clear();
                return ;
            }
            else
            {
                cli.setFlgUser(true);
                cli.setUser(cmdvec[1]);
                cli.setRealNm(cmdvec[5]);
                std::cout << "user is " << cli.getUser() << std::endl;
                cmdvec.clear();
                cli.setAuth();
                time_t currentTime = time(0); // time now non readable for humain
                std::string time_ = ctime(&currentTime);
                isRegistred(cli, time_);
                return ;
            }
        }
        cmdvec.clear();
        return ;
    }
    else
    {
        if (cmdvec[0] == "pass" || cmdvec[0] == "user")
        {
            sendMsgToCli(cli.getCliFd(), ERR_ALREADYREGISTERED(nick, _hostIp));
            cmdvec.clear();
            return ;
        }
        else if(cmdvec[0] == "nick")
        {
            // change nick the user
        }
        else
        {
           // ft_commande_j_m(vec_of_commande, _index_client, client_);
        }
        cmdvec.clear();
    }

}
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

void Server::isRegistred(Client &cli, std::string time){
    sendMsgToCli(cli.getCliFd(),RPL_WELCOME(cli.getNickNm(), cli.getIpAddrCli()));
    sendMsgToCli(cli.getCliFd(),RPL_YOURHOST(cli.getNickNm(), cli.getIpAddrCli()));
    sendMsgToCli(cli.getCliFd(),RPL_CREATED(cli.getNickNm(), cli.getIpAddrCli(), time));
    sendMsgToCli(cli.getCliFd(),RPL_MYINFO(cli.getNickNm(), cli.getIpAddrCli()));
};

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



