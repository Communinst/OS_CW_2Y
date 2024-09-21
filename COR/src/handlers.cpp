
#include <handlers.h>


chain_of_responsibility::request_with_command::request_with_command(command_pattern::command *target_action) :
    _target_action(target_action)
{}

chain_of_responsibility::request_with_command::~request_with_command()
{
    delete _target_action;
}
        
bool chain_of_responsibility::request_with_command::handle(const std::string &request, time_t &user_date)
{
    // Handles external chain
    if (request != "")
    {
        if (!_target_action->can_execute(request))
        {
            return (_next_handler != nullptr) ? _next_handler->handle(request, user_date)             
                                              : false;
        }

        try
        {
            _target_action->execute();
        }
        catch (const std::exception &e)
        {
            logger_singleton::get_singleton()->get_logger()->log(e.what(), logger::severity::trace);
            return false;
        }

        //db_storage::get_singleton()->_chain.add_handler(_target_action);

        RWCC_singleton::get_singleton()->_chain.add_handler(_target_action);

        _target_action = nullptr;

        return true;
        
    }
    // Handles chain inside of DB
    else
    {
        struct tm buff;
        std::istringstream iss(_target_action->get_date());

        iss >> std::get_time(&buff, "%Y-%m-%dT%H:%M:%SZ");
        time_t action_date = mktime(&buff);

        if (std::difftime(action_date, user_date) > 0)
        {
            return false; 
        }
        _target_action->execute();

        if (_next_handler != nullptr)
        {
            return _next_handler->handle(request, user_date);
        }

        return true;

    }

}



chain_of_responsibility::request_with_command_chain::request_with_command_chain() :
    _first_handler(nullptr), _last_handler(nullptr)
{}

chain_of_responsibility::request_with_command_chain::~request_with_command_chain()
{
    while (_first_handler)
    {
        _last_handler = _first_handler;
        _first_handler = _first_handler->_next_handler;
        delete _last_handler;
    }
}


bool chain_of_responsibility::request_with_command_chain::handle(const std::string &request, const std::string date) const
{
    if (!_first_handler)    
    {
        return false;
    }
    
    struct tm buff;
    std::istringstream iss(date);

    iss >> std::get_time(&buff, "%Y-%m-%dT%H:%M:%SZ");
    time_t user_date = mktime(&buff);

    return _first_handler->handle(request, user_date);
    
}


chain_of_responsibility::request_with_command_chain& chain_of_responsibility::request_with_command_chain::add_handler(command_pattern::command * command)
{
    _last_handler = !_first_handler
                    ? _first_handler = new request_with_command(command)
                    : _last_handler->_next_handler = new request_with_command(command);
    return *this;
}

RWCC_singleton::RWCC_singleton ()
{   }

RWCC_singleton *RWCC_singleton::get_singleton()
{

    static RWCC_singleton *singleton = new RWCC_singleton();
    return singleton;

}

void RWCC_singleton::clear ()
{
    _chain.~request_with_command_chain();
}

