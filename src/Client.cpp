/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamsate <shamsate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 15:27:47 by shamsate          #+#    #+#             */
/*   Updated: 2024/12/12 14:14:43 by shamsate         ###   ########.fr       */
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
