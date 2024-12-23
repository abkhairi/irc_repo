#ifndef CLIENT_H
#define CLIENT_H

#include "Server.hpp"

class Client{
    private :
        int             _cliSockFd;
        std::string     _ipAddrCli;
        std::string     _dataRec;
        std::string     _nick;
        std::string     _CPass;
        std::string     _user;
        std::string     _rname;
        bool            _auth;
        bool            _pFlg;
        bool            _uFlg;
        bool            _nFlg;
        std::vector<std::string>_channels;
    public :
        Client(int _cliSockFd, std::string _ipAddrCli);
        void            displayCli();
        //:::::::::Getters:::::::::::::::
        int             getCliFd();
        std::string     getRecLn();
        std::string     getNickNm();
        std::string     getPass();
        std::string     getUser();
        std::string     getRealNm();
        std::string     getIpAddrCli();
        std::vector<std::string>getChNm();
        //:::::::::Setters:::::::::::::::
        void    setDataRec(std::string data);
        void    setFlgPass(bool flgpass);
        void    setFlgNick(bool flgnick);
        void    setFlgUser(bool flguser);
        void    setNickNm(std::string nicknm);
        void    setPass(std::string pass);
        void    setUser(std::string user);
        void    setRealNm(std::string rname);
        void    setAuth();
        //:::::::::Channel:::::::::::::::
        void    pushCh(std::string ch);
};

#endif