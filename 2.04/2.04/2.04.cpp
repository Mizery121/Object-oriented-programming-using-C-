#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;

// ЗАДАНИЕ 1
class BankAccount {
private:
    string ownerName;
    double balance;

public:
    // Конструктор: выбрасывает invalid_argument, если начальный баланс отрицательный
    BankAccount(const string& name, double initialBalance)
        : ownerName(name), balance(initialBalance) {
        if (initialBalance < 0) {
            throw invalid_argument("Ошибка: начальный баланс не может быть отрицательным!");
        }
    }

    // Метод снятия денег
    void withdraw(double amount) {
        if (amount < 0) {
            throw invalid_argument("Ошибка: сумма снятия не может быть отрицательной!");
        }
        if (amount > balance) {
            throw runtime_error("Ошибка: недостаточно средств на счете!");
        }
        balance -= amount;
        cout << "Снято " << amount << " руб. Новый баланс: " << balance << endl;
    }

    // Геттер для баланса (для отладки)
    double getBalance() const { return balance; }
    string getOwnerName() const { return ownerName; }
};

// ЗАДАНИЕ 2
// Собственное исключение для деления на ноль
class DivisionByZeroException : public exception {
public:
    const char* what() const noexcept override {
        return "Ошибка: деление на ноль!";
    }
};

class SafeDivision {
public:
    // Статический метод деления
    static double divide(double a, double b) {
        if (b == 0.0) {
            throw DivisionByZeroException();
        }
        return a / b;
    }
};

int main() {
    setlocale(LC_ALL, "rus");

    cout << "========== ЗАДАНИЕ 1: BankAccount ==========\n";

    // Создание счета с отрицательным балансом (выбросит исключение)
    try {
        BankAccount acc1("Иван", -100);
    }
    catch (const invalid_argument& e) {
        cout << "Исключение при создании счета: " << e.what() << endl;
    }

    // Корректное создание счета
    BankAccount acc2("Петр", 500);
    cout << "Счет " << acc2.getOwnerName() << " создан. Баланс: " << acc2.getBalance() << endl;

    // Попытка снять отрицательную сумму
    try {
        acc2.withdraw(-50);
    }
    catch (const invalid_argument& e) {
        cout << "Исключение при снятии: " << e.what() << endl;
    }

    // Попытка снять больше, чем есть
    try {
        acc2.withdraw(1000);
    }
    catch (const runtime_error& e) {
        cout << "Исключение при снятии: " << e.what() << endl;
    }

    // Корректное снятие
    try {
        acc2.withdraw(200);
    }
    catch (const exception& e) {
        cout << "Неожиданное исключение: " << e.what() << endl;
    }

    cout << "\n========== ЗАДАНИЕ 2: SafeDivision ==========\n";

    // Деление на ноль
    try {
        double result = SafeDivision::divide(10, 0);
        cout << "Результат: " << result << endl;
    }
    catch (const DivisionByZeroException& e) {
        cout << "Перехвачено DivisionByZeroException: " << e.what() << endl;
    }

    // Корректное деление
    try {
        double result = SafeDivision::divide(10, 2);
        cout << "10 / 2 = " << result << endl;
    }
    catch (const DivisionByZeroException& e) {
        cout << e.what() << endl;
    }

    // Деление с дробными числами
    try {
        double result = SafeDivision::divide(7.5, 2.5);
        cout << "7.5 / 2.5 = " << result << endl;
    }
    catch (const DivisionByZeroException& e) {
        cout << e.what() << endl;
    }

    return 0;
}