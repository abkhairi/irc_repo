/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channels.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamsate <shamsate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 16:18:55 by shamsate          #+#    #+#             */
/*   Updated: 2024/12/26 01:37:00 by shamsate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNELS_HPP
#define CHANNELS_HPP

#include "Server.hpp"
#include "Client.hpp"

class Client;
class Server;

class Channels{
    private :
        bool            _inv;
        bool            _flgPass;
        bool            _topc;
        bool            _userLimit;
        size_t          _limit;
        size_t          _userSize;
        std::string     _name;
        std::string     _topicSetter;
        std::string     _topicTime;
        std::string     _pass;
        std::string     _topic;
        std::string     _nmChDisplay;
        std::map<std::pair<bool, int>, Client>_users;
        std::vector<int>_invited;
    public :
        Channels(std::string    nmch);
        void pushToMap(bool priv, Client &cli);
        //:::::::::::::::::setter::::::::::::::::::
        void setPass(std::string pass);
        void setFlgpass(bool flgpass);
        void setSizeUser(size_t sizeuser);
        void setNmDisplay(std::string name);
        void setInv(bool inv);
        void setTopic(std::string topic) ;
        void  setTopicAttr(std::string topic, bool topc, std::string seter, std::string time);
       //:::::::::::::::::Getter::::::::::::::::::
        bool            getInv();
        bool            getSiUserLimit();
        std::string     getPass();
        bool            getFlgpass();
        size_t          getSizeuser();
        std::string     getNmCh();
        size_t          getLimit();
        std::string     getNmChDispaly();
        std::map<std::pair<bool,int>, Client>& getMapUser();
        std::string     getTopic();
        bool            getTopicBool();
        std::string     getTopicSeter();
        std::string     getTopicTime();
        bool            checkIfOperat(std::string nickname);
        bool            nickExist(std::string user);
        //
        bool	        isInvited(int sockfd);
        void            deleteCli(std::string nick);
};
#endif