#include <iostream>
#include <vector>
#include <string>

using namespace std;

// ЗАДАНИЕ 4

class Drawable {
public:
    virtual void draw() const = 0;
    virtual ~Drawable() = default;
};

class Serializable {
public:
    virtual string serialize() const = 0;
    virtual ~Serializable() = default;
};

// Класс Circle реализует оба интерфейса.
class Circle : public Drawable, public Serializable {
    int x, y;        // координаты центра
    double radius;   // радиус
public:
    Circle(int x, int y, double r) : x(x), y(y), radius(r) {}

    // Реализация draw() из Drawable.
    void draw() const override {
        cout << "Рисую круг в (" << x << "," << y << ") радиусом " << radius << endl;
    }

    // Реализация serialize() из Serializable.
    string serialize() const override {
        return "Circle " + to_string(x) + " " + to_string(y) + " " + to_string(radius);
    }
};

// Класс Rectangle также реализует оба интерфейса.
class Rectangle : public Drawable, public Serializable {
    int x, y;            // координаты левого верхнего угла
    double width, height;
public:
    Rectangle(int x, int y, double w, double h) : x(x), y(y), width(w), height(h) {}

    void draw() const override {
        cout << "Рисую прямоугольник в (" << x << "," << y << ") ширина " << width << " высота " << height << endl;
    }

    string serialize() const override {
        return "Rectangle " + to_string(x) + " " + to_string(y) + " " + to_string(width) + " " + to_string(height);
    }
};

// ЗАДАНИЕ 5

// Базовый класс "Транспортное средство"
class Vehicle {
public:
    // Запуск двигателя. Может быть переопределён в наследниках.
    virtual void startEngine() const { cout << "Engine started" << endl; }
    // Максимальная скорость. По умолчанию 0.
    virtual double getMaxSpeed() const { return 0.0; }
    // Общая информация.
    virtual void info() const { cout << "I am a vehicle" << endl; }
    // Виртуальный деструктор – для корректного удаления через указатель на Vehicle.
    virtual ~Vehicle() = default;
};

// Класс "Автомобиль" – наследует Vehicle.
class Car : public Vehicle {
public:
    // override явно указывает, что метод переопределён.
    void startEngine() const override { cout << "Car engine started" << endl; }
    double getMaxSpeed() const override { return 180.0; }
    void info() const override { cout << "I am a car" << endl; }
};

// Класс "Электромобиль" – наследует Car.
class ElectricCar : public Car {
public:
    void startEngine() const override { cout << "Electric motor silently started" << endl; }
    // final означает, что ни один наследник ElectricCar не сможет переопределить getMaxSpeed().
    double getMaxSpeed() const final { return 180.0; }
    // info() не переопределяем – остаётся как в Car.
};

// Класс "Велосипед" – final класс, от него нельзя наследовать.
class Bicycle final : public Vehicle {
public:
    void startEngine() const override { cout << "No engine, just pedals" << endl; }
    double getMaxSpeed() const override { return 30.0; }
    void info() const override { cout << "I am a bicycle" << endl; }
};

int main() {
    // Устанавливаем русскую локаль для вывода кириллицы в консоль.
    setlocale(LC_ALL, "rus");

    cout << "========== ЗАДАНИЕ 4 ==========\n";

    // Вектор указателей на Drawable – может хранить любые объекты, реализующие Drawable.
    vector<Drawable*> drawables;
    Circle c(10, 20, 5);
    Rectangle r(0, 0, 30, 15);
    drawables.push_back(&c);
    drawables.push_back(&r);

    // Полиморфный вызов draw() для каждого объекта.
    for (auto* d : drawables) d->draw();

    // Вектор указателей на Serializable.
    vector<Serializable*> serializables;
    serializables.push_back(&c);
    serializables.push_back(&r);
    cout << "\n=== Сериализация ===\n";
    for (auto* s : serializables) cout << "Сериализовано: " << s->serialize() << endl;

    // Демонстрация dynamic_cast: преобразование Drawable* в Serializable*.
    cout << "\n=== dynamic_cast ===\n";
    for (auto* d : drawables) {
        // dynamic_cast проверяет, является ли объект, на который указывает d, также Serializable.
        // Если да – возвращает указатель, иначе nullptr.
        Serializable* ser = dynamic_cast<Serializable*>(d);
        if (ser) cout << "Объект также Serializable: " << ser->serialize() << endl;
        // В нашем случае оба объекта (Circle и Rectangle) реализуют Serializable, поэтому условие сработает.
    }

    cout << "\n========== ЗАДАНИЕ 5 ==========\n";

    // Создаём объекты через указатели на базовый класс Vehicle.
    Vehicle* v1 = new Car();
    Vehicle* v2 = new ElectricCar();
    Vehicle* v3 = new Bicycle();

    // Полиморфные вызовы – будут вызваны переопределённые методы.
    v1->startEngine(); cout << "Max speed: " << v1->getMaxSpeed() << " km/h\n"; v1->info(); cout << endl;
    v2->startEngine(); cout << "Max speed: " << v2->getMaxSpeed() << " km/h\n"; v2->info(); cout << endl;
    v3->startEngine(); cout << "Max speed: " << v3->getMaxSpeed() << " km/h\n"; v3->info();

    delete v1; delete v2; delete v3;

    return 0;
}