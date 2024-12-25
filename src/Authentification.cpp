/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Authentification.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamsate <shamsate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 21:02:10 by shamsate          #+#    #+#             */
/*   Updated: 2024/12/25 21:21:51 by shamsate         ###   ########.fr       */
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

void Server::handleAuthCmd(std::string cmdf, size_t &idxci){

std::vector<std::string> &cmdvec = cmdVec;
    // ft_gethostname();
    char hostnm[256]; // Buffer to store the hostname
    if (gethostname(hostnm, sizeof(hostnm)) != 0)
        std::cerr << "Error retrieving hostname: " << strerror(errno) << std::endl;
    _hostIp = hostnm;

    Client &cli = getCliByIdx(cliIdx - 1);
    std::string nick = cli.getNickNm();

    // std::cout << "size of vector = " << vec_of_commande.size() << std::endl;
    // ici segfault if nc localhost 4545 after click sur entre hhhhhh
    if (cli.getAuth() == false)
    {
        if (cmdvec.size() <= 1)
        {
            if (cmdVec[0] == "nick")
                sendMsgToCli(cli.getCliFd(), ERR_NONICKNAMEGIVEN(nick, _hostIp));
            else if (cmdVec[0] != "nick" || cmdvec.size() == 0)
                sendMsgToCli(cli.getCliFd(), ":IRC ==> 461 :Not enough parameters\r\n");
            cmdvec.clear();
            return ;
        }
        if (cmdvec[0] == "pass" && cmdVec[1] == _pass && cli.getFlgPass() == false)
        {
            if (cmdvec.size() == 2)
            {
                // std::cout << "is a pass cmd" << std::endl;
                cli.setFlgPass(true);
                cli.setPass(cmdVec[1]);
            }
            else
                sendMsgToCli(cli.getCliFd(), ":IRC ==> 464 :Password incorrect\r\n");
            cmdvec.clear();
            return ;
        }
        else if (cmdVec[0] == "pass" && cmdVec[1] != _pass && cli.getFlgPass() == false)
        {
            sendMsgToCli(cli.getCliFd(), ":IRC ==> 464 :Password incorrect\r\n");
            cmdvec.clear();
            return ;
        }
        if (cmdVec[0] == "nick" && cmdvec.size() == 2 && cli.getFlgNick() == false)
        {
            // check if any client in vector has the same nickname ft_check_nickname()
            cli.setFlgNick(true);
            cli.setNickNm(cmdVec[1]);
            cmdvec.clear();
            return ;
        }
        else if (cmdVec[0] == "nick" && cmdvec.size() > 2 && cli.getFlgNick() == false)
        {
            sendMsgToCli(cli.getCliFd(), ":IRC ==> 432 :Erroneous nickname\r\n");
            cmdvec.clear();
            return ;
        }
        if (cmdVec[0] == "user" && cli.getFlgNick() && cli.getFlgPass())
        {
            // std::cout << "herre fi user\n";
            if (cmdvec.size() > 5 || cmdVec[1].empty())
            {
                sendMsgToCli(cli.getCliFd(), ":irc.abkhairi.chat 461 :Need more parameters\r\n");
                cmdvec.clear();
                return ;
            }
            else
            {
                cli.setFlgUser(true);
                cli.setUser(cmdVec[1]);
                cli.setRealNm(cmdVec[5]);
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
        if (cmdVec[0] == "pass" || cmdVec[0] == "user")
        {
            sendMsgToCli(cli.getCliFd(), ERR_ALREADYREGISTERED(nick, _hostIp));
            cmdvec.clear();
            return ;
        }
        else if(cmdVec[0] == "nick")
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


