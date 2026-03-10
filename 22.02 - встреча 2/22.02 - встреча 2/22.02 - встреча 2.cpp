#define _CRT_SECURE_NO_WARNINGS  // для Visual Studio: отключает предупреждения о небезопасных функциях

#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <limits>

using namespace std;

// ==================== Класс "Точка" ====================
class Point {
private:
    double x, y, z;

public:
    // Конструкторы
    Point() : x(0), y(0), z(0) {}
    Point(double x, double y, double z) : x(x), y(y), z(z) {}
    Point(const Point& other) : x(other.x), y(other.y), z(other.z) {}

    ~Point() {}

    // Ввод данных
    void input() {
        cout << "Введите координаты x y z: ";
        cin >> x >> y >> z;
    }

    // Вывод данных
    void print() const {
        cout << "(" << x << ", " << y << ", " << z << ")";
    }

    // Аксессоры (inline)
    inline double getX() const { return x; }
    inline double getY() const { return y; }
    inline double getZ() const { return z; }
    inline void setX(double val) { x = val; }
    inline void setY(double val) { y = val; }
    inline void setZ(double val) { z = val; }

    // Сохранение в файл
    void saveToFile(const char* filename) const {
        ofstream file(filename);
        if (file.is_open()) {
            file << x << " " << y << " " << z;
            file.close();
        }
        else {
            cerr << "Ошибка: не удалось открыть файл для записи!" << endl;
        }
    }

    // Загрузка из файла
    void loadFromFile(const char* filename) {
        ifstream file(filename);
        if (file.is_open()) {
            file >> x >> y >> z;
            file.close();
        }
        else {
            cerr << "Ошибка: не удалось открыть файл для чтения!" << endl;
        }
    }
};

// ==================== Класс "Дробь" ====================
class Fraction {
private:
    int numerator;   // числитель
    int denominator; // знаменатель

public:
    // Конструкторы
    Fraction() : numerator(0), denominator(1) {}
    Fraction(int num, int denom) : numerator(num), denominator(denom) {
        if (denominator == 0) denominator = 1; // защита от нуля
    }
    Fraction(const Fraction& other) : numerator(other.numerator), denominator(other.denominator) {}

    ~Fraction() {}

    // Ввод данных
    void input() {
        cout << "Введите числитель и знаменатель: ";
        cin >> numerator >> denominator;
        if (denominator == 0) {
            cout << "Знаменатель не может быть нулем. Установлено значение 1." << endl;
            denominator = 1;
        }
    }

    // Вывод данных
    void print() const {
        cout << numerator << "/" << denominator;
    }

    // Аксессоры (inline)
    inline int getNumerator() const { return numerator; }
    inline int getDenominator() const { return denominator; }
    inline void setNumerator(int num) { numerator = num; }
    inline void setDenominator(int denom) {
        if (denom != 0) denominator = denom;
        else cerr << "Знаменатель не может быть нулем!" << endl;
    }

    // Арифметическая операция (сложение)
    Fraction add(const Fraction& other) const {
        return Fraction(numerator * other.denominator + other.numerator * denominator,
            denominator * other.denominator);
    }
};

// ==================== Класс "Студент" ====================
class Student {
private:
    char* fullName;          // динамическая память под ФИО
    string birthDate;        // дата рождения
    string phone;            // контактный телефон
    string city;             // город проживания
    string country;          // страна проживания
    string university;       // название учебного заведения
    string uniCity;          // город учебного заведения
    string uniCountry;       // страна учебного заведения
    string group;            // номер группы

public:
    // Конструктор по умолчанию
    Student() : fullName(nullptr), birthDate(""), phone(""), city(""), country(""),
        university(""), uniCity(""), uniCountry(""), group("") {
        fullName = new char[1];
        fullName[0] = '\0';
    }

    // Конструктор с параметрами
    Student(const char* name, const string& bDate, const string& ph, const string& c,
        const string& cntr, const string& uni, const string& uCity,
        const string& uCntr, const string& grp)
        : birthDate(bDate), phone(ph), city(c), country(cntr),
        university(uni), uniCity(uCity), uniCountry(uCntr), group(grp) {
        fullName = new char[strlen(name) + 1];
        strcpy(fullName, name);
    }

    // Конструктор копирования (глубокое копирование)
    Student(const Student& other)
        : birthDate(other.birthDate), phone(other.phone), city(other.city),
        country(other.country), university(other.university),
        uniCity(other.uniCity), uniCountry(other.uniCountry), group(other.group) {
        fullName = new char[strlen(other.fullName) + 1];
        strcpy(fullName, other.fullName);
    }

    // Оператор присваивания (глубокое копирование)
    Student& operator=(const Student& other) {
        if (this != &other) {
            delete[] fullName;
            fullName = new char[strlen(other.fullName) + 1];
            strcpy(fullName, other.fullName);

            birthDate = other.birthDate;
            phone = other.phone;
            city = other.city;
            country = other.country;
            university = other.university;
            uniCity = other.uniCity;
            uniCountry = other.uniCountry;
            group = other.group;
        }
        return *this;
    }

    // Деструктор
    ~Student() {
        delete[] fullName;
    }

    // Ввод данных
    void input() {
        char buffer[1024];
        cout << "Введите ФИО: ";
        cin.getline(buffer, 1024);
        setFullName(buffer);

        cout << "Введите дату рождения: ";
        getline(cin, birthDate);
        cout << "Введите контактный телефон: ";
        getline(cin, phone);
        cout << "Введите город проживания: ";
        getline(cin, city);
        cout << "Введите страну проживания: ";
        getline(cin, country);
        cout << "Введите название учебного заведения: ";
        getline(cin, university);
        cout << "Введите город учебного заведения: ";
        getline(cin, uniCity);
        cout << "Введите страну учебного заведения: ";
        getline(cin, uniCountry);
        cout << "Введите номер группы: ";
        getline(cin, group);
    }

    // Вывод данных
    void print() const {
        cout << "ФИО: " << (fullName ? fullName : "") << endl;
        cout << "Дата рождения: " << birthDate << endl;
        cout << "Телефон: " << phone << endl;
        cout << "Город: " << city << endl;
        cout << "Страна: " << country << endl;
        cout << "Учебное заведение: " << university << endl;
        cout << "Город учебы: " << uniCity << endl;
        cout << "Страна учебы: " << uniCountry << endl;
        cout << "Группа: " << group << endl;
    }

    // Аксессоры (inline)
    inline const char* getFullName() const { return fullName; }
    inline string getBirthDate() const { return birthDate; }
    inline string getPhone() const { return phone; }
    inline string getCity() const { return city; }
    inline string getCountry() const { return country; }
    inline string getUniversity() const { return university; }
    inline string getUniCity() const { return uniCity; }
    inline string getUniCountry() const { return uniCountry; }
    inline string getGroup() const { return group; }

    inline void setFullName(const char* name) {
        delete[] fullName;
        fullName = new char[strlen(name) + 1];
        strcpy(fullName, name);
    }
    inline void setBirthDate(const string& bd) { birthDate = bd; }
    inline void setPhone(const string& ph) { phone = ph; }
    inline void setCity(const string& c) { city = c; }
    inline void setCountry(const string& c) { country = c; }
    inline void setUniversity(const string& u) { university = u; }
    inline void setUniCity(const string& uc) { uniCity = uc; }
    inline void setUniCountry(const string& uc) { uniCountry = uc; }
    inline void setGroup(const string& g) { group = g; }
};


int main() {
    // Устанавливаем локаль для поддержки русского языка (для Windows)
    setlocale(LC_ALL, "Russian");

    // Демонстрация класса Точка
    cout << "=== Точка ===" << endl;
    Point p1(1.5, 2.5, 3.5);
    cout << "p1 = ";
    p1.print();
    cout << endl;

    Point p2;
    p2.input();  // после этого в буфере остаётся '\n'
    cout << "p2 = ";
    p2.print();
    cout << endl;

    p2.saveToFile("point.txt");
    Point p3;
    p3.loadFromFile("point.txt");
    cout << "Загруженная из файла точка: ";
    p3.print();
    cout << endl;

    // Демонстрация класса Дробь
    cout << "\n=== Дробь ===" << endl;
    Fraction f1(3, 4);
    cout << "f1 = ";
    f1.print();
    cout << endl;

    Fraction f2;
    f2.input();  // после этого в буфере остаётся '\n'

    // Очищаем входной буфер перед вводом строк для Student
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "f2 = ";
    f2.print();
    cout << endl;

    Fraction f3 = f1.add(f2);
    cout << "f1 + f2 = ";
    f3.print();
    cout << endl;

    // Демонстрация класса Студент
    cout << "\n=== Студент ===" << endl;
    Student s1("Иванов Иван Иванович", "01.01.2000", "+7-123-456-78-90",
        "Москва", "Россия", "МГУ", "Москва", "Россия", "ИУ8-11");
    s1.print();

    cout << "\nВвод данных для другого студента:\n";
    Student s2;
    s2.input();  // теперь getline сработает корректно
    cout << "\nВведенные данные:\n";
    s2.print();

    // Проверка копирования
    Student s3 = s1;
    cout << "\nКопия первого студента:\n";
    s3.print();

    return 0;
}