#pragma once
#include "CSVEventsList.h"

class Tests {

public:
    static void test_genericSort();
    static void test_domain();
    static void test_repository();
    static void test_user_repository();
    static void test_service();
    static void test_validation();
public:
    static void run_all_tests();
};