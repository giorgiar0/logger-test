#include <iostream>
#include <stdexcept>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>


class AppLogger {
public:
    AppLogger() {
        logger = spdlog::stdout_color_mt("console");
        spdlog::set_level(spdlog::level::debug);
    }

    void logDebug(const std::string& message) {
        logger->debug(message);
    }

    void logInfo(const std::string& message) {
        logger->info(message);
    }

    void logWarn(const std::string& message) {
        logger->warn(message);
    }

    void logError(const std::string& message) {
        logger->error(message);
    }

    void logFatal(const std::string& message) {
        logger->critical(message);
    }

    void run() {
        try {
            logInfo("Application starting");
            logDebug("Calling function: run()");

            logInfo("Initialization complete.");
            logDebug("Debugging details about internal state...");

            logWarn("This is a warning level log.");
            logError("An error has occurred.");
            logFatal("Critical failure detected!");

            std::string emptyMsg;
            if (emptyMsg.empty()) {
                throw std::invalid_argument("Message cannot be empty");
            }

        } catch (const std::exception& ex) {
            logError(std::string("Exception caught: ") + ex.what());
        }
    }

private:
    std::shared_ptr<spdlog::logger> logger;
};

int main() {
    AppLogger logger;
    logger.run();
}
