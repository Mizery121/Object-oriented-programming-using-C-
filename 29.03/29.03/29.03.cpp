#include <iostream>
#include <string>
#include <cmath>
#include <stdexcept>

using namespace std;

// 1. КЛАСС POINT
class Point {
private:
    double x, y;
    static int pointCount;   // счётчик созданных объектов

public:
    // Конструктор по умолчанию (инициализация нулями)
    Point() : x(0.0), y(0.0) {
        ++pointCount;
    }

    // Конструктор с параметрами (список инициализации)
    Point(double x, double y) : x(x), y(y) {
        ++pointCount;
    }

    // Конструктор копирования
    Point(const Point& other) : x(other.x), y(other.y) {
        ++pointCount;
    }

    // Деструктор (не уменьшает счётчик, так как по условию это не требуется)
    ~Point() {}

    // Геттеры (константные методы)
    double getX() const { return x; }
    double getY() const { return y; }

    // Расстояние от начала координат
    double distance() const {
        return sqrt(x * x + y * y);
    }

    // Статический метод для получения количества точек
    static int getPointCount() {
        return pointCount;
    }

    // Перегрузка операторов сравнения
    bool operator==(const Point& other) const {
        return (x == other.x && y == other.y);
    }

    bool operator!=(const Point& other) const {
        return !(*this == other);
    }

    // Дружественные функции для ввода/вывода
    friend ostream& operator<<(ostream& os, const Point& p);
    friend istream& operator>>(istream& is, Point& p);
};

// Инициализация статического поля
int Point::pointCount = 0;

// Вывод в поток в формате (x; y)
ostream& operator<<(ostream& os, const Point& p) {
    os << "(" << p.x << "; " << p.y << ")";
    return os;
}

// Ввод из потока (ожидает два числа, разделённых пробелом)
istream& operator>>(istream& is, Point& p) {
    is >> p.x >> p.y;
    return is;
}

// 2. БАЗОВЫЙ КЛАСС VEHICLE
class Vehicle {
protected:
    string model;
    int year;
    Point position;

    static int totalVehicles;     // общее количество созданных ТС

public:
    // Конструктор с параметрами (список инициализации всех полей)
    Vehicle(const string& model, int year, const Point& pos)
        : model(model), year(year), position(pos) {
        ++totalVehicles;
    }

    // Конструктор копирования (увеличивает totalVehicles)
    Vehicle(const Vehicle& other)
        : model(other.model), year(other.year), position(other.position) {
        ++totalVehicles;
    }

    // Виртуальный деструктор (обязателен для полиморфизма)
    virtual ~Vehicle() {

    }

    // Чисто виртуальные методы (делают класс абстрактным)
    virtual double getMaxSpeed() const = 0;
    virtual void print() const = 0;

    // Константный метод: изменение позиции
    void move(const Point& newPos) {
        position = newPos;
    }

    explicit Vehicle(const string& model)
        : model(model), year(2020), position(0.0, 0.0) {
        ++totalVehicles;
    }

    // Статический метод для доступа к totalVehicles
    static int getTotalVehicles() {
        return totalVehicles;
    }

    // Геттеры для доступа к полям (могут пригодиться в наследниках)
    string getModel() const { return model; }
    int getYear() const { return year; }
    Point getPosition() const { return position; }
};

// Инициализация статического поля
int Vehicle::totalVehicles = 0;

int main() {
    setlocale(LC_ALL, "rus");

    cout << "========== ДЕМОНСТРАЦИЯ КЛАССА POINT ==========\n";

    // 1. Создание точек разными конструкторами
    Point p1;                     // по умолчанию (0,0)
    Point p2(3.5, 4.2);          // с параметрами
    Point p3(p2);                 // копирование

    cout << "Точка p1: " << p1 << ", расстояние от (0,0): " << p1.distance() << endl;
    cout << "Точка p2: " << p2 << ", расстояние от (0,0): " << p2.distance() << endl;
    cout << "Точка p3 (копия p2): " << p3 << endl;

    // 2. Сравнение точек
    cout << "p2 == p3 ? " << (p2 == p3 ? "да" : "нет") << endl;
    cout << "p1 != p2 ? " << (p1 != p2 ? "да" : "нет") << endl;

    // 4. Статический счётчик точек
    cout << "Всего создано точек: " << Point::getPointCount() << endl;

    // 5. Дополнительная демонстрация оператора вывода
    Point p5(7, -2.5);
    cout << "Ещё одна точка: " << p5 << endl;

    cout << "\n========== ДЕМОНСТРАЦИЯ КЛАССА VEHICLE ==========\n";
    cout << "Класс Vehicle является абстрактным (содержит чисто виртуальные методы).\n";
    cout << "Его конструкторы и статические поля можно проверить только через наследников.\n";
    cout << "Тем не менее, покажем, что explicit-конструктор существует и запрещает неявное преобразование:\n\n";
    cout << "Статический счётчик totalVehicles = " << Vehicle::getTotalVehicles() << " (пока 0, так как объекты не создавались).\n";
    cout << "При создании объектов-наследников (например, Car, Bike) счётчик будет увеличиваться.\n";

    return 0;
}