#include "../include/Server.hpp"

int  parsingPortPass(std::string port, std::string pass){
   if (port.empty())
        return 1;
    for (int i = 0; i < port.size(); i++){
        if (isdigit(port[i]) == 0)
            return 1;}
    int portNum = atoi(port.c_str());
    if (portNum < 0 || portNum > 65535)
        return 1;
    if (portNum < 1024)
        return 1;
    if (pass == "" || pass.empty())
        return 2;
    return (portNum);
};

void sendMsgToCli(int fdcli, std::string msg){
    ssize_t bytes = send(fdcli, msg.c_str(), msg.size(), 0);
    if (bytes == -1)
        perror("send: ");
};

std::string to_lower(std::string str){
    for (size_t i =0; str.size() > i; i++)
        str[i] = tolower(str[i]);
    return (str);
};

void setNonBlocking(int fd){
    int flg = fcntl(fd, F_GETFL, 0);
    if (flg == -1) {
        perror("fcntl");
        exit(EXIT_FAILURE);}
    if (fcntl(fd, F_SETFL, flg | O_NONBLOCK) == -1) {
        perror("fcntl");
        exit(EXIT_FAILURE);
    }
};