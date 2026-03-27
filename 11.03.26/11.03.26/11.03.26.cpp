#include <iostream>
#include <cstring>
#include <sstream>

using namespace std;

class Array {
private:
    int* data;
    size_t size;

public:
    // Конструктор
    Array(size_t s = 0) : size(s) {
        data = new int[size](); // Инициализация нулями
    }

    // Деструктор
    ~Array() {
        delete[] data;
    }

    // Конструктор копирования
    Array(const Array& other) : size(other.size) {
        data = new int[size];
        for (size_t i = 0; i < size; ++i)
            data[i] = other.data[i];
    }

    // Оператор присваивания
    Array& operator=(const Array& other) {
        if (this != &other) {
            delete[] data;
            size = other.size;
            data = new int[size];
            for (size_t i = 0; i < size; ++i)
                data[i] = other.data[i];
        }
        return *this;
    }

    // Перегрузка оператора [] – доступ по индексу
    int& operator[](size_t index) {
        if (index >= size)
            throw out_of_range("Index out of range");
        return data[index];
    }

    const int& operator[](size_t index) const {
        if (index >= size)
            throw out_of_range("Index out of range");
        return data[index];
    }

    // Перегрузка оператора () – увеличение всех элементов на value
    void operator()(int value) {
        for (size_t i = 0; i < size; ++i)
            data[i] += value;
    }

    // Преобразование к int – сумма элементов
    operator int() const {
        int sum = 0;
        for (size_t i = 0; i < size; ++i)
            sum += data[i];
        return sum;
    }

    // Преобразование к char* – строковое представление элементов
    operator char* () const {
        ostringstream oss;
        for (size_t i = 0; i < size; ++i) {
            if (i != 0) oss << ", ";
            oss << data[i];
        }
        string str = oss.str();
        char* result = new char[str.size() + 1];
        // Используем memcpy вместо strcpy для устранения предупреждения C4996
        memcpy(result, str.c_str(), str.size() + 1);
        return result;
    }

    // Вспомогательный метод для вывода
    void print() const {
        for (size_t i = 0; i < size; ++i)
            cout << data[i] << ' ';
        cout << endl;
    }

    // Метод для изменения размера (для удобства)
    void resize(size_t newSize) {
        int* newData = new int[newSize]();
        size_t minSize = (newSize < size) ? newSize : size;
        for (size_t i = 0; i < minSize; ++i)
            newData[i] = data[i];
        delete[] data;
        data = newData;
        size = newSize;
    }
};

// Пример использования
int main() {
    setlocale(LC_ALL, "RU");
    try {
        Array arr(5);
        for (size_t i = 0; i < 5; ++i)
            arr[i] = static_cast<int>(i + 1); // Явное приведение типа для наглядности

        cout << "Исходный массив: ";
        arr.print();

        cout << "Элемент с индексом 2: " << arr[2] << endl;

        arr(10);
        cout << "После увеличения на 10: ";
        arr.print();

        int sum = arr;
        cout << "Сумма элементов: " << sum << endl;

        char* str = arr;
        cout << "Строковое представление: " << str << endl;
        delete[] str; // Освобождаем память, выделенную в operator char*()

    }
    catch (const exception& e) {
        cerr << "Ошибка: " << e.what() << endl;
    }

    return 0;
}