#include <iostream>
#include <string>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <stdexcept>


/**
 * 
 * @enum LoggingLevel
 * @brief Enum representing different levels of logging severity.
 * 
 */

enum LoggingLevel {
    DEBUG = 0,  ///< Detailed debug information.
    INFO = 1,   ///< General information.
    WARN = 2,   ///< Warning messages.
    ERROR = 3,  ///< Error messages.
    FATAL = 4   ///< Critical errors that may lead to program termination.
};


/**
 * @class ConsoleLogger
 * @brief A simple logger that outputs messages to the console with timestamps and severity levels.
 */

class ConsoleLogger {
public:

    /**
     * @brief Prints a simple message to the console.
     * 
     * @param message The message to print. Must not be empty.
     * @throws std::invalid_argument if the message is empty.
     */

    void print(const std::string& message) const {
        if (message.empty()) {
            throw std::invalid_argument("Message cannot be empty.");
        }
        std::cout << message << std::endl;
    }

    /**
     * @brief Logs a message with a specified logging level.
     * 
     * @param type The logging level (DEBUG, INFO, WARN, ERROR, FATAL).
     * @param message The message to log. Must not be empty.
     * @throws std::invalid_argument if the message is empty.
     */

    void log(LoggingLevel type, const std::string& message) const {
        if (message.empty()) {
            throw std::invalid_argument("Log message cannot be empty.");
        }

        static const char* logLevelStr[] = {"DEBUG", "INFO", "WARN", "ERROR", "FATAL"};
        std::cout << "[" << getCurrentTimestamp() << "][" << logLevelStr[type] << "]: " << message << std::endl;
    
        
        if (type == FATAL) {
            std::cerr << "[FATAL]: Critical error" << std::endl;
        }
    }
    
    /**
     * @brief Demonstrates usage of the logger with various log levels.
     * 
     * Catches and displays any thrown exceptions.
     */

    void run() {
        try {
            print("Application starting");
            log(INFO, "Initialization complete.");
            log(DEBUG, "Debugging details...");
            log(WARN, "Potential issue detected.");
            log(ERROR, "An error has occurred");
            log(FATAL, "Critical failure!");
            log(INFO, "");
        } catch (const std::exception& e) {
            std::cerr << "[ERROR]: Exception caught: " << e.what() << std::endl;
        }
    }

private:

    /**
     * @brief Gets the current timestamp.
     * 
     * @return A string representing the current time (e.g., "2025/04/08T12:34:56.789").
     */

    std::string getCurrentTimestamp() const {
        auto now = std::chrono::system_clock::now();
        auto nowTime = std::chrono::system_clock::to_time_t(now);
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(
            now.time_since_epoch()) % 1000;

        std::ostringstream timestamp;
        timestamp << std::put_time(std::localtime(&nowTime), "%Y/%m/%dT%H:%M:%S")
                  << '.' << std::setfill('0') << std::setw(3) << ms.count();
        return timestamp.str();
    }
};

int main() {

    /**
     * @brief Main entry point of the program. Runs the logger demo.
     * 
     * @return int Exit code.
     */

    ConsoleLogger logger;
    logger.run();
}
