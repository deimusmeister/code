#include <iostream>
#include <future>

/**
 * This is minimalistic example demonstrating std::promise and std::future
 */

int main() {

    std::promise<int> p;
    std::future<int> f{p.get_future()};

    std::thread t1([&] {
        std::cout << "setting a value in promise" << std::endl; 
        p.set_value(1);
    });

    std::thread t2([&] {
        auto value = f.get();
        std::cout << "value received from future " << value << std::endl;
    });
    
    t1.join();
    t2.join();

    return 0;
}
