#include <iostream>
#include <string>
#include <fstream>

using namespace std;

// ЗАДАНИЕ 1
namespace Geometry {
    const double PI = 3.14159;

    double circleArea(double radius) {
        return PI * radius * radius;
    }

    double rectangleArea(double width, double height) {
        return width * height;
    }

    namespace Shapes {
        class Circle {
        private:
            double radius;
        public:
            Circle(double r) : radius(r) {}
            double area() const {
                return Geometry::circleArea(radius);
            }
        };
    }
}

// ЗАДАНИЕ 2
namespace Logger {
    enum LogLevel { INFO, WARNING, ERROR };

    void log(LogLevel level, const string& message) {
        switch (level) {
        case INFO:    cout << "[INFO] "; break;
        case WARNING: cout << "[WARNING] "; break;
        case ERROR:   cout << "[ERROR] "; break;
        }
        cout << message << endl;
    }

    namespace FileLogger {
        void logToFile(const string& filename, const string& message) {
            ofstream file(filename, ios::app);
            if (file.is_open()) {
                file << message << endl;
                file.close();
            }
            else {
                cerr << "Не удалось открыть файл: " << filename << endl;
            }
        }
    }
}

int main() {
    setlocale(LC_ALL, "ru");

    cout << "========== ЗАДАНИЕ 1 ==========\n";

    // 1. Полная квалификация
    cout << "Площадь круга (радиус 5): " << Geometry::circleArea(5) << endl;
    cout << "Площадь прямоугольника (4x6): " << Geometry::rectangleArea(4, 6) << endl;

    // 2. Using-объявление для одной функции
    using Geometry::rectangleArea;
    cout << "Площадь прямоугольника (через using): " << rectangleArea(3, 7) << endl;

    // 3. Использование вложенного класса
    Geometry::Shapes::Circle c(3);
    cout << "Площадь круга через класс Circle: " << c.area() << endl;

    using namespace Geometry;
    cout << "Ещё одна площадь круга (через using namespace): " << circleArea(2) << endl;

    cout << "\n========== ЗАДАНИЕ 2 ==========\n";

    using namespace Logger;

    log(INFO, "Программа запущена");
    log(WARNING, "Баланс на исходе");
    log(ERROR, "Критическая ошибка");

    // Вызов функции из вложенного пространства
    FileLogger::logToFile("log.txt", "Это сообщение записано в файл");
    cout << "Сообщение записано в файл log.txt" << endl;

    return 0;
}