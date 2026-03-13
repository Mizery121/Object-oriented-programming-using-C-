#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <algorithm>
#include <sstream>
#include <string>

using namespace std;

// ==================== Класс Set (множество целых чисел) ====================
class Set {
private:
    int* data;      // указатель на динамический массив элементов
    size_t size;    // текущее количество элементов

public:
    // Конструктор по умолчанию (пустое множество)
    Set() : data(nullptr), size(0) {}

    // Конструктор от initializer_list (позволяет создавать множество вида {1,2,3})
    Set(initializer_list<int> list) : size(list.size()) {
        data = new int[size];
        size_t i = 0;
        for (int val : list) {
            if (!contains(val)) {
                data[i++] = val;
            }
            else {
                --size;
            }
        }
        if (i != size) {
            int* newData = new int[i];
            for (size_t j = 0; j < i; ++j)
                newData[j] = data[j];
            delete[] data;
            data = newData;
            size = i;
        }
    }

    // Конструктор копирования
    Set(const Set& other) : size(other.size) {
        data = new int[size];
        for (size_t i = 0; i < size; ++i)
            data[i] = other.data[i];
    }

    // Деструктор
    ~Set() {
        delete[] data;
    }

    // Проверка наличия элемента
    bool contains(int value) const {
        for (size_t i = 0; i < size; ++i)
            if (data[i] == value)
                return true;
        return false;
    }

    // Добавление элемента
    Set& operator+=(int value) {
        if (!contains(value)) {
            int* newData = new int[size + 1];
            for (size_t i = 0; i < size; ++i)
                newData[i] = data[i];
            newData[size] = value;
            delete[] data;
            data = newData;
            ++size;
        }
        return *this;
    }

    Set operator+(int value) const {
        Set result = *this;
        result += value;
        return result;
    }

    // Объединение множеств
    Set& operator+=(const Set& other) {
        for (size_t i = 0; i < other.size; ++i) {
            *this += other.data[i];
        }
        return *this;
    }

    Set operator+(const Set& other) const {
        Set result = *this;
        result += other;
        return result;
    }

    // Удаление элемента
    Set& operator-=(int value) {
        for (size_t i = 0; i < size; ++i) {
            if (data[i] == value) {
                int* newData = new int[size - 1];
                for (size_t j = 0; j < i; ++j)
                    newData[j] = data[j];
                for (size_t j = i + 1; j < size; ++j)
                    newData[j - 1] = data[j];
                delete[] data;
                data = newData;
                --size;
                break;
            }
        }
        return *this;
    }

    Set operator-(int value) const {
        Set result = *this;
        result -= value;
        return result;
    }

    // Разность множеств
    Set& operator-=(const Set& other) {
        for (size_t i = 0; i < other.size; ++i) {
            *this -= other.data[i];
        }
        return *this;
    }

    Set operator-(const Set& other) const {
        Set result = *this;
        result -= other;
        return result;
    }

    // Пересечение множеств
    Set& operator*=(const Set& other) {
        Set result;
        for (size_t i = 0; i < size; ++i) {
            if (other.contains(data[i])) {
                result += data[i];
            }
        }
        *this = result;
        return *this;
    }

    Set operator*(const Set& other) const {
        Set result;
        for (size_t i = 0; i < size; ++i) {
            if (other.contains(data[i])) {
                result += data[i];
            }
        }
        return result;
    }

    // Присваивание
    Set& operator=(const Set& other) {
        if (this != &other) {
            delete[] data;
            size = other.size;
            data = new int[size];
            for (size_t i = 0; i < size; ++i)
                data[i] = other.data[i];
        }
        return *this;
    }

    // Сравнение
    bool operator==(const Set& other) const {
        if (size != other.size) return false;
        for (size_t i = 0; i < size; ++i) {
            if (!other.contains(data[i]))
                return false;
        }
        return true;
    }

    bool operator!=(const Set& other) const {
        return !(*this == other);
    }

    // Потоковый вывод
    friend ostream& operator<<(ostream& os, const Set& s) {
        os << "{";
        for (size_t i = 0; i < s.size; ++i) {
            if (i > 0) os << ", ";
            os << s.data[i];
        }
        os << "}";
        return os;
    }

    // Потоковый ввод (формат: числа через пробел, окончание - перевод строки)
    friend istream& operator>>(istream& is, Set& s) {
        // Очищаем текущее множество
        delete[] s.data;
        s.data = nullptr;
        s.size = 0;

        // Считываем всю строку
        string line;
        if (is.peek() == '\n') is.ignore(); // если остался символ новой строки
        getline(is, line);

        // Превращаем строку в поток и читаем числа
        stringstream ss(line);
        int val;
        while (ss >> val) {
            s += val;
        }

        return is;
    }

    size_t getSize() const { return size; }
};

// ==================== Расширенная демонстрация ====================
int main() {
    setlocale(LC_ALL, "Russian");

    cout << "********** Демонстрация класса Set (множество целых чисел) **********\n";

    // Первое множество (заданное явно)
    Set A = { 3, 8, 46, 5, 11 };
    Set B = { 18, 8, 90, 11, 2 };

    cout << "A (явное задание) = " << A << endl;
    cout << "B (явное задание) = " << B << endl << endl;

    // Демонстрация базовых операций
    cout << "--- Базовые операции ---" << endl;
    A += 4;
    cout << "A += 4 -> " << A << endl;
    A += 3;
    cout << "A += 3 (уже есть) -> " << A << endl;
    A -= 5;
    cout << "A -= 5 -> " << A << endl;

    Set C = A + B;
    cout << "A + B = " << C << endl;

    Set D = A * B;
    cout << "A * B = " << D << endl;

    Set E = A - B;
    cout << "A - B = " << E << endl;

    Set F = { 3, 8, 46, 11, 4 };
    cout << "F = " << F << endl;
    cout << "A == F ? " << (A == F ? "да" : "нет") << endl << endl;

    // Проверка принадлежности
    cout << "A содержит 8? " << (A.contains(8) ? "да" : "нет") << endl;
    cout << "A содержит 100? " << (A.contains(100) ? "да" : "нет") << endl << endl;

    // Интерактивный ввод первого множества
    cout << "Введите элементы первого множества через пробел и нажмите Enter: ";
    Set G;
    cin >> G;
    cout << "Вы ввели: " << G << endl << endl;

    // Интерактивный ввод второго множества
    cout << "Введите элементы второго множества через пробел и нажмите Enter: ";
    Set H;
    cin >> H;
    cout << "Вы ввели: " << H << endl << endl;

    // Демонстрация операций с введёнными множествами
    cout << "--- Операции с введёнными множествами ---" << endl;
    cout << "G = " << G << endl;
    cout << "H = " << H << endl;
    cout << "G + H = " << (G + H) << endl;
    cout << "G * H = " << (G * H) << endl;
    cout << "G - H = " << (G - H) << endl;
    cout << "G == H ? " << (G == H ? "да" : "нет") << endl;

    // Добавление и удаление по одному элементу
    cout << "\nДобавим 100 в G:" << endl;
    G += 100;
    cout << "G = " << G << endl;

    cout << "Удалим 11 из H (если есть):" << endl;
    H -= 11;
    cout << "H = " << H << endl;

    return 0;
}