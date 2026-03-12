#include <iostream>
#include <cstring>

using namespace std;

class String {
private:
    char* str;
    size_t length;
    size_t capacity;
    static size_t objectCount;

public:
    String() : String(80) {}

    explicit String(size_t size)
        : capacity(size + 1), length(0) {
        str = new char[capacity];
        str[0] = '\0';
        ++objectCount;
    }

    String(const char* s)
        : String(strlen(s)) {
        strcpy_s(str, capacity, s);  // безопасное копирование с указанием размера
        length = strlen(s);
    }

    String(const String& other)
        : capacity(other.capacity), length(other.length) {
        str = new char[capacity];
        strcpy_s(str, capacity, other.str);
        ++objectCount;
    }

    String& operator=(const String& other) {
        if (this != &other) {
            delete[] str;
            capacity = other.capacity;
            length = other.length;
            str = new char[capacity];
            strcpy_s(str, capacity, other.str);
        }
        return *this;
    }

    ~String() {
        delete[] str;
        --objectCount;
    }

    void input() {
        cout << "Введите строку (макс. " << capacity - 1 << " символов): ";
        cin.getline(str, capacity);
        length = strlen(str);
    }

    void output() const {
        cout << str << endl;
    }

    static size_t getObjectCount() {
        return objectCount;
    }

    size_t getLength() const { return length; }
    size_t getCapacity() const { return capacity; }
};

size_t String::objectCount = 0;

int main() {
    setlocale(LC_ALL, "RU");
    cout << "Объектов сейчас: " << String::getObjectCount() << "\n\n";

    // Конструктор по умолчанию (строка на 80 символов)
    String s1;
    cout << "s1 (пустая, ёмкость " << s1.getCapacity() - 1 << "): ";
    s1.output();

    // Конструктор с заданным размером
    String s2(10);
    cout << "s2 (пустая, ёмкость " << s2.getCapacity() - 1 << "): ";
    s2.output();

    // Конструктор от C-строки
    String s3("Привет, мир!");
    cout << "s3: ";
    s3.output();

    cout << "После создания трёх объектов: " << String::getObjectCount() << "\n\n";

    // Ввод строки с клавиатуры
    cout << "Введите строку для s1:\n";
    s1.input();
    cout << "s1 теперь: ";
    s1.output();
    cout << "Длина s1: " << s1.getLength() << "\n\n";

    // Копирование
    String s4 = s3;
    cout << "s4 (копия s3): ";
    s4.output();
    cout << "Объектов после копирования: " << String::getObjectCount() << "\n\n";

    return 0;
}