#ifndef WG_ENTRY_TASKS_SRC_FIRST_TASK_IS_EVEN_HPP
#define WG_ENTRY_TASKS_SRC_FIRST_TASK_IS_EVEN_HPP

namespace tasks 
{
    bool is_even(int value) 
    {
        return (value & 1) == 0;
    }

} //namespace tasks

#endif