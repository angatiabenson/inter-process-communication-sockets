#ifndef SOCKET_H_
#define SOCKET_H_

#include <sys/socket.h>  
#include <sys/un.h>
#include <unistd.h> 
#include <cassert> 
#include <cerrno> 
#include <cstddef>
#include <cstdlib> 
#include <cstring> 
#include <string>
#include <iostream>

using namespace std;

class Socket {
 public:
  static const char kEoT = '\004';

  static const char kUS = '\037'; 


  explicit Socket(const char *socket_path, bool abstract = true);

  bool Setup(int domain = AF_UNIX, int type = SOCK_STREAM, int protocol = 0);

  bool Associate();

  bool Ready(size_t max_connections = 1) const;

  bool Join(int* client_request_socket_filedesc) const;

  bool Link() const;
  ::ssize_t Receive(string* buffer,
                 int socket_file_descriptor = 0,  
                 ::ssize_t return_after_bytes = 0, 
                 char end_of_transmission = Socket::kEoT) const;


  ::ssize_t Send(const string& bytes,
                  int socket_file_descriptor = 0, 
                  char end_of_transmission = Socket::kEoT) const;
  void Terminate(int socket_file_descriptor = 0) const;

 protected:
  int fd; 
  ::sockaddr_un addr_; 

  string path_; 
};

#endif 
