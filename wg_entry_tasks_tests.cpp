#include <gtest/gtest.h>
#include <string>

#include "src/first_task/is_even.hpp"
#include "src/second_task/cyclic_buffer_list.hpp"
#include "src/second_task/cyclic_buffer_array.hpp"
#include "src/third_task/merge_sort.hpp"

//=============first_task/is_even.hpp===========
TEST(TestIsEven, HandlesPositiveInputs)
{
    for(int i = 0; i < 1000; ++i) 
    {
        if(i % 2 == 0)
        {
            EXPECT_TRUE(tasks::is_even(i));
        }
        else
        {
            EXPECT_FALSE(tasks::is_even(i));
        }
    }
}
TEST(TestIsEven, HandlesNegativeInputs)
{
    for(int i = 0; i > -1000; --i)
    {
        if(i % 2 == 0)
        {
            EXPECT_TRUE(tasks::is_even(i));
        }
        else
        {
            EXPECT_FALSE(tasks::is_even(i));
        }
    }
}
//=============simple class for buffer tests================
class SimpleClass
{
public:
    SimpleClass(int data = 0) { _data = data; }
    int Get() const noexcept { return _data; }
private:
    int _data;
};
//=============second_task/cyclic_buffer_list.hpp===========
TEST(TestCyclicBufferList, HandlesIntItems)
{
    tasks::list_impl::cyclic_buffer<int, 5> buffer;
    EXPECT_TRUE(buffer.is_empty());
    EXPECT_EQ(buffer.count(), 0);
    EXPECT_EQ(buffer.size(), 5);

    buffer.push(1);
    buffer.push(2);
    buffer.push(3);
    buffer.push(4);
    buffer.push(5);
    EXPECT_ANY_THROW(buffer.push(99));
    EXPECT_EQ(buffer.size(), 5);
    EXPECT_EQ(buffer.count(), 5);
    EXPECT_EQ(buffer.pop(), 1);
    EXPECT_EQ(buffer.pop(), 2);
    EXPECT_EQ(buffer.pop(), 3);
    buffer.pop();
    buffer.pop();
    EXPECT_ANY_THROW(buffer.pop());
    buffer.push(1);
    buffer.push(2);
    buffer.pop();
    buffer.push(3);
    buffer.pop();
    buffer.push(4);
    buffer.push(5);
    EXPECT_EQ(buffer.count(), 3);
    buffer.clear();
    EXPECT_EQ(buffer.count(), 0);
    EXPECT_EQ(buffer.size(), 5);
}
TEST(TestCyclicBufferList, HandlesClassItems)
{
    SimpleClass obj_1(111);
    SimpleClass obj_2(222);
    SimpleClass obj_3(333);

    tasks::list_impl::cyclic_buffer<SimpleClass, 3> buffer;

    EXPECT_TRUE(buffer.is_empty());
    EXPECT_EQ(buffer.count(), 0);
    EXPECT_EQ(buffer.size(), 3);

    EXPECT_TRUE(buffer.is_empty());
    EXPECT_EQ(buffer.count(), 0);
    EXPECT_EQ(buffer.size(), 3);

    buffer.push(obj_1);
    buffer.push(obj_2);
    buffer.push(obj_3);
    EXPECT_ANY_THROW(buffer.push(SimpleClass(444)));
    EXPECT_EQ(buffer.size(), 3);
    EXPECT_EQ(buffer.count(), 3);
    EXPECT_EQ(buffer.pop().Get(), 111);
    EXPECT_EQ(buffer.pop().Get(), 222);
    EXPECT_EQ(buffer.pop().Get(), 333);
    EXPECT_ANY_THROW(buffer.pop());
    EXPECT_EQ(buffer.count(), 0);
    buffer.push(obj_1);
    buffer.push(obj_2);
    buffer.push(obj_3);
    buffer.clear();
    EXPECT_EQ(buffer.count(), 0);
    EXPECT_EQ(buffer.size(), 3);
}
//=============second_task/cyclic_buffer_array.hpp===========
TEST(TestCyclicBufferArray, HandlesIntItems)
{
    tasks::array_impl::cyclic_buffer<int, 5> buffer;
    EXPECT_TRUE(buffer.is_empty());
    EXPECT_EQ(buffer.count(), 0);
    EXPECT_EQ(buffer.size(), 5);

    buffer.push(1);
    buffer.push(2);
    buffer.push(3);
    buffer.push(4);
    buffer.push(5);
    EXPECT_ANY_THROW(buffer.push(99));
    EXPECT_EQ(buffer.size(), 5);
    EXPECT_EQ(buffer.count(), 5);
    EXPECT_EQ(buffer.pop(), 1);
    EXPECT_EQ(buffer.pop(), 2);
    EXPECT_EQ(buffer.pop(), 3);
    buffer.pop();
    buffer.pop();
    EXPECT_ANY_THROW(buffer.pop());
    buffer.push(1);
    buffer.push(2);
    buffer.pop();
    buffer.push(3);
    buffer.pop();
    buffer.push(4);
    buffer.push(5);
    EXPECT_EQ(buffer.count(), 3);
    buffer.clear();
    EXPECT_EQ(buffer.count(), 0);
    EXPECT_EQ(buffer.size(), 5);
}
TEST(TestCyclicBufferArray, HandlesClassItems)
{
    SimpleClass obj_1(111);
    SimpleClass obj_2(222);
    SimpleClass obj_3(333);

    tasks::array_impl::cyclic_buffer<SimpleClass, 3> buffer;

    EXPECT_TRUE(buffer.is_empty());
    EXPECT_EQ(buffer.count(), 0);
    EXPECT_EQ(buffer.size(), 3);

    EXPECT_TRUE(buffer.is_empty());
    EXPECT_EQ(buffer.count(), 0);
    EXPECT_EQ(buffer.size(), 3);

    buffer.push(obj_1);
    buffer.push(obj_2);
    buffer.push(obj_3);
    EXPECT_ANY_THROW(buffer.push(SimpleClass(444)));
    EXPECT_EQ(buffer.size(), 3);
    EXPECT_EQ(buffer.count(), 3);
    EXPECT_EQ(buffer.pop().Get(), 111);
    EXPECT_EQ(buffer.pop().Get(), 222);
    EXPECT_EQ(buffer.pop().Get(), 333);
    EXPECT_ANY_THROW(buffer.pop());
    EXPECT_EQ(buffer.count(), 0);
    buffer.push(obj_1);
    buffer.push(obj_2);
    buffer.push(obj_3);
    buffer.clear();
    EXPECT_EQ(buffer.count(), 0);
    EXPECT_EQ(buffer.size(), 3);
}
//================third_task/merge_sort.hpp===================
TEST(TestMergeSort, GeneralTest)
{
    auto arr = new int[100];
    for(int i = 0; i < 100; ++i) 
    {
        arr[i] = 99 - i;
    }
    tasks::merge_sort(arr, 0, 99);
    for(int i = 0; i < 100; ++i)
    {
        EXPECT_EQ(arr[i], i);
    }
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}