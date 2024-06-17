#include <iostream>
#include <cstring>
#include <windows.h>

using namespace std;

// ����� "�������"
class Person
{
private:
    char* name;

public:
    // �����������
    Person(const char* name)
    {
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);
    }

    // ����������� �����������
    Person(const Person& other)
    {
        name = new char[strlen(other.name) + 1];
        strcpy(name, other.name);
    }

    // �������� ������������
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

    // ����������
    ~Person()
    {
        delete[] name;
    }

    // ������� ������ ���������� � ��������
    void print() const
    {
        std::cout << "�������: " << name << std::endl;
    }
};

// ����� "��������"
class Apartment {
private:
    Person** residents;
    size_t numResidents;

public:
    // �����������
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

    // ����������� �����������
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

    // �������� ������������
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

    // ����������
    ~Apartment() {
        for (size_t i = 0; i < numResidents; ++i)
        {
            delete residents[i];
        }
        delete[] residents;
    }

    // ������� ���������� ������
    void addResident(size_t index, const char* name)
    {
        if (index < numResidents)
        {
            delete residents[index];
            residents[index] = new Person(name);
        }
    }

    // ������� ������ ���������� � ��������
    void print() const {
        cout << "����������� � " << numResidents << " ��������:" << endl;
        for (size_t i = 0; i < numResidents; ++i)
        {
            if (residents[i] != nullptr)
            {
                residents[i]->print();
            }
        }
    }
};

// ����� "���"
class Building {
private:
    Apartment* apartments;
    size_t numApartments;

public:
    // �����������
    Building(size_t numApartments = 0) : apartments(nullptr), numApartments(numApartments) {
        if (numApartments > 0)
        {
            apartments = new Apartment[numApartments];
        }
    }

    // ����������� �����������
    Building(const Building& other) : numApartments(other.numApartments) {
        apartments = new Apartment[numApartments];
        for (size_t i = 0; i < numApartments; ++i)
        {
            apartments[i] = other.apartments[i];
        }
    }

    // �������� ������������
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

    // ����������
    ~Building()
    {
        delete[] apartments;
    }

    // ������� ���������� ��������
    void addApartment(size_t index, size_t numResidents)
    {
        if (index < numApartments)
        {
            apartments[index] = Apartment(numResidents);
        }
    }

    // ������� ���������� ������ � ��������
    void addResidentToApartment(size_t apartmentIndex, size_t residentIndex, const char* name) {
        if (apartmentIndex < numApartments)
        {
            apartments[apartmentIndex].addResident(residentIndex, name);
        }
    }

    // ������� ������ ���������� � ����
    void print() const
    {
        cout << "������ � " << numApartments << " �������������:" << endl;
        for (size_t i = 0; i < numApartments; ++i)
        {
            apartments[i].print();
        }
    }
};

int main()
{
    // �������� ���� � 2 ����������
    Building building(2);

    // ���������� �������
    building.addApartment(0, 2);
    building.addApartment(1, 3);

    // ���������� ������� � ��������
    building.addResidentToApartment(0, 0, "���� ������");
    building.addResidentToApartment(0, 1, "����� �������");
    building.addResidentToApartment(1, 0, "���� ������");
    building.addResidentToApartment(1, 1, "���� �������");
    building.addResidentToApartment(1, 2, "������ �������");

    // ����� ���������� � ����
    building.print();

    // ������������ ������������ �����������
    Building buildingCopy = building;
    cout << "����� ������:" << endl;
    buildingCopy.print();

    // ������������ ��������� ������������
    Building anotherBuilding;
    anotherBuilding = building;
    cout << "������ ������ ����� ���������:" << endl;
    anotherBuilding.print();

    return 0;
}