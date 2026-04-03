#include <iostream>
#include <thread>
#include <chrono>
#include <clocale>

using namespace std;

// Класс-обёртка для потока с автоматическим join в деструкторе
class ThreadGuard {
public:
    // Запрещаем копирование
    ThreadGuard(const ThreadGuard&) = delete;
    ThreadGuard& operator=(const ThreadGuard&) = delete;

    // Конструктор: принимает вызываемый объект и его аргументы, запускает поток
    template<typename Callable, typename... Args>
    explicit ThreadGuard(Callable&& f, Args&&... args)
        : t(forward<Callable>(f), forward<Args>(args)...) {
    }

    // Деструктор: дожидаемся завершения потока, если он ещё присоединяем
    ~ThreadGuard() {
        if (t.joinable()) {
            t.join();
        }
    }

private:
    thread t;
};

// Пример функции для потока с задержкой
void slowFunction(int id, int delay_ms) {
    this_thread::sleep_for(chrono::milliseconds(delay_ms));
    cout << "Поток " << id << " завершился после задержки " << delay_ms << " мс\n";
}

// Пример быстрой функции
void fastFunction(int id) {
    cout << "Быстрый поток " << id << " выполнился\n";
}

int main() {
    setlocale(LC_ALL, "ru");
    cout << "Запуск демонстрации ThreadGuard\n";

    {
        // Первый поток с задержкой 500 мс
        ThreadGuard t1(slowFunction, 1, 500);
        // Второй быстрый поток
        ThreadGuard t2(fastFunction, 2);

        // Ещё один поток с лямбдой
        ThreadGuard t3([]() {
            cout << "Лямбда-поток выполнился\n";
            });

        cout << "Все потоки запущены, выходим из области видимости...\n";
    } // Здесь деструкторы t1, t2, t3 вызовут join()

    cout << "Все потоки завершены, программа завершается.\n";
    return 0;
}