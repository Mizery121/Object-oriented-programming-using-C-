#include <iostream>
#include <cmath>
using namespace std;

class Fraction {
private:
    int numerator;      // числитель
    int denominator;    // знаменатель

    // Вспомогательная функция для нахождения НОД (наибольший общий делитель)
    int gcd(int a, int b) {
        a = abs(a);
        b = abs(b);
        while (b != 0) {
            int temp = b;
            b = a % b;
            a = temp;
        }
        return a;
    }

    // Функция для сокращения дроби
    void reduce() {
        if (denominator == 0) return; // защита от деления на ноль

        int divisor = gcd(numerator, denominator);
        numerator /= divisor;
        denominator /= divisor;

        // Оставляем знак только в числителе
        if (denominator < 0) {
            numerator = -numerator;
            denominator = -denominator;
        }
    }

public:
    // Конструкторы
    Fraction() : numerator(0), denominator(1) {}

    Fraction(int num, int denom) : numerator(num), denominator(denom) {
        if (denominator == 0) {
            cout << "Ошибка: знаменатель не может быть равен 0!" << endl;
            denominator = 1;
        }
        reduce();
    }

    // Функция для ввода данных
    void input() {
        cout << "Введите числитель: ";
        cin >> numerator;

        do {
            cout << "Введите знаменатель (не равный 0): ";
            cin >> denominator;
            if (denominator == 0) {
                cout << "Знаменатель не может быть равен 0! Повторите ввод." << endl;
            }
        } while (denominator == 0);

        reduce();
    }

    // Функция для вывода дроби
    void display() const {
        if (denominator == 1)
            cout << numerator;
        else if (numerator == 0)
            cout << 0;
        else
            cout << numerator << "/" << denominator;
    }

    // Арифметические операции
    Fraction add(const Fraction& other) const {
        int newNumerator = numerator * other.denominator + other.numerator * denominator;
        int newDenominator = denominator * other.denominator;
        return Fraction(newNumerator, newDenominator);
    }

    Fraction subtract(const Fraction& other) const {
        int newNumerator = numerator * other.denominator - other.numerator * denominator;
        int newDenominator = denominator * other.denominator;
        return Fraction(newNumerator, newDenominator);
    }

    Fraction multiply(const Fraction& other) const {
        int newNumerator = numerator * other.numerator;
        int newDenominator = denominator * other.denominator;
        return Fraction(newNumerator, newDenominator);
    }

    Fraction divide(const Fraction& other) const {
        if (other.numerator == 0) {
            cout << "Ошибка: деление на ноль!" << endl;
            return Fraction(0, 1);
        }
        int newNumerator = numerator * other.denominator;
        int newDenominator = denominator * other.numerator;
        return Fraction(newNumerator, newDenominator);
    }

    // Дополнительные операции
    Fraction power(int exponent) const {
        if (exponent == 0) return Fraction(1, 1);

        int newNumerator = pow(numerator, abs(exponent));
        int newDenominator = pow(denominator, abs(exponent));

        if (exponent < 0) {
            // Переворачиваем дробь при отрицательной степени
            swap(newNumerator, newDenominator);
        }

        return Fraction(newNumerator, newDenominator);
    }

    // Операции сравнения
    bool isEqual(const Fraction& other) const {
        return (numerator == other.numerator && denominator == other.denominator);
    }

    bool isGreater(const Fraction& other) const {
        return (numerator * other.denominator > other.numerator * denominator);
    }

    bool isLess(const Fraction& other) const {
        return (numerator * other.denominator < other.numerator * denominator);
    }

    // Преобразование в десятичную дробь
    double toDecimal() const {
        return static_cast<double>(numerator) / denominator;
    }

    // Геттеры (для доступа к закрытым членам)
    int getNumerator() const { return numerator; }
    int getDenominator() const { return denominator; }
};

// Демонстрация работы класса
int main() {
    setlocale(LC_ALL, "Russian");

    Fraction f1, f2;

    cout << "Введите первую дробь:" << endl;
    f1.input();

    cout << "Введите вторую дробь:" << endl;
    f2.input();

    cout << "\nПервая дробь: ";
    f1.display();
    cout << " = " << f1.toDecimal() << endl;

    cout << "Вторая дробь: ";
    f2.display();
    cout << " = " << f2.toDecimal() << endl;

    // Демонстрация арифметических операций
    Fraction result;

    result = f1.add(f2);
    cout << "\nСложение: ";
    f1.display();
    cout << " + ";
    f2.display();
    cout << " = ";
    result.display();
    cout << " = " << result.toDecimal() << endl;

    result = f1.subtract(f2);
    cout << "Вычитание: ";
    f1.display();
    cout << " - ";
    f2.display();
    cout << " = ";
    result.display();
    cout << " = " << result.toDecimal() << endl;

    result = f1.multiply(f2);
    cout << "Умножение: ";
    f1.display();
    cout << " * ";
    f2.display();
    cout << " = ";
    result.display();
    cout << " = " << result.toDecimal() << endl;

    result = f1.divide(f2);
    cout << "Деление: ";
    f1.display();
    cout << " / ";
    f2.display();
    cout << " = ";
    result.display();
    cout << " = " << result.toDecimal() << endl;

    // Дополнительные операции
    cout << "\nВозведение первой дроби в степень 2: ";
    result = f1.power(2);
    result.display();

    cout << "\nВозведение второй дроби в степень -1: ";
    result = f2.power(-1);
    result.display();

    // Операции сравнения
    cout << "\n\nСравнение дробей:" << endl;
    if (f1.isEqual(f2)) {
        cout << "Дроби равны" << endl;
    }
    else if (f1.isGreater(f2)) {
        cout << "Первая дробь больше второй" << endl;
    }
    else {
        cout << "Первая дробь меньше второй" << endl;
    }

    return 0;
}