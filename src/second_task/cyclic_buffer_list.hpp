#ifndef WG_ENTRY_TASKS_SRC_SECOND_TASK_CYCLIC_BUFFER_LIST_HPP
#define WG_ENTRY_TASKS_SRC_SECOND_TASK_CYCLIC_BUFFER_LIST_HPP

#include <stdexcept>
#include <memory>

namespace tasks
{
namespace list_impl 
{
    template<typename ItemType>
    struct buffer_item
    {
        ItemType value = 0;
        buffer_item* next = nullptr;

        buffer_item(const ItemType val = 0, buffer_item* nextItem = nullptr)
        {
            value = val;
            next = nextItem;
        }

        buffer_item& operator=(const buffer_item& that)
        {
            value = that.value;
            next = nullptr;
            return *this;
        }

        buffer_item& operator=(buffer_item&& that)
        {
            value = std::move(that.value);
            next = nullptr;
            that.next = nullptr;
            return *this;
        }
    };

    template<typename ItemType, size_t Size>
    class cyclic_buffer
    {
        using item_type = ItemType;
        using item = buffer_item<item_type>;
        using allocator_traits = std::allocator_traits<std::allocator<item_type>>;

    public:
        cyclic_buffer()
        {
            for (int i = 0; i < Size - 1; ++i) {
                _items[i].next = &_items[i + 1];
            }
            _items[Size - 1].next = &_items[0];
            _head = _items;
            _tail = _head;
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
            _head->value = item;
            _head = _head->next;
            ++_counter;
        }

        void push(item_type&& item)
        {
            if (is_full())
            {
                throw std::logic_error("Buffer is full!");
            }
            _head->value = std::move(item);
            _head = _head->next;
            ++_counter;
        }

        item_type [[nodiscard]] pop()
        {
            if (is_empty())
            {
                throw std::logic_error("Buffer is empty!");
            }
            item_type item = std::move(_tail->value);
            _tail = _tail->next;
            --_counter;
            return item;
        }

        void clear()
        {
            if(is_empty()) {
                return;
            }
            allocator_traits::destroy(_allocator, _items);
            _head = nullptr;
            _tail = nullptr;
            _counter = 0;
        }

    private:
        item _items[Size];

        item* _head;
        item* _tail;
        size_t _counter;

        std::allocator<item_type> _allocator;
    };
    
} //namespace list_impl
} //namespace tasks

#endif