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
    class FileLogger: public ILogger {
        public:
            FileLogger(string logName, LogLevel maxLogLevel, string filename, uint32_t bufferSize, uint32_t maxFileSizeInMiB, bool flushBufferAfterWrite, bool createFile = false); //!< object constructor
            virtual ~FileLogger(); //!< virtual destructor

        private:
            string _filename;
            uint8_t _numLogs = 0;
            uint32_t _maxFileSize; //!< max size of log file in MB

            bool fileExists(string filename);
            int fileSize(string filename);
            virtual void flushBuffer(); //!< Flushes the underlying buffer.
            const uint32_t maxFileSizeInMiB() const { return _maxFileSize; } //!< getter for _maxFileSize
            void maxFileSize(const uint32_t maxFileSize) { _maxFileSize = maxFileSize; } //!< setter for _maxFileSize
    };

}

#endif // !FILE_LOGGER_HPP
