/**
 * @file LeakDetection.cpp
 * @author Simon Cahill (simon@h3lix.de)
 * @brief Contains the implementation of the LeakDetection header.
 * @version 0.1
 * @date 2020-01-29
 * 
 * @copyright Copyright (c) 2020
 */

#include "memory_allocation/LeakDetection.hpp"

#include <cstdio>

namespace logpp { namespace memory {

    LeakLogger* LeakLogger::_instance = nullptr;

} /* memory */ } /* logpp */

void* operator new(const std::size_t size, const string file, const int32_t line) {
    logpp::memory::LeakLogger::getInstance().allocatedMemory(size, file, line);
    return operator new(size);
}

void* operator new[](const std::size_t size, const string file, const int32_t line) {
    logpp::memory::LeakLogger::getInstance().allocatedMemory(size, file, line);
    return operator new[](size);
}

void operator delete(void* mem, const string file, const int32_t line) {
    logpp::memory::LeakLogger::getInstance().deallocatedMemory(file, line);
    operator delete(mem);
}

void operator delete[](void* mem, const string file, const int32_t line) {
    logpp::memory::LeakLogger::getInstance().deallocatedMemory(file, line);
    operator delete(mem);
}
