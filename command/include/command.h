
#ifndef OPERATING_SYSTEMS_COURSE_WORK_COMMAND_H
#define OPERATING_SYSTEMS_COURSE_WORK_COMMAND_H

#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>


#include "../../logger/logger_singleton/include/singleton.h"
#include "../../inner_architecture/include/inner_architecture.h"
#include "../../IPC/include/ipc.h"

namespace command_pattern
{

//enum class commands
//{
//
//    ADDPOOL = 0,
//    DISPOSEPOOL,
//    ADDSCHEMA,
//    DISPOSESCHEMA,
//    ADDCOLLECTION,
//    DISPOSECOLLECTION,
//    ADDUSER,
//    UPDATEUSER,
//    DISPOSEUSER,
//    OBTAINUSER,
//    OBTAINBETWEEN,
//    OBTAINMIN,
//    OBTAINMAX
//
//};
//
//commands string_to_commands (const std::string &command)
//{
//
//    if (command == "ADDPOOL")
//    {
//        return commands::ADDPOOL;
//    }
//    else if (command == "DISPOSEPOOL")
//    {
//        return commands::DISPOSEPOOL;
//    }
//
//    else if (command == "ADDSCHEMA")
//    {
//        return commands::ADDSCHEMA;
//    }
//    else if (command == "DISPOSESCHEMA")
//    {
//        return commands::DISPOSESCHEMA;
//    }
//
//    else if (command == "ADDCOLLECTION")
//    {
//        return commands::ADDCOLLECTION;
//    }
//    else if (command == "DISPOSECOLLECTION")
//    {
//        return commands::DISPOSECOLLECTION;
//    }
//
//    else if (command == "ADDUSER")
//    {
//        return commands::ADDUSER;
//    }
//    else if (command == "UPDATEUSER")
//    {
//        return commands::UPDATEUSER;
//    }
//    else if (command == "DISPOSEUSER")
//    {
//        return commands::DISPOSEUSER;
//    }
//
//    else if (command == "OBTAINUSER")
//    {
//        return commands::OBTAINUSER;
//    }
//    else if (command == "OBTAINBETWEEN")
//    {
//        return commands::OBTAINBETWEEN;
//    }
//    else if (command == "OBTAINMIN")
//    {
//        return commands::OBTAINMIN;
//    }
//    else if (command == "OBTAINMAX")
//    {
//        return commands::OBTAINMAX;
//    }
//
//    else
//    {
//        throw std::logic_error("Invalid command typed.");
//    }
//
//
//
//
//
//}

    std::string getCurrentTime();

#pragma region COMMAND PARENT PROPS

    class command 
    {

    protected:

        std::string _date;

    public:

        command (const std::string data = "");

        virtual ~command() = default;

    public:

        std::string get_date () const noexcept;

        virtual bool can_execute(const std::string &) = 0;

        virtual void execute () = 0;

    };

#pragma endregion COMMAND PARENT PROPS



#pragma region POOL_INTER





    #pragma region ADD_POOL PROPS

    class add_pool final :
        public command
    {

    private:

        std::string _pool_name;

        ipc::search_tvar _search_tvar;
        size_t _param_for_tree;

        

    public:

        add_pool (const std::string data = "");

        bool can_execute (const std::string &request) override;

        void execute () override;

    };

    #pragma endregion ADD_POOL PROPS




    #pragma region DISPOSE_POOL PROPS

    class dispose_pool final :
        public command
    {

    private:

        std::string _pool_name;
        

    public:

        dispose_pool (const std::string data = "");

        bool can_execute (const std::string &request) override;

        void execute () override;

    };

    #pragma endregion DISPOSE_POOL PROPS





#pragma endregion POOL_INTER



#pragma region SCHEMA_INTER





    #pragma region ADD_SCHEMA PROPS

    class add_schema final :
        public command
    {

    private:

        std::string _pool_name;
        std::string _schema_name;

        ipc::search_tvar _search_tvar;
        size_t _param_for_tree;

        

    public:

        add_schema (const std::string data = "");

        bool can_execute (const std::string &request) override;

        void execute () override;

    };

    #pragma endregion ADD_SCHEMA PROPS




    #pragma region DISPOSE_SCHEMA PROPS

    class dispose_schema final :
        public command
    {

    private:

        std::string _pool_name;
        std::string _schema_name;

    public:

        dispose_schema (const std::string data = "");

        bool can_execute (const std::string &request) override;

        void execute () override;

    };

    #pragma endregion DISPOSE_SCHEMA PROPS





#pragma endregion SCHEMA_INTER



#pragma region COLLECTION_INTER





    #pragma region ADD_COLLECTION PROPS

    class add_collection final :
        public command
    {

    private:

        std::string _pool_name;
        std::string _schema_name;
        std::string _collection_name;

        ipc::search_tvar _search_tvar;
        ipc::allocator_var _allocator_var;
        allocator_with_fit_mode::fit_mode _fit_mode;
        size_t _param_for_tree;

        

    public:

        add_collection (const std::string data = "");

        bool can_execute (const std::string &request) override;

        void execute () override;

    };

    #pragma endregion ADD_COLLECTION PROPS




    #pragma region DISPOSE_COLLECTION PROPS

    class dispose_collection final :
        public command
    {

    private:

        std::string _pool_name;
        std::string _schema_name;
        std::string _collection_name;
        

    public:

        dispose_collection (const std::string data = "");

        bool can_execute (const std::string &request) override;

        void execute () override;

    };

    #pragma endregion DISPOSE_COLLECTION PROPS





#pragma endregion COLLECTION_INTER



#pragma region USER_INTER





    #pragma region ADD_USER PROPS

    class add_user final :
        public command
    {

    private:

        std::string _pool_name;
        std::string _schema_name;
        std::string _collection_name;
        std::string _user_name;
        std::string _nickname;
        std::string _password;
        
    public:

        add_user (const std::string data = "");

        bool can_execute (const std::string &request) override;

        void execute () override;

    };

    #pragma endregion ADD_USER PROPS





#pragma region UPDATE_USER PROPS

    class update_user final :
        public command
    {

    private:

        std::string _pool_name;
        std::string _schema_name;
        std::string _collection_name;
        std::string _user_name;
        std::string _nickname;
        std::string _password;

    public:

        update_user (const std::string data = "");

        bool can_execute (const std::string &request) override;

        void execute () override;

    };

    #pragma endregion UPDATE_USER PROPS




    #pragma region DISPOSE_USER PROPS

    class dispose_user final :
        public command
    {

    private:

        std::string _pool_name;
        std::string _schema_name;
        std::string _collection_name;
        std::string _user_name;        

    public:

        dispose_user (const std::string data = "");

        bool can_execute (const std::string &request) override;

        void execute () override;

    };

    #pragma endregion DISPOSE_USER PROPS





    #pragma region OBTAIN_USER PROPS

    class obtain_user final :
        public command
    {

    private:

        std::string _pool_name;
        std::string _schema_name;
        std::string _collection_name;
        std::string _user_name;

    public:

        obtain_user (const std::string data = "");

        bool can_execute (const std::string &request) override;

        void execute () override;

    };

    #pragma endregion OBTAIN_USER PROPS





    #pragma region OBTAIN_USERS_BETWEEN PROPS

    class obtain_user_between final :
        public command
    {

    private:

        std::string _pool_name;
        std::string _schema_name;
        std::string _collection_name;

        std::string _lower_bound;
        std::string _upper_bound;

        bool _lower_bound_inclusive;
        bool _upper_bound_inclusive;

    public:

        obtain_user_between (const std::string data = "");

        bool can_execute (const std::string &request) override;

        void execute () override;

    };

    #pragma endregion OBTAIN_USER_BETWEEN PROPS





    #pragma region OBTAIN_MIN_USER PROPS

    class obtain_min_user final :
        public command
    {

    private:

        std::string _pool_name;
        std::string _schema_name;
        std::string _collection_name;

    public:

        obtain_min_user (const std::string data = "");

        bool can_execute (const std::string &request) override;

        void execute () override;

    };

    #pragma endregion OBTAIN_MIN_USER PROPS





    #pragma region OBTAIN_MAX_USER PROPS

    class obtain_max_user final :
        public command
    {

    private:

        std::string _pool_name;
        std::string _schema_name;
        std::string _collection_name;

    public:

        obtain_max_user (const std::string date = "");

        bool can_execute (const std::string &request) override;

        void execute () override;

    };

    #pragma endregion OBTAIN_MAX_USER PROPS





#pragma endregion USER_INTER


}

#endif //OPERATING_SYSTEMS_COURSE_WORK_COMMAND