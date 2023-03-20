#include <thread>
#include <numeric>
#include <iostream>
#include <algorithm>
#include <vector>
#include <chrono>
#include <random>
#include <functional>
#include <typeinfo>
#include <fstream>
#include "json.hpp"

using steady_clock_t = std::chrono::steady_clock;



double times1 = 0;

template <typename T>
class Timer {
public:
	Timer(const std::string& message): message(message), begin(steady_clock_t::now()) {}
	
	~Timer() 
    {
       times1 = std::chrono::duration_cast<T>(steady_clock_t::now() - begin).count();
	}
private:
	steady_clock_t::time_point begin;
	std::string message;
};

template<typename Iter, typename T>
void accumulate_block(Iter begin, Iter end, T init, T& result) {
	result = std::accumulate(begin, end, init);
}

template<typename Iter, typename T>
T parallel_accumulate(Iter begin, Iter end, T init, int num_threads) {
	std::vector<std::thread> threads;
	std::vector<T> results(num_threads - 1);
	auto block_size = std::distance(begin, end) / num_threads;
	for (auto i = 0u; i + 1 < num_threads; i++) {
		threads.push_back(std::thread(
			accumulate_block<Iter, T>,
			std::next(begin, i * block_size),
			std::next(begin, (i + 1) * block_size),
			0,
			std::ref(results[i]))
		);
	}
	T last_result;
	accumulate_block(std::next(begin, (num_threads - 1) * block_size),
			end, init, last_result);
	std::for_each(std::begin(threads), std::end(threads), std::mem_fn(&std::thread::join));
	return std::accumulate(std::begin(results), std::end(results), last_result);
}

int main() {
    nlohmann::json jsonfile;
	auto size = 0u;
    int N;
    std::cout << "size";
    std::cin >> size;
    std::cout << "number of experiments";
    std::cin >> N;
    std::vector<double> times(std::thread::hardware_concurrency());
    std::vector<int> numbers(size);
    for (int num_threads = 1; num_threads < std::thread::hardware_concurrency(); num_threads ++)
    {
        times1 = 0;
        times[num_threads] = 0;
        for(int j = 0; j < N; j++)
        {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> d(1, 10);
        
            std::vector<int> randoms;
            std::generate_n(std::back_inserter(randoms), size, [&gen, &d](){return d(gen);});
            {
                Timer<std::chrono::microseconds> t("Parallel");
                auto result = parallel_accumulate(randoms.begin(), randoms.end(), 0, num_threads); 
            }
            times[num_threads] = times[num_threads] + times1;
        }
        times[num_threads] = times[num_threads]/N;
    }
    std::ofstream file("data.json");
    for (int i = 1; i < std::thread::hardware_concurrency(); i++)
    {
        std::cout << times[i] << std::endl;
        jsonfile[i-1] = times[i];
    }
    file << jsonfile;
}
