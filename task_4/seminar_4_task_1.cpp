#include "json.hpp"
#include <iostream>
#include <fstream>
#include <cstring>
#include <filesystem>
#include <vector>

struct Human
{
public:
    std::string name;
    std::string surname;
    int age;
    int weight;
    int height;
    Human(std::string name = "", std::string surname = "" , int age = 0, int weight = 0, int height = 0) : name(name), surname(surname), age(age), weight(weight), height(height){}
    ~Human(){}
    friend std::istream& operator>>(std::istream &in, Human &human);
    friend std::ostream& operator<<(std::ostream &out, Human &human);
};

std::istream& operator>>(std::istream& in, Human &human)
{
    std::cout << " name "  << std::endl;
    in >> human.name;
    std::cout << " surname "  << std::endl;
    in >> human.surname;
    std::cout << " age "  << std::endl;
    in >> human.age;
    std::cout << " weight "  << std::endl;
    in >> human.weight;
    std::cout << " height "  << std::endl;
    in >> human.height;
    return in;
}

std::ostream& operator<<(std::ostream& out, Human &human)
{
    out << human.name << std::endl;
    out << human.surname << std::endl;
    out << human.age << std::endl;
    out << human.weight << std::endl;
    out << human.height << std::endl;
    return out;
}

int main() 
{
    int N = 3;
    std::vector<Human> list(N);
    std::cout << "white an information about human" << std::endl;
    nlohmann::json jsonfile;
    for (int i = 0; i < N; i++)
    {
        std::cin >> list[i];
        jsonfile[i]["name"] = list[i].name;
        jsonfile[i]["surname"] = list[i].surname;
        jsonfile[i]["age"] = list[i].age;
        jsonfile[i]["weight"] = list[i].weight;
        jsonfile[i]["height"] = list[i].height;
        std::ofstream file("person.json");
        file << jsonfile;
    }
    return 0;
}