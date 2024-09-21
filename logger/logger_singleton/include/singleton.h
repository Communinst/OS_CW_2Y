
#ifndef OPERATING_SYSTEMS_COURSE_WORK_LOGGER_SINGLETON_H
#define OPERATING_SYSTEMS_COURSE_WORK_LOGGER_SINGLETON_H


#include <map>
#include <string>
#include "../../logger/include/logger.h"



class logger_singleton final
{

private:

    logger *_logger;

private:

    logger_singleton ();

public:

    ~logger_singleton ();

    logger_singleton (const logger_singleton &other) = delete;

    logger_singleton (const logger_singleton &&other) = delete;

    logger_singleton &operator= (const logger_singleton &other) = delete;

    logger_singleton &operator= (const logger_singleton &&other) = delete;

public:

    static logger_singleton *get_singleton ();  

    logger *get_logger ();

};


#endif