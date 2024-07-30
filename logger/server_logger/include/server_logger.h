#ifndef OPERATING_SYSTEMS_COURSE_WORK_SERVER_LOGGER_H
#define OPERATING_SYSTEMS_COURSE_WORK_SERVER_LOGGER_H

#include <logger.h>
#include "server_logger_builder.h"

class server_logger final:
    public logger
{

public:

    server_logger(
        server_logger const &other);

    server_logger &operator=(
        server_logger const &other);

    server_logger(
        server_logger &&other) noexcept;

    server_logger &operator=(
        server_logger &&other) noexcept;

    ~server_logger() noexcept final;

public:

    [[nodiscard]] logger const *log(
        const std::string &message,
        logger::severity severity) const noexcept override;

};

#endif //OPERATING_SYSTEMS_COURSE_WORK_SERVER_LOGGER_H