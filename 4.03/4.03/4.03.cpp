#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

// ==================== Класс String (Задание 1) ====================
class String {
private:
    char* str;      // указатель на динамический буфер
    size_t length;  // текущая длина строки (без учёта '\0')
    size_t capacity;// размер выделенной памяти (включая '\0')

public:
    // Конструктор по умолчанию (строка на 80 символов)
    String() : String(80) {}

    // Конструктор, создающий строку заданного размера (ёмкость)
    explicit String(size_t size)
        : capacity(size + 1), length(0) {
        str = new char[capacity];
        str[0] = '\0';
        cout << "String(char) constructor, capacity = " << capacity - 1 << endl;
    }

    // Конструктор, инициализирующий строку литералом
    String(const char* s)
        : String(strlen(s)) {   // делегирование конструктору с размером
        strcpy(str, s);
        length = strlen(s);
        cout << "String(const char*) constructor: " << str << endl;
    }

    // Конструктор копирования (глубокое копирование)
    String(const String& other)
        : capacity(other.capacity), length(other.length) {
        str = new char[capacity];
        strcpy(str, other.str);
        cout << "String copy constructor: " << str << endl;
    }

    // Деструктор
    ~String() {
        cout << "String destructor: " << str << endl;
        delete[] str;
    }

    // Метод ввода строки с клавиатуры (с учётом размера буфера)
    void input() {
        cout << "Введите строку (макс. " << capacity - 1 << " символов): ";
        cin.getline(str, capacity);
        length = strlen(str);
    }

    // Метод вывода строки на экран
    void display() const {
        cout << str;
    }

    // Геттер длины
    size_t getLength() const { return length; }
};

// ==================== Класс Array (Задание 2) ====================
class Array {
private:
    int* data;      // указатель на динамический массив
    size_t size;    // текущий размер массива

public:
    // Конструктор по умолчанию (пустой массив)
    Array() : size(0), data(nullptr) {
        cout << "Array() constructor" << endl;
    }

    // Конструктор с размером (выделяет память, не инициализирует)
    explicit Array(size_t n) : size(n) {
        data = new int[size];
        cout << "Array(size_t) constructor, size = " << size << endl;
    }

    // Конструктор копирования (глубокое копирование)
    Array(const Array& other) : size(other.size) {
        data = new int[size];
        for (size_t i = 0; i < size; ++i)
            data[i] = other.data[i];
        cout << "Array copy constructor" << endl;
    }

    // Деструктор
    ~Array() {
        cout << "Array destructor, size = " << size << endl;
        delete[] data;
    }

    // Оператор присваивания (для полноты правила трёх)
    Array& operator=(const Array& other) {
        cout << "Array assignment operator" << endl;
        if (this != &other) {          // проверка на самоприсваивание (использование this)
            delete[] data;              // освобождаем старую память
            size = other.size;
            data = new int[size];
            for (size_t i = 0; i < size; ++i)
                data[i] = other.data[i];
        }
        return *this;                   // возврат ссылки на текущий объект
    }

    // Заполнение массива значениями
    void fill(int value) {
        for (size_t i = 0; i < size; ++i)
            data[i] = value;
    }

    // Заполнение массива последовательностью 0,1,2,...
    void fillSequence() {
        for (size_t i = 0; i < size; ++i)
            data[i] = i;
    }

    // Вывод массива на экран
    void print() const {
        cout << "[";
        for (size_t i = 0; i < size; ++i) {
            if (i > 0) cout << ", ";
            cout << data[i];
        }
        cout << "]" << endl;
    }

    // Изменение размера массива (с сохранением данных, новые элементы = 0)
    void resize(size_t newSize) {
        int* newData = new int[newSize];
        size_t copySize = (newSize < size) ? newSize : size;
        for (size_t i = 0; i < copySize; ++i)
            newData[i] = data[i];
        for (size_t i = copySize; i < newSize; ++i)
            newData[i] = 0;
        delete[] data;
        data = newData;
        size = newSize;
    }

    // Сортировка массива (пузырьковая для простоты)
    void sort() {
        for (size_t i = 0; i < size - 1; ++i) {
            for (size_t j = 0; j < size - i - 1; ++j) {
                if (data[j] > data[j + 1]) {
                    int tmp = data[j];
                    data[j] = data[j + 1];
                    data[j + 1] = tmp;
                }
            }
        }
    }

    // Минимальное значение
    int min() const {
        if (size == 0) return 0; // или выбросить исключение
        int m = data[0];
        for (size_t i = 1; i < size; ++i)
            if (data[i] < m) m = data[i];
        return m;
    }

    // Максимальное значение
    int max() const {
        if (size == 0) return 0;
        int m = data[0];
        for (size_t i = 1; i < size; ++i)
            if (data[i] > m) m = data[i];
        return m;
    }

    // Геттер размера
    size_t getSize() const { return size; }
};


int main() {
    setlocale(LC_ALL, "Russian");

    cout << "********** Демонстрация класса String **********" << endl;
    String s1;                       // по умолчанию (80)
    String s2("Привет, мир!");       // из литерала
    String s3 = s2;                   // копирование (глубокое)

    cout << "s2 = "; s2.display(); cout << endl;
    cout << "s3 (копия) = "; s3.display(); cout << endl;

    cout << "\nВвод строки для s1:" << endl;
    s1.input();
    cout << "s1 = "; s1.display(); cout << endl;

    // Показываем опасность побитового копирования (если бы не было конструктора копирования)
    cout << "\nЕсли бы не было конструктора копирования, то при побитовом копировании" << endl;
    cout << "s2 и s3 указывали бы на одну память, и деструктор удалил бы её дважды." << endl;
    cout << "Благодаря глубокому копированию каждый объект владеет своей памятью.\n" << endl;

    cout << "\n********** Демонстрация класса Array **********" << endl;
    Array arr1(5);                    // массив из 5 элементов
    arr1.fillSequence();
    cout << "arr1: "; arr1.print();

    Array arr2 = arr1;                 // копирование
    cout << "arr2 (копия): "; arr2.print();

    arr2.resize(8);
    cout << "arr2 после resize(8): "; arr2.print();

    arr2.fill(10);
    cout << "arr2 после fill(10): "; arr2.print();

    arr1.sort();
    cout << "arr1 после сортировки: "; arr1.print();
    cout << "min arr1 = " << arr1.min() << ", max arr1 = " << arr1.max() << endl;

    // Показываем использование оператора присваивания
    Array arr3;
    arr3 = arr2;                       // присваивание
    cout << "arr3 (после arr3 = arr2): "; arr3.print();

    cout << "\nЗавершение программы. Начинается разрушение объектов." << endl;
    return 0;
}