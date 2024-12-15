/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EventOnSocket.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamsate <shamsate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 14:17:28 by shamsate          #+#    #+#             */
/*   Updated: 2024/12/15 14:57:32 by shamsate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Server.hpp"

void Server::rmvFromCh(int idx) {
    // Iterate through all channels
    for (auto it = _channels.begin(); it != _channels.end(); it++) {
        // Access the users map of the current channel
        mapUsers &users = it->second.getUsersMap();
        // Iterate through users in the channel
        for (auto it2 = users.begin(); it2 != users.end(); it2++) {
            // If the client file descriptor matches
            if (it2->second.getClientFd() == idx) {
                // Broadcast a "QUIT" message to all other users in the channel
                broadcastMsg(it->second, RPL_QUIT(it2->second.getNickNm(), _host, "good bye"),idx);
                // Erase the user from the users map
                users.erase(it2);
                // Decrease the user count of the channel
                it->second.setUsersSize(-1);
                // Exit the loop once the user is removed
                break;
            }
        }
    }
};

/* ************************************************************************** */
void Server::eventOnServSock() {
    socklen_t cli_add_len = sizeof(_servAddr);
    int cliSockFd = accept(getSkFd(), (struct sockaddr *)&_servAddr, &cli_add_len);
    std::string cliIp = inet_ntoa(_servAddr.sin_addr);
    if (cliSockFd == -1)
        perror("accept");
    else
    {
        std::cout<<"New Connection From Cli , fd = "<< cliSockFd << " & IP : "<< std::endl;
        Client cli(cliSockFd);
        cli.setIpAdss(cliIp);
        setClient(cli);
        struct pollfd Pfd;
        Pfd.fd = cliSockFd;
        Pfd.events = POLLIN | POLLOUT;
        getPollfdVec().push_back(Pfd);
    }
};


void Server::eventOnCliSock(){
    std::vector<struct pollfd> &pollFd = getPollfdVec();
    int cli_sock_fd = pollFd[idx].fd;
    Client &cli =  getClientByFd(cli_sock_fd);
    char buffer[1024];
    memset(buffer, 0, 1024);
    ssize_t recvln = recv(cli_sock_fd, buffer, sizeof(buffer), 0);
    buffer[recvln] = '\0';
    if (recvln == -1)
        perror("recv");
    else if (recvln == 0){
        std::cout<<"Client : "<<cli_sock_fd<< " Disconnected "<<std::endl;
    close(cli_sock_fd);
    _pollFd.erase(_pollFd.begin() + idx);
    rmvClient(idx - 1);
    rmvFromCh(cli_sock_fd);
    idx--;
    channelMap::iterator it = _channels.begin();
    while (it != _channels.end())
    {
        if (it->second.getUsersize() == 0)
            it = _channels.erase(it);
        else
        ++it;
    }
    return ;
    }
    else
    {
        cli.setRecLn(buffer);
        memset(buffer, 0, 1024);
        if (strstr(cli.getRecLn().c_str(), "\n")){
            size_t pos = cli.getRecLn().find_first_of("\n");
            if (pos > cli.getRecLn().size())
                return ;
            std::string cmd = cli.getRecLn().substr(0, pos + 1);
            std::cout<< cmd <<std::endl;
            command(cmd, idx);
            cli.getRecLn() = cli.getRecLn().erase(0, pos + 1);
        }
    }
}