/**
 * ConsoleLogger.hpp
 *
 * log++ - Intuitive logging library for C++ written by Simon Cahill.
 * Co-author: Pascal Lüttmann
 */

#ifndef FILE_LOGGER_HPP
#define FILE_LOGGER_HPP

#include "ILogger.hpp"

namespace logpp {

    /**
     * @brief A basic file logger for your logging pleasure.
     *
     * This object logs file contents to the standard outputs.
     * Unlike console logger no different configurations may be used to modify the behaviour of the logger, such as outputting bad logs to the standard error.
     */
    class FileLogger : public ILogger {
        public:
            FileLogger(string logName, LogLevel maxLogLevel, string filename, uint32_t bufferSize, bool flushBufferAfterWrite); //!< object constructor
            virtual ~FileLogger(); //!< virtual destructor

        private:
            string _filename;
            uint8_t _numLogs = 0;

            bool fileExists (string filename);
            int fileSize (string filename);
            virtual void flushBuffer (); ///!< Flushes the underlying buffer.
    };

}

#endif // !FILE_LOGGER_HPP
