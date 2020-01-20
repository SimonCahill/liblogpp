/**
 * ConsoleLogger.hpp
 *
 * log++ - Intuitive logging library for C++ written by Simon Cahill.
 * Co-author: Pascal L�ttmann
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
#include <iostream>
#include <ostream>
#include <sys/stat.h>

namespace logpp {

	using std::invalid_argument;
    using std::iostream;
    using std::ostream;
    using std::to_string;


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
    ILogger(logName, maxLogLevel, bufferSize, flushBufferAfterWrite) {
        _filename = filename;
        if (fileExists(filename)) {
            FileLogger::maxFileSize(maxFileSize);
        } else if (createFileIfNotExists) {
			// Create file if required.
            createFile(filename);
		} else {
            throw invalid_argument(formatString("File %s doesn't exist!", filename.c_str()));
            // create file
        }
    }

    /**
     * @brief Destroy the fileLogger::fileLogger object
     */
    FileLogger::~FileLogger () {}


    /**
     * @brief checks if file exists
     *
     * @param filename name of requested file
     *
     * @return true if file exists, false else
     */
    bool FileLogger::fileExists (string filename) {
        struct stat buffer;
        return (stat (filename.c_str (), &buffer) == 0);
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
        stat (filename.c_str (), &buffer);
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
        using std::endl;
        getLogBuffer() << msg << endl; // Add message to buffer

        // Now check if we need to flush
        if (isBadLog(level) || (getMaxBufferSize() == 0 || getBufferSize() >= getMaxBufferSize()) || flushBufferAfterWrite()) {
            flushBuffer();
        }
    }

    /**
     * @brief writes buffer into given file. If file is greater than _maxFileSize (in MiB) in size a new file with incremented endnumber will be created
     *
     */
    void FileLogger::flushBuffer () {
        if (fileSize(_filename) > _maxFileSize * 1'048'576u) {
            if (_numLogs > 0) {
                // delete last character
                _filename.pop_back();
            }
            // add/increment number at the end of _filename
            _filename.append(to_string(_numLogs++));
        }
        FILE* file = fopen(_filename.c_str(), "a");

        if (file) {
            fputs(getLogBufferAsString().c_str(), file);
            fclose(file);
            clearStringStream(getLogBuffer());
        }
    }
}
