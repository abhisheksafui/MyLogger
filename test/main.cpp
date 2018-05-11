#include <iostream>
#include <Poco/Thread.h>
#include "MyLogger.h"


class Test{
    MyLogger logger;
    
public:
    Test()
    :logger("Test")
    {
        
    }
    
    void test(){
        logger.log(Poco::Message::PRIO_CRITICAL, __FILE__, __LINE__, "Started..");
    }
    
    void count(){
        static int i=0;
        logger.log(TRACE, "count = %d", i++);
    }
};

int main(int argc, char *argv[]){

    Test t;
    
    t.test();
    
    while(true){
        t.count();
        Poco::Thread::sleep(500);
    }


}
