#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

// Вспомогательная функция для нахождения НОД
int gcd(int a, int b) {
    a = abs(a);
    b = abs(b);
    while (b) {
        int t = a % b;
        a = b;
        b = t;
    }
    return a;
}

// ==================== Класс Дробь ====================
class Fraction {
private:
    int numerator;   // числитель
    int denominator; // знаменатель (всегда > 0, дробь сокращена)

    // Сокращение дроби
    void reduce() {
        if (denominator == 0) {
            cerr << "Знаменатель не может быть нулем!" << endl;
            denominator = 1;
        }
        if (denominator < 0) { // Переносим знак в числитель
            numerator = -numerator;
            denominator = -denominator;
        }
        int d = gcd(numerator, denominator);
        if (d != 0) {
            numerator /= d;
            denominator /= d;
        }
    }

public:
    // Конструктор с параметрами (список инициализации)
    Fraction(int num, int denom) : numerator(num), denominator(denom) {
        reduce();
    }

    // Конструктор по умолчанию – делегирует конструктору (0,1)
    Fraction() : Fraction(0, 1) {}

    // Метод ввода дроби с клавиатуры
    void input() {
        cout << "Введите числитель и знаменатель: ";
        cin >> numerator >> denominator;
        reduce();
    }

    // Вывод дроби на экран
    void display() const {
        cout << numerator << "/" << denominator;
    }

    // Сложение с дробью (модифицирует текущую)
    Fraction& add(const Fraction& other) {
        numerator = numerator * other.denominator + other.numerator * denominator;
        denominator = denominator * other.denominator;
        reduce();
        return *this;
    }

    // Вычитание дроби
    Fraction& sub(const Fraction& other) {
        numerator = numerator * other.denominator - other.numerator * denominator;
        denominator = denominator * other.denominator;
        reduce();
        return *this;
    }

    // Умножение на дробь
    Fraction& mul(const Fraction& other) {
        numerator *= other.numerator;
        denominator *= other.denominator;
        reduce();
        return *this;
    }

    // Сложение с целым числом
    Fraction& add(int value) {
        return add(Fraction(value, 1));
    }

    // Вычитание целого числа
    Fraction& sub(int value) {
        return sub(Fraction(value, 1));
    }

    // Умножение на целое число
    Fraction& mul(int value) {
        return mul(Fraction(value, 1));
    }
};

// ==================== Класс Дата ====================
class Date {
private:
    int day;
    int month;
    int year;

public:
    Date(int d = 1, int m = 1, int y = 2000) : day(d), month(m), year(y) {}

    // Метод ввода даты
    void input() {
        cout << "Введите день, месяц и год (через пробел): ";
        cin >> day >> month >> year;
    }

    void display() const {
        cout << (day < 10 ? "0" : "") << day << "."
            << (month < 10 ? "0" : "") << month << "."
            << year;
    }

    // Геттеры (при необходимости)
    int getDay() const { return day; }
    int getMonth() const { return month; }
    int getYear() const { return year; }
};

// ==================== Класс Человек ====================
class Person {
private:
    int id;
    char* surname;
    char* name;
    char* patronymic;
    Date birthDate;
    static size_t count; // счётчик объектов

public:
    // Конструктор с параметрами (список инициализации)
    Person(int pid, const char* sname, const char* nm, const char* patr, const Date& bd)
        : id(pid), birthDate(bd) {
        surname = new char[strlen(sname) + 1];
        strcpy(surname, sname);
        name = new char[strlen(nm) + 1];
        strcpy(name, nm);
        patronymic = new char[strlen(patr) + 1];
        strcpy(patronymic, patr);
        ++count;
    }

    // Конструктор по умолчанию – делегирует конструктору с пустыми строками
    Person() : Person(0, "", "", "", Date()) {}

    // Конструктор копирования (глубокое копирование)
    Person(const Person& other)
        : id(other.id), birthDate(other.birthDate) {
        surname = new char[strlen(other.surname) + 1];
        strcpy(surname, other.surname);
        name = new char[strlen(other.name) + 1];
        strcpy(name, other.name);
        patronymic = new char[strlen(other.patronymic) + 1];
        strcpy(patronymic, other.patronymic);
        ++count;
    }

    // Деструктор
    ~Person() {
        delete[] surname;
        delete[] name;
        delete[] patronymic;
        --count;
    }

    // Статическая функция для подсчёта созданных экземпляров
    static size_t getCount() {
        return count;
    }

    // Сеттеры
    void setId(int newId) { id = newId; }
    void setSurname(const char* sname) {
        delete[] surname;
        surname = new char[strlen(sname) + 1];
        strcpy(surname, sname);
    }
    void setName(const char* nm) {
        delete[] name;
        name = new char[strlen(nm) + 1];
        strcpy(name, nm);
    }
    void setPatronymic(const char* patr) {
        delete[] patronymic;
        patronymic = new char[strlen(patr) + 1];
        strcpy(patronymic, patr);
    }
    void setBirthDate(const Date& bd) { birthDate = bd; }

    // Геттеры (возвращают копии или указатели)
    int getId() const { return id; }
    const char* getSurname() const { return surname; }
    const char* getName() const { return name; }
    const char* getPatronymic() const { return patronymic; }
    Date getBirthDate() const { return birthDate; }

    // Метод ввода информации о человеке
    void input() {
        cout << "Введите ID: ";
        cin >> id;
        char buffer[256];
        cout << "Введите фамилию: ";
        cin >> buffer;
        setSurname(buffer);
        cout << "Введите имя: ";
        cin >> buffer;
        setName(buffer);
        cout << "Введите отчество: ";
        cin >> buffer;
        setPatronymic(buffer);
        cout << "Введите дату рождения:" << endl;
        birthDate.input();
    }

    // Вывод информации о человеке
    void display() const {
        cout << "ID: " << id << ", ФИО: " << surname << " " << name << " " << patronymic
            << ", дата рождения: ";
        birthDate.display();
        cout << endl;
    }
};

// Определение статической переменной
size_t Person::count = 0;

// ==================== Класс Строка ====================
class MyString {
private:
    size_t length;   // длина строки без учёта '\0'
    char* str;       // динамический буфер

public:
    // Конструктор с параметром-строкой
    MyString(const char* s) {
        length = strlen(s);
        str = new char[length + 1];
        strcpy(str, s);
    }

    // Конструктор с параметром длина строки (создаёт пустую строку с запасом)
    explicit MyString(size_t len) {
        length = 0;
        str = new char[len + 1];
        str[0] = '\0';
    }

    // Конструктор копирования
    MyString(const MyString& other) {
        length = other.length;
        str = new char[length + 1];
        strcpy(str, other.str);
    }

    // Деструктор
    ~MyString() {
        delete[] str;
    }

    // Метод ввода строки с клавиатуры
    void input() {
        char buffer[1024];
        cout << "Введите строку: ";
        cin.ignore(); // очищаем буфер перед getline (если до этого был cin >>)
        cin.getline(buffer, 1024);
        set(buffer);
    }

    // Вывод строки на экран
    void display() const {
        cout << str;
    }

    // Сеттер (принимает const char*)
    void set(const char* s) {
        size_t newLen = strlen(s);
        if (newLen >= length) { // Не хватает места (включая '\0')
            delete[] str;
            str = new char[newLen + 1];
        }
        strcpy(str, s);
        length = newLen;
    }

    // Геттер для длины (опционально)
    size_t getLength() const { return length; }
};

int main() {
    setlocale(LC_ALL, "Russian");

    cout << "=== Ввод дроби ===" << endl;
    Fraction f;
    f.input();
    cout << "Вы ввели дробь: ";
    f.display();
    cout << "\n\n";

    cout << "=== Ввод информации о человеке ===" << endl;
    Person p;
    p.input();
    cout << "Вы ввели:" << endl;
    p.display();
    cout << endl;

    cout << "=== Ввод строки ===" << endl;
    MyString s(100); // буфер на 100 символов
    s.input();
    cout << "Вы ввели строку: ";
    s.display();
    cout << endl;

    return 0;
}