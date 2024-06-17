#include <iostream>
#include <cstring>
#include <windows.h>

using namespace std;

// Класс "Человек"
class Person
{
private:
    char* name;

public:
    // Конструктор
    Person(const char* name)
    {
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);
    }

    // Конструктор копирования
    Person(const Person& other)
    {
        name = new char[strlen(other.name) + 1];
        strcpy(name, other.name);
    }

    // Оператор присваивания
    Person& operator=(const Person& other)
    {
        if (this != &other)
        {
            delete[] name;
            name = new char[strlen(other.name) + 1];
            strcpy(name, other.name);
        }
        return *this;
    }

    // Деструктор
    ~Person()
    {
        delete[] name;
    }

    // Функция вывода информации о человеке
    void print() const
    {
        std::cout << "Человек: " << name << std::endl;
    }
};

// Класс "Квартира"
class Apartment {
private:
    Person** residents;
    size_t numResidents;

public:
    // Конструктор
    Apartment(size_t numResidents = 0) : residents(nullptr), numResidents(numResidents) {
        if (numResidents > 0)
        {
            residents = new Person * [numResidents];
            for (size_t i = 0; i < numResidents; ++i)
            {
                residents[i] = nullptr;
            }
        }
    }

    // Конструктор копирования
    Apartment(const Apartment& other) : numResidents(other.numResidents)
    {
        residents = new Person * [numResidents];
        for (size_t i = 0; i < numResidents; ++i)
        {
            if (other.residents[i] != nullptr)
            {
                residents[i] = new Person(*other.residents[i]);
            }
            else
            {
                residents[i] = nullptr;
            }
        }
    }

    // Оператор присваивания
    Apartment& operator=(const Apartment& other)
    {
        if (this != &other) {
            for (size_t i = 0; i < numResidents; ++i)
            {
                delete residents[i];
            }
            delete[] residents;

            numResidents = other.numResidents;
            residents = new Person * [numResidents];
            for (size_t i = 0; i < numResidents; ++i)
            {
                if (other.residents[i] != nullptr)
                {
                    residents[i] = new Person(*other.residents[i]);
                }
                else
                {
                    residents[i] = nullptr;
                }
            }
        }
        return *this;
    }

    // Деструктор
    ~Apartment() {
        for (size_t i = 0; i < numResidents; ++i)
        {
            delete residents[i];
        }
        delete[] residents;
    }

    // Функция добавления жильца
    void addResident(size_t index, const char* name)
    {
        if (index < numResidents)
        {
            delete residents[index];
            residents[index] = new Person(name);
        }
    }

    // Функция вывода информации о квартире
    void print() const {
        cout << "Апартаменты с " << numResidents << " жителями:" << endl;
        for (size_t i = 0; i < numResidents; ++i)
        {
            if (residents[i] != nullptr)
            {
                residents[i]->print();
            }
        }
    }
};

// Класс "Дом"
class Building {
private:
    Apartment* apartments;
    size_t numApartments;

public:
    // Конструктор
    Building(size_t numApartments = 0) : apartments(nullptr), numApartments(numApartments) {
        if (numApartments > 0)
        {
            apartments = new Apartment[numApartments];
        }
    }

    // Конструктор копирования
    Building(const Building& other) : numApartments(other.numApartments) {
        apartments = new Apartment[numApartments];
        for (size_t i = 0; i < numApartments; ++i)
        {
            apartments[i] = other.apartments[i];
        }
    }

    // Оператор присваивания
    Building& operator=(const Building& other)
    {
        if (this != &other)
        {
            delete[] apartments;

            numApartments = other.numApartments;
            apartments = new Apartment[numApartments];
            for (size_t i = 0; i < numApartments; ++i)
            {
                apartments[i] = other.apartments[i];
            }
        }
        return *this;
    }

    // Деструктор
    ~Building()
    {
        delete[] apartments;
    }

    // Функция добавления квартиры
    void addApartment(size_t index, size_t numResidents)
    {
        if (index < numApartments)
        {
            apartments[index] = Apartment(numResidents);
        }
    }

    // Функция добавления жильца в квартиру
    void addResidentToApartment(size_t apartmentIndex, size_t residentIndex, const char* name) {
        if (apartmentIndex < numApartments)
        {
            apartments[apartmentIndex].addResident(residentIndex, name);
        }
    }

    // Функция вывода информации о доме
    void print() const
    {
        cout << "Здание с " << numApartments << " апартаментами:" << endl;
        for (size_t i = 0; i < numApartments; ++i)
        {
            apartments[i].print();
        }
    }
};

int main()
{
    // Создание дома с 2 квартирами
    Building building(2);

    // Добавление квартир
    building.addApartment(0, 2);
    building.addApartment(1, 3);

    // Добавление жильцов в квартиры
    building.addResidentToApartment(0, 0, "Иван Иванов");
    building.addResidentToApartment(0, 1, "Мария Иванова");
    building.addResidentToApartment(1, 0, "Петр Петров");
    building.addResidentToApartment(1, 1, "Анна Петрова");
    building.addResidentToApartment(1, 2, "Сергей Сергеев");

    // Вывод информации о доме
    building.print();

    // Тестирование конструктора копирования
    Building buildingCopy = building;
    cout << "Копия здания:" << endl;
    buildingCopy.print();

    // Тестирование оператора присваивания
    Building anotherBuilding;
    anotherBuilding = building;
    cout << "Другое здание после изменения:" << endl;
    anotherBuilding.print();

    return 0;
}