/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JoinCh.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamsate <shamsate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 18:29:45 by shamsate          #+#    #+#             */
/*   Updated: 2024/12/16 18:53:11 by shamsate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Channel.hpp"

bool Server::alreadyMmember(int clifd, Channel channel)
{
    mapUsers mapOfClis = channel.getUsersMap();
    mapUsers::iterator it;
    for(it = mapOfClis.begin(); it != mapOfClis.end(); it++)
    {
        if (it->second.getClientFd() == clifd)
            return true;
    }
    return false;
};