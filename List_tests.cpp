#include "List.hpp"
#include "unit_test_framework.hpp"

using namespace std;

// Add your test cases here


TEST(test_default_constructor) {
    List<int> l;
    ASSERT_TRUE(l.empty());
    ASSERT_EQUAL(l.size(), 0); 
}

TEST(test_front_and_back_and_size) {
    List<int> l;
    for (int i = 1; i < 4; ++i) {
        l.push_back(i);
    }
    ASSERT_EQUAL(l.size(), 3);
    ASSERT_EQUAL(l.front(), 1);
    ASSERT_EQUAL(l.back(), 3);
}

TEST(test_push_front) {
    List<int> l;
    l.push_front(1);
    ASSERT_EQUAL(l.size(), 1);
    ASSERT_EQUAL(l.front(), 1);
    l.push_front(2);
    ASSERT_EQUAL(l.size(), 2);
    ASSERT_EQUAL(l.front(), 2);
    ASSERT_EQUAL(l.back(), 1);
}

TEST(test_push_back) {
    List<int> l;
    l.push_back(1);
    ASSERT_EQUAL(l.size(), 1);
    ASSERT_EQUAL(l.back(), 1);
    l.push_back(2);
    ASSERT_EQUAL(l.size(), 2);
    ASSERT_EQUAL(l.back(), 2);
    ASSERT_EQUAL(l.front(), 1);
}

TEST(test_pop_front) {
    List<int> l;
    l.push_back(1);
    l.push_back(2);
    l.push_back(3);
    l.pop_front();
    ASSERT_EQUAL(l.front(), 2);
    ASSERT_EQUAL(l.back(), 3);
    ASSERT_EQUAL(l.size(), 2);
    l.pop_front();
    l.pop_front();
    ASSERT_TRUE(l.empty());
}

TEST(test_pop_back) {
    List<int> l;
    l.push_back(1);
    l.push_back(2);
    l.push_back(3);
    l.pop_back();
    ASSERT_EQUAL(l.front(), 1);
    ASSERT_EQUAL(l.back(), 2);
    ASSERT_EQUAL(l.size(), 2);
    l.pop_back();
    l.pop_back();
    ASSERT_TRUE(l.empty());
}

TEST(test_clear) {
    List<int> l;
    for (int i = 1; i < 4; ++i) {
        l.push_back(i);
    }
    ASSERT_FALSE(l.empty());
    l.clear();
    ASSERT_TRUE(l.empty());
}

TEST(test_iterator_begin_and_end) {
    List<int> l;
    ASSERT_TRUE(l.begin() == l.end());
    for (int i = 1; i < 4; ++i) {
        l.push_back(i);
    }
    ASSERT_EQUAL(*l.begin(), 1);
    ASSERT_TRUE(l.begin() != l.end());
    auto it = l.begin();
    ++it;
    ++it;
    ASSERT_TRUE(it == l.end());
}

TEST(test_iterator_increment_decrement) {
    List<int> l;
    for (int i = 1; i < 4; ++i) {
        l.push_back(i);
    }
    auto it = l.begin();
    ++it;
    ASSERT_EQUAL(*it, 2);
    ASSERT_EQUAL(*it++, 2);
    ASSERT_EQUAL(*it, 3);
    --it;
    ASSERT_EQUAL(*it, 2);
    ASSERT_EQUAL(*it--, 2);
    ASSERT_EQUAL(*it, 1);
}


TEST(test_erase) {
    List<int> l;
    for (int i = 1; i < 5; ++i) {
        l.push_back(i);
    }
    auto it = l.begin();
    it = l.erase(it);
    ASSERT_TRUE(it == l.begin());
    ASSERT_EQUAL(*it, 2);
    ++it;
    it = l.erase(it);
    ASSERT_EQUAL(l.size(), 2);
    ASSERT_EQUAL(*it, 4);
    it = l.erase(it);
    ASSERT_EQUAL(l.size(), 1);
    ASSERT_TRUE(it == l.end());
    --it;
    it = l.erase(it);
    ASSERT_TRUE(l.empty());
    ASSERT_TRUE(it == l.end());
}

TEST(test_insert) {
    
}

TEST_MAIN()
