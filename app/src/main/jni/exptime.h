#pragma once

#include <ctime>
#include <sstream>
#include <iomanip>
#include <string>

using namespace std;
std::string EXP = OBFUSCATE("2024-07-31 12:00:00");

string GetCurrentTime() {
    std::time_t currentTime = time(nullptr);
    std::tm* timeInfo = localtime(&currentTime);

    ostringstream oss;
    oss << std::put_time(timeInfo, ("%Y-%m-%d %H:%M:%S"));
    return oss.str();
}

int ConvertDateTimeToInt(const char* datetimeString) {
    std::tm timeInfo = {};
    istringstream ss(datetimeString);
    int temp;

    ss >> timeInfo.tm_year;
    ss.ignore(); // Ignore the "-" sign
    ss >> timeInfo.tm_mon;
    ss.ignore(); // Ignore the "-" sign
    ss >> timeInfo.tm_mday;
    ss.ignore(); // Ignore the " "
    ss >> timeInfo.tm_hour;
    ss.ignore(); // Ignore the ":"
    ss >> timeInfo.tm_min;
    ss.ignore(); // Ignore the ":"
    ss >> timeInfo.tm_sec;

    timeInfo.tm_year -= 1900;
    timeInfo.tm_mon -= 1;

    time_t timestamp = mktime(&timeInfo);

    int result = static_cast<int>(timestamp);
    return result;
}
