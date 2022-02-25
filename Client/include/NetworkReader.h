//
// Created by spl211 on 01/01/2021.
//

#ifndef BOOST_ECHO_CLIENT_NETWORKREADER_H
#define BOOST_ECHO_CLIENT_NETWORKREADER_H

#include <connectionHandler.h>
#include <string>
#include <iostream>
#include <mutex>
#include <condition_variable>

enum MessageType{
    ACK,
    ERR
};


class NetworkReader{
private:
    ConnectionHandler* handler;
    std::mutex& m;
    std::condition_variable& cv;
    bool shouldTerminate = false;
    MessageType getType(short opcode);
    short bytesToShort(char* bytesArr);
    void handleMessage(MessageType type,short messageopCode);
    void readSocketImpl();
    void handleACK(short messageOpcode);
    void handleERR(short messageOpcode);

public:
    NetworkReader(ConnectionHandler& handler,std::mutex& mutex,std::condition_variable& conditionVariable);
    void readSocket();
    void terminate();
    bool isTerminated();

};
#endif //BOOST_ECHO_CLIENT_NETWORKREADER_H
