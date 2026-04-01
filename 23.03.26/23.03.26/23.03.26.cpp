#include <iostream>
#include <vector>
#include <string>
#include <locale>

using namespace std;

// ========== 1. КОМПОЗИЦИЯ: Дом и комнаты ==========
class Room {
public:
    string name;
    Room(const string& n) : name(n) {
        cout << "Создана комната: " << name << endl;
    }
    ~Room() {
        cout << "Удалена комната: " << name << endl;
    }
};

class House {
private:
    vector<Room> rooms; // композиция: комнаты хранятся по значению
public:
    void addRoom(const string& name) {
        rooms.emplace_back(name);
    }
    ~House() {
        cout << "Дом снесён" << endl;
    }
};

// ========== 2. АГРЕГАЦИЯ: Университет и студенты ==========
class Student {
public:
    string name;
    Student(const string& n) : name(n) {
        cout << "Создан студент: " << name << endl;
    }
    ~Student() {
        cout << "Удалён студент: " << name << endl;
    }
};

class University {
private:
    vector<Student*> students; // агрегация: храним указатели на внешних студентов
public:
    void enroll(Student* s) {
        students.push_back(s);
        cout << "Студент " << s->name << " зачислен в университет" << endl;
    }
    ~University() {
        cout << "Университет закрыт" << endl;
    }
};

int main() {
    setlocale(LC_ALL, "Russian");

    // Демонстрация композиции
    cout << "=== КОМПОЗИЦИЯ (Дом и комнаты) ===\n";
    {
        House myHouse;
        myHouse.addRoom("Гостиная");
        myHouse.addRoom("Спальня");
        cout << "--- Внутри блока ---\n";
    } // здесь myHouse уничтожается, и комнаты тоже
    cout << "--- После блока ---\n\n";

    // Демонстрация агрегации
    cout << "=== АГРЕГАЦИЯ (Университет и студенты) ===\n";
    {
        Student alice("Алиса");
        Student bob("Боб");
        University uni;
        uni.enroll(&alice);
        uni.enroll(&bob);
        cout << "--- Внутри блока ---\n";
    } // здесь uni уничтожается, студенты остаются до конца блока
    cout << "--- После блока ---\n";

    return 0;
}