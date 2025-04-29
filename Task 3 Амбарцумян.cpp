#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <algorithm>
#include <iomanip>

using namespace std;

// Перечисление статусов студентов
enum class StudentStatus {
    FULL_TIME,
    PART_TIME,
    EXCHANGE,
    GRADUATED,
    DROPPED_OUT
};

// Преобразование статуса в строку
string statusToString(StudentStatus status) {
    switch (status) {
        case StudentStatus::FULL_TIME: return "Full-time";
        case StudentStatus::PART_TIME: return "Part-time";
        case StudentStatus::EXCHANGE: return "Изменен";
        case StudentStatus::GRADUATED: return "Выпустился";
        case StudentStatus::DROPPED_OUT: return "Отчислен";
        default: return "Неизвестно";
    }
}

struct Student {
    string name;
    int id;
    string major;
    double gpa;
    StudentStatus status;

    // Конструктор 
    Student(const string& name, int id, const string& major, double gpa, StudentStatus status)
        : name(name), id(id), major(major), gpa(gpa), status(status) {}

    // Вывод инфы о студенте
    void print() const {
        cout << left << setw(20) << name 
             << setw(10) << id 
             << setw(10) << major 
             << fixed << setprecision(2) << setw(8) << gpa 
             << statusToString(status) << endl;
    }
};

class StudentRegistry {
private:
    vector<Student> students;

public:
    // Регистрация нового студента
    void registerStudent(const string& name, int id, const string& major, double gpa, StudentStatus status) {
        // Проверка на дубликат ID
        if (find_if(students.begin(), students.end(), 
            [id](const Student& s) { return s.id == id; }) != students.end()) {
            throw invalid_argument("Студент с ID " + to_string(id) + " уже существует.");
        }

        if (gpa < 0.0 || gpa > 4.0) {
            throw invalid_argument("GPA не меньше 0 и не больше 4.");
        }

        if (name.empty()) {
            throw invalid_argument("имя не может быть пустым.");
        }

        // Добавление студента
        students.emplace_back(name, id, major, gpa, status);
    }

    void changeStatus(const string& name, StudentStatus newStatus) {
        bool found = false;
        for (auto& student : students) {
            if (student.name == name) {
                student.status = newStatus;
                found = true;
                break;
            }
        }
        
        if (!found) {
            throw invalid_argument("Студент '" + name + "' не найден.");
        }
    }

    // Вывод списка всех студентов
    void printStudents() const {
        if (students.empty()) {
            cout << "Студенты кончились." << endl;
            return;
        }

        cout << left << setw(20) << "Имя" 
             << setw(10) << "ID" 
             << setw(10) << "Major" 
             << setw(10) << "GPA" 
             << "Статус" << endl;
        cout << string(70, '-') << endl;

        for (const auto& student : students) {
            student.print();
        }
    }

    // Колво зарег студентов
    size_t getStudentCount() const {
        return students.size();
    }
};

int main() {
    StudentRegistry registry;
    return 0;
}