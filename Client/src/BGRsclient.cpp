
#include <stdlib.h>
#include <connectionHandler.h>

#include <NetworkReader.h>
#include <InputReader.h>
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;


int main (int argc, char *argv[])
{
    std::mutex m;
    std::condition_variable cv;
    std::string host = argv[1];
    short port = atoi(argv[2]);
    ConnectionHandler handler(host,port);
    handler.connect();
    InputReader inputReader(handler,m,cv);
    NetworkReader networkReader(handler,m,cv);
    std::thread readInputThread(&InputReader::readInput,&inputReader);
    std::thread readNetworkThread(&NetworkReader::readSocket,&networkReader);

    readNetworkThread.join();
    if(networkReader.isTerminated()){
        std::lock_guard<std::mutex> lock(m); // acquire the mutex
        inputReader.terminate();
    }
    cv.notify_one();         // notify the rader thread he can continue and finish his work
    readInputThread.join();

    return 0;
}


