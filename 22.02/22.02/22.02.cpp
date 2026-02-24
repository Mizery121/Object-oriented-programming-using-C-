// Объединенное задание 1 и 2: Лифт + Стоимость обоев
// С поддержкой русского языка через setlocale

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <iomanip>
#include <clocale>

using namespace std;

// ====================== Часть 1: Класс Лифт ======================

class Lift {
private:
    int lowerFloor;
    int upperFloor;
    bool isOn;
    int currentFloor;

public:
    Lift(int lower, int upper) : lowerFloor(lower), upperFloor(upper), isOn(false), currentFloor(lower) {}

    void turnOn() { isOn = true; }
    void turnOff() { isOn = false; }

    string getStatus() const {
        return isOn ? "работает" : "не работает";
    }

    int getCurrentFloor() const {
        return currentFloor;
    }

    void call(int targetFloor) {
        if (!isOn) {
            cout << "Лифт выключен. Вызов невозможен." << endl;
            return;
        }
        if (targetFloor < lowerFloor || targetFloor > upperFloor) {
            cout << "Этаж " << targetFloor << " вне допустимого диапазона ("
                << lowerFloor << "-" << upperFloor << ")." << endl;
            return;
        }
        cout << "Лифт едет с этажа " << currentFloor << " на этаж " << targetFloor << "..." << endl;
        currentFloor = targetFloor;
        cout << "Лифт прибыл на этаж " << currentFloor << "." << endl;
    }
};

// ====================== Часть 2: Классы для обоев ======================

class Room {
public:
    string name;
    double length;
    double width;
    double height;
    bool needCeil; // true - клеить потолок

    Room(const string& n, double l, double w, double h, bool ceil)
        : name(n), length(l), width(w), height(h), needCeil(ceil) {
    }

    double wallArea() const {
        return 2 * (length + width) * height;
    }

    double ceilingArea() const {
        return length * width;
    }
};

class WallpaperRoll {
public:
    string name;
    double rollLength;
    double rollWidth;
    double price;

    WallpaperRoll(const string& n, double len, double wid, double p)
        : name(n), rollLength(len), rollWidth(wid), price(p) {
    }

    double areaPerRoll() const {
        return rollLength * rollWidth;
    }
};

class Apartment {
public:
    vector<Room> rooms;

    void addRoom(const Room& room) {
        rooms.push_back(room);
    }
};

// ====================== Тестирование ======================

void testLift() {
    cout << "\n========== ТЕСТИРОВАНИЕ ЛИФТА ==========" << endl;
    Lift myLift(1, 9);

    cout << "Состояние: " << myLift.getStatus() << endl;
    cout << "Текущий этаж: " << myLift.getCurrentFloor() << endl;

    cout << "\nПопытка вызвать на 5 (лифт выключен):" << endl;
    myLift.call(5);

    cout << "\nВключаем лифт." << endl;
    myLift.turnOn();
    cout << "Состояние: " << myLift.getStatus() << endl;

    cout << "\nВызов на 5:" << endl;
    myLift.call(5);

    cout << "\nВызов на 10 (вне диапазона):" << endl;
    myLift.call(10);

    cout << "\nВызов на 1:" << endl;
    myLift.call(1);

    cout << "\nВыключаем лифт." << endl;
    myLift.turnOff();
    cout << "Состояние: " << myLift.getStatus() << endl;

    cout << "\nПопытка вызвать на 3 (выключен):" << endl;
    myLift.call(3);
}

void testWallpaper() {
    cout << "\n========== РАСЧЁТ СТОИМОСТИ ОБОЕВ ==========" << endl;

    int roomCount;
    cout << "Введите количество комнат: ";
    cin >> roomCount;

    Apartment apt;
    for (int i = 0; i < roomCount; ++i) {
        cout << "\n--- Комната " << i + 1 << " ---" << endl;
        string name;
        double length, width, height;
        char ceilChar;

        cout << "Название комнаты: ";
        cin >> name;
        cout << "Длина (м): ";
        cin >> length;
        cout << "Ширина (м): ";
        cin >> width;
        cout << "Высота (м): ";
        cin >> height;
        cout << "Клеить потолок? (y/n): ";
        cin >> ceilChar;
        bool needCeil = (ceilChar == 'y' || ceilChar == 'Y');

        apt.addRoom(Room(name, length, width, height, needCeil));
    }

    int rollTypeCount;
    cout << "\nВведите количество видов обоев: ";
    cin >> rollTypeCount;

    vector<WallpaperRoll> rolls;
    for (int i = 0; i < rollTypeCount; ++i) {
        cout << "\n--- Вид обоев " << i + 1 << " ---" << endl;
        string name;
        double length, width, price;

        cout << "Название: ";
        cin >> name;
        cout << "Длина рулона (м): ";
        cin >> length;
        cout << "Ширина рулона (м): ";
        cin >> width;
        cout << "Цена за рулон (руб): ";
        cin >> price;

        rolls.emplace_back(name, length, width, price);
    }

    vector<int> roomRollChoice(roomCount);
    cout << "\nДля каждой комнаты укажите номер вида обоев (от 1 до " << rollTypeCount << "):" << endl;
    for (int i = 0; i < roomCount; ++i) {
        cout << apt.rooms[i].name << ": ";
        cin >> roomRollChoice[i];
        roomRollChoice[i]--;
        if (roomRollChoice[i] < 0 || roomRollChoice[i] >= rollTypeCount) {
            cout << "Неверный номер, используем вид 1." << endl;
            roomRollChoice[i] = 0;
        }
    }

    vector<double> totalArea(rollTypeCount, 0.0);
    for (int i = 0; i < roomCount; ++i) {
        int rollIdx = roomRollChoice[i];
        totalArea[rollIdx] += apt.rooms[i].wallArea();
        if (apt.rooms[i].needCeil) {
            totalArea[rollIdx] += apt.rooms[i].ceilingArea();
        }
    }

    cout << "\n=== РЕЗУЛЬТАТЫ РАСЧЁТА ===" << endl;
    double totalCost = 0.0;
    for (int i = 0; i < rollTypeCount; ++i) {
        double area = totalArea[i];
        double rollArea = rolls[i].areaPerRoll();
        int rollsNeeded = static_cast<int>(ceil(area / rollArea));
        double cost = rollsNeeded * rolls[i].price;
        totalCost += cost;

        cout << "\nВид обоев: " << rolls[i].name << endl;
        cout << "  Требуемая площадь: " << fixed << setprecision(2) << area << " кв. м" << endl;
        cout << "  Необходимо рулонов: " << rollsNeeded << endl;
        cout << "  Стоимость: " << fixed << setprecision(2) << cost << " руб." << endl;
    }

    cout << "\nОБЩАЯ СТОИМОСТЬ ЗАКУПКИ: " << fixed << setprecision(2) << totalCost << " руб." << endl;
}

int main() {
    // Устанавливаем локаль для поддержки русского языка
    setlocale(LC_ALL, "Russian");
    // Для некоторых систем может потребоваться "ru_RU.UTF-8" или ".1251", но стандартный вариант часто работает

    testLift();
    testWallpaper();

    return 0;
}