// 8:15 AM/09/28/2017
#pragma once
#include <iostream>       // std::cout
#include <thread>         // std::thread
#include <mutex>          // std::mutex
#include <chrono>
using namespace std;
volatile int counter(0);
volatile int counter2(0);
mutex mtx;//This mutex class is synchronization primitive that
//can be used to protect shared data from being simultaneously accessed by multiple threads.
// mutex类时一个同步原语，用来保护共享数据，阻止多线程同时访问
mutex mtx2;

void run()
{
	for (int i = 0; i < 100; ++i)
	{
		mtx.lock();// lock mtx,blocks if mtx is not available
		// the word block means that when the mtx is avaiable,it will lock mtx and the following code will being executed
		++counter;
		cout << this_thread::get_id() << "==> " << counter << endl;

		mtx.unlock();// this function will make mtx is available,
		//and other threads that is being blocked will detect the mtx is available
		// but the others don't mean that all of them can detect the mtx is available because if one detect it and it will lock it.
		// only the one thread will own the mtx 
		//here the function unlock is necessary
	}
}

void run2()
{
	for (int i = 0; i < 100; i++)
	{
		if (mtx2.try_lock())
			//It differs from the function lock.Here,it will not block and if mtx2 is available,it will be lock and return ture.
		{
			++counter2;
			cout << this_thread::get_id() << "==> " << counter2 << endl;
			mtx2.unlock();
		}
	}
}

int main(int argc, const char* argv[])
{
	thread ts[10];
	for (int i = 0; i < 10; ++i)
	{
		ts[i] = thread(run);
	}
	for (auto& t : ts) t.join();

	std::this_thread::sleep_for(std::chrono::seconds(2));
	// sleep for 2s

	thread ts2[10];
	for (int i = 0; i < 10; ++i)
	{
		ts2[i] = thread(run2);
	}
	for (auto& t : ts2)t.join();
}
//We see that the results of counter and counter2 is unequal,and we convincingly konw the counter is equal
//to 1000 because of the function lock.The counter2,however,may not have a unique result owing to the function
// try_lock without blocking.