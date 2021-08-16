/**
 * ConsoleLogger.hpp
 *
 * log++ - Intuitive logging library for C++ written by Simon Cahill.
 * Co-author: Pascal Lüttmann
 */

/****************************
 *	    Local Includes	    *
 ****************************/
#include "FileLogger.hpp"
#include "LogExtensions.hpp"

/***************************
 *	    System Includes    *
 ***************************/
#include <exception>
#include <fstream>
#include <sys/stat.h>

namespace logpp {

    using std::endl;
	using std::invalid_argument;
    using std::ofstream;
    using std::to_string;

    const static uint64_t ONE_MIB = 1'048'576u;
    const uint32_t FileLogger::DEFAULT_MAX_LOG_FILES = 4;

    /**
    * @brief Construct a new fileLogger::fileLogger object
    *
    * @param logName The name for this logger.
    * @param maxLogLevel The maximum logging level to log.
    * @param filename The path/to/file for printing inside
    * @param bufferSize The maximum buffer size before flushing.
    * @param flushBufferAfterWrite Indicates whether to flush the buffer after each write to it.
    */
    FileLogger::FileLogger(string logName, LogLevel maxLogLevel, string filename, uint32_t bufferSize, uint32_t maxFileSize,
                           bool flushBufferAfterWrite, bool createFileIfNotExists):
    ILogger(logName, maxLogLevel, bufferSize, flushBufferAfterWrite), _maxFileCount(DEFAULT_MAX_LOG_FILES), _maxFileSize(maxFileSize) {
        _filename = filename;
        if (createFileIfNotExists && !fileExists(filename))
            createFile(filename);
    }

    /**
     * @brief Destroy the fileLogger::fileLogger object
     */
    FileLogger::~FileLogger() {}

    /**
     * @brief checks if file exists
     *
     * @param filename name of requested file
     *
     * @return true if file exists, false else 
     */
    bool FileLogger::fileExists(string filename) {
        struct stat buffer;
        return (stat(filename.c_str (), &buffer) == 0);
    }

    /**
     * @brief returns size of file in bytes
     *
     * @param filename is the name of requested file
     *
     * @return size of file in bytes
     */
    uint32_t FileLogger::fileSize(string filename) {
        struct stat buffer;
        stat(filename.c_str(), &buffer);
        return buffer.st_size;
    }
    
    /**
     * @brief Writes a message to the underlying log buffer and flushes the buffer accordingly.
     *
     * @remarks Bad log levels (log levels above four) will cause the buffer to always be flushed in this default implementation!
     *
     * @param level The level of the current log.
     * @param msg The (formatted) message to output.
     */
    void FileLogger::logMessage(LogLevel level, string msg) {
        if (level > getCurrentMaxLogLevel()) return;

        getLogBuffer() << msg << endl; // Add message to buffer

        // Now check if we need to flush
        if (isBadLog(level) || (getMaxBufferSize() == 0 || getBufferSize() >= getMaxBufferSize()) || flushBufferAfterWrite()) {
            flushBuffer();
        }
    }

    /**
     * @brief writes buffer into given file. If file is greater than _maxFileSize (in MiB) in size a new file with incremented end number will be created.
     */
    void FileLogger::flushBuffer() {
        if (fileSize(formatString("%s%d", _filename, _numLogs)) >= _maxFileSize * ONE_MIB) {
            _numLogs = (_numLogs > _maxFileCount ? 0 : _numLogs + 1);
        }

        ofstream outStream(formatString("%s%d", _filename, _numLogs));
        outStream << getLogBufferAsString() << endl;

        clearStringStream(getLogBuffer());
    }
}
