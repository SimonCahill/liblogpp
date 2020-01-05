#include <log.hpp>

int main(int32_t argC, char* argV[]) {
    using logpp::ConsoleLogger;
    using logpp::LogLevel;

    ConsoleLogger logger("TestLogger", LogLevel::Trace, true, 4096u, true);
}