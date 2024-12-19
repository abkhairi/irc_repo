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

std::string Client::getRealNm(){
    return _RealName;
};

std::string Client::getUserNm(){
    return _UserName;
};

void Client::setRealNm(std::string rnm){
    _RealName = rnm;
};

void Client::setUserNm(std::string usm){
    _UserName = usm;
};

bool  Client::getpflag(){
    return _passFlag;
};

bool Client::getnflag(){
    return _nickFlag;
};

bool Client::getuflag(){
    return _userFlag;
};
bool Client::getOperator(){
    return _operat;
};

std::string & Client::getIpAdss(){
    return _ipAddss;
};

void Client::setNickNm(std::string kname){
    _NickName = kname;
};

void Client::setpflg(bool flg){
    _passFlag = flg;
};

void Client::setnflg(bool flg){
    _nickFlag = flg;
};
void Client::setuflg(bool flg){
    _userFlag = flg;
    _authentif = true;
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

