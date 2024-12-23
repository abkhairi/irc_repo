/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamsate <shamsate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 21:01:05 by shamsate          #+#    #+#             */
/*   Updated: 2024/12/23 21:01:10 by shamsate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/Server.hpp"

int main(int ac, char** av){
    if (ac != 3){
        std::cout << "Invalid args :( " << std::endl;
        return  1;
    }
    std::string port = av[1];
    std::string pass = av[2];

    int port_int = parsingPortPass(port, pass);
    if (port_int == 1)
    {
        std::cout << "Error in port :(" << std::endl;
        return 1;
    }
    if (port_int == 2){
        std::cout << "Error in Password :(" << std::endl;
        return 1;}
    Server irc(port_int, pass);
    size_t &i = irc.cliIdx;
    irc.init_serv(port_int, pass, i);
    return 0;
};