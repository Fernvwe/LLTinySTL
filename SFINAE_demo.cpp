#include <cstddef>
#include <cstdio>
#include <iostream>
#include <type_traits>
#include <vector>
class Widget {
   private:
    int* data;
    size_t size;

   public:
    Widget(size_t n, const int& val) { ::printf("this is constructor 1 \n"); }
    template <class InputIt, class T = typename std::enable_if_t<
                                 !std::is_integral<InputIt>::value>>
    Widget(InputIt first, InputIt last) {
        ::printf("this is constructor 2 \n");
    }
};

int main() {
    Widget w1(static_cast<size_t>(10), 10);
    Widget w2(10, 20);
    system("pause");
    return 0;
}
