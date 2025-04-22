#pragma once
#include <string>
#include <vector>
#include <iostream>

using namespace std;

enum class LogLevel { DEBUG, INFO, WARN, ERROR };

struct LogEntry {
    LogLevel level;
    string message;
};

class Logger {
public:
    void log(LogLevel level, const string& message);
    const vector<LogEntry>& getLogs() const;
    void printLogs() const;

private:
    vector<LogEntry> logs;
    string levelToString(LogLevel level) const;
};
