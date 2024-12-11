/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EventOnSocket.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamsate <shamsate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 14:17:28 by shamsate          #+#    #+#             */
/*   Updated: 2024/12/11 14:42:48 by shamsate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Server.hpp"

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
    rmvClient(idx);
    
    }
}