/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamsate <shamsate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 21:07:06 by shamsate          #+#    #+#             */
/*   Updated: 2024/12/26 21:07:12 by shamsate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Server.hpp"

void    Server::invite(std::vector<std::string > veccmd, size_t idxcli, Client cli)
{
    size_t index = 0;
    try 
    {
        channels &obj = getChannel(veccmd[2]);
        if(obj.existe_nick(veccmd[1]) == true)
            send(cli.getCliFd(), ERR_USERONCHANNEL(_hostIp, cli.getNickNm(), obj.getChNmDisplay()));
        else if(obj.check_if_operator(cli.getNickNm()) == false)
            sendMsgToCli(cli.getCliFd(), ERR_CHANOPRIVSNEEDED(cli.getNickNm(), obj.getChNmDisplay()));
        else 
        {
            if(veccmd.size() < 3) {
                sendMsgToCli(cli.getCliFd(), ERR_NEEDMOREPARAMS(cli.getNickNm(), veccmd[2]));
                return ;
            }
            if (!isMember(cli.getCliFd(), obj)) {
                sendMsgToCli(cli.getCliFd(), ERR_NOTONCHANNEL(cli.getNickNm(), veccmd[2]));
                return ;cliVec
            }
            while(index < cliVec.size())
            {
                if (cliVec[index].getNickNm() == veccmd[1])
                {
                        sendMsgToCli(cli.getCliFd(), RPL_INVITING(_hostIp, cli.getNickNm(), veccmd[1], veccmd[2]));//who invite 
                        sendMsgToCli(cliVec[index].getCliFd(), RPL_INVITE(cli.getNickNm(), cliVec[index].getUser(), _hostIp, veccmd[1], veccmd[2]));//c being invited
                        obj.setinvited(cliVec[index].getCliFd());
                        break ;
                }
                index++;
            }
        }
    }
    catch(const char *)
    {
        sendMsgToCli(cli.getCliFd(), ERR_NOSUCHCHANNEL(_hostIp, cli.getNickNm(), veccmd[2]));
        veccmd.clear();
        return ;
    }
}