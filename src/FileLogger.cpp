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
#include <cstring>
#include <exception>
#include <fstream>

#ifndef logpp_USE_FSTAT
    #if __cplusplus < 201703L
        #include <experimental/filesystem>
    #else
        #include <filesystem>
    #endif
#else
    #include <sys/stat.h>
#endif

namespace logpp {

    using std::cout;
    using std::endl;
    using std::ifstream;
	using std::invalid_argument;
    using std::ios_base;
    using std::ofstream;
    using std::to_string;

    #ifndef logpp_USE_FSTAT
        #if __cplusplus < 201703L
            namespace fs = std::experimental::filesystem;
        #else
            namespace fs = std::filesystem;
        #endif
    #endif

    const static uint64_t ONE_MIB = 1048576u;

    const string FileLogger::LOGPP_CTRL_DIR = ".logpp";
    const uint32_t FileLogger::CTRL_FILE_MAGIC = 0xf00d'beef;
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
    FileLogger::FileLogger(const string& logName, const LogLevel maxLogLevel, const string& filename, const uint32_t bufferSize,
                           const uint32_t maxFileSize, const bool flushBufferAfterWrite, const bool createFileIfNotExists
                          ): ILogger(logName, maxLogLevel, bufferSize, flushBufferAfterWrite),
                          _maxFileCount(DEFAULT_MAX_LOG_FILES), _maxFileSize(maxFileSize),
                          _filename(filename) {
        initLogContinuation();
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
    bool FileLogger::fileExists(const string& filename) {
        #ifdef logpp_USE_FSTAT
        struct stat buffer;
        return (stat(filename.c_str (), &buffer) == 0);
        #else
        return fs::exists(filename);
        #endif
    }

    /**
     * @brief Gets the path to the control file for the current logger.
     * 
     * @return string The path to the control file.
     */
    string FileLogger::getControlFilePath() const {
        return formatString(
            "%s/%s/%s.lcf",
            logpp::getBaseName(_filename).c_str(),
            FileLogger::LOGPP_CTRL_DIR.c_str(),
            getCurrentLoggerName().c_str()
        );
    }

    /**
     * @brief returns size of file in bytes
     *
     * @param filename is the name of requested file
     *
     * @return size of file in bytes
     */
    uint32_t FileLogger::fileSize(const string& filename) {
        #ifdef logpp_USE_FSTAT
        struct stat buffer;
        stat(filename.c_str(), &buffer);
        return buffer.st_size;
        #else
        return static_cast<uint32_t>(fs::file_size(filename));
        #endif
    }
    
    /**
     * @brief Writes a message to the underlying log buffer and flushes the buffer accordingly.
     *
     * @remarks Bad log levels (log levels above four) will cause the buffer to always be flushed in this default implementation!
     *
     * @param level The level of the current log.
     * @param msg The (formatted) message to output.
     */
    void FileLogger::logMessage(const LogLevel level, const string& msg) {
        if (level > getCurrentMaxLogLevel()) return;

        getLogBuffer() << msg;
        if (msg.back() != '\n' || msg.back() != '\r') {
            // Add the missing line feed
            getLogBuffer() << getOsNewLineChar();
        }

        // Now check if we need to flush
        if (isBadLog(level) || (getMaxBufferSize() == 0 || getBufferSize() >= getMaxBufferSize()) || flushBufferAfterWrite()) {
            flushBuffer();
        }
    }

    /**
     * @brief writes buffer into given file. If file is greater than _maxFileSize (in MiB) in size a new file with incremented end number will be created.
     */
    void FileLogger::flushBuffer() {
        bool changedLogNo = false;
        if (fileSize(formatString("%s%d", _filename.c_str(), _numLogs)) >= _maxFileSize * ONE_MIB) {
            _numLogs = (_numLogs > _maxFileCount ? 0 : _numLogs + 1);
            changedLogNo = true;
            storeLatestLogFile();
        }

        ofstream outStream(formatString("%s%d", _filename.c_str(), _numLogs), (changedLogNo ? ios_base::trunc : ios_base::app));
        outStream << getLogBufferAsString() << endl;

        clearStringStream(getLogBuffer());
    }

    void FileLogger::initLogContinuation() {
        ifstream inStream(getControlFilePath());

        // uint8_t buffer[fileSize(getControlFilePath())] = { 0 };
        const auto ctrlFileSize = fileSize(getControlFilePath());
        uint8_t* buffer = new uint8_t[ctrlFileSize];
        memset(buffer, 0, ctrlFileSize);
        ControlFileContents contents = { 0 };

        inStream >> buffer;
        std::memcpy(&contents, buffer, sizeof(contents));

        delete[] buffer;

        if (contents.magicNumber == CTRL_FILE_MAGIC) {
            _numLogs = contents.currentWrittenLogFile;
        }
    }

    void FileLogger::storeLatestLogFile() {
        ofstream outStream(getControlFilePath(), ios_base::trunc);
        const ControlFileContents ctrlFile {
            CTRL_FILE_MAGIC,
            _numLogs
        };

        const char* fileContents = reinterpret_cast<const char*>(&ctrlFile);
        outStream.write(fileContents, sizeof(ctrlFile));
        outStream.flush();
    }
}
