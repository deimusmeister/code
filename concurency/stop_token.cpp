#include <iostream>
#include <thread>
#include <future>
#include <stop_token>
#include <chrono>

/**
 * This is minimalistic example demonstrating std::stop_token
 */

void task1(std::stop_source source) {
    std::cout << __func__ << "setting value in 3 seconds" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(3));
    source.request_stop();
}

void task2(std::stop_source source) {
    std::cout << __func__ << "setting value in 3 seconds" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(3));
    source.request_stop();
}

void task3(std::stop_source source) {
    auto token = source.get_token();
    while (!token.stop_requested()) {
        std::cout << __func__ << " retry in one sec" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void task4(std::stop_source source) {
    auto token = source.get_token();
    while (!token.stop_requested()) {
        std::cout << __func__ << " retry in one sec" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

int main() {
    std::stop_source source;   
    
    // Producers
    std::thread t1(task1, source);
    std::thread t2(task2, source);
    
    // Consumers
    std::thread t3(task3, source);
    std::thread t4(task4, source);

    t1.join();
    t2.join();
    
    t3.join();
    t4.join();
    
    return 0;
}
