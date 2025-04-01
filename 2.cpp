#include <iostream>
#include <string>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <stdexcept>

enum LoggingLevel {
    DEBUG = 0,
    INFO = 1,
    WARN = 2,
    ERROR = 3,
    FATAL = 4
};

class ConsoleLogger {
public:
    void print(const std::string& message) const {
        if (message.empty()) {
            throw std::invalid_argument("Message cannot be empty.");
        }
        std::cout << message << std::endl;
    }

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
    ConsoleLogger logger;
    logger.run();
}
