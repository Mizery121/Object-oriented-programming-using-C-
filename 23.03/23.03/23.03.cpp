#include <iostream>
#include <string>
#include <stdexcept>
#include <locale>

using namespace std;

template <typename T>
class SinglyLinkedList {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& value) : data(value), next(nullptr) {}
    };

    Node* head;
    size_t list_size;

public:
    SinglyLinkedList() : head(nullptr), list_size(0) {}

    ~SinglyLinkedList() {
        clear();
    }

    // Запрещаем копирование
    SinglyLinkedList(const SinglyLinkedList&) = delete;
    SinglyLinkedList& operator=(const SinglyLinkedList&) = delete;

    void push_front(const T& value) {
        Node* new_node = new Node(value);
        new_node->next = head;
        head = new_node;
        ++list_size;
    }

    void push_back(const T& value) {
        Node* new_node = new Node(value);
        if (!head) {
            head = new_node;
        }
        else {
            Node* current = head;
            while (current->next)
                current = current->next;
            current->next = new_node;
        }
        ++list_size;
    }

    void pop_front() {
        if (empty())
            throw underflow_error("Список пуст");
        Node* temp = head;
        head = head->next;
        delete temp;
        --list_size;
    }

    void pop_back() {
        if (empty())
            throw underflow_error("Список пуст");
        if (list_size == 1) {
            delete head;
            head = nullptr;
        }
        else {
            Node* current = head;
            while (current->next && current->next->next)
                current = current->next;
            delete current->next;
            current->next = nullptr;
        }
        --list_size;
    }

    T& front() {
        if (empty())
            throw underflow_error("Список пуст");
        return head->data;
    }

    T& back() {
        if (empty())
            throw underflow_error("Список пуст");
        Node* current = head;
        while (current->next)
            current = current->next;
        return current->data;
    }

    bool empty() const {
        return list_size == 0;
    }

    size_t size() const {
        return list_size;
    }

    void clear() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
        list_size = 0;
    }
};

int main() {
    setlocale(LC_ALL, "Ru");

    // ----- Целые числа -----
    cout << "=== Целые числа ===" << endl;
    SinglyLinkedList<int> intList;

    intList.push_back(10);
    intList.push_back(20);
    intList.push_back(30);
    intList.push_front(5);

    cout << "Размер: " << intList.size() << endl;
    cout << "Первый: " << intList.front() << ", последний: " << intList.back() << endl;

    cout << "Удаляем первый и последний" << endl;
    intList.pop_front();
    intList.pop_back();
    cout << "Размер после удалений: " << intList.size() << endl;

    // Вывод вручную (без итератора)
    cout << "Элементы: ";
    cout << "front = " << intList.front() << ", size = " << intList.size() << endl;

    intList.clear();
    cout << "После очистки пуст? " << (intList.empty() ? "Да" : "Нет") << endl;

    // ----- Строки -----
    cout << "\n=== Строки ===" << endl;
    SinglyLinkedList<string> strList;
    strList.push_back("Hello");
    strList.push_back("world");
    strList.push_front("C++");

    cout << "Первый: " << strList.front() << ", последний: " << strList.back() << endl;
    cout << "Размер: " << strList.size() << endl;

    strList.pop_front();
    strList.pop_back();
    cout << "После удалений размер: " << strList.size() << endl;
    cout << "Оставшийся элемент: " << strList.front() << endl;

    strList.clear();
    cout << "Пусто? " << (strList.empty() ? "Да" : "Нет") << endl;

    return 0;
}