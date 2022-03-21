#pragma once

#include <chrono>
#include <functional>

using namespace std;
using namespace std::chrono;

/**
 * @brief Runs a specified function with a debounce
 *
 * @param f the function to run
 * @param db the debounce, in milliseconds
 * @param t reference to the timestamp associated with the function call
 */
void handleWithDebounce(function<void()> f, double db, high_resolution_clock &t)
{
    auto now = high_resolution_clock::now();
    double elapsed_time_ms = chrono::duration<double, std::milli>(now - t).count();

    if (elapsed_time_ms >= db)
    {
        f();
    }

    t = high_resolution_clock::now();
}
