/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamsate <shamsate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 15:27:47 by shamsate          #+#    #+#             */
/*   Updated: 2024/12/16 18:34:04 by shamsate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Client.hpp"

void Client::setIpAdss(std::string ipAdss) {
    _ipAddss = ipAdss;
};

int Client::getClientFd() {
    return (_sock_Fd);
};


std::string Client::getNickNm(){
    return (_NickName);
};


void Client::setRecLn(std::string recvln) {
    _recvln = recvln;
};

std::string & Client::getRecLn() {
    return (_recvln);
};

Client::Client(){
    _passFlag   = false;
    _nickFlag   = false;
    _userFlag   = false;
    _authentif  = false;
    _operat     = false;
};

Client::Client(int sockfd){
    _sock_Fd = sockfd;
    _passFlag   = false;
    _nickFlag   = false;
    _userFlag   = false;
    _authentif  = false;
    _operat     = false;
};

Client::~Client(){};

