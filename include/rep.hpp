/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rep.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamsate <shamsate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 13:47:04 by shamsate          #+#    #+#             */
/*   Updated: 2024/12/16 18:47:21 by shamsate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_HPP
# define HEADER_HPP

#define RPL_QUIT(nick, _host, message)                                       ":" + nick + "!" + "~" + nick + "@" + _host + " QUIT : " + message + "\r\n"
#define ERR_NOSUCHCHANNEL(buffer, nick, channel)                            ":" + buffer + " 403 " + nick + " " + channel + " :No such channel\r\n"
#define ERR_CANNOTSENDTOCHAN(buffer, channel)                               "404 " + buffer + " " + channel + " :Cannot send to channel\r\n"
#define ERR_NOSUCHCHANNEL(buffer, nick, channel)                            ":" + buffer + " 403 " + nick + " " + channel + " :No such channel\r\n"
#endif