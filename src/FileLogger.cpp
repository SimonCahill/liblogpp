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

  /***************************
   *	    System Includes    *
   ***************************/
#include <iostream>
#include <ostream>
#include <sys/stat.h>

namespace logpp {

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
    FileLogger::FileLogger (string logName, LogLevel maxLogLevel, string filename, uint32_t bufferSize, bool flushBufferAfterWrite) :
        ILogger(logName, maxLogLevel, bufferSize, flushBufferAfterWrite){
        
        if (fileExists (filename)) {
            _filename = filename;
        } else {
            throw std::exception::exception ("File does not exist");
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
    int FileLogger::fileSize (string filename) {
        struct stat buffer;
        stat (filename.c_str (), &buffer);
        return buffer.st_size;
    }

    /**
     * @brief writes buffer into given file. If file is greater than 100 bytes in size a new file with incremented endnumber will be created
     *
     */
    void FileLogger::flushBuffer () {
        if (fileSize (_filename) > 100) {
            if (_numLogs > 0) {
                // delete last character
                _filename.pop_back ();

            }
            // add/increment number at the end of _filename
            _filename.append (to_string (_numLogs++));
        }
        FILE *file = fopen (_filename.c_str (), "a");
        if (file) {
            fputs (getLogBuffer ().str ().c_str (), file);
            fclose (file);
            getLogBuffer ().clear ();
        }
    }
}