#include <iostream>
#include <algorithm>  // copy, fill_n
#include <vector>     // vector
#include <utility>    // move

using namespace std;

// ============================ Задание 1 ============================
namespace task1 {
    class IntArray {
    private:
        int* data;
        size_t size;

    public:
        // Конструктор по умолчанию: создаёт пустой массив
        IntArray() : data(nullptr), size(0) {
            cout << "IntArray: Default constructor\n";
        }

        // Конструктор от размера: выделяет память под n элементов и заполняет нулями
        explicit IntArray(size_t n) : data(new int[n]), size(n) {
            fill_n(data, n, 0);
            cout << "IntArray: Size constructor (size = " << size << ")\n";
        }

        // Конструктор копирования: глубокое копирование
        IntArray(const IntArray& other) : data(new int[other.size]), size(other.size) {
            copy(other.data, other.data + size, data);
            cout << "IntArray: Copy constructor\n";
        }

        // Конструктор перемещения: передача владения, источник обнуляется
        IntArray(IntArray&& other) noexcept : data(other.data), size(other.size) {
            other.data = nullptr;
            other.size = 0;
            cout << "IntArray: Move constructor\n";
        }

        // Деструктор: освобождает память
        ~IntArray() {
            delete[] data;
            cout << "IntArray: Destructor\n";
        }

        // Оператор присваивания копированием (сначала выделяем новую память, чтобы не испортить объект при исключении)
        IntArray& operator=(const IntArray& other) {
            if (this != &other) {
                int* newData = new int[other.size];
                copy(other.data, other.data + other.size, newData);
                delete[] data;
                data = newData;
                size = other.size;
                cout << "IntArray: Copy assignment\n";
            }
            else {
                cout << "IntArray: Copy assignment (self-assignment)\n";
            }
            return *this;
        }

        // Оператор присваивания перемещением
        IntArray& operator=(IntArray&& other) noexcept {
            if (this != &other) {
                delete[] data;
                data = other.data;
                size = other.size;
                other.data = nullptr;
                other.size = 0;
                cout << "IntArray: Move assignment\n";
            }
            else {
                cout << "IntArray: Move assignment (self-assignment)\n";
            }
            return *this;
        }

        // Метод для отладки: выводит элементы массива
        void print() const {
            cout << "[";
            for (size_t i = 0; i < size; ++i) {
                cout << data[i];
                if (i + 1 < size) cout << ", ";
            }
            cout << "]\n";
        }
    };
}

// ============================ Задание 4 ============================
namespace task4 {
    class Buffer {
        int* data;
        size_t size;

    public:
        Buffer(size_t n) : data(new int[n]), size(n) {
            cout << "Buffer: Constructor (size = " << n << ")\n";
        }

        ~Buffer() {
            delete[] data;
            cout << "Buffer: Destructor\n";
        }

        // Конструктор копирования
        Buffer(const Buffer& other) : data(new int[other.size]), size(other.size) {
            copy(other.data, other.data + size, data);
            cout << "Buffer: Copy constructor\n";
        }

        // Конструктор перемещения (noexcept)
        Buffer(Buffer&& other) noexcept : data(other.data), size(other.size) {
            other.data = nullptr;
            other.size = 0;
            cout << "Buffer: Move constructor\n";
        }

        // Оператор присваивания копированием
        Buffer& operator=(const Buffer& other) {
            if (this != &other) {
                int* newData = new int[other.size];
                copy(other.data, other.data + other.size, newData);
                delete[] data;
                data = newData;
                size = other.size;
                cout << "Buffer: Copy assignment\n";
            }
            return *this;
        }

        // Оператор присваивания перемещением (noexcept)
        Buffer& operator=(Buffer&& other) noexcept {
            if (this != &other) {
                delete[] data;
                data = other.data;
                size = other.size;
                other.data = nullptr;
                other.size = 0;
                cout << "Buffer: Move assignment\n";
            }
            return *this;
        }
    };
}

int main() {
    setlocale(LC_ALL, "RU");
    cout << "========== Демонстрация IntArray (Задание 1) ==========\n";
    {
        using namespace task1;

        cout << "\n--- Создание объектов ---\n";
        IntArray a1;                     // default constructor
        IntArray a2(5);                  // size constructor
        a2.print();

        cout << "\n--- Копирование ---\n";
        IntArray a3(a2);                 // copy constructor
        a3.print();

        cout << "\n--- Перемещение из временного объекта ---\n";
        IntArray a4(IntArray(3));        // move constructor (temporary)
        a4.print();

        cout << "\n--- Перемещение с std::move ---\n";
        IntArray a5(move(a2));           // move constructor
        a5.print();
        cout << "a2 после перемещения: ";
        a2.print();

        cout << "\n--- Присваивание копированием ---\n";
        IntArray a6;
        a6 = a3;                         // copy assignment
        a6.print();

        cout << "\n--- Присваивание перемещением (временный) ---\n";
        a6 = IntArray(2);                // move assignment
        a6.print();

        cout << "\n--- Присваивание перемещением (std::move) ---\n";
        IntArray a7;
        a7 = move(a5);                   // move assignment
        a7.print();
        cout << "a5 после перемещения: ";
        a5.print();
    }
    cout << "\n(Объекты IntArray уничтожаются при выходе из блока)\n";

    cout << "\n========== Демонстрация Buffer (Задание 4) ==========\n";
    {
        using namespace task4;

        vector<Buffer> buffers;
        buffers.reserve(2);              // чтобы не было реаллокации (для наглядности)

        cout << "\n--- emplace_back (конструктор от размера) ---\n";
        buffers.emplace_back(100);       // вызывает Buffer(size_t)

        cout << "\n--- Копирование lvalue ---\n";
        Buffer b(200);
        buffers.push_back(b);            // copy constructor

        cout << "\n--- Перемещение rvalue ---\n";
        buffers.push_back(move(b));      // move constructor
        // b теперь пуст (data == nullptr)

        cout << "\n--- Присваивание перемещением ---\n";
        Buffer b2(300);
        Buffer b3(10);
        b3 = move(b2);                   // move assignment

    }


    return 0;
}