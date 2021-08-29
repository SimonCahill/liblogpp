#include <log.hpp>


using logpp::ConsoleLogger;
using logpp::FileLogger;
using logpp::LogLevel;

using std::cout;
using std::endl;

void showConsoleLogger();
void showFileLogger();
// void showStreamLogger(); // not yet available

int main(int32_t argC, char* argV[]) {

    showConsoleLogger();
    cout << endl << endl;
    showFileLogger();

    return 0;
}

void showConsoleLogger() {
    ConsoleLogger logger("TestLogger", LogLevel::Trace, true, 4096u, true);

    logger.info("This is an informational message with the default configuration");
    logger.error("This is an error message");
    logger.debug("This is a debug message.");
    logger.trace("This is a trace message");
    logger.fatal("This is a fatal message.");
    logger.warning("This is a warning.");
    logger.ok("This message is just fine :)");

    logger.info("You can set the name of your application, like logpp_test.");
    logger.setCurrentApplicationName("logpp_test");
    logger.info("logpp also allows you to change the format of the log output.");
    logger.setCurrentLoggerFormat(R"([[ ${datetime} ]] [${appname}] ${llevel} ${lmsg})");
    logger.info("This means your log output can be however you like.");
    logger.info("You can even format messages using C-like string formatting!");
    logger.infoFmt("%s is a formatted message with a %%s and a %%d: %d", "This", 1337);
}

void showFileLogger() {
    ConsoleLogger logger("TestCFLogger", LogLevel::Trace, true, 0, true, true, ".", 12);

    logger.info("This is a ConsoleLogger using an internal FileLogger too!");
    logger.infoFmt("Logs are currently being written to %s.log!", logger.getCurrentLoggerName().c_str());
    logger.ok("FYI: FileLoggers can be used on their own, just use the FileLogger class instead of the ConsoleLogger class!");


    logger.flushBuffer();
}
