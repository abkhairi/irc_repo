#include "../include/Client.hpp"

std::string Client::getRecLn(){
    return _dataRec;
};

std::string Client::getIpAddrCli(){
    return (_ipAddrCli);
};

void    Client::setRealNm(std::string rname){
    _rname = rname;
};

std::string Client::getRealNm(){
    return (_rname);
}

;void Client::setAuth(){
    _auth = true;
};

void Client::setDataRec(std::string data){
    _dataRec = data;
};

void Client::displayCli(){
        std::cout <<"The Client Fd " << this->_cliSockFd << std::endl;
        std::cout <<"The Client Ip " << this->_ipAddrCli<< std::endl;
};

