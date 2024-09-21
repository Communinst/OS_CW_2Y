

#include "../include/singleton.h"

#include "../../server_logger/include/server_logger.h"
#include "../../server_logger/include/server_logger_builder.h"



logger_singleton::logger_singleton ()
{

    server_logger_builder *builder = new server_logger_builder();

    logger *fresh_logger = builder
        ->add_console_stream(logger::severity::information)
        ->add_console_stream(logger::severity::error)
        ->add_console_stream(logger::severity::debug)
        ->add_console_stream(logger::severity::trace)
        ->add_console_stream(logger::severity::warning)
        ->add_console_stream(logger::severity::critical)
        ->build();

    _logger = fresh_logger;
    delete builder;

}

logger_singleton *logger_singleton::get_singleton ()
{
    static auto *singleton = new logger_singleton();
    return singleton;
}

logger *logger_singleton::get_logger ()
{
    return _logger;
}


