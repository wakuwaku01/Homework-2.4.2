#include <fstream>
#include <iostream>
#include <string>

class Address {
public:
    Address() {}
    Address(std::string city, std::string street, int building, int flat);
    std::string print_to_file() {
        std::string out = city + ", " + street + ", " + std::to_string(building) +
            ", " + std::to_string(flat);
        return out;
    }
    std::string compare_city() { return city; }

private:
    std::string city;
    std::string street;
    int building;
    int flat;
};

Address::Address(std::string city, std::string street, int building, int flat) {
    this->city = city;
    this->street = street;
    this->building = building;
    this->flat = flat;
}

int main() {
    setlocale(LC_ALL, "Russian");
    unsigned num = 0, building = 0, flat = 0;
    std::string city, street;
    std::ifstream fin("in.txt");
    std::ofstream fout("out.txt");
    if (!fin.is_open()) {
        std::cout << "Не удалось открыть файл." << std::endl;
        return 0;
    }
    fin >> num;
    fout << num << std::endl;

    Address *arr = new Address[num];
    for (int i = 0; i < num; ++i) {
        fin >> city >> street >> building >> flat;
        Address address = Address(city, street, building, flat);
        arr[i] = address;
    }

    bool swapped = false;
    do {
        swapped = false;
        for (int i = num - 1; i > 0; i--) {
            if (arr[i].compare_city() < arr[i - 1].compare_city()) {
                Address temp_address = arr[i - 1];
                arr[i - 1] = arr[i];
                arr[i] = temp_address;
                swapped = true;
            }
        }
    } while (swapped);

    for (int i = 0; i < num; ++i) {
        fout << arr[i].print_to_file() << std::endl;
    }
    delete[] arr;
    fin.close();
    fout.close();
    return 0;
}
