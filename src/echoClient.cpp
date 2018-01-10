#include <stdlib.h>
#include "../include/connectionHandler.h"

/**
* This code assumes that the server replies the exact text the client sent it (as opposed to the practical session example)
*/

#include <boost/thread.hpp>         // std::thread

void foo(ConnectionHandler &ch)
{
    while(1){
    const short bufsize = 1024;
    char buf[bufsize];
    std::cin.getline(buf, bufsize);
    std::string line(buf);
    //int len=line.length();
    ch.sendLine(line);
    }
}

void boo(ConnectionHandler &ch){
    while(1){
        std::string answer;
        ch.getLine(answer);
        std::cout << answer;
    }

}

//void foo(){
//    std::cout << "task1 say" << std::endl;
//};

int main (int argc, char *argv[]) {
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " host port" << std::endl << std::endl;
        return -1;
    }
    std::string host = argv[1];
    short port = atoi(argv[2]);

    ConnectionHandler connectionHandler(host, port);
    if (!connectionHandler.connect()) {
        std::cerr << "Cannot connect to " << host << ":" << port << std::endl;
        return 1;
    }

    //From here we will see the rest of the ehco client implementation:

        boost::thread th1(foo, boost::ref(connectionHandler));
        boost::thread th2(boo, boost::ref(connectionHandler));
        th1.join();
        th2.join();
//        if (!connectionHandler.sendLine(line)) {
//            std::cout << "Disconnected. Exiting...\n" << std::endl;
//            break;
//        }
        // connectionHandler.sendLine(line) appends '\n' to the message. Therefor we send len+1 bytes.
        //std::cout << "Sent " << len+1 << " bytes to server" << std::endl;


        // We can use one of three options to read data from the server:
        // 1. Read a fixed number of characters
        // 2. Read a line (up to the newline character using the getline() buffered reader
        // 3. Read up to the null character

        // Get back an answer: by using the expected number of bytes (len bytes + newline delimiter)
        // We could also use: connectionHandler.getline(answer) and then get the answer without the newline char at the end


        //len=answer.length();
        // A C string must end with a 0 char delimiter.  When we filled the answer buffer from the socket
        // we filled up to the \n char - we must make sure now that a 0 char is also present. So we truncate last character.answer.resize(len-1);

//        if (answer == "ACK signout succeeded") {
//            //std::cout << "Exiting...\n" << std::endl;//TODO: remove
//            break;
//        }

    return 0;
}