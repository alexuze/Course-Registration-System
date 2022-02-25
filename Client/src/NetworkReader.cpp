//
// Created by spl211 on 01/01/2021.
//

#include <NetworkReader.h>
using namespace std;
NetworkReader::NetworkReader(ConnectionHandler& connectionHandler,std::mutex& mutex,std::condition_variable& conditionVariable) : handler(&connectionHandler),m(mutex),cv(conditionVariable){
}
void NetworkReader::readSocket() {
    while(!isTerminated())
    {
        readSocketImpl();
    }
}
void NetworkReader::readSocketImpl() {
    char opCodeBytes[2];
    char messageOpcodeBytes[2];
    handler->getBytes(opCodeBytes,2);
    handler->getBytes(messageOpcodeBytes,2);
    short opcode = bytesToShort(opCodeBytes);
    short messageOpcode = bytesToShort(messageOpcodeBytes);
    MessageType type = getType(opcode);
    handleMessage(type,messageOpcode);
}
void NetworkReader::handleMessage(MessageType type,short messageOpcode) {

    if(type == ACK)
        handleACK(messageOpcode);
    else
        handleERR(messageOpcode);
}
short NetworkReader::bytesToShort(char *bytesArr) {

    short result = (short)((bytesArr[0] & 0xff) << 8);
    result += (short)(bytesArr[1] & 0xff);
    return result;
}
MessageType NetworkReader::getType(short opcode) {
    if(opcode == 12)
        return ACK;
    return ERR;
}
bool NetworkReader::isTerminated() {
    return shouldTerminate;
}
void NetworkReader::handleACK(short messageOpcode) {
    cout << "ACK "<< messageOpcode << endl;
    string attachment = "";
    handler->getFrameAscii(attachment,'\0'); // get the string to print
    if(attachment.compare("") != 0)
        cout << attachment << endl;
    if(messageOpcode == 4) // logout message
    {
        terminate();
    }
}
void NetworkReader::handleERR(short messageOpcode) {

    cout << "ERROR "<< messageOpcode << endl;
    if(messageOpcode == 4) // logout
    {
        std::lock_guard<std::mutex> lock(m); // acquire the mutex
    }
    cv.notify_one();


}
void NetworkReader::terminate() {
    shouldTerminate = true;
}


