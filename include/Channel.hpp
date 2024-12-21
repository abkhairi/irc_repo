/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamsate <shamsate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 14:43:26 by shamsate          #+#    #+#             */
/*   Updated: 2024/12/21 13:57:19 by shamsate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"
#include <vector>
#include <map>


// typedef std::map<std::pair<bool, int>, Client>mapUsers;

// class Channel{
//     private :
//         std::string _name;
//         std::string _pass;
//         std::string _topic;
//         std::string _nameToDisplay;
//         std::string _topicSeter;
//         std::string _topicTime;
//         size_t _usersSize;
//         size_t _limit;
//         bool   _userLimit;
//         bool   _topicFlag;
//         bool   _inv;
//         bool   _passFlag;
//         std::vector<int> _invit;
//         mapUsers _users;
//     public :
//         Channel();
//         Channel(std::string name);
//         ~Channel();

//         mapUsers &getUsersMap();
//         void setUsersSize(int size);
//         size_t getUsersize();
//         std::string getChDisplayNm();
// };