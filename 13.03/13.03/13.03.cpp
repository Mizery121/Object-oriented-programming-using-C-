#include <iostream>
#include <cmath>
#include <stdexcept>
#include <cstring>

using namespace std;

// Встреча 11, задание №1: шаблон для среднего арифметического массива

template<typename T>
double average(const T* arr, size_t size) {
    if (size == 0) return 0.0;
    double sum = 0.0;
    for (size_t i = 0; i < size; ++i) {
        sum += static_cast<double>(arr[i]);
    }
    return sum / size;
}


// Встреча 11, задание №2: перегруженные шаблоны для решения уравнений


// Линейное уравнение a*x + b = 0
// Возвращает количество корней (0, 1, бесконечность) и значение корня через root
// Особые случаи: a==0, b==0 -> бесконечно много корней; a==0, b!=0 -> нет корней
template<typename T>
int solve(const T& a, const T& b, double& root) {
    if (a == 0) {
        if (b == 0) return -1;   // бесконечно много корней
        else return 0;           // нет корней
    }
    root = -static_cast<double>(b) / static_cast<double>(a);
    return 1;
}

// Квадратное уравнение a*x^2 + b*x + c = 0
// Возвращает количество вещественных корней (0,1,2) и заполняет x1, x2
template<typename T>
int solve(const T& a, const T& b, const T& c, double& x1, double& x2) {
    if (a == 0) {
        // вырождается в линейное
        return solve(b, c, x1);
    }
    double A = static_cast<double>(a);
    double B = static_cast<double>(b);
    double C = static_cast<double>(c);
    double disc = B * B - 4 * A * C;
    if (disc < 0) return 0;
    if (disc == 0) {
        x1 = -B / (2 * A);
        return 1;
    }
    double sqrt_disc = sqrt(disc);
    x1 = (-B - sqrt_disc) / (2 * A);
    x2 = (-B + sqrt_disc) / (2 * A);
    return 2;
}


// Встреча 12, задание 1: шаблонный класс-контейнер Array

template<typename T>
class Array {
private:
    T* data;          // указатель на динамический массив
    size_t capacity;  // текущая выделенная память (размер массива)
    size_t count;     // количество реально хранимых элементов
    int grow;         // шаг роста (увеличивается на grow при нехватке места)

    void resize(size_t newCapacity) {
        T* newData = new T[newCapacity];
        // копируем существующие элементы
        for (size_t i = 0; i < count; ++i) {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
        capacity = newCapacity;
    }

public:
    // Конструктор
    Array(int initialSize = 0, int growBy = 1)
        : data(nullptr), capacity(0), count(0), grow(growBy > 0 ? growBy : 1) {
        if (initialSize > 0) {
            data = new T[initialSize];
            capacity = initialSize;
        }
    }

    // Деструктор
    ~Array() {
        delete[] data;
    }

    // Конструктор копирования
    Array(const Array& other)
        : data(nullptr), capacity(0), count(0), grow(other.grow) {
        if (other.capacity > 0) {
            data = new T[other.capacity];
            capacity = other.capacity;
            count = other.count;
            for (size_t i = 0; i < count; ++i) {
                data[i] = other.data[i];
            }
        }
    }

    // Оператор присваивания
    Array& operator=(const Array& other) {
        if (this != &other) {
            delete[] data;
            grow = other.grow;
            capacity = other.capacity;
            count = other.count;
            if (capacity > 0) {
                data = new T[capacity];
                for (size_t i = 0; i < count; ++i) {
                    data[i] = other.data[i];
                }
            }
            else {
                data = nullptr;
            }
        }
        return *this;
    }

    // Получение размера массива (capacity)
    size_t GetSize() const {
        return capacity;
    }

    // Установка нового размера массива
    void SetSize(int newSize, int growBy = 1) {
        if (newSize < 0) return;
        if (growBy > 0) grow = growBy;
        size_t newCap = static_cast<size_t>(newSize);
        if (newCap > capacity) {
            // увеличиваем память
            resize(newCap);
        }
        else if (newCap < capacity) {
            // уменьшаем память, теряем элементы, если нужно
            if (newCap < count) count = newCap;
            T* newData = new T[newCap];
            for (size_t i = 0; i < count; ++i) {
                newData[i] = data[i];
            }
            delete[] data;
            data = newData;
            capacity = newCap;
        }
    }

    // Последний допустимый индекс (count-1, если есть элементы)
    int GetUpperBound() const {
        return (count == 0) ? -1 : static_cast<int>(count - 1);
    }

    // Проверка, пуст ли массив
    bool IsEmpty() const {
        return count == 0;
    }

    // Удалить лишнюю память (выше последнего допустимого индекса)
    void FreeExtra() {
        if (capacity > count) {
            resize(count);
        }
    }

    // Удалить все элементы (но память остаётся)
    void RemoveAll() {
        count = 0;
    }

    // Получение элемента по индексу (без проверки границ – быстрый доступ)
    T GetAt(size_t index) const {
        if (index >= count) throw out_of_range("Index out of range");
        return data[index];
    }

    // Установка элемента по индексу
    void SetAt(size_t index, const T& value) {
        if (index >= count) throw out_of_range("Index out of range");
        data[index] = value;
    }

    // Оператор [] (чтение и запись)
    T& operator[](size_t index) {
        if (index >= count) throw out_of_range("Index out of range");
        return data[index];
    }

    const T& operator[](size_t index) const {
        if (index >= count) throw out_of_range("Index out of range");
        return data[index];
    }

    // Добавление элемента в конец
    void Add(const T& value) {
        if (count >= capacity) {
            // нужен рост
            size_t newCap = capacity + (capacity > 0 ? grow : 1);
            resize(newCap);
        }
        data[count++] = value;
    }

    // Присоединение другого массива
    void Append(const Array& other) {
        for (size_t i = 0; i < other.count; ++i) {
            Add(other.data[i]);
        }
    }

    // Получение указателя на внутренние данные
    T* GetData() const {
        return data;
    }

    // Вставка одного элемента в позицию index
    void InsertAt(size_t index, const T& value) {
        if (index > count) throw out_of_range("Index out of range");
        if (count >= capacity) {
            size_t newCap = capacity + (capacity > 0 ? grow : 1);
            resize(newCap);
        }
        // сдвигаем элементы вправо
        for (size_t i = count; i > index; --i) {
            data[i] = data[i - 1];
        }
        data[index] = value;
        ++count;
    }

    // Вставка нескольких элементов из другого массива, начиная с позиции index
    void InsertAt(size_t index, const Array& other) {
        if (index > count) throw out_of_range("Index out of range");
        size_t otherSize = other.count;
        if (otherSize == 0) return;

        // гарантируем место
        if (count + otherSize > capacity) {
            size_t needed = count + otherSize;
            size_t newCap = capacity;
            while (newCap < needed) {
                newCap += (newCap > 0 ? grow : 1);
            }
            resize(newCap);
        }
        // сдвигаем существующие элементы, начиная с конца
        for (size_t i = count; i > index; --i) {
            data[i + otherSize - 1] = data[i - 1];
        }
        // копируем вставляемые элементы
        for (size_t i = 0; i < otherSize; ++i) {
            data[index + i] = other.data[i];
        }
        count += otherSize;
    }

    // Удаление одного элемента по индексу
    void RemoveAt(size_t index) {
        if (index >= count) throw out_of_range("Index out of range");
        for (size_t i = index; i < count - 1; ++i) {
            data[i] = data[i + 1];
        }
        --count;
    }

    // Удаление нескольких элементов, начиная с index, количество countToRemove
    void RemoveAt(size_t index, size_t countToRemove) {
        if (index >= count) throw out_of_range("Index out of range");
        if (countToRemove == 0) return;
        if (index + countToRemove > count) countToRemove = count - index;
        for (size_t i = index; i + countToRemove < count; ++i) {
            data[i] = data[i + countToRemove];
        }
        count -= countToRemove;
    }

    // Вспомогательная функция для вывода (для демонстрации)
    void Print() const {
        for (size_t i = 0; i < count; ++i) {
            cout << data[i] << " ";
        }
        cout << endl;
    }
};

int main() {
    setlocale(LC_ALL, "RU");
    cout << "========== Задание 11.1: среднее арифметическое ==========\n";
    int intArr[] = { 1, 2, 3, 4, 5 };
    double doubleArr[] = { 1.5, 2.5, 3.5 };
    cout << "Среднее int: " << average(intArr, 5) << endl;
    cout << "Среднее double: " << average(doubleArr, 3) << endl;

    cout << "\n========== Задание 11.2: решение уравнений ==========\n";
    double root;
    int res = solve(2.0, 5.0, root);
    cout << "2x+5=0: корней=" << res << " корень=" << root << endl;
    double x1, x2;
    res = solve(1.0, -3.0, 2.0, x1, x2);
    cout << "x^2 -3x +2=0: корней=" << res << " корни=" << x1 << ", " << x2 << endl;

    cout << "\n========== Задание 12.1: шаблонный класс Array ==========\n";
    Array<int> arr;
    arr.Add(10);
    arr.Add(20);
    arr.Add(30);
    cout << "Массив: ";
    arr.Print();
    cout << "GetSize(): " << arr.GetSize() << " (выделенная память)\n";
    cout << "GetUpperBound(): " << arr.GetUpperBound() << endl;
    cout << "IsEmpty(): " << arr.IsEmpty() << endl;
    arr.SetSize(5, 2);
    cout << "После SetSize(5): GetSize()=" << arr.GetSize() << endl;
    arr.Add(40);
    arr.Add(50);
    arr.Add(60); // должен сработать grow (2)
    cout << "После добавления 40,50,60: ";
    arr.Print();
    cout << "GetSize() стало: " << arr.GetSize() << endl;

    Array<int> arr2;
    arr2.Add(100);
    arr2.Add(200);
    arr.Append(arr2);
    cout << "После Append: ";
    arr.Print();

    arr.InsertAt(2, 999);
    cout << "После InsertAt(2, 999): ";
    arr.Print();

    arr.RemoveAt(3);
    cout << "После RemoveAt(3): ";
    arr.Print();

    cout << "Элемент [1] через operator[]: " << arr[1] << endl;
    arr[1] = 777;
    cout << "После изменения arr[1]=777: ";
    arr.Print();

    arr.FreeExtra();
    cout << "После FreeExtra(): GetSize()=" << arr.GetSize() << endl;

    return 0;
}