#include "../include/text-server.h"
#include "../include/filereader.h"

vector<int> parse_msg(string msg, string *file_path) {
  bool path_read = false;
  vector<int> lines = vector<int>();
  int line_num = 0;
  for (char c : msg) {
    if (!path_read) {
      if (c == Socket::kUS) {
        path_read = true;
      } else {
        file_path->push_back(c);
      }
      continue;
    }
    if (c == Socket::kUS) {
      lines.push_back(line_num);
      line_num = 0;
      continue;
    }
    line_num = line_num * 10 + (c - '0');
  }
  return lines;
}

void Server::Run() {
  int socket_fd;

  if (!Setup() || !Associate())
    exit(1);

  cout << "SERVER STARTED\nMAX CLIENTS: "
  << get_nprocs_conf() << endl;

  if (!Ready())
    exit(2);

  while (true) {
    socket_fd = ::accept(fd, nullptr, nullptr);
    if (socket_fd  < 0) {
      cerr << "Socket connection: " << ::strerror(errno) << endl;
      continue;
    }
    cout << "CLIENT CONNECTED" << endl;

    string msg;
    ::ssize_t bytes_read = Receive(&msg, socket_fd);

    if (bytes_read < 0) {
      cerr << "Server shutting down..." << endl;
      exit(3);
    } else if (!bytes_read) {
      cout << "Client disconnected" << endl;
      close(socket_fd);
    }

    string file_path;
    vector<int> lines = parse_msg(msg, &file_path);
    cout << "\tPATH: " << file_path << endl;
    sort(lines.begin(), lines.end());
    cout << "\tLines: ";
    int line_size = lines.size();
    for (int i = 0; i < line_size; ++i) {
      cout << lines[i];
      if (i != line_size - 1) {
        cout << ", ";
      }
    }
    cout << endl;

    vector<string> content = filereader::readFile(file_path, &lines);

    //cout<<content.size()<<endl;

    string response = "";
    int content_size = content.size();
    for (int i = 0; i < content_size; ++i) {
      response += content[i];
      if (i != content_size - 1) {
        response += Socket::kUS;
      }
    }
    //cout<<response<<endl;
    response += Socket::kEoT;
    ssize_t bytes_written = Send(response, socket_fd);
    if (bytes_written < 0) {
      cerr << "Error writing to client: "
      << ::strerror(errno) << endl;
      return;
    }
    cout << "BYTES SENT: " << bytes_written << endl;
  }
}

int main(int argc, char *argv[]) {
  char* socket_path = argv[1];
  Server server(socket_path);
  server.Run();
  return 0;
}
