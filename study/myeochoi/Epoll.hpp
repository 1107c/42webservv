#ifndef EPOLL_HPP
#define EPOLL_HPP

#include "Conf.hpp"
#include <sys/epoll.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
#include <netdb.h> 

class Epoll 
{
    private :
        const std::vector<std::vector<Location> >& _config;
        int _epollfd;
        std::vector<int> _socket;
        static const unsigned int MAX_EVENTS = 100; 
        
    public :
        Epoll(const Conf& config);
        Epoll(const Epoll &other);
        Epoll &operator&=(const Epoll &other);
        ~Epoll();
        void run();
        void initSocket();
        void bindSocket(const std::string &host, const unsigned int &port);
        void registerSeverSocket();
        void initClient();
        int isServerSocket(int &fd);
        void handleNewConnection(int &fd);
        void handleRead(int &fd);
        void handleWrite(int &fd);
        void handleClose(int &fd);
        void closeFd();
};

#endif