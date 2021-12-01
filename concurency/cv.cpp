#include <iostream>
#include <future>
#include <chrono>
#include <condition_variable>

/**
 * This is minimalistic example demonstrating std::condition_variable
 * NOTE: predicate is needed for avoiding 
 * - spurious wakeup
 * - lost wakeup, when wait is invoked executed before notify
 */

void task1(std::condition_variable& cv, std::mutex& m, bool& stop) {
    std::cout << __func__ << " setting value in 3 seconds" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(3));
    {
        std::lock_guard<std::mutex> lk(m);
        stop = true;
    }
    cv.notify_all();
}

void task2(std::condition_variable& cv, std::mutex& m, bool& stop) {
    std::unique_lock<std::mutex> lk(m);
    while(cv.wait_for(lk, std::chrono::seconds(0), [&stop] { return stop; }) == false) {
        std::cout << __func__ << " retry in one second" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

int main() {
    std::mutex m;
    std::condition_variable cv;
    bool stop{false};

    // Producer
    std::thread t1(task1, std::ref(cv), std::ref(m), std::ref(stop));

    // Consumer
    std::thread t2(task2, std::ref(cv), std::ref(m), std::ref(stop));

    t1.join();
    t2.join();

    return 0;
}
