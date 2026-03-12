#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>

using namespace std;

// Базовый класс Кошка
class Cat {
protected:
    string name;   // кличка
    int age;       // возраст
    string color;  // окрас

public:
    // Конструктор с параметрами
    Cat(const string& name, int age, const string& color)
        : name(name), age(age), color(color) {
        cout << "Конструктор Cat: " << name << endl;
    }

    // Деструктор
    ~Cat() {
        cout << "Деструктор Cat: " << name << " уничтожен" << endl;
    }

    // Вывод информации
    void printInfo() const {
        cout << "Имя: " << name << ", Возраст: " << age << ", Окрас: " << color;
    }

    // Звук кошки
    void sound() const {
        cout << "Кошка издает звук: Мяу!" << endl;
    }

    // Геттеры
    string getName() const { return name; }
    int getAge() const { return age; }
    string getColor() const { return color; }
};

// Производный класс Домашняя кошка
class HouseCat : public Cat {
private:
    string ownerName; // имя хозяина

public:
    // Конструктор
    HouseCat(const string& name, int age, const string& color, const string& owner)
        : Cat(name, age, color), ownerName(owner) {
        cout << "Конструктор HouseCat: " << name << endl;
    }

    // Деструктор
    ~HouseCat() {
        cout << "Деструктор HouseCat: " << name << " уничтожен" << endl;
    }

    // Переопределение sound()
    void sound() const {
        cout << name << " мурлычет: Мрр-мрр" << endl;
    }

    // Переопределение printInfo()
    void printInfo() const {
        Cat::printInfo();
        cout << ", Хозяин: " << ownerName;
    }

    // Собственный метод
    void play() const {
        cout << name << " играет с мячиком" << endl;
    }
};

// Производный класс Дикая кошка
class WildCat : public Cat {
private:
    string habitat; // среда обитания

public:
    WildCat(const string& name, int age, const string& color, const string& habitat)
        : Cat(name, age, color), habitat(habitat) {
        cout << "Конструктор WildCat: " << name << endl;
    }

    ~WildCat() {
        cout << "Деструктор WildCat: " << name << " уничтожен" << endl;
    }

    void sound() const {
        cout << name << " рычит: Рррр!" << endl;
    }

    void printInfo() const {
        Cat::printInfo();
        cout << ", Среда обитания: " << habitat;
    }

    void hunt() const {
        cout << name << " охотится" << endl;
    }
};

// Производный класс Персидская кошка
class PersianCat : public Cat {
private:
    int woolLength; // длина шерсти (см)

public:
    PersianCat(const string& name, int age, const string& color, int woolLength)
        : Cat(name, age, color), woolLength(woolLength) {
        cout << "Конструктор PersianCat: " << name << endl;
    }

    ~PersianCat() {
        cout << "Деструктор PersianCat: " << name << " уничтожен" << endl;
    }

    void sound() const {
        cout << name << " тихо мяукает: Мяу" << endl;
    }

    void printInfo() const {
        Cat::printInfo();
        cout << ", Длина шерсти: " << woolLength << " см";
    }

    void groom() const {
        cout << name << " нуждается в расчесывании" << endl;
    }
};

int main() {
    setlocale(LC_ALL, "Russian");

    cout << "=== Создание объектов ===\n" << endl;

    // Создаём объекты разных типов
    Cat basicCat("Барсик", 5, "серый");
    HouseCat houseCat("Мурка", 3, "белый", "Анна");
    WildCat wildCat("Шерхан", 7, "рыжий", "джунгли");
    PersianCat persianCat("Снежок", 2, "белый", 15);

    cout << "\n=== Демонстрация методов ===\n" << endl;

    // Прямой вызов методов через объекты производных классов
    cout << "--- Домашняя кошка ---" << endl;
    houseCat.printInfo();
    cout << endl;
    houseCat.sound();
    houseCat.play();

    cout << "\n--- Дикая кошка ---" << endl;
    wildCat.printInfo();
    cout << endl;
    wildCat.sound();
    wildCat.hunt();

    cout << "\n--- Персидская кошка ---" << endl;
    persianCat.printInfo();
    cout << endl;
    persianCat.sound();
    persianCat.groom();

    cout << "\n=== Вызов через указатели на базовый класс ===\n" << endl;

    // Указатели на базовый класс, но указывают на производные объекты
    Cat* ptr1 = &houseCat;
    Cat* ptr2 = &wildCat;
    Cat* ptr3 = &persianCat;

    cout << "ptr1 (HouseCat):" << endl;
    ptr1->printInfo();   // вызывается Cat printInfo
    cout << endl;
    ptr1->sound();       // Cat sound

    cout << "\nptr2 (WildCat):" << endl;
    ptr2->printInfo();
    cout << endl;
    ptr2->sound();

    cout << "\nptr3 (PersianCat):" << endl;
    ptr3->printInfo();
    cout << endl;
    ptr3->sound();

    cout << "\n--- Объяснение ---" << endl;
    cout << "Методы printInfo и sound не являются виртуальными, поэтому при вызове через указатель на базовый класс "
        "вызываются версии базового класса (сокрытие, а не полиморфизм). Чтобы вызвать версии производных классов, "
        "нужно использовать указатель именно на производный класс или привести тип." << endl;

    // Приведение типов для доступа к методам производных классов
    cout << "\n--- Приведение типов ---" << endl;
    static_cast<HouseCat*>(ptr1)->play();
    static_cast<WildCat*>(ptr2)->hunt();
    static_cast<PersianCat*>(ptr3)->groom();

    cout << "\n=== Копирование объектов ===\n" << endl;
    // Создадим копию через конструктор копирования
    PersianCat persianCopy = persianCat;
    cout << "Копия персидской кошки: ";
    persianCopy.printInfo();
    cout << endl;

    cout << "\n=== Завершение программы (деструкторы) ===\n" << endl;
    return 0;
}