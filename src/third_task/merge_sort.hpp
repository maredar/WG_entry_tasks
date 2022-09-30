#ifndef WG_ENTRY_TASKS_SRC_THIRD_TASK_MERGE_SORT_HPP
#define WG_ENTRY_TASKS_SRC_THIRD_TASK_MERGE_SORT_HPP

namespace tasks
{
    template<typename ItemType>
    void merge(ItemType arr[], size_t left, size_t mid, size_t right)
    {
        size_t left_size = mid - left + 1;
        size_t right_size = right - mid;

        ItemType* left_arr = new ItemType[left_size];
        ItemType* right_arr = new ItemType[right_size];

        for(int i = 0; i < left_size; ++i)
        {
            left_arr[i] = arr[left + i];
        }
        for(int i = 0; i < right_size; ++i)
        {
            right_arr[i] = arr[mid + 1 + i];
        }

        size_t left_index = 0;
        size_t right_index = 0;
        size_t merge_index = left;

        while(left_index < left_size && right_index < right_size)
        {
            if(left_arr[left_index] <= right_arr[right_index])
            {
                arr[merge_index] = left_arr[left_index];
                ++left_index;
            }
            else
            {
                arr[merge_index] = right_arr[right_index];
                ++right_index;
            }
            ++merge_index;
        }

        while(left_index < left_size)
        {
            arr[merge_index] = left_arr[left_index];
            ++left_index;
            ++merge_index;
        }

        while(right_index < right_size)
        {
            arr[merge_index] = right_arr[right_index];
            ++right_index;
            ++merge_index;
        }

        delete[] right_arr;
        delete[] left_arr;
    }

    template<typename ItemType>
    void merge_sort(ItemType arr[], size_t left, size_t right)
    {
        if (left >= right)
        {
            return;
        }

        size_t mid = left + (right - left) / 2;
        merge_sort(arr, left, mid);
        merge_sort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }

} //namespace tasks

#endif