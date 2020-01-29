/**
 * @file LeakDetection.hpp
 * @author Simon Cahill (simon@h3lix.de)
 * @brief Contains a simple override for new and delete, which can be used to detect and debug memory leaks.
 * @version 0.1
 * @date 2020-01-29
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef LOGPP_LEAKDETECTION_HPP
#define LOGPP_LEAKDETECTION_HPP

#include "ConsoleLogger.hpp"

#include <string>

using std::string;
namespace logpp { namespace memory {


    /**
     * @brief Very simple class which outputs memory allocations/deallocations to console.
     */
    class LeakLogger {
        public:
            static LeakLogger& getInstance() {
                return  (_instance == nullptr) ?
                       *(_instance = new LeakLogger()) :
                       * _instance;
            }

            ~LeakLogger() {
                delete _instance;
                delete _consoleLogger;
            }

        public: // +++ Logging +++
            void allocatedMemory(const size_t bytes, const string file, const int32_t line) {
                _consoleLogger->trace(formatString("Allocated memory (%d Bytes) in %s:%d!", bytes, getBaseName(file).c_str(), line));
            }

            void deallocatedMemory(const string file, const int32_t line) {
                _consoleLogger->trace(formatString("Deallocated memory in %s:%d!", getBaseName(file).c_str(), line));
            }

        private:
            LeakLogger(): _consoleLogger(new ConsoleLogger("Memory Allocation", LOGLEVEL_MAXVALUE, true, 0, true)) { }

        private:
            ConsoleLogger* _consoleLogger = nullptr;

            static LeakLogger* _instance;
    };

} /* memory */ } /* logpp */

void* operator new(const size_t, const string, const int32_t);
void* operator new[](const size_t, const string, const int32_t);
void operator delete(void*, const string, const int32_t);
void operator delete[](void*, const string, const int32_t);
#define DEBUG_NEW new(__FILE__, __LINE__)
//#define new DEBUG_NEW
#define DEBUG_DELETE delete(__FILE__, __LINE__)
#endif // LOGPP_LEAKDETECTION_HPP