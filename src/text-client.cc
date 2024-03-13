#include "../include/text-client.h"

vector<string> decodeMessage(string message)
{
  vector<string> decodedLines;
    string header = "";
    string calcExpression = "";
    bool colonEncountered = false;

    for (size_t index = 0; index < message.length(); ++index) {
        if (!colonEncountered) {
            if (message[index] == ':') {
                colonEncountered = true; // Include the colon as part of the header
                header += message[index];
            } else {
                header += message[index];
            }
        } else {
            if (message[index] == Socket::kUS) {
                if (!calcExpression.empty()) { // Ensure there's an expression to process
                    decodedLines.push_back(header + calcExpression + " = " + calculator::calculate_from_string(calcExpression));
                } else {
                    decodedLines.push_back(header); // In case there's no expression, just add the header
                }
                // Reset for the next line
                header = "";
                calcExpression = "";
                colonEncountered = false;
            } else {
                calcExpression += message[index];
            }
        }
    }

    // Handle the last line if message does not end with Socket::kUS
    if (colonEncountered && !calcExpression.empty()) {
        decodedLines.push_back(header + calcExpression + " = " + calculator::calculate_from_string(calcExpression));
    } else if (!header.empty()) {
        decodedLines.push_back(header); // In case the last line is only a header
    }

    return decodedLines;
}

void Client::Execute()
{
  if (!Setup() || !Link())
  {
    cerr << "SocketClient terminating..." << endl;
    exit(1);
  }

  cout << "SERVER CONNECTION ACCEPTED" << endl;

  auto bytesSent = Send(inputData);
  if (bytesSent < 0)
  {
    cerr << "SocketClient terminating..." << endl;
    exit(2);
  }
  else if (bytesSent == 0)
  {
    cerr << "Server disconnected" << endl;
    exit(3);
  }

  string serverResponse;
  ssize_t bytesRead = Receive(&serverResponse);

  if (bytesRead < 0)
  {
    cerr << "Error reading from server: " << ::strerror(errno) << endl;
    exit(4);
  }
  else if (bytesRead == 0)
  {
    cerr << "Server disconnected" << endl;
    return;
  }

  vector<string> decodedMessages = decodeMessage(serverResponse);
  //cout<<serverResponse<<endl;
  //cout<<decodedMessages.size()<<endl;
  for (const string &message : decodedMessages)
  {
    cout << message << endl;
  }
  cout << "BYTES RECEIVED: " << bytesRead << endl;
}

int main(int argc, char *argv[])
{
  char* socketPath = argv[1];
  Client socketClient(socketPath);
  for (int i = 2; i < argc; i++)
  {
    socketClient.inputData += argv[i];
    socketClient.inputData += Socket::kUS;
  }
  socketClient.inputData += Socket::kEoT;
  socketClient.Execute();
  return 0;
}
