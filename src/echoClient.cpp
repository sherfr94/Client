#include <stdlib.h>
#include "../include/connectionHandler.h"

/**
* This code assumes that the server replies the exact text the client sent it (as opposed to the practical session example)
*/

#include <boost/thread.hpp>         // std::thread

int status = 1;
void foo(ConnectionHandler &ch)
{
    while(status){

            const short bufsize = 1024;
            char buf[bufsize];
            std::cin.getline(buf, bufsize);
            std::string line(buf);
            ch.sendLine(line);
    }
}

void boo(ConnectionHandler &ch){
    while(status){

        std::string answer;
        ch.getLine(answer);
        std::cout << answer;

        if (answer == "ACK signout succeeded\n") {
            status=0;
        }
    }

}


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
        th2.join();


    return 0;
}