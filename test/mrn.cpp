

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

    //argc = 2;
    //argv[1] = "X:\\Coding\\CPP\\CourseWorkOpS\\test\\command.txt";

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

    db_storage::get_singleton()->setup(1, ipc::mode::RAM);



    db_storage *db = db_storage::get_singleton();

    user f1("Slave", "Moronovich");
    user f2("Slave", "Moronovichkov");
    user f3("Slave", "Moronovichkova");
    user f4("Nigger", "Beatend");
    user f5("Poo", "Rbastard");

    db
        ->add_pool("a", ipc::search_tvar::B, 5);
        //->add_schema("a", "b", ipc::search_tvar::B, 5)
        //->add_collection("a", "b", "a", 
        //    ipc::search_tvar::B,
        //    ipc::allocator_var::GLOBAL_HEAP,
        //    allocator_with_fit_mode::fit_mode::the_best_fit,
        //    5)
        //->add_collection("a", "b", "b", 
        //    ipc::search_tvar::B,
        //    ipc::allocator_var::GLOBAL_HEAP,
        //    allocator_with_fit_mode::fit_mode::the_best_fit,
        //    5)
        //->add_user_data("a", "b", "a", "a", f1)
        //->add_user_data("a", "b", "a", "b", f2)
        //->add_user_data("a", "b", "a", "c", f3)
        //->add_user_data("a", "b", "a", "d", f4)
        //->add_user_data("a", "b", "a", "e", f5)
        //->dispose_user_data("a", "b", "a", "e");


    //user user = db_storage::get_singleton()
    //    ->add_collection("moron", "gay", "fag", ipc::search_tvar::B, 
    //                            ipc::allocator_var::BOUNDARY_TAGS, 
    //                            allocator_with_fit_mode::fit_mode::the_best_fit, 6)
    //    ->add_user_data("moron", "gay", "fag", "off", fresh1)
    //    ->add_user_data("moron", "gay", "jerk", "on", fresh2)
    //    ->obtain_user_data("moron", "gay", "jerk", "up");   

    //db_storage::get_singleton()

    db_storage::pool pool = db->obtain_from_inner("a");
    //db_storage::schema schema = pool.obtain_from_inner("b");
    //db_storage::collection collection = db->obtain_from_inner("a").obtain_from_inner("b").obtain_from_inner("b");
    //user user = db->obtain_user_data("a", "b", "a", "e");


    db_storage::get_singleton()->clear();

    return 0;

}