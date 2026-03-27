#include <iostream>
#include <cmath>

using namespace std;

class Circle {
private:
    double radius;   // радиус окружности

    // Статическая функция для получения числа π (вычисляется один раз)
    static double PI() {
        return acos(-1.0);
    }

public:
    // Конструктор (по умолчанию радиус = 0)
    Circle(double r = 0.0) : radius(r) {}

    // Геттер радиуса
    double getRadius() const { return radius; }

    // Вычисление длины окружности: L = 2πR
    double length() const {
        return 2 * PI() * radius;
    }

    // Оператор == сравнивает радиусы
    bool operator==(const Circle& other) const {
        return radius == other.radius;
    }

    // Оператор > сравнивает длины окружностей
    bool operator>(const Circle& other) const {
        return length() > other.length();
    }

    // Оператор += увеличивает радиус на delta (может быть отрицательным)
    Circle& operator+=(double delta) {
        radius += delta;
        return *this;
    }

    // Оператор -= уменьшает радиус на delta, не допуская отрицательного значения
    Circle& operator-=(double delta) {
        radius = (radius - delta > 0) ? radius - delta : 0.0;
        return *this;
    }

    // Вспомогательный метод для вывода
    void print() const {
        cout << "Circle(radius=" << radius << ", length=" << length() << ")\n";
    }
};

int main() {
    setlocale(LC_ALL, "RU");
    // Создаём окружности
    Circle c1(5.0);
    Circle c2(5.0);
    Circle c3(3.0);

    cout << "Исходные окружности:\n";
    c1.print();
    c2.print();
    c3.print();

    // Проверка равенства радиусов (оператор ==)
    cout << "\nСравнение радиусов c1 и c2: ";
    if (c1 == c2)
        cout << "радиусы равны\n";
    else
        cout << "радиусы не равны\n";

    // Сравнение длин (оператор >)
    cout << "Сравнение длин c1 и c3: ";
    if (c1 > c3)
        cout << "c1 длиннее c3\n";
    else
        cout << "c1 не длиннее c3\n";

    // Изменение радиуса через += и -=
    cout << "\nПосле c1 += 2.0:\n";
    c1 += 2.0;
    c1.print();

    cout << "После c1 -= 1.0:\n";
    c1 -= 1.0;
    c1.print();

    cout << "Попытка уменьшить радиус c3 на 10 (станет 0):\n";
    c3 -= 10.0;
    c3.print();

    return 0;
}