#include "../include/Server.hpp"


Server::Server(int port, std::string pass){
    _port = port;
    _pass = pass;
};

Server::~Server(){};



Client& Server::getCliByIdx(size_t idx){
    return (cliVec[idx]);
};

Client& Server::getCliOrg(int sockCli){
    for (size_t i = 0; cliVec.size() > i; i++)
    {
        if (cliVec[i].getCliFd() == sockCli)
            return (cliVec[i]);
    }
    return cliVec[0];
};

std::string Server::getHostIp(){
    return (_hostIp);
};

void    Server::display(){
    for (std::vector<struct pollfd>::iterator it = pollFdVec.begin(); it != pollFdVec.end(); it++)
    {
        std::cout << "Struct  Fd  = " << it->fd << std::endl;
        std::cout << "Struct Event  = " << it->events << std::endl;
        std::cout << "Struct Revent  = " << it->revents << std::endl;
    }
};

void  Server::rmvCli(int id){
    cliVec.erase(cliVec.begin() +id);
};

std::string Server::timee() {
    time_t now = time(0);
    char buffer[30];
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", std::localtime(&now));
    return std::string(buffer) + " (" + std::to_string(now) + ")";
};