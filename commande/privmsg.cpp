#include "../include/Server.hpp"

void Server::privmsg(std::vector<std::string > vec_cmd, size_t _indexclient, Client client_)
{
    std::string msg;

    for(size_t i = 0; i < vec_cmd.size(); i++)
    {
        if(i > 1)
        {
            if (vec_cmd[2][0] == ':')
                msg += vec_cmd[i] + " ";
            else
            {
                msg = vec_cmd[2];
                break;
            }
        }
    }
    if (msg[0] == ':')
        msg = msg.substr(1);
    sendMessage(client_, vec_cmd[1], msg);
}

void    serverr::sendMessage(cliente &client, std::string vec1, std::string _message)
{
    std::string senderNick = client.getNickNm(); // abkhairi
    std::string senderUsername = client.getUser(); // a
    if (channels_.size() == 0 && vec1[0] == '#') // if not have channel 
    {
        sendMsgToCli(client.getCliFd(), ERR_NOSUCHCHANNEL(senderNick, senderNick, vec1));
        return ;
    }
    std::map<std::string, channels>::iterator it = channels_.find(to_lower(vec1));
    if (it != channels_.end())
    {
        if (isMember(client.getCliFd(), it->second) == false) // if client not membre in channel o bera iresl msg hhh
        {
            sendMsgToCli(client.getCliFd(), ERR_CANNOTSENDTOCHAN(senderNick, it->second.getNmChDispaly()));
            return ;
        }
        // here send msg to all client sauf client li rasel msg
        broadcastMessage(it->second, ":" + senderNick + "!~" + senderUsername + "@127.0.0.1 PRIVMSG " + vec1 + " :" + _message + "\r\n", client.getCliFd());
    }
    else if (vec1[0] == '#')
    {
        sendMsgToCli(client.getCliFd(), ERR_NOSUCHCHANNEL(senderNick, senderNick, it->second.get_name_chan()));
        return ;
    }
    else
    {
        size_t i = 0;
        while(i < vec_client.size())
        {
            if (vec_client[i].getNickNm() == vec1)
            {
                sendMsgToCli(vec_client[i].getCliFd(), ":" + senderNick + "!~" + senderUsername + "@127.0.0.1 PRIVMSG " + vec1 + " :" + _message + "\r\n");
                return ;
            }
            i++;
        }
    }
}
