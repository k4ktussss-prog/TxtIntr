#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>
#include <vector>

using namespace std;

// Функция для преобразования радианов в градусы
double radiansToDegrees(double radians) {
    return radians * 180.0 / M_PI;
}

int main(int argc, char* argv[]) {
    // Если запустили без параметров - показываем справку
    if (argc == 1) {
        cout << "Тригонометрический калькулятор (арксинус и арккосинус)" << endl;
        cout << "======================================================" << endl;
        cout << "Использование:" << endl;
        cout << "  calculator -o arcsin -m degrees 0.5 0.707 0.866" << endl;
        cout << "  calculator -o arccos -m radians 0.5 0.0 -0.5" << endl;
        cout << "  calculator -o arcsin -m degrees 0.2 0.4 0.6 0.8 0.9" << endl;
        cout << endl;
        cout << "Операции:" << endl;
        cout << "  arcsin  - арксинус (обратный синус)" << endl;
        cout << "  arccos  - арккосинус (обратный косинус)" << endl;
        cout << endl;
        cout << "Режимы вывода:" << endl;
        cout << "  degrees - результат в градусах" << endl;
        cout << "  radians - результат в радианах" << endl;
        cout << endl;
        cout << "Аргументы: от 3 до 5 чисел в диапазоне [-1, 1]" << endl;
        cout << "Калькулятор обрабатывает 1 операцию за вызов" << endl;
        return 0;
    }

    // Проверяем базовые условия
    if (argc < 6 || string(argv[1]) != "-o" || string(argv[3]) != "-m") {
        cout << "Ошибка: неправильный формат команды!" << endl;
        cout << "Используйте: calculator -o операция -m режим число1 число2 число3 ..." << endl;
        cout << "Пример: calculator -o arcsin -m degrees 0.5 0.707 0.866" << endl;
        return 1;
    }

    string operation = argv[2];
    string mode = argv[4];
    int num_count = argc - 5;

    // Проверяем количество аргументов
    if (num_count < 3 || num_count > 5) {
        cout << "Ошибка: нужно от 3 до 5 аргументов (получено " << num_count << ")" << endl;
        return 1;
    }

    // Проверяем корректность режима
    if (mode != "degrees" && mode != "radians") {
        cout << "Ошибка: режим должен быть 'degrees' или 'radians'" << endl;
        cout << "Получено: " << mode << endl;
        return 1;
    }

    // Проверяем корректность операции
    if (operation != "arcsin" && operation != "arccos") {
        cout << "Ошибка: неизвестная операция. Доступные: arcsin, arccos" << endl;
        cout << "Получено: " << operation << endl;
        return 1;
    }

    // Читаем числа и проверяем диапазон
    vector<double> arguments;
    bool has_error = false;
    
    for (int i = 0; i < num_count; i++) {
        try {
            double value = stod(argv[5 + i]);
            
            // Проверяем диапазон для арксинуса и арккосинуса
            if (value < -1.0 || value > 1.0) {
                cout << "Ошибка: аргумент " << value << " вне диапазона [-1, 1]" << endl;
                has_error = true;
            }
            
            arguments.push_back(value);
        }
        catch (const invalid_argument& e) {
            cout << "Ошибка: неверный аргумент '" << argv[5 + i] << "'" << endl;
            has_error = true;
        }
        catch (const out_of_range& e) {
            cout << "Ошибка: аргумент '" << argv[5 + i] << "' вне допустимого диапазона" << endl;
            has_error = true;
        }
    }
    
    if (has_error) {
        return 1;
    }

    // Устанавливаем точность вывода
    cout << fixed << setprecision(6);
    
    // Выводим заголовок
    if (operation == "arcsin") {
        cout << "АРКСИНУС (arcsin) - обратная функция синуса" << endl;
    } else {
        cout << "АРККОСИНУС (arccos) - обратная функция косинуса" << endl;
    }
    cout << "Режим вывода: " << (mode == "degrees" ? "градусы" : "радианы") << endl;
    cout << "======================================================" << endl;

    // Выполняем операцию
    for (int i = 0; i < num_count; i++) {
        double value = arguments[i];
        double result = 0.0;
        
        try {
            if (operation == "arcsin") {
                result = asin(value);
            } else { // arccos
                result = acos(value);
            }
            
            // Преобразуем в градусы если нужно
            if (mode == "degrees") {
                result = radiansToDegrees(result);
            }
            
            // Выводим результат
            cout << operation << "(" << value << ") = " << result;
            if (mode == "degrees") {
                cout << "°";
            }
            cout << endl;
        }
        catch (const exception& e) {
            cout << "Ошибка вычисления для аргумента " << value << ": " << e.what() << endl;
        }
    }
    
    cout << "======================================================" << endl;
    cout << "Все вычисления завершены!" << endl;

    return 0;
}
