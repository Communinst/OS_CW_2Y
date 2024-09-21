#ifndef OPERATING_SYSTEMS_COURSE_WORK_RELEVANT_TYPE_H
#define OPERATING_SYSTEMS_COURSE_WORK_RELEVANT_TYPE_H

#include "../../flyweight/flyweight_string/singleton/include/singleton.h"
#include <memory>
#include <string>

class user final
{

private:

    long int _balance;
    std::shared_ptr<flyweight_string> _nickname;
    std::shared_ptr<flyweight_string> _password;

public:

    user ();

    user (
        const std::string nickname,
        const std::string password,
        long balance = 0);

public:

    std::string get_nick ()  const noexcept;
    std::string get_password ()  const noexcept;
    long int get_balance () const noexcept;

private:

    void copy_from (
        const user &other);
    
    void move_from (
        user &&other);

public:

    ~user() = default;

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