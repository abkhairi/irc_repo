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

Client::Client(int clisockfd, std::string ipaddrcli){
    _cliSockFd  = clisockfd;
    _ipAddrCli  = ipaddrcli;
    _auth        = false;
    _nick       = "";
    _CPass   = "";
    _user           = "";
    _pFlg      = false;
    _nFlg      = false;
    _uFlg      = false;
};

int Client::getCliFd(){
    return (_cliSockFd);
};

std::string Client::getNickNm(){
    return (_nick);
}

std::string Client::getPass(){
    return (_CPass);
}

std::string Client::getUser(){
    return (_user);
}

bool Client::getAuth(){
    return (_auth);
}