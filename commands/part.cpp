#include "../include/Server.hpp"

void Server::part(std::vector<std::string> veccmd,size_t idxcli,Client cli)
{
    try
    {
        rmvFromCh(cli.getCliFd());
        channels &obj = getChannel(cmdVec[1]);
        if (obj.get_size_user() == 0)
            eraseCh(to_lower(cmdVec[1]));
        sendMsgToCli(cli.getCliFd(), RPL_QUIT(cli.getNickNm(),host_ip, "good bye"));
        sendMsgToCli(cli.getCliFd(), RPL_PART(cli.getNickNm(),cli.getUser(), host_ip, cmdVec[1]));
    }
    catch(const char *)
    {
        sendMsgToCli(cli.getCliFd(), ERR_NOSUCHCHANNEL(host_ip, cli.getNickNm(), cmdVec[1]));
        veccmd.clear();
        return ;
    }
}