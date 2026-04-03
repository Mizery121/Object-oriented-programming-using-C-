#include <iostream>
#include <vector>

using namespace std;

// Базовый класс Shape с виртуальным методом draw()
class Shape {
public:
    virtual void draw() const {
        cout << "Рисуем абстрактную фигуру" << endl;
    }
    virtual ~Shape() = default; // Виртуальный деструктор для полиморфного удаления
};

// Производный класс Circle
class Circle : public Shape {
public:
    void draw() const override {
        cout << "Рисуем круг" << endl;
    }
};

// Производный класс Rectangle
class Rectangle : public Shape {
public:
    void draw() const override {
        cout << "Рисуем прямоугольник" << endl;
    }
};

// Функция, которая пытается привести указатель к Circle или Rectangle
void identifyAndDraw(Shape* s) {
    if (s == nullptr) return;

    // Пробуем привести к Circle*
    Circle* circle = dynamic_cast<Circle*>(s);
    if (circle) {
        cout << "Обнаружен круг: ";
        circle->draw();
        return;
    }

    // Пробуем привести к Rectangle*
    Rectangle* rect = dynamic_cast<Rectangle*>(s);
    if (rect) {
        cout << "Обнаружен прямоугольник: ";
        rect->draw();
        return;
    }

    // Если ни одно приведение не удалось
    cout << "Неизвестный тип фигуры: ";
    s->draw();
}

int main() {
    setlocale(LC_ALL, "RU");
    // Создаём массив указателей на Shape
    Shape* shapes[] = {
        new Circle(),
        new Rectangle(),
        new Circle(),
        new Shape()   // объект базового класса
    };

    const size_t count = sizeof(shapes) / sizeof(shapes[0]);

    // Передаём каждый указатель в функцию identifyAndDraw
    for (size_t i = 0; i < count; ++i) {
        identifyAndDraw(shapes[i]);
    }

    // Освобождаем память
    for (size_t i = 0; i < count; ++i) {
        delete shapes[i];
    }

    return 0;
}