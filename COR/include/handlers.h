#ifndef OPERATING_SYSTEMS_COURSE_WORK_CHAIN_OF_RESPONIBILITY_H
#define OPERATING_SYSTEMS_COURSE_WORK_CHAIN_OF_RESPONIBILITY_H

#include "../../command/include/command.h"
#include <ctime>
#include <iomanip>

namespace chain_of_responsibility
{


#pragma region HANDLER PROPS


    class handler
    {

    public:

        handler * _next_handler;

    public:

        handler() : _next_handler(nullptr)
        {}

        virtual ~handler() = default;

    public:

        virtual bool handle(const std::string &request, time_t &user_date) = 0;
    };



    class request_with_command : public handler
    {

    private:

        command_pattern::command * _target_action;

    public:

        explicit request_with_command(command_pattern::command *target_action);

        ~request_with_command() override;
    public:

        bool handle(const std::string &request, time_t &user_date) override;

    public:

        request_with_command(request_with_command const& other) = delete;

        request_with_command(request_with_command&& other) = delete;

        request_with_command& operator=(request_with_command const& other) = delete;

        request_with_command& operator=(request_with_command const&& other) = delete;

    };



    class request_with_command_chain
    {

    private:

        handler *_first_handler;
        handler *_last_handler;

    public:

        request_with_command_chain();

        ~request_with_command_chain();

        request_with_command_chain(request_with_command_chain const & other) = delete;

        request_with_command_chain(request_with_command_chain && other) = delete;

        request_with_command_chain& operator=(request_with_command_chain const & other) = delete;

        request_with_command_chain& operator=(request_with_command_chain && other) = delete;

    public:

        bool handle(const std::string &request, const std::string date) const;

    public:

        request_with_command_chain& add_handler(command_pattern::command * command);
    };


    

};


class RWCC_singleton final
{

public:

    chain_of_responsibility::request_with_command_chain _chain;

private:

    RWCC_singleton ();

    RWCC_singleton (
        const RWCC_singleton &) = delete;

    RWCC_singleton (
        RWCC_singleton &&) = delete;

public:

    static RWCC_singleton *get_singleton ();

    void clear ();

};


#endif