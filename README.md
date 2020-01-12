# liblog++ - An intuitive, object-oriented logging library for C++.

# Introduction

Welcome to log++.
Log++ is my attempt at creating an intuitive logging library for C++ applications without any other major dependencies,
relying on object-oriented programming practices and paradigms.
This means including base loggers, anc extensible interfaces.

Log++ is built with knowledge gathered from different programming languages and experiences, in an attempt to 
combine "traditional" C++ programming with practices from other, modern languages.
This includes full-on encapsulation, namespaces and everything else that scares most C++ programmers I know of.

# Using log++

While building log++, I'm always attempting to make it as easy as possible to use, with as many types of projects as possible. 
This also means providing both static and dynamic libraries, along with the possibility of using the source code directly w/ CMake projects.

## Building the project

log++ includes both a CMake file and a Makefile for easy building.
Building log++ is not yet supported and will require additional work from your part.
I hope to include Windows build capabilities ASAP.

## Building with Make

Building the project with make requires only the Make build tools and the compiler you require.

### Cross compilation

If you wish to cross compile log++, you will need to specify the CROSS variable, either when executing Make or as an environment variable.
This CROSS variable should follow the example `<arch>-linux-<abi>-`.

### Calling make

There are no configure scripts required for this project, as such building the library is as simple as calling the Makefile, 
optionally specifiying which type of library to build: static or shared.
You may optionally build both types of libraries, by calling make with the `all` target.

Possible targets:
    - clean (cleans the project)
    - all (build both shared and static libraries)
    - shared (builds the shared library object)
    - static (builds the static library object)

```bash
    $ make [CROSS=<compilation-target>] <target>
```

## Building w/ CMake

If you only wish to build the project with CMake, then executing the following commands in a Bash shell will build either the shared or static libraries.

```bash
    $ mkdir build; cd build;
    $ cmake [-DBUILD_STATIC=OFF] .. && make all [-j<thread_count>] # Turning off BUILD_STATIC will build the dynamic library
```

### Cross compiling w/ CMake

If you require log++ on a platform which requires cross-compilation, I have provided some toolchain files for CMake, which make this process easier.
You are more than welcome to provide custom toolchain files as you see fit.

Building log++ with a toolchain file is very similar to simply building with CMake.
Follow the steps above, but add the following argument when calling CMake.

```bash
    $ cmake [-DBUILD_STATIC=OFF] <-DCMAKE_TOOLCHAIN_FILE=./toolchains/<toolchain>.cmake> .. && make all [-j<thread_count>]
```

## Using log++ in your project

### Custom logger implementation
Depending on your exact use-case, you may wish to create your own logger object.
In this case, all you'll have to do in your project, is expand this example code in your own code files:

```cpp
    #include <ILogger.hpp>

    class MyCustomLogger: public ILogger {
        public:

            MyCustomLogger(logName loggerName, LogLevel maxLevel/*, custom params?*/): ILogger(logName, maxLevel) {}

            //////////////////////////////////////////
            //      OVERRIDE ABSTRACT METHODS       //
            //    Implement these as you see fit.   //
            //////////////////////////////////////////
            virtual void logMessage(LogLevel level, string msg); // Optional override; will always write to underlying buffer

            virtual void flushBuffer(); // Mandatory override; flushBuffer is pure virtual.
    };
```

### Using the provided logger implementations

In most cases, the provided loggers should fullfil your needs and are expandable, if they are not.
This means all you'll have to do, is implement the following code.

```cpp
    #include <log.hpp>

    int main(int32_t argC, char* argV[]) {
        using logpp::ConsoleLogger;
        using logpp::formatString;

        // Creating a new ConsoleLogger.
        // Pointers are not required!
        auto consoleLogger = new ConsoleLogger(
            "myCustomLogger", /* give it a name */
            LogLevel::Trace, /* show all the logs! */
            true, /* redirect "bad" logs to stderr */
            4096u, /* buffer 4096B before flushing */
            false, /* don't flush buffer after each log. This is overridden by setting buffer size to 0u! */
            // The next parameters are OPTIONAL
            true, /* log to separate file */
            "/var/log/my_cool_app/.log", /* full path to log file */
            128 /* max log file size in MiB! (size * 1'048'576u) */
        );

        consoleLogger->debug("Setting up logger...");
        // Now let's set some funky things
        consoleLogger->setCurrentApplicationName("My Cool App");
        consoleLogger->setCurrentCustomFlare("{{TEST OUTPUT}}");
        consoleLogger->setCurrentLoggerFormat(formatString(
            "[%s] [%s] [%s] %s",
            ConsoleLogger::LOG_FMT_CUSTOM.c_str(), // add your custom flare
            ConsoleLogger::LOG_FMT_DATETIME, // add the current date and time
            ConsoleLogger::LOG_FMT_LOGLVL, // add the log level
            ConsoleLogger::LOG_FMT_MSG // add the actual log message
        ));

        // Now your changes have been made
        consoleLogger->info("Ready!");

        using logpp::LOGLEVEL_MAXVALUE;
        using logpp::LOGLEVEL_MINVALUE;
        for (int i = (int)LOGLEVEL_MINVALUE; i != (int)LOGLEVEL_MAXVALUE; i++) {
            // We're bypassing the shortcut methods, meaning we have to format the messages ourselves
            // virtual string formatLogMessage(string& msg, LogLevel lvl, string func = "", int32_t line = -1, exception* except = nullptr)
            auto msg = formatString("We're looping through all the log levels. Right now, we're at %s!", toString((LogLevel)i).c_str());
            consoleLogger->logMessage((LogLevel)i, 
                consoleLogger->formatLogMessage(
                    msg,
                    (LogLevel)i
                )
            );
        }

        delete consoleLogger;
        return 0;
    }
```
