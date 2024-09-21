
#include "../include/ipc.h"
#include <stdexcept>


ipc::search_tvar ipc::string_to_searchtvar (const std::string &sample)
{
    if (sample == "B")
    {
        return ipc::search_tvar::B;
    }
    else if (sample == "B_PLUS")
    {
        return ipc::search_tvar::B_PLUS;
    }
    else if (sample == "B_STAR")
    {
        return ipc::search_tvar::B_STAR;
    }
    else if (sample == "B_STAR_PLUS")
    {
        return ipc::search_tvar::B_STAR_PLUS;
    }
    else
    {
        throw std::logic_error("Invalid tree type.");
    }
}

ipc::allocator_var ipc::string_to_allocatorvar (const std::string &sample)
    {

        if (sample == "GLOBAL_HEAP")
        {
            return ipc::allocator_var::GLOBAL_HEAP;
        }
        else if (sample == "BOUNDARY_TAGS")
        {
            return ipc::allocator_var::BOUNDARY_TAGS;
        }
        else if (sample == "BUDDIES")
        {
            return ipc::allocator_var::BUDDIES;
        }
        else if (sample == "SORTED_LIST")
        {
            return ipc::allocator_var::SORTED_LIST;
        }
        else if (sample == "RBT")
        {
            return ipc::allocator_var::RBT;
        }
        else
        {
            throw std::logic_error("Invalid allocator type.");
        }

    }

allocator_with_fit_mode::fit_mode ipc::string_to_fmode (const std::string &sample)
{

    if (sample == "first_fit")
    {
        return allocator_with_fit_mode::fit_mode::first_fit;
    }
    else if (sample == "the_best_fit")
    {
        return allocator_with_fit_mode::fit_mode::the_best_fit;
    }
    else if (sample == "the_worst_fit")
    {
        return allocator_with_fit_mode::fit_mode::the_worst_fit;
    }
    else
    {
        throw std::logic_error("Invalid fmode type.");
    }

}

ipc::mode ipc::string_to_mode (const std::string &sample)
{
    if (sample == "FILE")
    {
        return ipc::mode::FILE;
    }
    else if (sample == "RAM")
    {
        return ipc::mode::RAM;
    }
    else
    {
        throw std::logic_error("Invalid tree type.");
    }
}