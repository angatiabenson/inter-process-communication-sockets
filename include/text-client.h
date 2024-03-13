#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>
#include <vector>
#include <string>

#include "socket.h"
#include "calculator.h"

using namespace std;

class Client : public Socket
{
public:
  using Socket::Socket;
  string inputData;
  void Execute();
};

#endif // CLIENT_H
