#pragma once

#include <iostream>

#define TEST_FUNC(_funcName) bool _funcName()
#define RUN_TEST_FUNC(_funcName) std::cout << (_funcName() ? "   OK" : "ERROR") << " -- " << #_funcName << std::endl;

#define BEGIN_TEST_GROUP(_groupName) std::cout << #_groupName << " Tests"  << std::endl;
#define END_TEST_GROUP() std::cout << std::endl;

