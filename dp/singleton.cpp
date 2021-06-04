#include <iostream>
#include <string>

class Singleton
{
private:
    Singleton() {};
    Singleton(const Singleton&) = delete;
    Singleton(Singleton&&) = delete;
    Singleton& operator=(const Singleton&) = delete;
    Singleton& operator=(Singleton&&) = delete;

public:
    static Singleton& getInstance() {
        static Singleton instance;
        return instance;
    }
    std::string info;
};

int main() {
    auto& p1 = Singleton::getInstance();
    p1.info = "some value";
    {
        auto& p2 = Singleton::getInstance();
        std::cout << p2.info << std::endl;
    }
    return 0;
}
