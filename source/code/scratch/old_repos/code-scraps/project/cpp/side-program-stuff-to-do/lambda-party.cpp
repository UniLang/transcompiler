#include <iostream>
#include <string>

using namespace std;

template <typename T>
class A{
};


template <typename T>
auto function (const A<T> i) -> void{
}






int main(){

//combos

//[] [&] [=]
//() (...)
//{} {again}
//(); ;;



//[](){}
//[&](){}
//[=](){}
//[](...){}
//[&](...){}
//[=](...){}

//[](){do}
//[&](){do}
//[=](){do}
//[](...){do}
//[&](...){do}
//[=](...){do}


//[](){}();
//[&](){}();
//[=](){}();
//[](...){}();
//[&](...){}();
//[=](...){}();

//[](){do}();
//[&](){do}();
//[=](){do}();
//[](...){do}();
//[&](...){do}();
//[=](...){do}();

//[](){};
//[&](){};
//[=](){};
//[](...){};
//[&](...){};
//[=](...){};

//[](){do};
//[&](){do};
//[=](){do};
//[](...){do};
//[&](...){do};
//[=](...){do};




//[&](   auto(*)()      ){};//();   //[](){}




[&]{[=]{[&]{[=]{[&]{[=]{}();}();}();}();}();}();
[&]{[=]{[&]{[=]{[&]{[=]{}();}();}();}();}();}();
[&]{[=]{[&]{[=]{[&]{[=]{}();}();}();}();}();}();
[&]{[=]{[&]{[=]{[&]{[=]{}();}();}();}();}();}();
[&]{[=]{[&]{[=]{[&]{[=]{}();}();}();}();}();}();
[&]{[=]{[&]{[=]{[&]{[=]{}();}();}();}();}();}();
[&]{[=]{[&]{[=]{[&]{[=]{}();}();}();}();}();}();
[&]{[=]{[&]{[=]{[&]{[=]{}();}();}();}();}();}();
[&]{[=]{[&]{[=]{[&]{[=]{}();}();}();}();}();}();
[&]{[=]{[&]{[=]{[&]{[=]{}();}();}();}();}();}();
[&]{[=]{[&]{[=]{[&]{[=]{}();}();}();}();}();}();
[&]{[=]{[&]{[=]{[&]{[=]{}();}();}();}();}();}();
[&]{[=]{[&]{[=]{[&]{[=]{}();}();}();}();}();}();

const A< const A<A<A<void********>const&>*****>&> a{};

const A <int const&> *** b{};
//function<int>(a);
}