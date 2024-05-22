#include "Utils.h"

bool timeRemaining(std::chrono::steady_clock::time_point start, int seconds) {
    auto now = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - start).count();
    return elapsed < seconds;
}
