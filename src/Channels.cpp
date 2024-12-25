/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channels.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamsate <shamsate@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-12-25 14:20:58 by shamsate          #+#    #+#             */
/*   Updated: 2024-12-25 14:20:58 by shamsate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/Channels.hpp"

bool Server::isMember(int fdcli, Channels ch){
    std::map<std::pair<bool,int>, Client > usermap = ch.getMapUser();
    for(std::map<std::pair<bool,int>, Client >::iterator it = usermap.begin(); it != usermap.end(); it++)
    {
        if (fdcli == it->second.getCliFd())
            return  true; 
    }
    return (false);
};

