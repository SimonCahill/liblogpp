/**
 * ConsoleLogger.hpp
 *
 * log++ - Intuitive logging library for C++ written by Simon Cahill.
 * Co-author: Pascal L�ttmann
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
        public: // +++ Public Static +++
            static const string     LOGPP_CTRL_DIR; //!< .logpp/
            static const uint32_t   CTRL_FILE_MAGIC; //!< Magic number for control files
            static const uint32_t   DEFAULT_MAX_LOG_FILES;

        public:
            FileLogger(const string& logName, const LogLevel maxLogLevel, const string& filename, const uint32_t bufferSize, 
                       const uint32_t maxFileSizeInMiB, const bool flushBufferAfterWrite, const bool createFile = false); ///!< object constructor
            virtual ~FileLogger(); ///!< virtual destructor

            virtual void logMessage(const LogLevel level, const string& msg) override;

            virtual FileLogger& setMaxFileCount(const uint32_t maxFileCount = DEFAULT_MAX_LOG_FILES) { _maxFileCount = maxFileCount; return *this; }

        protected:
            string getControlFilePath() const; //!< Gets the path to the control file for this logger
            void initLogContinuation(); //!< Initialises the log continuation logic
            void storeLatestLogFile(); //!< Stores the latest written log file to a control file in (...)/.logpp/<loggername>

        private:
            string _filename;
            uint32_t _numLogs = 0;
            uint32_t _maxFileSize; ///!< max size of log file in MB
            uint32_t _maxFileCount; ///!< The maximum amount of files logpp is allowed to create before overwriting the files in a loop

            bool fileExists(const string& filename);
            uint32_t fileSize(const string& filename);
            virtual void flushBuffer() override; ///!< Flushes the underlying buffer.
            uint32_t maxFileSizeInMiB() const { return _maxFileSize; } ///!< getter for _maxFileSize
            void maxFileSize(const uint32_t maxFileSize) { _maxFileSize = maxFileSize; } ///!< setter for _maxFileSize
    };

    /**
     * @brief Simple struct containing the internal structure of the control file
     */
    struct ControlFileContents {
        uint32_t magicNumber;
        uint32_t currentWrittenLogFile;
    } __packed__;

}

#endif // FILE_LOGGER_HPP
