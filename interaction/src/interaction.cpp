
#include <interaction.h>


int is_leap_year(const int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int is_valid_time_ISO_8601(const char *dateString) {
    // YYYY-MM-DDTHH:MM:SSZ
    if (strlen(dateString) != 20) {
        return 0; 
    }

    for (int i = 0; i < 20; i++) {
        if (i == 4 || i == 7) {
            if (dateString[i] != '-') {
                return 0; 
            }
        }
        else if (i == 13 || i == 16) {
            if (dateString[i] != ':') {
                return 0; 
            }
        }
        else if (i == 10) {
            if (dateString[i] != 'T') {
                return 0;
            }
        }
        else if (i == 19) {
            if (dateString[i] != 'Z') {
                return 0;
            }
        }
        else {
            if (!isdigit(dateString[i])) {
                return 0;
            }
        }
    }

    int year, month, day, hour, minute, second;
    sscanf(dateString, "%d-%d-%dT%d:%d:%dZ", &year, &month, &day, &hour, &minute, &second);

    if (year < 1000 || year > 9999 || month < 1 || month > 12 || day < 1 || day > 31 ||
     hour < 0 || hour > 23 || minute < 0 || minute > 59 || second < 0 || second > 59) {
        return 0; 
    }

    int daysInMonth[] = {31, 28 + is_leap_year(year), 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (day > daysInMonth[month - 1]) {
        return 0; 
    }

    return 1; 
}




int interaction::dialog (int argc, char **argv)
{

    std::cout << "Greetings. Shall we get started?. y/n" << std::endl;

    try
    {
        initiate_start ();
    }
    catch (const std::exception &e)
    {
        //logger_singleton::get_singleton()->get_logger()->log("Start wasn't initiated. System shut down.", logger::severity::trace);
    }

    
    for (auto res = 1; res != 0; res = initiate_setup_process()) {};
//    while (initiate_setup_process()) {};

    for (auto i = 1; i < argc; i++)
    {
        handle_requests_via_path (argv[i]);
    }

    if (is_futher_instructions())
    {
        handle_request_via_console ();
    }
    

    //db_storage::get_singleton()->clear();
    RWCC_singleton::get_singleton()->clear();

    return 0;

}

void interaction::initiate_start ()
{
    std::string buff_answer;
    while (std::getline(std::cin, buff_answer))
    {
        
        if (buff_answer == "y")
        {
            logger_singleton::get_singleton()->get_logger()->log("Initiating setup process", logger::severity::trace);
            break;
        }
        else if (buff_answer == "n")
        {
            throw (std::logic_error("Start wasn't initiated. System shut down."));
        }
        else
        {
            std::cout << "Please answer y/n" << std::endl;
        }
    }
}

int interaction::initiate_setup_process ()
{
    std::string input;
    std::cout << "Type in prefered database mode (FILE/RAM):" << std::endl;
    while(std::getline(std::cin, input))
    {
        
        try
        {
            ipc::mode buff = ipc::string_to_mode(input);
            db_storage::get_singleton()->setup(1, buff);
            break;
        }
        catch (const std::exception &e)
        {
            std::cout << "Invalid mode. Please try again." << std::endl;
        }
    
    }

    return 0;

}

int interaction::is_futher_instructions ()
{

    std::string answer;

    std::cout << "Any commands left? y/n" << std::endl;
    while (std::getline(std::cin, answer))
    {

        if (answer == "y")
        {
            return 1;
        }
        else if (answer == "n")
        {
            return 0;
        }
        else
        {
            std::cout << "Please answer y/n" << std::endl;
        }

    }

    
}

void interaction::handle_requests_via_path (const std::string &path)
{

    std::ifstream request_file_input(path);

    if (!request_file_input.is_open())
    {
        logger_singleton::get_singleton()->get_logger()->log("File down the path : [" + path + "] is abscent or corrupted. No commands were received.", logger::severity::trace);
        return;
    }
    
    std::string request;
    while (std::getline(request_file_input, request))
    {
        handle_request (request);
    }

}

void interaction::handle_request_via_console ()
{
    std::cout << "Provide me with a request. Since you're out of any requests type \"EXIT\" " << std::endl;

    std::string answer;

    while (std::getline(std::cin, answer))
    {
        if (answer == "EXIT")
        {
            return;
        }
        handle_request(answer);
    }
}

void interaction::handle_request (std::string &request)
{

    chain_of_responsibility::request_with_command_chain chain;
    chain
            .add_handler(new command_pattern::add_pool())
            .add_handler(new command_pattern::dispose_pool())
            .add_handler(new command_pattern::add_schema())
            .add_handler(new command_pattern::dispose_schema())
            .add_handler(new command_pattern::add_collection())
            .add_handler(new command_pattern::dispose_collection())
            .add_handler(new command_pattern::add_user)
            .add_handler(new command_pattern::update_user())
            .add_handler(new command_pattern::dispose_user());
            
    std::cout << request << std::endl;
    if (chain.handle(request, "0000-00-00T00:00:00Z"))
    {
        chain.~request_with_command_chain();
        return;
    }

    // If received command is related to obtain process
    chain.~request_with_command_chain();

    //db_storage::get_singleton()->clear();
    std::string fixed_time;

    chain 
        .add_handler(new command_pattern::obtain_user())
        .add_handler(new command_pattern::obtain_user_between())
        .add_handler(new command_pattern::obtain_min_user())
        .add_handler(new command_pattern::obtain_max_user());
}


