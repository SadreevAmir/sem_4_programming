#include <vector>
#include <array>
#include <deque>
#include <list>
#include <iostream>
#include <random>
#include <chrono>
#include <cmath>
#include <algorithm>

void print(std::vector <int> const &a) {
   std::cout << "numbers:";
   for(int i=0; i < a.size(); i++)
   std::cout << a.at(i) << ' ';
   std::cout << std::endl;
}

int main()
{
    std::vector<int> numbers(10);
    for (int i = 0; i < 10; i++)
    {
        numbers[i] = i + 1;
    }
    std::cout << "sequence P1" << std::endl;
    print(numbers);
    std::cout << "how many numbers will be entered?" << std::endl;
    int N;
    std::cin >> N;
    for (int i = 0; i < N; i ++)
    {
        int a;
        std::cin >> a;
        numbers.push_back(a);
    }
    std::cout << "P1 with cin" << std::endl;
    print(numbers);
    std::random_shuffle(numbers.begin(), numbers.end());
    std::cout << "shuffeled P1" << std::endl;
    print(numbers);
    sort(numbers.begin(), numbers.end() );
    numbers.erase(unique( numbers.begin(), numbers.end() ), numbers.end());
    std::cout << "no duplicates P1" << std::endl;
    print(numbers);
    int number_of_odd = 0;
    for (int i = 0; i < numbers.size(); i++)
    {
        if (numbers[i]%2 == 1)
        {
            number_of_odd += 1;
        }
    }
    std::cout << "numbers of odds" << std::endl;
    std::cout << number_of_odd << std::endl;
    sort(numbers.begin(), numbers.end());
    std::cout << "min:" << numbers[0] << " max: " << numbers[numbers.size() - 1] << std::endl;
    for (int i = 0; i < numbers.size(); i ++)
    {
        for (int j = 2; j < numbers[i]; j ++)
        {
            if (numbers[i]%j == 0)
            {
                break;
            }
            if(j == numbers[i] - 1)
            {
                std::cout << "prime number" << std::endl;
                std::cout << numbers[i] << std::endl;
            }
        }
    }
    for(int i = 0; i < numbers.size(); i ++)
    {
        numbers[i] = numbers[i] * numbers[i];
    }
    std::cout << "P1 with squares" << std::endl;
    print(numbers);
    std::random_device d;
	std::mt19937_64 mt(d());
	std::uniform_int_distribution<int> distribution(-100, 100);
    std::vector<int> numbers_2(numbers.size());
	for(int i = 0; i < numbers_2.size(); i++)
    {
		auto random_element = distribution(mt);
		numbers_2[i] = random_element;
	}
    std::cout << "sequence P2" << std::endl;
    print(numbers_2);
    int summ = 0;
    for (int i = 0; i < numbers_2.size(); i++)
    {
        summ += numbers_2[i];
    }
    std::cout << "summ P2" << std::endl;
    std::cout << summ << std::endl;
    std::cout << "How namy numbers will be changes to 1?";
    std::cin >> N;
    for (int i = 0; i < N; i++)
    {
        numbers_2[i] = 1;
    }
    print(numbers_2);
    std::vector<int> numbers_3(numbers.size());
    for (int i = 0; i < numbers.size(); i++)
    {
        numbers_3[i] = numbers[i] - numbers_2[i];
    }
    std::cout << "P1, P2, P3" << std::endl;
    print(numbers);
    print(numbers_2);
    print(numbers_3);
    for (int i = 0; i < numbers.size(); i++)
    {
        if (numbers_3[i] < 0)
        {
            numbers_3[i] = 0;
        }
    }
    std::cout << "negative to zero P3" << std::endl;
    print(numbers_3);
    for (int i = 0; i < numbers_3.size(); i++)
    {
        if (numbers_3[i] == 0)
        {
            numbers_3.erase(numbers_3.begin() + i);
            i -= 1;
        }
    }
    std::cout << "deleted 0" << std::endl;
    print(numbers_3);
    std::reverse(numbers_3.begin(), numbers_3.end());
    std::cout << "reversed P3" << std::endl;
    print(numbers_3);
    std::vector<int> vect = numbers_3;
    sort(vect.begin(), vect.end());
    for (int i = vect.size() - 1; i > vect.size() - 4; i --)
    {
        std::cout << " max value:" << vect[i] << std::endl;
    }
    vect.clear();
    std::cout << "sorted P1 and P2" << std::endl;
    sort(numbers.begin(), numbers.end());
    sort(numbers_2.begin(), numbers_2.end());
    print(numbers);
    print(numbers_2);
    std::vector<int> numbers_4(numbers.size() + numbers_2.size());
    merge (numbers.begin( ), numbers.end( ), numbers_2.begin( ), numbers_2.end( ), numbers_4.begin( ));
    std::cout << "sequence P4" << std::endl;
    print(numbers_4);
    for (int i = 0; i < numbers_4.size(); i++)
    {
        if (numbers_4[i] >= 1 and numbers_4[i - 1] < 1)
        {
            std::cout << "from " << i << ' ';
        }
        if (numbers_4[i] <= 1 and numbers_4[i + 1] > 1)
        {
            std::cout << "to " << i << ' ';
        }
    }
    return 0;
}

