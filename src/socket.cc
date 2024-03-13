#include "../include/socket.h"

Socket::Socket(const char* path, bool isAbstract) {
    fd = 0;
    path_ = string(path); 

    addr_ = {}; 
    addr_.sun_family = AF_UNIX; 
    if (isAbstract) {
        strncpy(addr_.sun_path + 1, path, sizeof(addr_.sun_path) - 2);
    } else {
        strncpy(addr_.sun_path, path, sizeof(addr_.sun_path) - 1);
    }
}

bool Socket::Setup(int domain, int type, int protocol) {
    fd = ::socket(domain, type, protocol);
    if (fd > 0)
        return true;

    cerr << "Socket::Setup failed: " << strerror(errno) << endl;
    return false;
}

bool Socket::Associate() {
    unlink(path_.c_str()); // Remove existing file if any.
    if (::bind(fd, reinterpret_cast<const sockaddr*>(&addr_), sizeof(addr_)) == 0)
        return true;

    cerr << "Socket::Associate() failed: " << strerror(errno) << endl;
    return false;
}

bool Socket::Ready(size_t queueLength) const {
    if (::listen(fd, queueLength) == 0)
        return true;

    cerr << "Socket::Ready failed: " << strerror(errno) << endl;
    return false;
}

bool Socket::Join(int* clientFd) const {
    *clientFd = ::accept(fd, nullptr, nullptr);
    if (*clientFd >= 0)
        return true;

    cerr << "Socket::Join() failed: " << strerror(errno) << endl;
    return false;
}

bool Socket::Link() const {
    if (::connect(fd, reinterpret_cast<const sockaddr*>(&addr_), sizeof(addr_)) == 0)
        return true;

    cerr << "Socket::Link failed: " << strerror(errno) << endl;
    return false;
}

::ssize_t Socket::Receive(string* output, int connFd, ::ssize_t stopAfter, char delimiter) const {
    if (!connFd)
        connFd = fd;

    const size_t BufferSize = 1024;
    char buffer[BufferSize];

    ::ssize_t bytesReadTotal = 0, bytesRead;
    bytesRead = bytesReadTotal = ::read(connFd, buffer, BufferSize);

    if (bytesRead <= 0) {
        return bytesReadTotal; // Return the number of bytes read (or error code).
    }

    while (buffer[bytesRead - 1] != delimiter && (stopAfter && bytesRead < stopAfter)) {
        output->append(buffer, bytesRead);
        bytesRead = ::read(connFd, buffer, BufferSize);
        bytesReadTotal += bytesRead;
        if (bytesRead <= 0) {
            return bytesReadTotal;
        }
    }

    output->append(buffer, bytesRead - 1); // Exclude delimiter from output
    return bytesReadTotal;
}

::ssize_t Socket::Send(const string& data, int connFd, char endChar) const {
    if (!connFd)
        connFd = fd;

    ::ssize_t totalSent = 0, sent;
    do {
        sent = ::write(connFd, data.data() + totalSent, data.length() - totalSent);
        if (sent < 0) {
            cerr << "Socket::Send error: " << strerror(errno) << endl;
            return sent;
        }
        totalSent += sent;
    } while (totalSent < static_cast<::ssize_t>(data.length()));

    // Send end-of-transmission character
    sent = ::write(connFd, &endChar, 1);
    if (sent < 0) {
        cerr << "Socket::Send endChar error: " << strerror(errno) << endl;
        return sent;
    }

    return totalSent + sent; // Include endChar in total
}

void Socket::Terminate(int connFd) const {
    if (connFd)
        ::close(connFd);
    else
        ::close(fd);
}
