#ifndef SERVER_H_
#define SERVER_H_

#include "socket.h"

#include <sys/socket.h>
#include <sys/sysinfo.h>
#include <sys/un.h>
#include <unistd.h>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
#include <cerrno>
#include <cstddef>
#include <cstdlib>
#include <cstring>

using namespace std;

class Server : public Socket {
 public:
  using ::Socket::Socket;

  void Run();
};

#endif  // SERVER_H
