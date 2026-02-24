// Задание 2: Стоимость обоев
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

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

    // Площадь стен (без учёта окон/дверей, упрощённо)
    double wallArea() const {
        return 2 * (length + width) * height;
    }

    // Площадь потолка
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

    // Площадь одного рулона
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

int main() {
    cout << "=== Расчёт стоимости обоев ===" << endl;

    // Ввод количества комнат
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

    // Ввод видов обоев
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

    // Для каждой комнаты выбираем вид обоев
    vector<int> roomRollChoice(roomCount);
    cout << "\nДля каждой комнаты укажите номер вида обоев (от 1 до " << rollTypeCount << "):" << endl;
    for (int i = 0; i < roomCount; ++i) {
        cout << apt.rooms[i].name << ": ";
        cin >> roomRollChoice[i];
        // переводим в индекс вектора (с 0)
        roomRollChoice[i]--;
        if (roomRollChoice[i] < 0 || roomRollChoice[i] >= rollTypeCount) {
            cout << "Неверный номер, используем вид 1." << endl;
            roomRollChoice[i] = 0;
        }
    }

    // Суммируем площади по каждому виду
    vector<double> totalArea(rollTypeCount, 0.0);
    for (int i = 0; i < roomCount; ++i) {
        int rollIdx = roomRollChoice[i];
        totalArea[rollIdx] += apt.rooms[i].wallArea();
        if (apt.rooms[i].needCeil) {
            totalArea[rollIdx] += apt.rooms[i].ceilingArea();
        }
    }

    // Расчёт необходимого количества рулонов и стоимости
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

    return 0;
}