// #include <sys/epoll.h>
// #include <sys/socket.h>
// #include <netinet/in.h>
// #include <unistd.h>
// #include <fcntl.h>
// #include <string.h>
// #include <errno.h>
// #include <stdio.h> 
// #include <iostream>
// #include <sstream>
// #include <cstring>
// #include <fstream>
#include "Conf.hpp"
#include "Epoll.hpp"

// std::string create_http_response() {
//     std::ifstream file("home.html");
//     std::string html;
//     std::string line;
//     while (std::getline(file, line)) {
//         html += line + "\n";
//     }
//     std::ostringstream ss;
//     ss << html.size();
    
//     std::string response = "HTTP/1.1 200 OK\r\n";
//     response += "Content-Type: text/html\r\n";
//     response += "Content-Length: " + ss.str() + "\r\n";
//     response += "\r\n";
//     response += html;
//     return response;
// }
// int is_socket_nonblocking(int sockfd) {
//     int flags = fcntl(sockfd, F_GETFL, 0);
    
//     if (flags == -1) {
//         // 에러 발생
//         perror("fcntl");
//         return -1;
//     }
    
//     // O_NONBLOCK 플래그가 설정되어 있는지 확인
//     return (flags & O_NONBLOCK) != 0;
// }
int main(int args, char **argv)
{
    Epoll* epoll = NULL;

    try
    {
        Conf conf(Conf::checkInput(args, argv[1]));
        conf.parseConf();
        epoll = new Epoll(conf);
        epoll->run();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        if (epoll)
        {
            epoll->closeFd();
            delete epoll;
        }
    } 


    // // 3. epoll에 서버 소켓 등록
    // epoll_event ev;
    // ev.events = EPOLLIN | EPOLLET;  // EPOLLET는 엣지 트리거 모드
    // ev.data.fd = server_sock;
    // if (epoll_ctl(epfd, EPOLL_CTL_ADD, server_sock, &ev) == -1) {
    //     perror("epoll_ctl");
    //     return -1;
    // }

    // // 4. 이벤트 처리 루프
    // const int MAX_EVENTS = 100;
    // epoll_event events[MAX_EVENTS];
    
    // while (true) {
    //     // epoll_wait로 이벤트 대기
    //     int nfds = epoll_wait(epfd, events, MAX_EVENTS, -1);
    //     if (nfds == -1) {
    //         perror("epoll_wait");
    //         break;
    //     }

    //     // 발생한 이벤트 처리
    //     for (int i = 0; i < nfds; i++) {
                // if (events[i].data.fd == server_sock) {
                //     // 새로운 클라이언트 연결 처리
                //     while (true) {
                //         sockaddr_in client_addr;
                //         socklen_t client_len = sizeof(client_addr);
                //         int client_sock = accept(server_sock,
                //                                 (struct sockaddr*)&client_addr,
                //                                 &client_len);

                //         if (client_sock == -1) {
                //             if (errno == EAGAIN || errno == EWOULDBLOCK) {
                //                 break;
                //             }
                //             perror("accept");
                //             break;
                //         }
                //         // 소켓을 epoll에 바로 등록
                //         struct epoll_event ev;
                //         ev.events = EPOLLIN;
                //         ev.data.fd = client_sock;
                //         if (epoll_ctl(epfd, EPOLL_CTL_ADD, client_sock, &ev ) == -1) {
                //             perror("epoll_ctl");
                //             close(client_sock);
                //             break;
                //         }
                //     }
    //         } else {
    //             // 클라이언트로부터 데이터 수신 처리 11111 4
    //             char buffer[6];
    //             while (true) {
    //                 int len = read(events[i].data.fd, buffer, sizeof(buffer));
    //                 if (len == -1) {
    //                     if (errno == EAGAIN || errno == EWOULDBLOCK) {
    //                         std::cout << "end########\n";
    //                         // 더 이상 읽을 데이터 없음
    //                         break;
    //                     }
    //                     perror("read");
    //                     // 에러 발생 시 클라이언트 연결 종료
    //                     epoll_ctl(epfd, EPOLL_CTL_DEL, events[i].data.fd, NULL);
    //                     close(events[i].data.fd);
    //                     break;
    //                 } else if (len == 0) {
    //                     // 클라이언트가 연결을 종료함
    //                     epoll_ctl(epfd, EPOLL_CTL_DEL, events[i].data.fd, NULL);
    //                     close(events[i].data.fd);
    //                     break;
    //                 }
    //                 std::cout << "Received: " << std::string(buffer, len) << std::endl;
    //                 ssize_t written = write(events[i].data.fd, buffer, len);
    //                 if (written == -1) {
    //                     perror("write");
    //                     epoll_ctl(epfd, EPOLL_CTL_DEL, events[i].data.fd, NULL);
    //                     close(events[i].data.fd);
    //                     break;
    //                 } else if (written < len) {
    //                     std::cout << "Partial write occurred\n";
    //                     // 실제 프로덕션 환경에서는 여기서 남은 데이터를 처리해야 함
    //                 }
    //                 // std::string response = create_http_response();
    //                 // if (strncmp(buffer, "GET", 3) == 0)
    //                 //     write(events[i].data.fd, response.c_str(), strlen(response.c_str()));
    //             }
    //         }
    //     }
    // }

    // close(server_sock);
    // close(epfd);
    return 0;
}