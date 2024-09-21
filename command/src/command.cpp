
#include <command.h>
#include <iterator>



std::string command_pattern::getCurrentTime() {
    auto now = std::chrono::system_clock::now();
    std::time_t current_time = std::chrono::system_clock::to_time_t(now);

    std::tm time_info = *std::localtime(&current_time);

    std::stringstream ss;
    ss << std::put_time(&time_info, "%Y-%m-%dT%H:%M:%SZ");
    
    return ss.str();
}


#pragma region COMMAND PARENT IMPLEM

command_pattern::command::command (std::string date) :
    _date (date)
{   }

std::string command_pattern::command::get_date () const noexcept
{
    return _date;
}


#pragma endregion COMMAND PARENT IMPLEM





#pragma region POOL_INTER




    #pragma region ADD_POOL IMPLEM


command_pattern::add_pool::add_pool (const std::string date) :
    command_pattern::command (date)
{   }


bool command_pattern::add_pool::can_execute (const std::string &request)
{

    logger_singleton::get_singleton()->get_logger()->log("ADDPOOL command initiated verification procedure.", logger::severity::trace);

    std::istringstream iss(request);

    if (std::distance(std::istream_iterator<std::string>(iss), std::istream_iterator<std::string>()) != 4)
    {
        logger_singleton::get_singleton()->get_logger()->log("[ ADDPOOL" + request + " ]" + "\tFailed: Invalid amount of arguments.", logger::severity::error);
        return false;
    }
    iss.clear();
    iss.seekg(0);

    std::string command;

    iss >> command;

    std::cout << command.c_str() << std::endl;

    if (command != "ADDPOOL")
    {
        logger_singleton::get_singleton()->get_logger()->log("Not ADDPOOL", logger::severity::information);
        return false;
    }

    iss >> _pool_name;

    std::string tvar;
    iss >> tvar;
    try
    {
        _search_tvar = ipc::string_to_searchtvar(tvar);
        iss >> _param_for_tree;
    }
    catch (const std::exception &e)
    {
        logger_singleton::get_singleton()->get_logger()->log(e.what(), logger::severity::error);
        return false;
    }

    _date = getCurrentTime();


    return true;

}


void command_pattern::add_pool::execute ()
{

    logger_singleton::get_singleton()->get_logger()->log("ADDPOOL initiated execution procedure.", logger::severity::trace);
    db_storage::get_singleton()->add_pool(_pool_name, _search_tvar, _param_for_tree);

}


    #pragma endregion ADD_POOL IMPLEM


    #pragma region DISPOSE_POOL IMPLEM


command_pattern::dispose_pool::dispose_pool (const std::string date) :
    command_pattern::command (date)
{   }


bool command_pattern::dispose_pool::can_execute (const std::string &request)
{

    logger_singleton::get_singleton()->get_logger()->log("DISPOSEPOOL command initiated verification procedure.", logger::severity::trace);

    std::istringstream iss(request);

    if (std::distance(std::istream_iterator<std::string>(iss), std::istream_iterator<std::string>()) != 2)
    {
        logger_singleton::get_singleton()->get_logger()->log("[ DISPOSEPOOL" + request + " ]" + "\tFailed: Invalid amount of arguments.", logger::severity::error);
        return false;
    }
    iss.clear();
    iss.seekg(0);

    std::string command;

    iss >> command;

    if (command != "DISPOSEPOOL")
    {
        logger_singleton::get_singleton()->get_logger()->log("Not DISPOSEPOOL", logger::severity::information);
        return false;
    }

    iss >> _pool_name;

    _date = getCurrentTime();

    return true;

}


void command_pattern::dispose_pool::execute ()
{

    logger_singleton::get_singleton()->get_logger()->log("DISPOSEPOOL initiated execution procedure.", logger::severity::trace);
    db_storage::get_singleton()->dispose_pool(_pool_name);

}


    #pragma endregion DISPOSE_POOL IMPLEM




#pragma endregion POOL_INTER






#pragma region SCHEMA_INTER




    #pragma region ADD_SCHEMA IMPLEM


command_pattern::add_schema::add_schema (const std::string date) :
    command_pattern::command (date)
{   }


bool command_pattern::add_schema::can_execute (const std::string &request)
{

    logger_singleton::get_singleton()->get_logger()->log("ADDSCHEMA command initiated verification procedure.", logger::severity::trace);

    std::istringstream iss(request);

    if (std::distance(std::istream_iterator<std::string>(iss), std::istream_iterator<std::string>()) != 5)
    {
        logger_singleton::get_singleton()->get_logger()->log("[ ADDSCHEMA" + request + " ]" + "\tFailed: Invalid amount of arguments.", logger::severity::error);
        return false;
    }
    iss.clear();
    iss.seekg(0);

    std::string command;

    iss >> command;

    if (command != "ADDSCHEMA")
    {
        logger_singleton::get_singleton()->get_logger()->log("Not ADDSCHEMA", logger::severity::information);
        return false;
    }

    iss >> _pool_name;
    iss >> _schema_name;

    std::string tvar;
    iss >> tvar;
    try
    {
        _search_tvar = ipc::string_to_searchtvar(tvar);
        iss >> _param_for_tree;
    }
    catch (const std::exception &e)
    {
        logger_singleton::get_singleton()->get_logger()->log(e.what(), logger::severity::error);
        return false;
    }

    _date = getCurrentTime();

    return true;

}


void command_pattern::add_schema::execute ()
{

    logger_singleton::get_singleton()->get_logger()->log("ADDSCHEMA initiated execution procedure.", logger::severity::trace);
    db_storage::get_singleton()->add_schema(_pool_name, _schema_name, _search_tvar, _param_for_tree);

}


    #pragma endregion ADD_SCHEMA IMPLEM


    #pragma region DISPOSE_SCHEMA IMPLEM


command_pattern::dispose_schema::dispose_schema (const std::string date) :
    command_pattern::command (date)
{   }


bool command_pattern::dispose_schema::can_execute (const std::string &request)
{

    logger_singleton::get_singleton()->get_logger()->log("DISPOSESCHEMA command initiated verification procedure.", logger::severity::trace);

    std::istringstream iss(request);

    if (std::distance(std::istream_iterator<std::string>(iss), std::istream_iterator<std::string>()) != 3)
    {
        logger_singleton::get_singleton()->get_logger()->log("[ DISPOSESCHEMA" + request + " ]" + "\tFailed: Invalid amount of arguments.", logger::severity::error);
        return false;
    }
    iss.clear();
    iss.seekg(0);

    std::string command;

    iss >> command;

    if (command != "DISPOSESCHEMA")
    {
        logger_singleton::get_singleton()->get_logger()->log("Not DISPOSESCHEMA", logger::severity::information);
        return false;
    }

    iss >> _pool_name;
    iss >> _schema_name;

    _date = getCurrentTime();

    return true;

}


void command_pattern::dispose_schema::execute ()
{

    logger_singleton::get_singleton()->get_logger()->log("DISPOSESCHEMA initiated execution procedure.", logger::severity::trace);
    db_storage::get_singleton()->dispose_schema(_pool_name, _schema_name);

}


    #pragma endregion DISPOSE_SCHEMA IMPLEM




#pragma endregion SCHEMA_INTER





#pragma region COLLECTION_INTER




    #pragma region ADD_COLLECTION IMPLEM

command_pattern::add_collection::add_collection (const std::string date) :
    command_pattern::command (date)
{   }


bool command_pattern::add_collection::can_execute (const std::string &request)
{

    logger_singleton::get_singleton()->get_logger()->log("ADDCOLLECTION command initiated verification procedure.", logger::severity::trace);

    std::istringstream iss(request);

    if (std::distance(std::istream_iterator<std::string>(iss), std::istream_iterator<std::string>()) != 8)
    {
        logger_singleton::get_singleton()->get_logger()->log("[ ADDCOLLECTION" + request + " ]" + "\tFailed: Invalid amount of arguments.", logger::severity::error);
        return false;
    }
    iss.clear();
    iss.seekg(0);

    std::string command;

    iss >> command;

    if (command != "ADDCOLLECTION")
    {
        logger_singleton::get_singleton()->get_logger()->log("Not ADDCOLLECTION", logger::severity::information);
        return false;
    }

    iss >> _pool_name;
    iss >> _schema_name;
    iss >> _collection_name;

    std::string tvar, avar, fmode;
    iss >> tvar;
    iss >> avar;
    iss >> fmode;

    try
    {
        _search_tvar = ipc::string_to_searchtvar(tvar);
        _allocator_var = ipc::string_to_allocatorvar(avar);
        _fit_mode = ipc::string_to_fmode(fmode);
        iss >> _param_for_tree;
    }
    catch (const std::exception &e)
    {
        logger_singleton::get_singleton()->get_logger()->log("Invalid request arguments.", logger::severity::error);
        return false;
    }

    _date = getCurrentTime();

    return true;

}


void command_pattern::add_collection::execute ()
{

    logger_singleton::get_singleton()->get_logger()->log("ADDCOLLECTION initiated execution procedure.", logger::severity::trace);
    db_storage::get_singleton()->add_collection(
                                                _pool_name, 
                                                _schema_name, 
                                                _collection_name, 
                                                _search_tvar, 
                                                _allocator_var,
                                                _fit_mode,
                                                _param_for_tree);

}





    #pragma endregion ADD_COLLECTION IMPLEM


    #pragma region DISPOSE_COLLECTION IMPLEM


command_pattern::dispose_collection::dispose_collection (const std::string date) :
    command_pattern::command (date)
{   }


bool command_pattern::dispose_collection::can_execute (const std::string &request)
{

    logger_singleton::get_singleton()->get_logger()->log("DISPOSECOLLECTION command initiated verification procedure.", logger::severity::trace);

    std::istringstream iss(request);

    if (std::distance(std::istream_iterator<std::string>(iss), std::istream_iterator<std::string>()) != 4)
    {
        logger_singleton::get_singleton()->get_logger()->log("[ DISPOSECOLLECTION" + request + " ]" + "\tFailed: Invalid amount of arguments.", logger::severity::error);
        return false;
    }
    iss.clear();
    iss.seekg(0);

    std::string command;

    iss >> command;

    if (command != "DISPOSECOLLECTION")
    {
        logger_singleton::get_singleton()->get_logger()->log("Not DISPOSECOLLECTION", logger::severity::information);
        return false;
    }

    iss >> _pool_name;
    iss >> _schema_name;
    iss >> _collection_name;

    _date = getCurrentTime();

    return true;

}


void command_pattern::dispose_collection::execute ()
{

    logger_singleton::get_singleton()->get_logger()->log("DISPOSECOLLECTION initiated execution procedure.", logger::severity::trace);
    db_storage::get_singleton()->dispose_collection(_pool_name, _schema_name, _collection_name);

}


    #pragma endregion DISPOSE_COLLECTION IMPLEM




#pragma endregion COLLECTION_INTER





#pragma region USER_INTER




    #pragma region ADD_USER IMPLEM


command_pattern::add_user::add_user (const std::string date) :
    command_pattern::command (date)
{   }


bool command_pattern::add_user::can_execute (const std::string &request)
{

    logger_singleton::get_singleton()->get_logger()->log("ADDUSER command initiated verification procedure.", logger::severity::trace);

    std::istringstream iss(request);

    if (std::distance(std::istream_iterator<std::string>(iss), std::istream_iterator<std::string>()) != 7)
    {
        logger_singleton::get_singleton()->get_logger()->log("[ ADDUSER" + request + " ]" + "\tFailed: Invalid amount of arguments.", logger::severity::error);
        return false;
    }
    iss.clear();
    iss.seekg(0);

    std::string command;

    iss >> command;

    if (command != "ADDUSER")
    {
        logger_singleton::get_singleton()->get_logger()->log("Not ADDUSER", logger::severity::information);
        return false;
    }

    iss >> _pool_name;
    iss >> _schema_name;
    iss >> _collection_name;
    iss >> _user_name;
    iss >> _nickname;
    iss >> _password;

    _date = getCurrentTime();

    return true;

}


void command_pattern::add_user::execute ()
{

    logger_singleton::get_singleton()->get_logger()->log("ADDUSER initiated execution procedure.", logger::severity::trace);
    
    user fresh_user(_nickname, _password);
    
    db_storage::get_singleton()->add_user_data(
                                                _pool_name, 
                                                _schema_name, 
                                                _collection_name, 
                                                _user_name,
                                                fresh_user);

}



    #pragma endregion ADD_USER IMPLEM


    #pragma region UPDATE_USER IMPLEM


command_pattern::update_user::update_user (const std::string date) :
    command_pattern::command (date)
{   }


bool command_pattern::update_user::can_execute (const std::string &request)
{

    logger_singleton::get_singleton()->get_logger()->log("UPDATEUSER command initiated verification procedure.", logger::severity::trace);

    std::istringstream iss(request);

    if (std::distance(std::istream_iterator<std::string>(iss), std::istream_iterator<std::string>()) != 7)
    {
        logger_singleton::get_singleton()->get_logger()->log("[ UPDATEUSER" + request + " ]" + "\tFailed: Invalid amount of arguments.", logger::severity::error);
        return false;
    }
    iss.clear();
    iss.seekg(0);

    std::string command;

    iss >> command;

    if (command != "UPDATEUSER")
    {
        logger_singleton::get_singleton()->get_logger()->log("Not UPDATEUSER", logger::severity::information);
        return false;
    }

    iss >> _pool_name;
    iss >> _schema_name;
    iss >> _collection_name;
    iss >> _user_name;
    iss >> _nickname;
    iss >> _password;

    _date = getCurrentTime();

    return true;

}


void command_pattern::update_user::execute ()
{

    logger_singleton::get_singleton()->get_logger()->log("UPDATEUSER initiated execution procedure.", logger::severity::trace);
    
    user fresh_user(_nickname, _password);
    
    db_storage::get_singleton()->add_user_data(
                                                _pool_name, 
                                                _schema_name, 
                                                _collection_name, 
                                                _user_name,
                                                fresh_user);

}

    #pragma endregion UPDATE_USER IMPLEM


    #pragma region DISPOSE_USER IMPLEM



command_pattern::dispose_user::dispose_user (const std::string date) :
    command_pattern::command (date)
{   }


bool command_pattern::dispose_user::can_execute (const std::string &request)
{

    logger_singleton::get_singleton()->get_logger()->log("DISPOSEUSER command initiated verification procedure.", logger::severity::trace);

    std::istringstream iss(request);

    if (std::distance(std::istream_iterator<std::string>(iss), std::istream_iterator<std::string>()) != 5)
    {
        logger_singleton::get_singleton()->get_logger()->log("[ DISPOSEUSER" + request + " ]" + "\tFailed: Invalid amount of arguments.", logger::severity::error);
        return false;
    }
    iss.clear();
    iss.seekg(0);

    std::string command;

    iss >> command;

    if (command != "DISPOSEUSER")
    {
        logger_singleton::get_singleton()->get_logger()->log("Not DISPOSEUSER", logger::severity::information);
        return false;
    }

    iss >> _pool_name;
    iss >> _schema_name;
    iss >> _collection_name;
    iss >> _user_name;

    _date = getCurrentTime();

    return true;

}


void command_pattern::dispose_user::execute ()
{

    logger_singleton::get_singleton()->get_logger()->log("DISPOSEUSER initiated execution procedure.", logger::severity::trace);
    db_storage::get_singleton()->dispose_user_data(_pool_name, _schema_name, _collection_name, _user_name);

}




    #pragma endregion DISPOSE_USER IMPLEM


    #pragma region OBTAIN_USER IMPLEM


command_pattern::obtain_user::obtain_user (const std::string date) :
    command_pattern::command (date)
{   }


bool command_pattern::obtain_user::can_execute (const std::string &request)
{

    logger_singleton::get_singleton()->get_logger()->log("OBTAINUSER command initiated verification procedure.", logger::severity::trace);

    std::istringstream iss(request);

    if (std::distance(std::istream_iterator<std::string>(iss), std::istream_iterator<std::string>()) != 5)
    {
        logger_singleton::get_singleton()->get_logger()->log("[ OBTAINUSER" + request + " ]" + "\tFailed: Invalid amount of arguments.", logger::severity::error);
        return false;
    }
    iss.clear();
    iss.seekg(0);

    std::string command;

    iss >> command;

    if (command != "OBTAINUSER")
    {
        logger_singleton::get_singleton()->get_logger()->log("Not OBTAINUSER", logger::severity::information);
        return false;
    }

    iss >> _pool_name;
    iss >> _schema_name;
    iss >> _collection_name;
    iss >> _user_name;

    _date = getCurrentTime();

    return true;

}


void command_pattern::obtain_user::execute ()
{

    logger_singleton::get_singleton()->get_logger()->log("OBTAINUSER initiated execution procedure.", logger::severity::trace);
    db_storage::get_singleton()->obtain_user_data(_pool_name, _schema_name, _collection_name, _user_name);

}


    #pragma endregion OBTAIN_USER IMPLEM


    #pragma region OBTAIN_USERS_BETWEEN IMPLEM


command_pattern::obtain_user_between::obtain_user_between (const std::string date) :
    command_pattern::command (date)
{   }


bool command_pattern::obtain_user_between::can_execute (const std::string &request)
{

    logger_singleton::get_singleton()->get_logger()->log("OBTAINBETWEEN command initiated verification procedure.", logger::severity::trace);

    std::istringstream iss(request);

    if (std::distance(std::istream_iterator<std::string>(iss), std::istream_iterator<std::string>()) != 8)
    {
        logger_singleton::get_singleton()->get_logger()->log("[ OBTAINBETWEEN" + request + " ]" + "\tFailed: Invalid amount of arguments.", logger::severity::error);
        return false;
    }
    iss.clear();
    iss.seekg(0);

    std::string command;

    iss >> command;

    if (command != "OBTAINBETWEEN")
    {
        logger_singleton::get_singleton()->get_logger()->log("Not OBTAINBETWEEN", logger::severity::information);
        return false;
    }

    iss >> _pool_name;
    iss >> _schema_name;
    iss >> _collection_name;
    iss >> _lower_bound;
    iss >> _upper_bound;

    try
    {
        iss >> _lower_bound_inclusive;
        iss >> _upper_bound_inclusive;
    }
    catch (const std::exception &e)
    {
        logger_singleton::get_singleton()->get_logger()->log(e.what(), logger::severity::error);
        return 0;
    }

    _date = getCurrentTime();

    return true;

}


void command_pattern::obtain_user_between::execute ()
{

    logger_singleton::get_singleton()->get_logger()->log("OBTAINUSER initiated execution procedure.", logger::severity::trace);
    db_storage::get_singleton()->obtain_between( 
                                                    _pool_name,
                                                    _schema_name, 
                                                    _collection_name,
                                                    _lower_bound,
                                                    _upper_bound,
                                                    _lower_bound_inclusive,
                                                    _upper_bound_inclusive);

}


    #pragma endregion OBTAIN_USER_BETWEEN IMPLEM


    #pragma region OBTAIN_MIN_USER IMPLEM

command_pattern::obtain_min_user::obtain_min_user (const std::string date) :
    command_pattern::command (date)
{   }


bool command_pattern::obtain_min_user::can_execute (const std::string &request)
{

    logger_singleton::get_singleton()->get_logger()->log("OBTAINMINUSER command initiated verification procedure.", logger::severity::trace);

    std::istringstream iss(request);

    if (std::distance(std::istream_iterator<std::string>(iss), std::istream_iterator<std::string>()) != 4)
    {
        logger_singleton::get_singleton()->get_logger()->log("[ OBTAINMINUSER" + request + " ]" + "\tFailed: Invalid amount of arguments.", logger::severity::error);
        return false;
    }
    iss.clear();
    iss.seekg(0);

    std::string command;

    iss >> command;

    if (command != "OBTIANMINUSER")
    {
        logger_singleton::get_singleton()->get_logger()->log("Not OBTAINMINUSER", logger::severity::information);
        return false;
    }

    iss >> _pool_name;
    iss >> _schema_name;
    iss >> _collection_name;

    _date = getCurrentTime();

    return true;

}


void command_pattern::obtain_min_user::execute ()
{

    logger_singleton::get_singleton()->get_logger()->log("OBTAINMINUSER initiated execution procedure.", logger::severity::trace);
    db_storage::get_singleton()->obtain_min_user(_pool_name, _schema_name, _collection_name);

}


    #pragma endregion OBTAIN_MIN_USER IMPLEM


    #pragma region OBTAIN_MAX_USER IMPLEM

    
command_pattern::obtain_max_user::obtain_max_user (const std::string date) :
    command_pattern::command (date)
{   }


bool command_pattern::obtain_max_user::can_execute (const std::string &request)
{

    logger_singleton::get_singleton()->get_logger()->log("OBTAINMAXUSER command initiated verification procedure.", logger::severity::trace);

    std::istringstream iss(request);

    if (std::distance(std::istream_iterator<std::string>(iss), std::istream_iterator<std::string>()) != 4)
    {
        logger_singleton::get_singleton()->get_logger()->log("[ OBTAINMAXUSER" + request + " ]" + "\tFailed: Invalid amount of arguments.", logger::severity::error);
        return false;
    }
    iss.clear();
    iss.seekg(0);

    std::string command;

    iss >> command;

    if (command != "OBTAINMAXUSER")
    {
        logger_singleton::get_singleton()->get_logger()->log("Not OBTAINMAXUSER", logger::severity::information);
        return false;
    }

    iss >> _pool_name;
    iss >> _schema_name;
    iss >> _collection_name;

    _date = getCurrentTime();

    return true;

}


void command_pattern::obtain_max_user::execute ()
{

    logger_singleton::get_singleton()->get_logger()->log("OBTAINMAXUSER initiated execution procedure.", logger::severity::trace);
    db_storage::get_singleton()->obtain_max_user(_pool_name, _schema_name, _collection_name);

}


    #pragma endregion OBTAIN_MAX_USER IMPLEM




#pragma endregion USER_INTER


