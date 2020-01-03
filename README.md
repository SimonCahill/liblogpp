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
    $ cmake [-DBUILD_STATIC=OFF] .. && make all -j4 # Turning off BUILD_STATIC will build the dynamic library
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
            virtual void logMessage(LogLevel level, logMessage msg, lineNo line = -1, funcName function = "");

            virtual void debug(logMessage msg, exception* except = nullptr, lineNo line = -1, funcName func = "");
            virtual void error(logMessage msg, exception* except = nullptr, lineNo line = -1, funcName func = "");
            virtual void fatal(logMessage msg, exception* except = nullptr, lineNo line = -1, funcName func = "");
            virtual void info(logMessage msg, exception* except = nullptr, lineNo line = -1, funcName func = "");
            virtual void ok(logMessage msg, exception* except = nullptr, lineNo line = -1, funcName func = "");
            virtual void trace(logMessage msg, exception* except = nullptr, lineNo line = -1, funcName func = "");
            virtual void warning(logMessage msg, exception* except = nullptr, lineNo line = -1, funcName func = "");

    };
```

### Using the provided logger implementations

In most cases, the provided loggers should fullfil your needs and are expandable, if they are not.
This means all you'll have to do, is implement the following code.

```cpp
    #include <log.hpp>

    int main(int32_t argC, char* argV[]) {
        auto fileLogger = LogFactory::buildFileLogger(/* max logging level */LogLevel::Trace, 
                                                      /* filename */"my.log", 
                                                      /* buffer size */4096/*B*/,
                                                      /* flush after write */false);
        auto consoleLogger = LogFactory::buildConsoleLogger(/* max logging level */LogLevel::Trace,
                                                            /* output bad logs to stderr */true,
                                                            /* buffer size */4096,
                                                            /* flush after write */false);
        auto streamLogger = LogFactory::buildStreamLogger(/* max logging level */LogLevel::Trace,
                                                          /* output stream */myStream,
                                                          /* buffer size */4096,
                                                          /* flush after write */false);
    }
```
