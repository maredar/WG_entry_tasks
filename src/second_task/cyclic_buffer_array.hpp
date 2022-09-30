#ifndef WG_ENTRY_TASKS_SRC_SECOND_TASK_CYCLIC_BUFFER_ARRAY_HPP
#define WG_ENTRY_TASKS_SRC_SECOND_TASK_CYCLIC_BUFFER_ARRAY_HPP

#include <stdexcept>
#include <memory>

namespace tasks
{
namespace array_impl 
{
    template<typename ItemType, size_t Size>
    class cyclic_buffer
    {
        using item_type = ItemType;
        using allocator_traits = std::allocator_traits<std::allocator<item_type>>;

    public:
        cyclic_buffer() noexcept
        {
            _head = 0;
            _tail = 0;
            _counter = 0;
        }
        ~cyclic_buffer()
        {
            clear();
        }

    public:
        bool [[nodiscard]] is_empty() const noexcept
        {
            return _counter == 0;
        }

        bool [[nodiscard]] is_full() const noexcept
        {
            return _counter == Size;
        }

        constexpr size_t [[nodiscard]] size() const noexcept
        {
            return Size;
        }

        size_t [[nodiscard]] count() const noexcept
        {
            return _counter;
        }

        void push(const item_type& item)
        {
            if (is_full())
            {
                throw std::logic_error("Buffer is full!");
            }

            allocator_traits::construct(_allocator, _items + _head, item);

            _head = next_index_of(_head);
            ++_counter;
        }

        void push(item_type&& item)
        {
            if (is_full())
            {
                throw std::logic_error("Buffer is full!");
            }

            allocator_traits::construct(_allocator, _items + _head, std::move(item));

            _head = next_index_of(_head);
            ++_counter;
        }

        item_type [[nodiscard]] pop()
        {
            if (is_empty())
            {
                throw std::logic_error("Buffer is empty!");
            }

            item_type item = std::move(_items[_tail]);

            _tail = next_index_of(_tail);
            --_counter;
            return item;
        }

        void clear()
        {
            if (is_empty()) {
                return;
            }
            allocator_traits::destroy(_allocator, _items);
            _head = 0;
            _tail = 0;
            _counter = 0;
        }

    private:
        item_type _items[Size];

        size_t _head;
        size_t _tail;
        size_t _counter;

        std::allocator<item_type> _allocator;

    private:
        size_t [[nodiscard]] next_index_of(size_t index) const noexcept
        {
            ++index;
            return index >= Size ? 0 : index;
        }
    };
    
} //namespace array_impl
} //namespace tasks

#endif