#include <iostream>
#include <vector>
#include <string>

// Базовый класс Animal
class Animal {
public:
    virtual void speak() const {
        std::cout << "I am an animal" << std::endl;
    }
    // Виртуальный деструктор пока не требуется, но для безопасности добавим (по желанию)
    virtual ~Animal() = default;
};

// Производные классы
class Dog : public Animal {
public:
    void speak() const override {
        std::cout << "Woof! Woof!" << std::endl;
    }
};

class Cat : public Animal {
public:
    void speak() const override {
        std::cout << "Meow!" << std::endl;
    }
};

class Cow : public Animal {
public:
    void speak() const override {
        std::cout << "Moo!" << std::endl;
    }
};

class Horse : public Animal {
public:
    void speak() const override {
        std::cout << "Neigh!" << std::endl;
    }
};

int main() {
    std::vector<Animal*> animals;

    animals.push_back(new Dog());
    animals.push_back(new Cat());
    animals.push_back(new Cow());
    animals.push_back(new Horse());

    for (const auto* animal : animals) {
        animal->speak();
    }

    // Освобождаем память
    for (auto* animal : animals) {
        delete animal;
    }

    return 0;
}