

#include "../interaction/include/interaction.h"

#include "../logger/server_logger/include/server_logger_builder.h"
#include "../logger/server_logger/include/server_logger.h"

#include <iostream>
#include <sstream>
#include <cstring>
#include <string>
//#include <filesystem>
//#include <windows.h>




int main (int argc, char *argv[])
{

    argc = 3;
    //argv[1] = "X:\\Coding\\CPP\\CourseWorkOpS\\test\\c1.txt";
    //argv[2] = "X:\\Coding\\CPP\\CourseWorkOpS\\test\\c2.txt";

    argv[1] = "C:\\Users\\Asus\\Desktop\\Coding\\CPP\\CourseWorkOpS\\test\\c1.txt";
    argv[2] = "C:\\Users\\Asus\\Desktop\\Coding\\CPP\\CourseWorkOpS\\test\\c2.txt";

    //logger_singleton::get_singleton()->get_logger()->information("moron1");
    //logger_builder *builder = new server_logger_builder();
    //
    //logger* logger = builder
    //        ->add_console_stream(logger::severity::information)
    //        ->add_console_stream(logger::severity::trace)
    //        ->add_file_stream ("X:\\Coding\\CPP\\CourseWorkOpS\\test\\tracer.txt", logger::severity::trace)
    //        ->build();
//
    //logger->log("INFO!!!", logger::severity::information);
    //logger->trace("TRACE!!!");
//
    //delete builder;
    //delete logger;

    //interaction::dialog(argc,  argv);
//
    //server_logger_builder *builder = new server_logger_builder();
//
    //logger *fresh_logger = builder
    //    ->add_console_stream(logger::severity::information)
    //    ->add_console_stream(logger::severity::trace)
    //    ->build();
//
    //fresh_logger->trace("moron");


    interaction::dialog(argc, argv);    

    return 0;

}