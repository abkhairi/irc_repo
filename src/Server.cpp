#include "../include/Server.hpp"


Server::Server(int port, std::string pass){
    _port = port;
    _pass = pass;
};

Server::~Server(){};




std::string Server::getHostIp(){
    return (host_ip);
};

void    Server::display(){
    for (std::vector<struct pollfd>::iterator it = vec_pollfd.begin(); it != vec_pollfd.end(); it++)
    {
        std::cout << "Struct  Fd  = " << it->fd << std::endl;
        std::cout << "Struct Event  = " << it->events << std::endl;
        std::cout << "Struct Revent  = " << it->revents << std::endl;
    }
};

void  Server::rmvCli(int id){
    vec_client.erase(vec_client.begin() +id);
};

std::string Server::timee() {
    time_t now = time(0);
    char buffer[30];
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", std::localtime(&now));
    return std::string(buffer) + " (" + std::to_string(now) + ")";
};