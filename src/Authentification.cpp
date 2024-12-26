/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Authentification.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamsate <shamsate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 21:02:10 by shamsate          #+#    #+#             */
/*   Updated: 2024/12/26 02:15:14 by shamsate         ###   ########.fr       */
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

void    Server::SendToAll(Channels ch, std::string msg)
{
    std::map<std::pair<bool, int>, Client> mapOfClients = ch.getMapUser();
    std::map<std::pair<bool, int>, Client>::iterator iter;
    for(iter = mapOfClients.begin(); iter != mapOfClients.end(); iter++)
        sendMsgToCli(iter->second.getCliFd(), msg);
        // send_msg_to_clinet(iter->first.second, _message);
};






