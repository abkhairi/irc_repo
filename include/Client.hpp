/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamsate <shamsate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 15:11:34 by shamsate          #+#    #+#             */
/*   Updated: 2024/12/12 14:22:14 by shamsate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <unistd.h>
#include <sys/socket.h>
#include <iostream>
#include <vector>
#include <arpa/inet.h>

class Client{
    private :
        int     _sock_Fd;
        std::string _ipAddss;
        std::string _UserName;
        std::string _RealName;
        std::string _NickName;
        std::string _recvln;
        std::vector<std::string> _channels;
        bool    _userFlag;
        bool    _passFlag;
        bool    _nickFlag;
        bool    _operat;
        bool    _authentif;
    public :
        Client();
        Client(int sockFd);
        ~Client();

        int Client::getClientFd();
        void Client::setIpAdss(std::string ipAdss);
        std::string Client::getNickNm();
        void Client::setRecLn(std::string recvln);
        std::string & Client::getRecLn();
};