
#ifndef OPERATING_SYSTEMS_COURSE_WORK_FLYWEIGHT_SINGLETON_H
#define OPERATING_SYSTEMS_COURSE_WORK_FLYWEIGHT_SINGLETON_H


#include <map>
#include <string>
#include <memory>
#include <flyweight_string.h>


class flyweight_string_singleton final
{

private:

    std::map<std::string, std::shared_ptr<flyweight_string>> _pool;

private:

    flyweight_string_singleton();

    static flyweight_string_singleton *define_singleton();  

    std::shared_ptr<flyweight_string> get_sample(const std::string &data);

    void update();

};


#endif