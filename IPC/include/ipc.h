
#ifndef OPERATING_SYSTEMS_COURSE_WORK_IPC_H
#define OPERATING_SYSTEMS_COURSE_WORK_IPC_H


#include <string>
#include "../../allocator/allocator/include/allocator_with_fit_mode.h"

namespace ipc
{

    
#pragma region ENUMS

    enum class search_tvar
    {
        B,
        B_PLUS,
        B_STAR,
        B_STAR_PLUS
    };

    ipc::search_tvar string_to_searchtvar (const std::string &sample);

    enum class allocator_var
    {
        GLOBAL_HEAP,
        BOUNDARY_TAGS,
        BUDDIES,
        SORTED_LIST,
        RBT
    };

    ipc::allocator_var string_to_allocatorvar (const std::string &sample);
    allocator_with_fit_mode::fit_mode string_to_fmode (const std::string &sample);

    enum class mode
    {
        UNINITIALIZED,
        RAM,
        FILE
    };

    ipc::mode string_to_mode (const std::string &sample);

#pragma endregion ENUMS


}


#endif