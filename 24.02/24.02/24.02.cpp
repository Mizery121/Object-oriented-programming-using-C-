#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cmath>
#include <cstring>
#include <vector>
#include <string>
#include <limits>
using namespace std;

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// ========== Класс Точка ==========
class Point {
private:
    double x, y, z;
    static int count;
public:
    Point() : Point(0, 0, 0) {}
    Point(double x, double y, double z) : x(x), y(y), z(z) { ++count; }
    Point(const Point& other) : x(other.x), y(other.y), z(other.z) { ++count; }
    ~Point() { --count; }
    static int getCount() { return count; }
    void print() const { cout << "(" << x << ", " << y << ", " << z << ")"; }
    void input() {
        cout << "Введите координаты x y z: ";
        cin >> x >> y >> z;
    }
};
int Point::count = 0;

// ========== Класс Дробь ==========
class Fraction {
private:
    int num, den;
    static int count;
public:
    Fraction() : Fraction(0, 1) {}
    Fraction(int n, int d) : num(n), den(d) { if (den == 0) den = 1; ++count; }
    Fraction(const Fraction& other) : num(other.num), den(other.den) { ++count; }
    ~Fraction() { --count; }
    static int getCount() { return count; }
    void print() const { cout << num << "/" << den; }
    void input() {
        cout << "Введите числитель и знаменатель: ";
        cin >> num >> den;
        if (den == 0) { den = 1; cout << "Знаменатель не может быть 0, установлен 1.\n"; }
    }
};
int Fraction::count = 0;

// ========== Класс Student (упрощённый) ==========
class Student {
private:
    char* fullName;
    static int count;
public:
    Student() : Student("") {}
    Student(const char* name) {
        fullName = new char[strlen(name) + 1];
        strcpy(fullName, name);
        ++count;
    }
    Student(const Student& other) {
        fullName = new char[strlen(other.fullName) + 1];
        strcpy(fullName, other.fullName);
        ++count;
    }
    ~Student() { delete[] fullName; --count; }
    static int getCount() { return count; }
    void print() const { cout << fullName; }
    void input() {
        cout << "Введите ФИО: ";
        string name;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, name);
        setFullName(name.c_str());
    }
    void setFullName(const char* name) {
        delete[] fullName;
        fullName = new char[strlen(name) + 1];
        strcpy(fullName, name);
    }
};
int Student::count = 0;

// ========== Класс для площадей ==========
class Geometry {
private:
    static int calcCount;
public:
    Geometry() = delete;

    static double triangleHeron(double a, double b, double c) {
        ++calcCount;
        double p = (a + b + c) / 2;
        return sqrt(p * (p - a) * (p - b) * (p - c));
    }
    static double triangleBaseHeight(double base, double height) {
        ++calcCount;
        return 0.5 * base * height;
    }
    static double triangleTwoSidesAngle(double a, double b, double angleDeg) {
        ++calcCount;
        return 0.5 * a * b * sin(angleDeg * M_PI / 180);
    }
    static double rectangle(double a, double b) {
        ++calcCount;
        return a * b;
    }
    static double square(double a) {
        ++calcCount;
        return a * a;
    }
    static double rhombusDiagonals(double d1, double d2) {
        ++calcCount;
        return (d1 * d2) / 2;
    }
    static double rhombusSideHeight(double side, double height) {
        ++calcCount;
        return side * height;
    }
    static int getCalcCount() { return calcCount; }
    static void resetCalcCount() { calcCount = 0; }
};
int Geometry::calcCount = 0;

// ========== Главная функция с меню ==========
int main() {
    setlocale(LC_ALL, "Russian");

    vector<Point> points;
    vector<Fraction> fractions;
    vector<Student> students;

    int choice;
    do {
        cout << "\n========== МЕНЮ ==========\n";
        cout << "1. Работа с точками\n";
        cout << "2. Работа с дробями\n";
        cout << "3. Работа со студентами\n";
        cout << "4. Вычисление площадей\n";
        cout << "0. Выход\n";
        cout << "Ваш выбор: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            int sub;
            cout << "--- Точки ---\n";
            cout << "1. Добавить точку\n";
            cout << "2. Показать все точки\n";
            cout << "3. Показать количество точек\n";
            cout << "Выбор: ";
            cin >> sub;
            if (sub == 1) {
                Point p;
                p.input();
                points.push_back(p);
                cout << "Точка добавлена. Всего точек: " << Point::getCount() << endl;
            }
            else if (sub == 2) {
                if (points.empty()) cout << "Список пуст.\n";
                else for (size_t i = 0; i < points.size(); ++i) {
                    cout << i << ": "; points[i].print(); cout << endl;
                }
            }
            else if (sub == 3) {
                cout << "Количество точек: " << Point::getCount() << endl;
            }
            break;
        }
        case 2: {
            int sub;
            cout << "--- Дроби ---\n";
            cout << "1. Добавить дробь\n";
            cout << "2. Показать все дроби\n";
            cout << "3. Показать количество дробей\n";
            cout << "Выбор: ";
            cin >> sub;
            if (sub == 1) {
                Fraction f;
                f.input();
                fractions.push_back(f);
                cout << "Дробь добавлена. Всего дробей: " << Fraction::getCount() << endl;
            }
            else if (sub == 2) {
                if (fractions.empty()) cout << "Список пуст.\n";
                else for (size_t i = 0; i < fractions.size(); ++i) {
                    cout << i << ": "; fractions[i].print(); cout << endl;
                }
            }
            else if (sub == 3) {
                cout << "Количество дробей: " << Fraction::getCount() << endl;
            }
            break;
        }
        case 3: {
            int sub;
            cout << "--- Студенты ---\n";
            cout << "1. Добавить студента\n";
            cout << "2. Показать всех студентов\n";
            cout << "3. Показать количество студентов\n";
            cout << "Выбор: ";
            cin >> sub;
            if (sub == 1) {
                Student s;
                s.input();
                students.push_back(s);
                cout << "Студент добавлен. Всего студентов: " << Student::getCount() << endl;
            }
            else if (sub == 2) {
                if (students.empty()) cout << "Список пуст.\n";
                else for (size_t i = 0; i < students.size(); ++i) {
                    cout << i << ": "; students[i].print(); cout << endl;
                }
            }
            else if (sub == 3) {
                cout << "Количество студентов: " << Student::getCount() << endl;
            }
            break;
        }
        case 4: {
            int fig;
            cout << "--- Вычисление площади ---\n";
            cout << "1. Треугольник (формула Герона)\n";
            cout << "2. Треугольник (основание и высота)\n";
            cout << "3. Треугольник (две стороны и угол)\n";
            cout << "4. Прямоугольник\n";
            cout << "5. Квадрат\n";
            cout << "6. Ромб (диагонали)\n";
            cout << "7. Ромб (сторона и высота)\n";
            cout << "Выберите фигуру: ";
            cin >> fig;

            double result = 0;
            switch (fig) {
            case 1: {
                double a, b, c;
                cout << "Введите три стороны: "; cin >> a >> b >> c;
                result = Geometry::triangleHeron(a, b, c);
                break;
            }
            case 2: {
                double base, h;
                cout << "Введите основание и высоту: "; cin >> base >> h;
                result = Geometry::triangleBaseHeight(base, h);
                break;
            }
            case 3: {
                double a, b, ang;
                cout << "Введите две стороны и угол (градусы): "; cin >> a >> b >> ang;
                result = Geometry::triangleTwoSidesAngle(a, b, ang);
                break;
            }
            case 4: {
                double a, b;
                cout << "Введите стороны прямоугольника: "; cin >> a >> b;
                result = Geometry::rectangle(a, b);
                break;
            }
            case 5: {
                double a;
                cout << "Введите сторону квадрата: "; cin >> a;
                result = Geometry::square(a);
                break;
            }
            case 6: {
                double d1, d2;
                cout << "Введите диагонали ромба: "; cin >> d1 >> d2;
                result = Geometry::rhombusDiagonals(d1, d2);
                break;
            }
            case 7: {
                double side, h;
                cout << "Введите сторону и высоту ромба: "; cin >> side >> h;
                result = Geometry::rhombusSideHeight(side, h);
                break;
            }
            default:
                cout << "Неверный выбор\n";
                continue;
            }
            cout << "Площадь = " << result << endl;
            cout << "Всего вычислений: " << Geometry::getCalcCount() << endl;
            break;
        }
        case 0:
            cout << "Выход.\n";
            break;
        default:
            cout << "Неверный пункт меню.\n";
        }
    } while (choice != 0);

    return 0;
}