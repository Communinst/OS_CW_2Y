
#ifndef OPERATING_SYSTEMS_COURSE_WORK_FLYWEIGHT_STRING_H
#define OPERATING_SYSTEMS_COURSE_WORK_FLYWEIGHT_STRING_H


#include <string>


class flyweight_string final
{

private:

    const std::string _data;

public:

    flyweight_string(
        const std::string &data);

    const std::string &get_data() const;

};


#endif