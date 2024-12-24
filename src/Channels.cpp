/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channels.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamsate <shamsate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 21:02:02 by shamsate          #+#    #+#             */
/*   Updated: 2024/12/23 21:02:06 by shamsate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Channels.hpp"

Channels::Channels(std::string nmch){
    _name = nmch;
    _inv = false;
    _flgPass = false;
    _topc = false;
    _limit = -1;
    _userSize = 0;
};

bool Channels::getTopicBool(){
    return (_topc);
};

std::string     Channels::getTopicSeter() {
    return (_topicSetter);
}

std::string     Channels::getTopicTime() {
    return (_topicTime);
};

void    Channels::setTopicAttr(std::string topic, bool topc, std::string seter, std::string time) {
    _topicSetter = seter;
    _topicTime = time;
    _topic = topic;
    _topc = topc;
};

std::string     Channels::getTopic() {
    return _topic;
}

void     Channels::setTopic(std::string topic) {
     _topic = topic;
}

bool	Channels::isInvited(int sockfd){
	std::vector<int>::iterator it = std::find(_invited.begin(), _invited.end(), sockfd);
    if(it != _invited.end())
    {
        return true;
    }
    return false;
}


bool Channels::getInv(){
    return (_inv);
}

void Channels::setInv(bool in){
    _inv = in;
}

bool Channels::getSiUserLimit(){
    return (_userLimit);
}

size_t Channels::getSizeuser(){
    return (_userSize);
}

size_t Channels::getLimit(){
    return (_limit);
}

std::string Channels::getNmChDispaly(){
    return (_nmChDisplay);
}

void Channels::setNmDisplay(std::string name){
    _nmChDisplay = name;
}


void Channels::pushToMap(bool privilege, Client &client_){
    std::pair<bool, int> paire(privilege, client_.getCliFd());
	_users.insert(std::make_pair(paire, client_));
}

std::string Channels::getNmCh(){
    return (_name);
}

std::string Channels::getPass(){
    return (_pass);
}

std::map<std::pair<bool,int>, Client >& Channels::getMapUser(){
	return _users;
}


void Channels::setSizeUser(size_t size_user){
    _userSize = size_user + _userSize; 
}

bool Channels::getFlgpass(){
    return (_flgPass);
}
void Channels::setPass(std::string password){
    _pass = password;
}

void Channels::setFlgpass(bool flagpass){
    _flgPass = flagpass;
}

bool    Channels::checkIfOperat(std::string nickname){
    std::map<std::pair<bool, int>, Client>::iterator it = _users.begin();

    for(; it != _users.end(); it++) 
    {
        if(it->second.getNickNm() == nickname)
            return it->first.first;
    }
    return false;
}

bool Channels::nickExist(std::string user){
    std::map<std::pair<bool, int>, Client>::iterator it = _users.begin();
    for (it = _users.begin(); it != _users.end(); it++)
    {
        if (it->second.getNickNm() == user)
            return (true);
    }
    return (false);
};

void Channels::deleteCli(std::string nick)
 {
    std::map<std::pair<bool, int>, Client>::iterator it = _users.begin();
    for (it = _users.begin(); it != _users.end(); it++) 
    {
        if (it->second.getNickNm() == nick)
            _users.erase(it++);
    }
};
