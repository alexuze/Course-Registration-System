//
// Created by spl211 on 31/12/2020.
//

#ifndef BOOST_ECHO_CLIENT_INPUTREADER_H
#define BOOST_ECHO_CLIENT_INPUTREADER_H

#include <connectionHandler.h>
#include <iostream>
#include <boost/lexical_cast.hpp>
#include <mutex>
#include <condition_variable>




// enum representing the structure of the message that is being sent
enum MessageStructure{
    TwoBytes,
    FourBytes,
    OneZero,
    TwoZeros
};
class InputReader{
private:

    ConnectionHandler* handler;
    std::mutex& m;
    std::condition_variable& cv;
    bool shouldTerminate = false;

    // a private function that returns the opcode of the command according to the first string in the command
    short getOpCode(std::string command);
    // a private function that converts short to byte array
    void shortToBytes(short num, char* bytesArr);
    // a private function that returns the structure of the command(Two bytes, Four bytes, One zero, Two zeros)
    MessageStructure getStructure(short num);
    // the main function that will read input from user
    void readInputImpl();
    void sendMessage(std::vector<std::string> partsOfCommand);
    void sendFourBytes(std::string courseNumberString);
    void sendOneZero(std::string studentUserName);
    void sendTwoZeros(std::string userName,std::string password);

public:
    // constructor
    InputReader(ConnectionHandler& handler,std::mutex& mutex,std::condition_variable& conditionVariable);
    // the thread function that will call the main runImpl function
    void readInput();
    void terminate();



};
#endif //BOOST_ECHO_CLIENT_INPUTREADER_H
