/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamsate <shamsate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 21:07:19 by shamsate          #+#    #+#             */
/*   Updated: 2024/12/26 21:07:21 by shamsate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Server.hpp"

void Server::part(std::vector<std::string> veccmd,size_t idxcli,Client cli)
{
    try
    {
        rmvFromCh(cli.getCliFd());
        channels &obj = getChannel(cmdVec[1]);
        if (obj.get_size_user() == 0)
            eraseCh(to_lower(cmdVec[1]));
        sendMsgToCli(cli.getCliFd(), RPL_QUIT(cli.getNickNm(),_hostIp, "good bye"));
        sendMsgToCli(cli.getCliFd(), RPL_PART(cli.getNickNm(),cli.getUser(), _hostIp, cmdVec[1]));
    }
    catch(const char *)
    {
        sendMsgToCli(cli.getCliFd(), ERR_NOSUCHCHANNEL(_hostIp, cli.getNickNm(), cmdVec[1]));
        veccmd.clear();
        return ;
    }
}