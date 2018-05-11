/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MyLogger.h
 * Author: abhi
 *
 * Created on 15 September, 2017, 12:07 AM
 */

#ifndef MYLOGGER_H
#define MYLOGGER_H
#include <string>
#include <Poco/AutoPtr.h>
#include <Poco/ConsoleChannel.h>
#include <Poco/FileChannel.h>
#include <Poco/PatternFormatter.h>
#include <Poco/FormattingChannel.h>
#include <Poco/Message.h>
#include <Poco/LogStream.h>
#include <memory>


using namespace std;
using Poco::ConsoleChannel;
using Poco::Logger;
using Poco::FileChannel;
using Poco::Message;

static const int MAX_MESSAGE_LEN = 1024;
static const string DEFAULT_FORMAT("[%d-%m-%y:%H:%M:%i] [%p] [%v] [%U:%u]: %t");


#define FILE_LINE __FILE__,__LINE__

/**
 *  Macros for logging with file and line 
 */
#define TRACE       Poco::Message::PRIO_TRACE,FILE_LINE
#define DEBUG       Poco::Message::PRIO_DEBUG,FILE_LINE
#define INFO        Poco::Message::PRIO_INFORMATION,FILE_LINE
#define NOTICE      Poco::Message::PRIO_NOTICE,FILE_LINE
#define WARN        Poco::Message::PRIO_WARNING,FILE_LINE
#define ERROR       Poco::Message::PRIO_ERROR,FILE_LINE
#define CRITICAL    Poco::Message::PRIO_CRITICAL,FILE_LINE
#define FATAL       Poco::Message::PRIO_FATAL,FILE_LINE




class MyLogger {
public:

    enum Level {
        LEVEL_TRACE = Poco::Message::PRIO_TRACE,
        LEVEL_DEBUG = Poco::Message::PRIO_DEBUG,
        LEVEL_INFO = Poco::Message::PRIO_INFORMATION,
        LEVEL_NOTICE = Poco::Message::PRIO_NOTICE,
        LEVEL_WARN = Poco::Message::PRIO_WARNING,
        LEVEL_ERROR = Poco::Message::PRIO_ERROR,
        LEVEL_CRITICAL = Poco::Message::PRIO_CRITICAL,
        LEVEL_FATAL = Poco::Message::PRIO_FATAL
    };

    /* Constructors */
    MyLogger(); //Blank constructor gets hold of root() Poco logger
    MyLogger(Logger& log);

    MyLogger(const string& name,
            Poco::Message::Priority prio = Poco::Message::PRIO_TRACE);

    MyLogger(const string &name, string& filename,
            Poco::Message::Priority prio = Poco::Message::PRIO_TRACE);

    MyLogger(const string &name, string& filename, string& pocoPattern,
            Poco::Message::Priority prio = Poco::Message::PRIO_TRACE);

    /* Copy Constructor */
    MyLogger(const MyLogger& orig);



    /* Destructor */
    virtual ~MyLogger();

    Poco::Logger & getPocoLogger();
    //    const Poco::LogStream&  getStream();

    /* Set level at any time */
    void setLevel(Level prio);

    /* Set Channel at any time */
    void setConsoleChannel();
    void setFileChannel(const string &path);

    void setPattern(string pattern);


    void log(Poco::Message::Priority level,
            const char * file,
            const int line,
            const string &message);

    /* printf style logging*/
    void log(Poco::Message::Priority prio,
            const char *file,
            const int line,
            const char *fmt, ...);


    void trace(string filename, const int line, string text);
    /* c style trace */
    void trace(Poco::Message::Priority prio,
                const char *file,
                const int line, 
                const char *fmt);

    Poco::LogStream & operator()();




private:
    /* Required to get the Poco Logger instance */
    const string loggerName;
    Logger& _logger;
    Poco::Message::Priority priority;

    Poco::AutoPtr<Poco::PatternFormatter> formatter;
    Poco::AutoPtr<Poco::FormattingChannel> formattingChannel;

};

#endif /* MYLOGGER_H */

