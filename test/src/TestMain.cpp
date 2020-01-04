#include <log.hpp>

int main(int32_t argC, char* argV[]) {
    using logpp::ConsoleLogger;
    using logpp::LogLevel;

    auto logger = ConsoleLogger("TestLogger", LogLevel::Trace, true, 4096, true);
}