#include "lockable.h"

#include <thread>
#include <vector>

class test{
public:
	test(int initial_value) :
		value(initial_value){
	}

	int value;
};

void main(){
  auto a = make_lockable<test>(0);
	std::vector<std::thread> threads;

	for(int i=0;i<10;i++){
		threads.push_back(
			std::thread([&a](){
				for(int i=0;i<10000;i++){
					a.lock([&a](){
						a->value ++;
					}); 
				}
			}));
	}
	for(auto &t : threads){
		t.join();
	}
	
	printf("%d\n", a->value);
}
