#ifndef OPERATING_SYSTEMS_COURSE_WORK_DC_UTILITIES_H
#define OPERATING_SYSTEMS_COURSE_WORK_DC_UTILITIES_H


#include <string>
#include <stdexcept>

#include "../../flyweight/flyweight_string/include/flyweight_string.h"
#include "../../flyweight/flyweight_string/singleton/include/singleton.h"

namespace DC_utilities
{

    std::string make_path (
        std::initializer_list<std::string> lists);

    std::string make_path (
        std::initializer_list<const char *> list);

    //template<
    //    typename T>
    //std::string make_string(T const &value);
    
    /*template<>*/ std::string make_string(int const &value);
    /*template<>*/ std::string make_string(long const &value);
    /*template<>*/ std::string make_string(long long const &value);
    /*template<>*/ std::string make_string(unsigned const &value);
    /*template<>*/ std::string make_string(unsigned long const &value);
    /*template<>*/ std::string make_string(unsigned long long const &value);
    /*template<>*/ std::string make_string(float const &value);
    /*template<>*/ std::string make_string(double const &value);
    /*template<>*/ std::string make_string(long double const &value);
    /*template<>*/ std::string make_string(const std::string &value);
    /*template<>*/ std::string make_string(char * const &value);
    /*template<>*/ std::string make_string(std::shared_ptr<flyweight_string> const &value);


    class file_cannot_be_opened final:
        public std::runtime_error
    {

    public:

        explicit file_cannot_be_opened(
            const std::string &file_path);

    };


    


}


#endif