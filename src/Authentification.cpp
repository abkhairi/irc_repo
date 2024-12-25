/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Authentification.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamsate <shamsate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 21:02:10 by shamsate          #+#    #+#             */
/*   Updated: 2024/12/23 21:02:14 by shamsate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Server.hpp"
#include "../include/Client.hpp"

std::string getHostNm(){
    char    hostnm[256];
    if (gethostname(hostnm, sizeof(hostnm)) != 0)
        std::cerr<< " Error retrieving hostname: " << strerror(errno) << std::endl;
    std::string hostip = hostnm;
    return (hostip); 
};

void Server::isRegistred(Client &cli, std::string time){
    sendMsgToCli(cli.getCliFd(),RPL_WELCOME(cli.getNickNm(), cli.getIpAddrCli()));
    sendMsgToCli(cli.getCliFd(),RPL_YOURHOST(cli.getNickNm(), cli.getIpAddrCli()));
    sendMsgToCli(cli.getCliFd(),RPL_CREATED(cli.getNickNm(), cli.getIpAddrCli(), time));
    sendMsgToCli(cli.getCliFd(),RPL_MYINFO(cli.getNickNm(), cli.getIpAddrCli()));
};

void Server::handleAuthCmd(std::string cmdf, size_t &idxci){
    
}

