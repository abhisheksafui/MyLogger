/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MyLogger.cpp
 * Author: abhi
 * 
 * Created on 15 September, 2017, 12:07 AM
 */


#include "MyLogger.h"
#include <cstdarg>
#include <queue>



/**
 * Default logger is root logger with name DEFAULT, default format pattern
 * and console channel
 */
MyLogger::MyLogger(): _logger(Logger::root()), loggerName("DEFAULT"){
    
    
    formatter = new Poco::PatternFormatter(DEFAULT_FORMAT);
    formattingChannel = new Poco::FormattingChannel(formatter,new ConsoleChannel());
    
    
    /** 
     * Always apply formatting channel to preserve pattern format, just set any new channel 
     *  to formattingChannel and reapply 
     */
    _logger.setChannel(formattingChannel);
    
    _logger.notice("Constructed default logger");
}

/**
 * 
 * @param name  Name of logger
 * @param prio  Priority of logging
 */
MyLogger::MyLogger(const string& name, Poco::Message::Priority prio)
: _logger(Logger::get(name)),
loggerName(name),
priority(prio) {

    /* Start with default format string and consoleChannel */
    //LOG_TRACE("Is global logger working?");
    formatter = new Poco::PatternFormatter(DEFAULT_FORMAT);
    formattingChannel = new Poco::FormattingChannel(formatter, new Poco::ConsoleChannel());
    
    _logger.setChannel(formattingChannel);
    _logger.setLevel(prio);

    this->log(TRACE,"Logger Constructed");
}



MyLogger::MyLogger(const MyLogger& orig) : _logger(orig._logger) {
    /* Copy Constructor */
    
}

MyLogger::MyLogger(Logger & log) : _logger(log), loggerName("DEFAULT") {

    /* Start with default format string and consoleChannel */
    
    formatter = new Poco::PatternFormatter("[%d-%m-%y] [%H:%M:%i] [%p] [%s:%U:%u]: %t");
    formattingChannel = new Poco::FormattingChannel(formatter, new Poco::ConsoleChannel());
    
    _logger.setChannel(formattingChannel);
    //logger.setLevel(Poco::Message::PRIO_TRACE);
    this->log(TRACE,"Logger initiaised");
    
}

MyLogger::~MyLogger() {
}

Logger& MyLogger::getPocoLogger(){
    return _logger;
}

//const Poco::LogStream& MyLogger::getStream(){
//    return Poco::LogStream(_logger,Poco::Message::PRIO_TRACE); 
//}

void MyLogger::setLevel(Level prio) {
    _logger.setLevel(prio);
}


void MyLogger::setConsoleChannel(){

    formattingChannel->setChannel(new ConsoleChannel());
     /** Re Apply the formatting channel to the Poco logger, 
     *  Since Poco Loggers channel may be changed by Application Constructor
     */
     _logger.setChannel(formattingChannel);
}

void MyLogger::setFileChannel(const string &path) {
    log(INFO,"Logger %s channel set to FILE %s\n",loggerName.c_str(),path.c_str());
    
    /* Create new fileChannel and apply to already created formattingChannel */
    Poco::AutoPtr<FileChannel> fileChannel = new FileChannel();
    fileChannel->setProperty("path", path);
    //(*formatter).setProperty(Poco::PatternFormatter::PROP_PATTERN, "[%d-%m-%y] [%H:%M:%i]: %t");
    
    (*formattingChannel).setChannel(fileChannel);
    
    /** 
     *  Re Apply the formatting channel to the Poco logger, 
     *  Since Poco Loggers channel may be changed by Application Constructor
     */
    _logger.setChannel(formattingChannel);
    
}


void MyLogger::setPattern(string pattern){
    
    log(TRACE,"Changing log patter of %s to: %s",loggerName.c_str(),pattern.c_str());
    /** Apply the new pattern to the formatter */
    (*formatter).setProperty(Poco::PatternFormatter::PROP_PATTERN, pattern);
    
    /** Re Apply the formatting channel to the Poco logger, 
     *  Since Poco Loggers channel may be changed by Application Constructor
     */
     _logger.setChannel(formattingChannel);

}

void MyLogger::log(Poco::Message::Priority prio,
        const char *file,
        const int line,
        const string &text) {

    Poco::Message message(loggerName, text, prio, file, line);
    _logger.log(message);
}

void MyLogger::log(Poco::Message::Priority prio,
        const char *file,
        const int line,
        const char *fmt, ...) {
    va_list ap;
    char buffer[MAX_MESSAGE_LEN];
    va_start(ap, fmt);
    vsprintf(buffer, fmt, ap);

    Poco::Message message(loggerName, buffer, prio, file, line);
    _logger.log(message);
    va_end(ap);
}

void MyLogger::trace(string filename, const int line, string text) {
    //Logger& logger = Logger::get(loggerName);
    _logger.trace(text);

}

void MyLogger::trace(Poco::Message::Priority prio,
                      const char *file,
                      const int line,
                      const char *fmt)
{
  log(prio, file, line, fmt);
}

