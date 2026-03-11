#define _CRT_SECURE_NO_WARNINGS  // для Visual Studio

#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <vector>
#include <limits>

using namespace std;

// ==================== Класс "Абонент" ====================
class Abonent {
private:
    char* fullName;         // ФИО (динамическая память)
    string homePhone;        // домашний телефон
    string workPhone;        // рабочий телефон
    string mobilePhone;      // мобильный телефон
    string info;             // дополнительная информация

public:
    // Конструктор по умолчанию (используем инициализаторы)
    Abonent() : fullName(nullptr), homePhone(""), workPhone(""), mobilePhone(""), info("") {
        fullName = new char[1];
        fullName[0] = '\0';
    }

    // Конструктор с параметрами (инициализаторы)
    Abonent(const char* name, const string& home, const string& work, const string& mobile, const string& extra)
        : homePhone(home), workPhone(work), mobilePhone(mobile), info(extra) {
        fullName = new char[strlen(name) + 1];
        strcpy(fullName, name);
    }

    // Конструктор копирования (глубокое копирование)
    Abonent(const Abonent& other)
        : homePhone(other.homePhone), workPhone(other.workPhone),
        mobilePhone(other.mobilePhone), info(other.info) {
        fullName = new char[strlen(other.fullName) + 1];
        strcpy(fullName, other.fullName);
    }

    // Оператор присваивания
    Abonent& operator=(const Abonent& other) {
        if (this != &other) {
            delete[] fullName;
            fullName = new char[strlen(other.fullName) + 1];
            strcpy(fullName, other.fullName);

            homePhone = other.homePhone;
            workPhone = other.workPhone;
            mobilePhone = other.mobilePhone;
            info = other.info;
        }
        return *this;
    }

    // Деструктор
    ~Abonent() {
        delete[] fullName;
    }

    // Ввод данных с клавиатуры
    void input() {
        char buffer[1024];
        cout << "Введите ФИО: ";
        cin.getline(buffer, 1024);
        setFullName(buffer);

        cout << "Введите домашний телефон: ";
        getline(cin, homePhone);
        cout << "Введите рабочий телефон: ";
        getline(cin, workPhone);
        cout << "Введите мобильный телефон: ";
        getline(cin, mobilePhone);
        cout << "Введите дополнительную информацию: ";
        getline(cin, info);
    }

    // Вывод данных на экран
    void print() const {
        cout << "ФИО: " << (fullName ? fullName : "") << endl;
        cout << "  Домашний: " << homePhone << endl;
        cout << "  Рабочий: " << workPhone << endl;
        cout << "  Мобильный: " << mobilePhone << endl;
        cout << "  Доп. информация: " << info << endl;
    }

    // Аксессоры (inline)
    inline const char* getFullName() const { return fullName; }
    inline string getHomePhone() const { return homePhone; }
    inline string getWorkPhone() const { return workPhone; }
    inline string getMobilePhone() const { return mobilePhone; }
    inline string getInfo() const { return info; }

    inline void setFullName(const char* name) {
        delete[] fullName;
        fullName = new char[strlen(name) + 1];
        strcpy(fullName, name);
    }
    inline void setHomePhone(const string& phone) { homePhone = phone; }
    inline void setWorkPhone(const string& phone) { workPhone = phone; }
    inline void setMobilePhone(const string& phone) { mobilePhone = phone; }
    inline void setInfo(const string& extra) { info = extra; }

    // Сохранение в файл (одна строка с разделителем ';')
    void saveToFile(ofstream& file) const {
        file << fullName << ';' << homePhone << ';' << workPhone << ';'
            << mobilePhone << ';' << info << '\n';
    }

    // Загрузка из файла (строка с разделителем ';')
    bool loadFromFile(ifstream& file) {
        string line;
        if (!getline(file, line)) return false;

        size_t pos1 = line.find(';');
        size_t pos2 = line.find(';', pos1 + 1);
        size_t pos3 = line.find(';', pos2 + 1);
        size_t pos4 = line.find(';', pos3 + 1);

        if (pos1 == string::npos || pos2 == string::npos || pos3 == string::npos || pos4 == string::npos)
            return false;

        string nameStr = line.substr(0, pos1);
        setFullName(nameStr.c_str());
        homePhone = line.substr(pos1 + 1, pos2 - pos1 - 1);
        workPhone = line.substr(pos2 + 1, pos3 - pos2 - 1);
        mobilePhone = line.substr(pos3 + 1, pos4 - pos3 - 1);
        info = line.substr(pos4 + 1);

        return true;
    }
};

// ==================== Класс "Телефонная книга" ====================
class PhoneBook {
private:
    vector<Abonent> abonents;

public:
    // Конструктор по умолчанию
    PhoneBook() {}

    // Деструктор (vector сам вызывает деструкторы Abonent)
    ~PhoneBook() {}

    // Добавление абонента
    void addAbonent() {
        Abonent a;
        cout << "--- Добавление нового абонента ---\n";
        // Очистка буфера перед вводом строки
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        a.input();
        abonents.push_back(a);
        cout << "Абонент добавлен.\n";
    }

    // Удаление абонента по ФИО (первого совпавшего)
    void removeAbonent(const string& name) {
        for (size_t i = 0; i < abonents.size(); ++i) {
            if (name == abonents[i].getFullName()) {
                abonents.erase(abonents.begin() + i);
                cout << "Абонент \"" << name << "\" удален.\n";
                return;
            }
        }
        cout << "Абонент с таким ФИО не найден.\n";
    }

    // Поиск абонентов по части ФИО (регистр учитывается)
    void searchByName(const string& part) const {
        bool found = false;
        for (size_t i = 0; i < abonents.size(); ++i) {
            if (strstr(abonents[i].getFullName(), part.c_str()) != nullptr) {
                cout << "[" << i << "]\n";
                abonents[i].print();
                cout << endl;
                found = true;
            }
        }
        if (!found) {
            cout << "Абоненты с ФИО, содержащим \"" << part << "\", не найдены.\n";
        }
    }

    // Показать всех абонентов
    void showAll() const {
        if (abonents.empty()) {
            cout << "Телефонная книга пуста.\n";
            return;
        }
        cout << "--- Список абонентов ---\n";
        for (size_t i = 0; i < abonents.size(); ++i) {
            cout << "[" << i << "]\n";
            abonents[i].print();
            cout << endl;
        }
    }

    // Сохранение в файл
    void saveToFile(const char* filename) const {
        ofstream file(filename);
        if (!file.is_open()) {
            cerr << "Ошибка открытия файла для записи!\n";
            return;
        }
        for (size_t i = 0; i < abonents.size(); ++i) {
            abonents[i].saveToFile(file);
        }
        file.close();
        cout << "Данные сохранены в файл \"" << filename << "\".\n";
    }

    // Загрузка из файла
    void loadFromFile(const char* filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cerr << "Ошибка открытия файла для чтения!\n";
            return;
        }

        abonents.clear();
        Abonent a;
        while (a.loadFromFile(file)) {
            abonents.push_back(a);
        }
        file.close();
        cout << "Данные загружены из файла \"" << filename << "\".\n";
    }
};

// ==================== Главная функция ====================
int main() {
    setlocale(LC_ALL, "Russian"); // для поддержки русского языка в консоли Windows

    PhoneBook book;
    int choice;
    string searchStr;

    do {
        cout << "\n===== Телефонная книга =====\n";
        cout << "1. Добавить абонента\n";
        cout << "2. Удалить абонента по ФИО\n";
        cout << "3. Поиск абонентов по ФИО\n";
        cout << "4. Показать всех\n";
        cout << "5. Сохранить в файл\n";
        cout << "6. Загрузить из файла\n";
        cout << "0. Выход\n";
        cout << "Ваш выбор: ";
        cin >> choice;

        switch (choice) {
        case 1:
            book.addAbonent();
            break;
        case 2: {
            cout << "Введите ФИО для удаления: ";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, searchStr);
            book.removeAbonent(searchStr);
            break;
        }
        case 3: {
            cout << "Введите часть ФИО для поиска: ";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, searchStr);
            book.searchByName(searchStr);
            break;
        }
        case 4:
            book.showAll();
            break;
        case 5:
            book.saveToFile("phonebook.txt");
            break;
        case 6:
            book.loadFromFile("phonebook.txt");
            break;
        case 0:
            cout << "Выход.\n";
            break;
        default:
            cout << "Неверный выбор!\n";
        }
    } while (choice != 0);

    return 0;
}