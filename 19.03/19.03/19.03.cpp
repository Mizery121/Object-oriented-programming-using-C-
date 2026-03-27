#include <iostream>
#include <cmath>

using namespace std;

class Complex {
private:
    double real;   // действительная часть
    double imag;   // мнимая часть

public:
    // Конструкторы
    Complex(double r = 0.0, double i = 0.0) : real(r), imag(i) {}
    Complex(const Complex& other) : real(other.real), imag(other.imag) {}

    // Оператор () – возвращает модуль комплексного числа (другая реализация по желанию)
    double operator()() const {
        return sqrt(real * real + imag * imag);
    }

    // Дружественные функции (объявлены внутри класса)
    friend istream& operator>>(istream& in, Complex& c);
    friend ostream& operator<<(ostream& out, const Complex& c);
    friend Complex operator+(const Complex& a, const Complex& b);
    friend Complex operator-(const Complex& a, const Complex& b);
    friend bool operator==(const Complex& a, const Complex& b);
    friend bool operator!=(const Complex& a, const Complex& b);
};

// Перегрузка оператора ввода
istream& operator>>(istream& in, Complex& c) {
    cout << "Введите действительную и мнимую части: ";
    in >> c.real >> c.imag;
    return in;
}

// Перегрузка оператора вывода
ostream& operator<<(ostream& out, const Complex& c) {
    out << c.real;
    if (c.imag >= 0) out << "+";
    out << c.imag << "i";
    return out;
}

// Сложение
Complex operator+(const Complex& a, const Complex& b) {
    return Complex(a.real + b.real, a.imag + b.imag);
}

// Вычитание
Complex operator-(const Complex& a, const Complex& b) {
    return Complex(a.real - b.real, a.imag - b.imag);
}

// Равенство
bool operator==(const Complex& a, const Complex& b) {
    return (a.real == b.real && a.imag == b.imag);
}

// Неравенство
bool operator!=(const Complex& a, const Complex& b) {
    return !(a == b);
}

int main() {
    setlocale(LC_ALL, "RU");
    Complex c1, c2;
    cout << "Введите первое комплексное число:\n";
    cin >> c1;
    cout << "Введите второе комплексное число:\n";
    cin >> c2;

    cout << "\nc1 = " << c1 << endl;
    cout << "c2 = " << c2 << endl;
    cout << "c1 + c2 = " << c1 + c2 << endl;
    cout << "c1 - c2 = " << c1 - c2 << endl;
    cout << "c1 == c2 ? " << (c1 == c2 ? "Да" : "Нет") << endl;
    cout << "c1 != c2 ? " << (c1 != c2 ? "Да" : "Нет") << endl;
    cout << "Модуль c1: " << c1() << endl;
    cout << "Модуль c2: " << c2() << endl;

    return 0;
}