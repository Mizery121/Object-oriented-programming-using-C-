#include <iostream>
#include <memory>
#include <chrono>
#include <thread>   // нужно для sleep_for
#include <clocale>

using namespace std;
using namespace chrono;

class Timer {
public:
    Timer() : start(steady_clock::now()) {
        cout << "Таймер создан\n";
    }

    ~Timer() {
        auto end = steady_clock::now();
        auto duration = duration_cast<milliseconds>(end - start).count();
        cout << "Таймер уничтожен. Прошло " << duration << " мс\n";
    }

private:
    steady_clock::time_point start;
};

// Функция, возвращающая unique_ptr<Timer>
unique_ptr<Timer> createTimer() {
    return make_unique<Timer>();
}

int main() {
    setlocale(LC_ALL, "ru");

    cout << "=== Демонстрация unique_ptr ===" << endl;

    {
        cout << "Вход в блок..." << endl;
        auto ptr = createTimer();   // создаём таймер
        cout << "Таймер управляется unique_ptr, работаем..." << endl;
        this_thread::sleep_for(milliseconds(600)); // имитируем работу
        cout << "Выход из блока..." << endl;
    } // здесь ptr уничтожается, вызывается деструктор Timer

    cout << "Блок закончен, таймер уже удалён автоматически." << endl;

    return 0;
}