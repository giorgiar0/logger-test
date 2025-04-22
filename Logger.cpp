#include "Logger.h"

void Logger::log(LogLevel level, const string& message) {
    logs.push_back({level, message});
}

const vector<LogEntry>& Logger::getLogs() const {
    return logs;
}

void Logger::printLogs() const {
    for (const auto& entry : logs) {
        cout << "[" << levelToString(entry.level) << "] " << entry.message << endl;
    }
}

string Logger::levelToString(LogLevel level) const {
    switch (level) {
        case LogLevel::DEBUG: return "DEBUG";
        case LogLevel::INFO:  return "INFO";
        case LogLevel::WARN:  return "WARN";
        case LogLevel::ERROR: return "ERROR";
        default:              return "UNKNOWN";
    }
}
