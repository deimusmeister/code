#include <iostream>
#include <string>
#include <string_view>

/**
 * This is a minimal example of std::string_view demo
 * printValue will not make any copy of str
 */
void printValue(std::string_view strv) {
    if(strv.length() >= 2) {
        strv.remove_prefix(2);
    }
    std::cout << strv << std::endl; 
}

int main() {
    std::string str = "xclorem ipsum";
    std::string_view strv{str};
    printValue(strv);
    return 0;
}
