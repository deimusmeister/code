#include <iostream>
#include <future>
#include <chrono>

/**
 * This is minimalistic example demonstrating std::atomic<bool>
 */

void task1(std::atomic<bool>& stop) {
    std::cout << __func__ << " setting value in 3 seconds" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(3));
    stop.store(true);
}

void task2(std::atomic<bool>& stop) {
    std::cout << __func__ << " setting value in 3 seconds" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(3));
    stop.store(true);
}

void task3(std::atomic<bool>& stop) {
    while(stop.load() == false) {
        std::cout << __func__ << " retry in one second" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void task4(std::atomic<bool>& stop) {
    while(stop.load() == false) {
        std::cout << __func__ << " retry in one second" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

int main() {
    std::atomic<bool> stop{false};

    // Consumers
    std::thread t3(task3, std::ref(stop));
    std::thread t4(task4, std::ref(stop));

    // Producers
    std::thread t1(task1, std::ref(stop));
    std::thread t2(task2, std::ref(stop));

    t3.join();
    t4.join();

    t1.join();
    t2.join();

    return 0;
}
