
#include <dc_utilities.h>


std::string DC_utilities::make_path(std::initializer_list<std::string> lists)
{
    std::string path = "";

    for (auto el : lists)
    {
        if (path[0])
        {
            path.push_back('/');
        }
        path += el;

    }

    return path;
}

std::string DC_utilities::make_path(std::initializer_list<const char *> lists)
{

    std::string path = "";

    for (auto el : lists)
    {
        if (path[0])
        {
            path.push_back('/');
        }
        path += el;

    }

    return path;    

}