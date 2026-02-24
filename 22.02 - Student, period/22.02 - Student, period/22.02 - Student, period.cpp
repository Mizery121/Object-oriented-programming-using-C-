#include <iostream>
#include <fstream>
#include <string>
#include <windows.h> // Для SetConsoleCP и SetConsoleOutputCP
using namespace std;

// ==================== КЛАСС СТУДЕНТ ====================
class Student {
private:
    string fullName;
    string birthDate;
    string phoneNumber;
    string city;
    string country;
    string university;
    string universityCity;
    string universityCountry;
    string groupNumber;

public:
    // Конструктор по умолчанию
    Student() {}

    // Конструктор с параметрами
    Student(string fn, string bd, string phone, string c, string cntr,
        string univ, string univCity, string univCntr, string group) {
        fullName = fn;
        birthDate = bd;
        phoneNumber = phone;
        city = c;
        country = cntr;
        university = univ;
        universityCity = univCity;
        universityCountry = univCntr;
        groupNumber = group;
    }

    // Функция для ввода данных
    void inputData() {
        cout << "\n--- Ввод данных студента ---\n";
        cout << "Введите ФИО студента: ";
        getline(cin, fullName);

        cout << "Введите дату рождения: ";
        getline(cin, birthDate);

        cout << "Введите контактный телефон: ";
        getline(cin, phoneNumber);

        cout << "Введите город: ";
        getline(cin, city);

        cout << "Введите страну: ";
        getline(cin, country);

        cout << "Введите название учебного заведения: ";
        getline(cin, university);

        cout << "Введите город учебного заведения: ";
        getline(cin, universityCity);

        cout << "Введите страну учебного заведения: ";
        getline(cin, universityCountry);

        cout << "Введите номер группы: ";
        getline(cin, groupNumber);
    }

    // Функция для вывода данных
    void displayData() const {
        cout << "\n--- Информация о студенте ---\n";
        cout << "ФИО: " << fullName << endl;
        cout << "Дата рождения: " << birthDate << endl;
        cout << "Телефон: " << phoneNumber << endl;
        cout << "Город: " << city << endl;
        cout << "Страна: " << country << endl;
        cout << "Учебное заведение: " << university << endl;
        cout << "Город учебы: " << universityCity << endl;
        cout << "Страна учебы: " << universityCountry << endl;
        cout << "Группа: " << groupNumber << endl;
        cout << "-----------------------------\n";
    }

    // Аксессоры (геттеры)
    string getFullName() const { return fullName; }
    string getBirthDate() const { return birthDate; }
    string getPhoneNumber() const { return phoneNumber; }
    string getCity() const { return city; }
    string getCountry() const { return country; }
    string getUniversity() const { return university; }
    string getUniversityCity() const { return universityCity; }
    string getUniversityCountry() const { return universityCountry; }
    string getGroupNumber() const { return groupNumber; }

    // Аксессоры (сеттеры)
    void setFullName(const string& fn) { fullName = fn; }
    void setBirthDate(const string& bd) { birthDate = bd; }
    void setPhoneNumber(const string& phone) { phoneNumber = phone; }
    void setCity(const string& c) { city = c; }
    void setCountry(const string& cntr) { country = cntr; }
    void setUniversity(const string& univ) { university = univ; }
    void setUniversityCity(const string& univCity) { universityCity = univCity; }
    void setUniversityCountry(const string& univCntr) { universityCountry = univCntr; }
    void setGroupNumber(const string& group) { groupNumber = group; }
};

// ==================== КЛАСС ТОЧКА ====================
class Point {
private:
    double x;
    double y;
    double z;

public:
    // Конструктор по умолчанию
    Point() : x(0), y(0), z(0) {}

    // Конструктор с параметрами
    Point(double xCoord, double yCoord, double zCoord) {
        x = xCoord;
        y = yCoord;
        z = zCoord;
    }

    // Функция для ввода данных
    void inputData() {
        cout << "\n--- Ввод координат точки ---\n";
        cout << "Введите координату X: ";
        cin >> x;

        cout << "Введите координату Y: ";
        cin >> y;

        cout << "Введите координату Z: ";
        cin >> z;
        cin.ignore(); // Очистка буфера ввода
    }

    // Функция для вывода данных
    void displayData() const {
        cout << "Точка: (" << x << ", " << y << ", " << z << ")" << endl;
    }

    // Аксессоры (геттеры)
    double getX() const { return x; }
    double getY() const { return y; }
    double getZ() const { return z; }

    // Аксессоры (сеттеры)
    void setX(double xCoord) { x = xCoord; }
    void setY(double yCoord) { y = yCoord; }
    void setZ(double zCoord) { z = zCoord; }

    // Сохранение в файл
    void saveToFile(const string& filename) const {
        ofstream file(filename);
        if (file.is_open()) {
            file << x << " " << y << " " << z << endl;
            file.close();
            cout << "Данные успешно сохранены в файл " << filename << endl;
        }
        else {
            cout << "Ошибка открытия файла для записи!" << endl;
        }
    }

    // Загрузка из файла
    void loadFromFile(const string& filename) {
        ifstream file(filename);
        if (file.is_open()) {
            file >> x >> y >> z;
            file.close();
            cout << "Данные успешно загружены из файла " << filename << endl;
        }
        else {
            cout << "Ошибка открытия файла для чтения!" << endl;
        }
    }
};

// ==================== ГЛАВНАЯ ФУНКЦИЯ ====================
int main() {
    // Настройка кодировки для правильного отображения русского языка в Windows
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int choice;

    do {
        cout << "\n========== МЕНЮ ==========\n";
        cout << "1. Работа со студентом\n";
        cout << "2. Работа с точкой\n";
        cout << "0. Выход\n";
        cout << "Выберите действие: ";
        cin >> choice;
        cin.ignore(); // Очистка буфера после ввода числа

        switch (choice) {
        case 1: {
            // Работа со студентом
            Student student;

            // Ввод данных
            student.inputData();

            // Вывод данных
            student.displayData();

            // Демонстрация аксессоров
            cout << "\n--- Демонстрация аксессоров ---\n";
            cout << "ФИО (через геттер): " << student.getFullName() << endl;
            cout << "Текущий телефон: " << student.getPhoneNumber() << endl;

            // Изменение данных через сеттер
            cout << "\nХотите изменить номер телефона? (1 - да, 0 - нет): ";
            int changePhone;
            cin >> changePhone;
            cin.ignore();

            if (changePhone == 1) {
                string newPhone;
                cout << "Введите новый номер телефона: ";
                getline(cin, newPhone);
                student.setPhoneNumber(newPhone);
                cout << "Номер телефона изменен!" << endl;
            }

            // Финальный вывод
            cout << "\n--- Обновленные данные студента ---\n";
            student.displayData();
            break;
        }

        case 2: {
            // Работа с точкой
            Point point;

            // Ввод данных
            point.inputData();

            // Вывод данных
            cout << "\n--- Введенная точка ---\n";
            point.displayData();

            // Демонстрация аксессоров
            cout << "\n--- Демонстрация аксессоров ---\n";
            cout << "Координата X (через геттер): " << point.getX() << endl;

            // Изменение данных через сеттер
            cout << "Хотите изменить координату Y? (1 - да, 0 - нет): ";
            int changeY;
            cin >> changeY;

            if (changeY == 1) {
                double newY;
                cout << "Введите новую координату Y: ";
                cin >> newY;
                point.setY(newY);
                cout << "Координата Y изменена!" << endl;
            }

            cout << "Обновленная координата Y: " << point.getY() << endl;

            // Работа с файлом
            cout << "\n--- Работа с файлом ---\n";
            point.saveToFile("point_data.txt");

            Point point2;
            point2.loadFromFile("point_data.txt");
            cout << "Загруженная из файла точка:\n";
            point2.displayData();
            break;
        }

        case 0:
            cout << "Программа завершена.\n";
            break;

        default:
            cout << "Неверный выбор. Попробуйте снова.\n";
        }
    } while (choice != 0);

    return 0;
}