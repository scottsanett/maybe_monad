#include "maybe.hpp"
#include <iostream>

auto add = [](Maybe<int> mx, Maybe<int> my) -> Maybe<int> {
    return mx >>= [&my](auto x){
        return my >>= [&x](auto y) {
            return (x + y);
        };
    };
};

auto divide = [](Maybe<int> mx, Maybe<int> my) -> Maybe<int> {
    return mx >>= [&my](auto x){
        return my >>= [&x](auto y) {
            return (y == 0) ? Maybe<int>{} : (x / y);
        };
    };
};

int main() {
    std::cout << add(Maybe<int>{100}, Maybe<int>{1000}).get() << std::endl;
    std::cout << divide(Maybe<int>{1000}, Maybe<int>{0}).is_valid() << std::endl;
}