#ifndef OPERATING_SYSTEMS_COURSE_WORK_DC_UTILITIES_H
#define OPERATING_SYSTEMS_COURSE_WORK_DC_UTILITIES_H


#include <string>

namespace DC_utilities
{

    std::string make_path (
        std::initializer_list<std::string> lists);

    std::string make_path (
        std::initializer_list<const char *> list);

}


#endif