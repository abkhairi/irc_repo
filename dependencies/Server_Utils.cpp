/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server_Utils.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamsate <shamsate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 17:52:52 by shamsate          #+#    #+#             */
/*   Updated: 2024/12/16 18:22:49 by shamsate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Server.hpp"

void handle_sig(int sig) {
        std::cout << "SIGPIPE Received, Avoid it." << std::endl;
        (void)sig;
};
//**********************************************************************************
std::string Server::tolowerstr(std::string _str1)
{
    size_t i = 0;
    std::string _lower = _str1;
    while (i < _str1.length())
    {
        _lower[i] = std::tolower(_str1[i]);
        i++;
    }
    return _lower;
};
