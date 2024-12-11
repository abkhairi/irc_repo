/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamsate <shamsate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 17:49:30 by shamsate          #+#    #+#             */
/*   Updated: 2024/12/10 14:14:18 by shamsate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/Server.hpp"

int main(int argc, char **argv){
    signal(SIGPIPE, handle_sig);
    serverCheckRequirements(argc, argv[1], argv[2]);
    Server serv(atoi(argv[1]), argv[2]);
    serv.setSocketaddr();
    serv.runServ();

    struct pollfd Pfd;
    Pfd.fd = serv.getSkFd();
    Pfd.events = POLLIN;
    std::vector<struct pollfd> &_pollFd = serv.getPollfdVec();
    _pollFd.push_back(Pfd);
    size_t &idx = serv.idx;
    while (1){
        int x = poll(_pollFd.data(), _pollFd.size(), -1);
        if (x == -1){
            if (errno == EINTR)
                continue;
        }
        perror("poll");
        exit(1);
    }
    for ( idx = 0; idx < _pollFd.size(); idx++)
    {
        if (_pollFd[idx].revents & POLLIN)
        {
            if (_pollFd[idx].fd == serv.getSkFd())
                serv.eventOnServSock();
            else
                serv.eventOnCliSock();
        }
    }
};
