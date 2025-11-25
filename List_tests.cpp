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
    List<int> l;
    auto it = l.begin();
    it = l.insert(it, 1);
    ASSERT_EQUAL(*it, 1);
    it = l.insert(it, 2);
    ASSERT_EQUAL(*it, 2)
    ASSERT_TRUE(l.begin() == it);
    ++it;
    ASSERT_EQUAL(*it, 1);
    it = l.end();
    l.insert(it, 3);
    ASSERT_TRUE(it == l.end());
    --it;
    ASSERT_EQUAL(*it, 3);
}

TEST(test_copy_constructor) {
    List<int> l1;
    for (int i = 1; i < 4; ++i) {
        l1.push_back(i);
    }
    List<int>l2(l1);

    ASSERT_EQUAL(l1.size(), l2.size());

    auto it1 = l1.begin();
    auto it2 = l2.begin();

    for (; it1 != l1.end(); ++it1, ++it2) {
        ASSERT_EQUAL(*it1, *it2);
    }

    --it1;
    --it2;

    *it1 = 4;

    ASSERT_EQUAL(*it1, 4);
    ASSERT_EQUAL(*it2, 3);
}

TEST (test_assignment_operator) {
    List<int> l1;
    for (int i = 1; i < 4; ++i) {
        l1.push_back(i);
    }
    List<int>l2;
    l2.push_back(2);
    l2 = l1;

    ASSERT_EQUAL(l1.size(), l2.size());

    auto it1 = l1.begin();
    auto it2 = l2.begin();

    for (; it1 != l1.end(); ++it1, ++it2) {
        ASSERT_EQUAL(*it1, *it2);
    }

    --it1;
    --it2;

    *it1 = 4;

    ASSERT_EQUAL(*it1, 4);
    ASSERT_EQUAL(*it2, 3);
}

TEST (test_self_assignment) {
    List<int> l1;
    for (int i = 1; i < 4; ++i) {
        l1.push_back(i);
    }
    List<int>& l2 = l1;
    l2 = l1;

    ASSERT_EQUAL(l1.size(), l2.size());
    ASSERT_TRUE(l1.begin() == l2.begin());
    ASSERT_TRUE(l1.end() == l2.end());

}

TEST (test_empty_assignment) {
    List<int> l1;
    List<int> l2;
    for (int i = 1; i < 4; ++i) {
        l1.push_back(i);
    }
    l1 = l2;

    ASSERT_TRUE(l1.empty());
    l1.push_back(1);
    ASSERT_TRUE(l2.empty());

    List<int> l3;
    List<int> l4;
    for (int i = 1; i < 4; ++i) {
        l3.push_back(i);
    }
    l4 = l3;
    
    auto it1 = l3.begin();
    auto it2 = l4.begin();

    for (; it1 != l3.end(); ++it1, ++it2) {
        ASSERT_EQUAL(*it1, *it2);
    }

    --it1;
    --it2;

    *it1 = 4;

    ASSERT_EQUAL(*it1, 4);
    ASSERT_EQUAL(*it2, 3);
}

TEST (test_smaller_to_larger) {
    List<int> l1;
    for (int i = 1; i < 4; ++i) {
        l1.push_back(i);
    }
    List<int> l2;
    l2.push_back(1);
    l1 = l2;

    ASSERT_EQUAL(l1.size(), l2.size());

    auto it1 = l1.begin();
    auto it2 = l2.begin();

    for (; it1 != l1.end(); ++it1, ++it2) {
        ASSERT_EQUAL(*it1, *it2);
    }

    --it1;
    --it2;

    *it1 = 4;

    ASSERT_EQUAL(*it1, 4);
    ASSERT_EQUAL(*it2, 1);
}

TEST_MAIN()
