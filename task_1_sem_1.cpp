#include <iostream>
#include <chrono>
#include <cmath>

template<typename T>

class Timer {
public:
	Timer()
	{
		start = std::chrono::steady_clock::now();
		stop = std::chrono::steady_clock::now();
		full_time = start - stop;
	}
	~Timer() 
	{
		std::cout << std::chrono::duration_cast<T>(full_time).count() << std::endl;
	};

	void Stop()
	{
		stop = std::chrono::steady_clock::now();
		full_time += stop - start;
	};

	void Start()
	{
		start = std::chrono::steady_clock::now();
	};

private:
	std::chrono::steady_clock::time_point start;
	std::chrono::steady_clock::time_point stop;
	std::chrono::duration<double> full_time;
	bool count = true;
};

void calculate_smth(int n)
{
	auto count = 0;
	for (auto i = 0; i < 1'000'000; i++) 
	{
		count += std::sin(i) + std::cos(i);
	}
}

int main() 
{
	Timer<std::chrono::microseconds> t;
	t.Start();
	calculate_smth(1'000'000);
	//t.Start();
	//t.Stop();
	calculate_smth(1'000'000);
	//t.Stop();
	//t.Start();
	calculate_smth(1'000'000);
	t.Stop();
	std::cout << "After" << std::endl;
}
