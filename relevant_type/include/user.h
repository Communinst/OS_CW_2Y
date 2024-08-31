#ifndef OPERATING_SYSTEMS_COURSE_WORK_RELEVANT_TYPE_H
#define OPERATING_SYSTEMS_COURSE_WORK_RELEVANT_TYPE_H

#include <singleton.h>
#include <memory>
#include <string>

class user final
{

private:

    long int _balance;
    std::shared_ptr<flyweight_string> _login;
    std::shared_ptr<flyweight_string> _password;

public:

    user(
        const std::string login,
        const std::string password);

private:

    void copy_from (
        const user &other);
    
    void move_from (
        user &&other);

public:

    ~user();

    user (
        const user &other);

    user (
        user &&other);

    user &operator= (
        const user &other);
    
    user &operator= (
        user &&other);

};


#endif