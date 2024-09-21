#ifndef OPERATING_SYSTEMS_COURSE_WORK_PROGRAM_H
#define OPERATING_SYSTEMS_COURSE_WORK_PROGRAM_H

#include "../../IPC/include/ipc.h"
#include "../../inner_architecture/include/inner_architecture.h"
#include "../../logger/logger_singleton/include/singleton.h"
#include "../../command/include/command.h"
#include "../../COR/include/handlers.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <iomanip>
#include <cstring>



namespace interaction
{



    // MAIN
    int dialog (int argc, char **argv);


    void initiate_start ();

    int initiate_setup_process ();

    int is_futher_instructions ();

    void handle_requests_via_path (const std::string &path = "");
    void handle_request_via_console ();
    
    void handle_request (std::string &request);
    
};

//class interaction final
//{
//private:
//
//    chain_of_responsibility::request_with_command_chain _chain_of_persistence;
//
//public:
//
//    int dialog (int argc, char **argv);
//
//    void initiate_start ();
//
//    int initiate_setup_process ();
//    
//    void handle_requests_via_path (const std::string &path = "");
//    void handle_request_via_console ();
//    void handle_request (const std::string &request);
//}






#endif