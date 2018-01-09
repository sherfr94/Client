//
// Created by shermanf on 1/9/18.
//

#ifndef CLIENT_KEYBOARDTHREAD_H
#define CLIENT_KEYBOARDTHREAD_H
#include <iostream>
#include <boost/thread.hpp>

class KeyboardThread {




private:
    int _id;
public:
    Task (int number) : _id(number) {}

    void operator()(){
        for (int i= 0; i < 100; i++){
            std::cout << i << ") Task " << _id << " is working" << std::endl;
        }
        boost::this_thread::yield(); //Gives up the remainder of the current thread's time slice, to allow other threads to run.
    }
};

};


#endif //CLIENT_KEYBOARDTHREAD_H
