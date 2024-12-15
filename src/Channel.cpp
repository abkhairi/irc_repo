/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamsate <shamsate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 15:00:23 by shamsate          #+#    #+#             */
/*   Updated: 2024/12/12 14:19:30 by shamsate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Channel.hpp"

mapUsers& Channel::getUsersMap() {
    return (_users);
};

void Channel::setUsersSize(int size) {
    _usersSize += size;
};


size_t Channel::getUsersize() {
    return (_usersSize);
};
