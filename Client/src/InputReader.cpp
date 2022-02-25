//
// Created by spl211 on 31/12/2020.
//
#include "InputReader.h"
using namespace std;
InputReader::InputReader(ConnectionHandler&  connectionHandler,std::mutex& mutex,std::condition_variable& conditionVariable) : handler(&connectionHandler),m(mutex),cv(conditionVariable){
}

void InputReader::readInput()
{
    while (!shouldTerminate)
    {
        readInputImpl();
    }
}
void InputReader::terminate() {
    shouldTerminate = true;
}
void InputReader::readInputImpl()
{
    string command;
    std::getline (std::cin,command);
    if(shouldTerminate) // check if we ended while waiting for input
        return;
    vector<string> partsOfCommand;
    string word = "";
    // split the command into parts
    for(auto x : command){
        if(x == ' ')
        {
            partsOfCommand.push_back(word);
            word = "";
        }
        else{
            word += x;
        }
    }
    partsOfCommand.push_back(word); // add the last part
    sendMessage(partsOfCommand);
}
void InputReader::sendMessage(std::vector<std::string> partsOfCommand) {
    short opcode = getOpCode(partsOfCommand[0]);
    MessageStructure structure = getStructure(opcode);
    char opcodeBytes[2];
    shortToBytes(opcode, opcodeBytes);
    handler->sendBytes(opcodeBytes,2); // you always send the opcode
    if(structure == FourBytes)
        sendFourBytes(partsOfCommand[1]);
    else if(structure == OneZero)
        sendOneZero(partsOfCommand[1]);
    else if(structure == TwoZeros)
        sendTwoZeros(partsOfCommand[1],partsOfCommand[2]);
    if(opcode == 4) // logout
    {
        std::unique_lock<std::mutex> lock(m); // acquire the mutex
        cv.wait(lock); // wait on the mutex until logout message was handled
    }
}

void InputReader::sendFourBytes(string courseNumberString) {
    short courseNumber = boost::lexical_cast<short>(courseNumberString); // in this case the two extra bytes are course number
    char  courseNumberBytes[2];
    shortToBytes(courseNumber,courseNumberBytes);
    handler->sendBytes(courseNumberBytes,2); // send the added 2 bytes
}
void InputReader::sendOneZero(string studentUserName) {
    handler->sendFrameAscii(studentUserName,'\0'); // send the string with addition of the zero byte at the end

}
void InputReader::sendTwoZeros(string userName,string password) {
// send both parts of the message with the zero byte in the end of each part
    handler->sendFrameAscii(userName,'\0');
    handler->sendFrameAscii(password,'\0');
}
short InputReader::getOpCode(std::string command) {
    if(command.compare("ADMINREG") == 0)
        return 1;
    else if(command.compare("STUDENTREG")== 0)
        return 2;
    else if(command.compare("LOGIN")== 0)
        return 3;
    else if(command.compare("LOGOUT")== 0)
        return 4;
    else if(command.compare("COURSEREG")== 0)
        return 5;
    else if(command.compare("KDAMCHECK")== 0)
        return 6;
    else if(command.compare("COURSESTAT")== 0)
        return 7;
    else if(command.compare("STUDENTSTAT")== 0)
        return 8;
    else if(command.compare("ISREGISTERED")== 0)
        return 9;
    else if(command.compare("UNREGISTER")== 0)
        return 10;
    else // must be MYCOURSES since the input is valid for sure
        return 11;
}

MessageStructure InputReader::getStructure(short num) {
    if(num == 8)
        return OneZero;
    else if(num == 1 || num == 2 || num == 3)
        return TwoZeros;
    else if(num == 4 || num == 11)
        return TwoBytes;
    else
        return FourBytes;
}
void InputReader::shortToBytes(short num, char *bytesArr) {
    bytesArr[0] = ((num >> 8) & 0xFF);
    bytesArr[1] = (num & 0xFF);
}


