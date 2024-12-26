/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HandleCmd.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamsate <shamsate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 14:11:41 by shamsate          #+#    #+#             */
/*   Updated: 2024/12/26 02:01:04 by shamsate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/Server.hpp"

void printNmCh(Client cli){
    std::vector<std::string> chnm = cli.getChNm();
    std::vector<std::string>::iterator it = chnm.begin();
    for (it = chnm.begin(); it != chnm.end(); it++)
    {
        std::cout << "Name Of Channel : " << cli.getNickNm() << " Join = "<< *it << std::endl;
    }
};


std::string getStrCh(std::vector<std::string> vec){
    std::string ch = vec[1];
    // parsing = handeler par exmple [join #chan1,#chan2,,,,, key1,key2]
    return (ch);
};

std::string getListOfNames(std::map<std::pair<bool, int>, Client> _users)
{
    std::string listOfNames;
    std::map<std::pair<bool, int>, Client>::iterator iter;
    for (iter = _users.begin(); iter != _users.end(); iter++)
    {
        if (iter->first.first == true)
            listOfNames += "@" + iter->second.getNickNm() + " ";
        else
            listOfNames += iter->second.getNickNm() + " ";
    }
    return (listOfNames);
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

bool Server::isMember(int fdcli, Channels ch){
    std::map<std::pair<bool,int>, Client > user_map = ch.getMapUser();
    for(std::map<std::pair<bool,int>, Client >::iterator it = user_map.begin(); it != user_map.end(); it++)
    {
        if (fdcli == it->second.getCliFd())
            return  true;
    }
    return false;
};

void printInfoUser(Channels  &ch){
    std::map<std::pair<bool, int>, Client> usermap = ch.getMapUser();
    std::map<std::pair<bool, int>, Client>::iterator it2;
    for (it2 = usermap.begin() ; it2 != usermap.end(); it2++)
    {
        std::cout << WHITE << "+" << RESET << BLUE << "          Nickname  : "<< RESET << WHITE<< it2->second.getNickNm()<< RESET<< "                  "<<  std::endl;
        std::cout << WHITE << "+" << RESET << BLUE << "          Sock_fd   : "<< RESET << WHITE<< it2->second.getCliFd()<< RESET<< "                         "<<  std::endl;
        std::cout << WHITE << "+" << RESET << BLUE << "          Authentif : "<< RESET << WHITE<< it2->second.getAuth()<< RESET<< "                         "<<  std::endl;
        std::cout << WHITE << "+" << RESET << BLUE << "          Operator  : "<< RESET << WHITE<< it2->first.first<< RESET<< "                         "<<  std::endl;
        std::cout << WHITE << "---------------------------------------" << RESET << std::endl; 
    }
};


void printCh(std::map<std::string, Channels> ch){
    //print channel name and code
    std::map<std::string, Channels>::iterator it = ch.begin();
    for (it = ch.begin(); it != ch.end(); it++){
        std::cout << WHITE << std::setfill('+') << std::setw(15) << "+" << RESET;
        std::cout << YELLOW << " Channel " << RESET << WHITE<< std::setfill('+') << std::setw(15) << "+"<<RESET << std::endl;
        std::cout << WHITE << "+" << RESET << BLUE << " NAME of channel : "<< RESET << WHITE<< it->first<< RESET<< "            +"<<  std::endl;
        std::cout << WHITE << "+" << RESET << BLUE << " PASS of channel : "<< RESET << WHITE<< it->second.getPass()<< RESET<< "              +"<< std::endl;
        std::cout << WHITE << "+++++++++++++++++++++++++++++++++++++++" << RESET << std::endl;
        printInfoUser(it->second);
    }
};


