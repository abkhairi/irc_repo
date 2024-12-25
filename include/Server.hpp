/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamsate <shamsate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 21:02:17 by shamsate          #+#    #+#             */
/*   Updated: 2024/12/25 21:39:07 by shamsate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>
#include <unistd.h>
#include <string>
#include <vector>
#include <map>
#include <fcntl.h>
#include <cstring>
#include <iomanip>
#include <cctype>
#include <sstream>
#include <poll.h>
#include <sys/socket.h>
#include <ctime>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <cstdlib>
#include "Client.hpp"
#include "Channels.hpp"
#include "rep.hpp"


class Client;

class Server{
    private :
        int                 _fdSockServ;
        int                 _port;
        std::string         _pass;
        std::string         _hostIp;
        std::vector<Client>cliVec;
        Server();
    public :
        Server(int port, std::string pass);
        ~Server();
        size_t              cliIdx;
        std::vector<struct pollfd> pollFdVec;
        std::vector<std::string>   cmdVec;
        // std::map<std::string, channels>channels;
        void init_serv(int port, std::string pass, size_t &i);
        void setFdSockServ(int fd);
        void display();

        void isRegistred(Client &cli, std::string time);
        void rmvCli(int id);
        void sendMsg(Client &cli, std::string rec, std::string msg);



        Client &getCliOrg(int sockCli);
        Client &getCliByIdx(size_t idx);


        std::string getHostIp();
        std::string timee();


        //:::::::::Channel:::::::::::::::

        // void ft_commande_j_m(std::vector<std::string> cmd_final, size_t &_index_client, Client &client_);
        bool isMember(int fdcli, Channels ch);
        void broadCastMsg(Channels ch, std::string msg, int clifd);
        // channels & getChannel(std::string channel);
        // void    SendToAll(channels channel_, std::string _message);




        int  getFdSockServ();
        //:::::::::CMD:::::::::::::::
        void authCli(std::string cmd, int socket_cli, Client &cli, size_t &idxCli);
        void handleAuthCmd(std::string cmdf, size_t &idxci);
        std::string recvCmd(int fdcli, size_t &idxcli);

        // void ft_join(std::vector<std::string> &vec_cmd,Client &client_,size_t &_index_client);
        // void kick(std::vector<std::string > vec_cmd,size_t _index_client, Client client_);
        // void topic(std::vector<std::string > vec_cmd,size_t _index_client,Client client_);
        // void privmsg(std::vector<std::string > vec_cmd, size_t _indexclient, Client client_);
        // void quit(std::vector<std::string > vec_cmd, size_t _indexclient, Client client_);




};
void sendMsgToCli(int fdcli, std::string msg);
int  parsingPortPass(std::string port, std::string pass);
void setNonBlocking(int fd);

#endif