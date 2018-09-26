#include <iostream>
#include <optional>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <boost/coroutine2/all.hpp>
//#include <boost/range/mutable_iterator.hpp>
//#include <boost/range/const_iterator.hpp>


int main() {

typedef boost::coroutines2::coroutine<int>   coro_t;

coro_t::pull_type source(
    [&](coro_t::push_type& sink){
        int first=1,second=1;
        sink(first);
        sink(second);
        for(int i=0;i<8;++i){
            int third=first+second;
            first=second;
            second=third;
            sink(third);
        }
    });

//for(auto i:source)
//    std::cout << i <<  " ";
	

for(size_t i=0; i<4 ; ++i) {
	std::cout << i << ": " << source.get() << "\n";
	source();
}


 return 0;   

}

