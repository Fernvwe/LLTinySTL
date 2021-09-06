#include <iostream>
#include <algorithm>

using namespace std;
class List{
private:
        int * value;
public:
    List(int val):value(&val){}    
    void swap(List& x){
        std::swap(value, x.value);
    }
};
int main()
{
    cout<<"Hello World";
    int c = 2, d = 4;
    List a(c);
    List b(d);
    b.swap(a);
    return 0;
}




