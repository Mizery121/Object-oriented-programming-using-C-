#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <cmath>

using namespace std;

// функции для дат
bool isLeap(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int daysInMonth(int month, int year) {
    if (month == 2) return isLeap(year) ? 29 : 28;
    if (month == 4 || month == 6 || month == 9 || month == 11) return 30;
    return 31;
}

// Задание 1
class Date {
private:
    int day, month, year;

    // Преобразование даты в количество дней от 01.01.0001
    long long toDays() const {
        long long total = 0;
        for (int y = 1; y < year; ++y)
            total += isLeap(y) ? 366 : 365;
        for (int m = 1; m < month; ++m)
            total += daysInMonth(m, year);
        total += day;
        return total;
    }

    // Преобразование дней обратно в дату (начиная с 01.01.0001)
    static Date fromDays(long long days) {
        int y = 1;
        while (days > (isLeap(y) ? 366LL : 365LL)) {
            days -= isLeap(y) ? 366 : 365;
            ++y;
        }
        int m = 1;
        while (days > daysInMonth(m, y)) {
            days -= daysInMonth(m, y);
            ++m;
        }
        int d = static_cast<int>(days);
        return Date(d, m, y);
    }

public:
    Date(int d = 1, int m = 1, int y = 2000) : day(d), month(m), year(y) {}

    // Разность двух дат – абсолютное количество дней между ними
    long long operator-(const Date& other) const {
        return llabs(toDays() - other.toDays());
    }

    // Увеличение даты на заданное количество дней
    Date operator+(long long days) const {
        long long newDays = toDays() + days;
        return fromDays(newDays);
    }

    Date& operator+=(long long days) {
        *this = *this + days;
        return *this;
    }

    // Уменьшение даты на заданное количество дней
    Date operator-(long long days) const {
        return *this + (-days);
    }

    Date& operator-=(long long days) {
        *this = *this - days;
        return *this;
    }

    friend ostream& operator<<(ostream& os, const Date& d) {
        os << d.day << '.' << d.month << '.' << d.year;
        return os;
    }

    friend istream& operator>>(istream& is, Date& d) {
        char dot;
        is >> d.day >> dot >> d.month >> dot >> d.year;
        return is;
    }
};

// Задание 2
class String {
private:
    char* str;
    size_t length;

public:
    String() : str(nullptr), length(0) {}

    String(const char* s) {
        length = strlen(s);
        str = new char[length + 1];
        strcpy(str, s);
    }

    String(const String& other) : length(other.length) {
        str = new char[length + 1];
        strcpy(str, other.str);
    }

    ~String() {
        delete[] str;
    }

    String& operator=(const String& other) {
        if (this != &other) {
            delete[] str;
            length = other.length;
            str = new char[length + 1];
            strcpy(str, other.str);
        }
        return *this;
    }

    // Оператор * – пересечение символов (общие символы без повторений)
    String operator*(const String& other) const {
        bool used[256] = { false };
        size_t resultLength = 0;
        for (size_t i = 0; i < length; ++i) {
            unsigned char ch = static_cast<unsigned char>(str[i]);
            if (!used[ch] && other.contains(str[i])) {
                used[ch] = true;
                ++resultLength;
            }
        }
        char* resultStr = new char[resultLength + 1];
        // Сбрасываем used для повторного заполнения
        for (int i = 0; i < 256; ++i) used[i] = false;
        size_t pos = 0;
        for (size_t i = 0; i < length; ++i) {
            unsigned char ch = static_cast<unsigned char>(str[i]);
            if (!used[ch] && other.contains(str[i])) {
                resultStr[pos++] = str[i];
                used[ch] = true;
            }
        }
        resultStr[pos] = '\0';
        String result(resultStr);
        delete[] resultStr;
        return result;
    }

    bool contains(char c) const {
        for (size_t i = 0; i < length; ++i)
            if (str[i] == c) return true;
        return false;
    }

    friend ostream& operator<<(ostream& os, const String& s) {
        if (s.str) os << s.str;
        return os;
    }

    friend istream& operator>>(istream& is, String& s) {
        char buffer[1024];
        is >> buffer;
        delete[] s.str;
        s.length = strlen(buffer);
        s.str = new char[s.length + 1];
        strcpy(s.str, buffer);
        return is;
    }
};

int main() {
    setlocale(LC_ALL, "Russian");

    cout << "********** Задание 1: Класс Date **********\n";
    Date d1, d2;
    cout << "Введите первую дату (дд.мм.гггг): ";
    cin >> d1;
    cout << "Введите вторую дату: ";
    cin >> d2;
    cout << "Разница между датами: " << (d1 - d2) << " дней\n";

    int days;
    cout << "Введите количество дней для увеличения первой даты: ";
    cin >> days;
    Date d3 = d1 + days;
    cout << "Новая дата: " << d3 << endl;

    cout << "\n********** Задание 2: Класс String (пересечение строк) **********\n";
    String s1, s2;
    cout << "Введите первую строку: ";
    cin >> s1;
    cout << "Введите вторую строку: ";
    cin >> s2;
    String s3 = s1 * s2;
    cout << "Пересечение строк (общие символы): \"" << s3 << "\"\n";

    return 0;
}