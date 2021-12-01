#include <iostream>
#include <future>
#include <chrono>


/**
 * This is minimalistic example demonstrating std::packaged_task
 */
 
void stop() {
    std::cout << __func__ << " stop called" << std::endl;
    return;
}

void task1(std::packaged_task<void()> task) {
    std::cout << __func__ << " setting value in 3 seconds" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(3));
    task();
}

void task2(std::shared_future<void> future) {
    while(future.wait_for(std::chrono::seconds(0)) == std::future_status::timeout) {
        std::cout << __func__ << " retry in one second" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

int main() {
    std::packaged_task<void()> task(stop);
    std::shared_future<void> f = task.get_future();

    // Consumer
    std::thread t2(task2, f);

    // Producer
    std::thread t1(task1, std::move(task));

    t1.join();
    t2.join();

    return 0;
}
