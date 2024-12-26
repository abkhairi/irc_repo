/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamsate <shamsate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 21:10:41 by shamsate          #+#    #+#             */
/*   Updated: 2024/12/26 21:10:43 by shamsate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Server.hpp"

int Server::modeSplit(std::string vec_cmd, Client client_){
    // vec_of_cmd = "MODE #chan1 +o nickname +k key";
    //vec_cmd = "+o nickname +k key"
    std::cout << "vec_cmd ===>  " << vec_cmd << std::endl;
    char x;
    std::string res;
    int idex = 3;
    for(int i = 1; vec_cmd[i]; i++) 
    {
        if (vec_cmd[i] != '-' && vec_cmd[i] != '+' && vec_cmd[i] != 'i' 
        && vec_cmd[i] != 't' && vec_cmd[i] != 'o' && vec_cmd[i] != 'k' && vec_cmd[i] != 'l' && vec_cmd[i] != 's' && vec_cmd[i] != 'n') 
        {
            sendMsgToCli(client_.getCliFd(), ERR_UNKNOWNMODE(_hostIp,client_.getNickNm(), vec_cmd[i]));
            return 1;
        }
        if (vec_cmd[i] == '-' || vec_cmd[i] == '+')
            x = vec_cmd[i++];
        if (x == '-') {
            res = "-";
            res += vec_cmd[i];
        }
        else
        {
            res  = "+";
            res += vec_cmd[i];
        }
        if (vec_cmd[i] == 'o' || vec_cmd[i] == 'k' || vec_cmd[i] == 'l')
            mod.push_back(std::make_pair(res,cmdVec[idex++]));
        else
            mod.push_back(std::make_pair(res,""));
    }
    return 0;
}

void Server::mode(std::vector<std::string > veccmd, size_t idxcli, Client cli)
{
    // MODE <channel> <mode> [<parameters>]
    std::string channel;
    std::string channel_name;
    if (veccmd.size() < 2)
    {
        sendMsgToCli(cli.getCliFd(), ERR_NEEDMOREPARAMS(cli.getNickNm(), _hostIp));
        veccmd.clear();
        return ;
    }
    try
    {
        channels &obj_chan = getChannel(veccmd[1]);
        channel = cli.getNickNm();
        channel_name = obj_chan.get_name_chanel_display();
        if (veccmd.size() > 2)veccmd
        {
            if (modeSplit(veccmd[2], cli) == 1)
            {
                mod.clear();
                veccmd.clear();
                return ;
            }
        }
        std::cout << "channel found secssusfly '*`" << std::endl;
        for (size_t i = 0 ; i < mod.size(); i++)
        {
            if (mod[i].first == "+i")
            {
                if (obj_chan.get_inv() == true)
                    sendMsgToCli(getCliByIdx(idxcli - 1).getCliFd(), RPL_ALLINV(veccmd[1]));
                else if (obj_chan.check_if_operator(channel) == false)
                    sendMsgToCli(getCliByIdx(idxcli - 1).getCliFd(), ERR_CHANOPRIVSNEEDED(_hostIp,channel_name));
                else
                {
                    SendToAll(obj_chan, RPL_MODE(obj_chan.getNmChDispaly(), cli.getNickNm(), "+i"));
                    obj_chan.set_inv(true);
                }
            }
            else if (mod[i].first == "-i")
            {
                if (obj_chan.get_inv() == false)
                    sendMsgToCli(getCliByIdx(idxcli - 1).getCliFd(), RPL_NOTINV(veccmd[1]));
                else if (obj_chan.check_if_operator(channel) == false)
                    sendMsgToCli(getCliByIdx(idxcli - 1).getCliFd(), ERR_CHANOPRIVSNEEDED(_hostIp,channel_name));
                else {
                    SendToAll(obj_chan, RPL_MODE(obj_chan.getNmChDispaly(), cli.getNickNm(), "-i"));
                    obj_chan.set_inv(false);
                }
            }
            if (mod[i].first == "+t")
            {
                if (obj_chan.check_if_operator(channel) == false)
                    sendMsgToCli(getCliByIdx(idxcli - 1).getCliFd(), ERR_CHANOPRIVSNEEDED(_hostIp,channel_name));
                else    
                {
                    SendToAll(obj_chan, RPL_MODE(obj_chan.get_name_chanel_display(), client_.get_nickname(), "+t"));
                    obj_chan.set_topic_bool(true);
                }
            }
            else if ( mod[i].first == "-t")
            {
                if (obj_chan.check_if_operator(channel) == false)
                    send_msg_to_clinet(get_client_by_index(_index_client - 1).get_client_fd(), ERR_CHANOPRIVSNEEDED(host_ip,channel_name));
                else    
                {
                    SendToAll(obj_chan, RPL_MODE(obj_chan.get_name_chanel_display(), client_.get_nickname(), "-t"));
                    obj_chan.set_topic_bool(false);
                } 
            }
            if (mod[i].first == "+k")
            {
                if(vec_cmd.size() < 4)
                    send_msg_to_clinet(get_client_by_index(_index_client - 1).get_client_fd(), RPL_NOKEY(client_.get_nickname(), channel_name, "k"));
                else if(obj_chan.get_password() == mod[i].second)
                    send_msg_to_clinet(get_client_by_index(_index_client - 1).get_client_fd(), RPL_ALREADYSET(client_.get_nickname()));
                else if (obj_chan.check_if_operator(channel) == false) 
                    send_msg_to_clinet(get_client_by_index(_index_client - 1).get_client_fd(), ERR_CHANOPRIVSNEEDED(host_ip,channel_name));
                else 
                {
                    SendToAll(obj_chan, RPL_MODE(obj_chan.get_name_chanel_display(), client_.get_nickname(), "+k " + mod[i].second));
                    obj_chan.set_password(mod[i].second);
                    obj_chan.setPass(true);
                }
            }
            else if (mod[i].first == "-k")
            {
                if(obj_chan.getPass() == false)
                    send_msg_to_clinet(get_client_by_index(_index_client - 1).get_client_fd(), RPL_NOPASSSET(client_.get_nickname()));
                else if(obj_chan.get_password() != mod[i].second)
                    send_msg_to_clinet(get_client_by_index(_index_client - 1).get_client_fd(), RPL_PASSNOTC(mod[i].second));
                else if (obj_chan.check_if_operator(channel) == false) 
                    send_msg_to_clinet(get_client_by_index(_index_client - 1).get_client_fd(), ERR_CHANOPRIVSNEEDED(host_ip,channel_name));
                else {
                    SendToAll(obj_chan, RPL_MODE(obj_chan.get_name_chanel_display(), client_.get_nickname(), "-k " + mod[i].second));
                    obj_chan.get_password().erase();
                    obj_chan.setPass(false);
            }
            if (mod[i].first == "+o")
            {
                try 
                {
                    if (vec_cmd.size() < 4)
                        send_msg_to_clinet(get_client_by_index(_index_client - 1).get_client_fd(), RPL_NOKEY(client_.get_nickname(), channel_name, "o"));
                    else if(obj_chan.check_if_operator(channel) == false)
                        send_msg_to_clinet(get_client_by_index(_index_client - 1).get_client_fd(), ERR_CHANOPRIVSNEEDED(host_ip,channel_name));
                    else if(obj_chan.check_if_operator(mod[i].second) == true)    
                        send_msg_to_clinet(get_client_by_index(_index_client - 1).get_client_fd(), RPL_ALLOP(mod[i].second));
                    else 
                    {
                        obj_chan.getUserBynickname(mod[i].second);
                        obj_chan.setPrvByNickname(mod[i].second, true);
                        SendToAll(obj_chan, RPL_MODE(obj_chan.get_name_chanel_display(), client_.get_nickname(), "+o " + mod[i].second));
                    }
                }    
                catch(const char *) 
                {
                        send_msg_to_clinet(get_client_by_index(_index_client - 1).get_client_fd(), ERR_WASNOSUCHNICK(host_ip,channel));
                }
            }
            else if (mod[i].first == "-o")
            {
                if(vec_cmd.size() < 4)
                    send_msg_to_clinet(get_client_by_index(_index_client - 1).get_client_fd(), ERR_NEEDMOREPARAM(host_ip,"-o"));
                else if(obj_chan.check_if_operator(channel) == false)
                    send_msg_to_clinet(get_client_by_index(_index_client - 1).get_client_fd(), ERR_CHANOPRIVSNEEDED(host_ip,channel_name));
                else if(obj_chan.check_if_operator(mod[i].second) == false)
                    send_msg_to_clinet(get_client_by_index(_index_client - 1).get_client_fd(), RPL_NOTOP(mod[i].second));
                else 
                {
                    try 
                    {
                        obj_chan.getUserBynickname(mod[i].second);
                        obj_chan.setPrvByNickname(mod[i].second, false);
                        SendToAll(obj_chan, RPL_MODE(obj_chan.get_name_chanel_display(), client_.get_nickname(), "-o " + mod[i].second));
                    }
                    catch(const char *) 
                    {
                        send_msg_to_clinet(get_client_by_index(_index_client - 1).get_client_fd(), ERR_WASNOSUCHNICK(host_ip,channel));
                    }
                }
            }
            if (mod[i].first == "+l")
            {
                if(vec_cmd.size() < 4) 
                {
                    send_msg_to_clinet(get_client_by_index(_index_client - 1).get_client_fd(), RPL_NOKEY(client_.get_nickname(), channel_name, "l"));
                    vec_cmd.clear();
                    return ;
                }
                std::stringstream ss(mod[i].second);
                size_t limit;
                ss >> limit;
                if (obj_chan.get_limit() == limit)
                    send_msg_to_clinet(get_client_by_index(_index_client - 1).get_client_fd(), RPL_LIMITSET(mod[i].second));
                else 
                {
                    obj_chan.setUserLimit(false);
                    obj_chan.setLimit(limit);
                    obj_chan.setUserLimit(true);
                    SendToAll(obj_chan, RPL_MODE(obj_chan.get_name_chanel_display(), client_.get_nickname(), "+l " + mod[i].second));
                }
            }
            else if (mod[i].first == "-l")
            {
                if(obj_chan.getUserLimit() == false)
                    send_msg_to_clinet(get_client_by_index(_index_client - 1).get_client_fd(), RPL_NOLIMITSET(client_.get_nickname()));
                else 
                {
                    obj_chan.setUserLimit(false);
                    obj_chan.setLimit(-1);
                    SendToAll(obj_chan, RPL_MODE(obj_chan.get_name_chanel_display(), client_.get_nickname(), "-l"));
                }
            }
        }
    }
    }
    catch(const char *) 
    {
        send_msg_to_clinet(client_.get_client_fd(), ERR_NOSUCHCHANNEL(host_ip, client_.get_nickname(), vec_cmd[1]));
        mod.clear();
        vec_cmd.clear();
        return ;
    }
}
