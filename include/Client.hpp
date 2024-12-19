/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamsate <shamsate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 15:11:34 by shamsate          #+#    #+#             */
/*   Updated: 2024/12/16 16:53:17 by shamsate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <unistd.h>
#include <sys/socket.h>
#include <iostream>
#include <vector>
#include <arpa/inet.h>

class Client{
/* *************************************************** */
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
/* *************************************************** */
    public :
        Client();
        Client(int sockFd);
        ~Client();
/* *************************************************** */
        std::vector<std::string>getChs();
/* *************************************************** */
        int getClientFd();
        std::string getRealNm();
        std::string getUserNm();
        std::string getNickNm();
/* *************************************************** */
        void setIpAdss(std::string ipAdss);
        void setRealNm(std::string rlnm);
        void setUserNm(std::string usrnm);
        void setNickNm(std::string NickNm);
        void setRecLn(std::string recvln);
        void setOperator(bool flg);
        void setpflg(bool flg);
        void setnflg(bool flg);
        void setuflg(bool flg);
/* *************************************************** */
        bool		isAuthed();
	bool		getpflag();
	bool		getnflag();
	bool		getuflag();
	bool		getOperator();
/* *************************************************** */
        std::string &getRecLn();
        std::string &getIpAdss();
/* *************************************************** */
        void pushCh(std::string Ch);
};
/* *************************************************** */