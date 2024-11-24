#pragma once

#include "Kursuch_Header.h"

int main() {
    setInputOutputEncoding(); // Установка кодировки ввода/вывода
    vector<Product> products; // Вектор для хранения товаров
    loadDataFromFile(products); // Загрузка данных из файла

    while (true) {
        clearConsole();
        displayMainMenu();

        string choice;
        cin >> choice;

        if (!validateInput(choice)) {
            displayMessage("Некорректный ввод. Пожалуйста, попробуйте снова.");
            continue;
        }

        int action = stoi(choice);

        switch (action) {
        case 1: // Регистрация
            clearConsole();
            registration();
            break;

        case 2: { // Вход в систему
            clearConsole();
            string username, password;
            if (login(username, password)) {
                if (username == ADMIN_USERNAME) {
                    // Меню администратора
                    while (true) {
                        clearConsole();
                        cout << "Меню администратора:\n";
                        cout << "1. Управление пользователями\n";
                        cout << "2. Управление данными товара на складе\n";
                        cout << "3. Выход из аккаунта\n";
                        cout << "Ваш выбор: ";

                        cin >> choice;

                        if (!validateInput(choice)) {
                            displayMessage("Некорректный ввод. Пожалуйста, попробуйте снова.");
                            continue;
                        }

                        int adminChoice = stoi(choice);

                        if (adminChoice == 1) {
                            manageUsers();
                        }
                        else if (adminChoice == 2) {
                            manageData(products);
                        }
                        else if (adminChoice == 3) {
                            break; // Выход из аккаунта
                        }
                        else {
                            displayMessage("Некорректный ввод. Пожалуйста, выберите существующий пункт меню.");
                        }
                    }
                }
                else {
                    // Меню пользователя
                    while (true) {
                        clearConsole();
                        cout << "Меню пользователя:\n";
                        cout << "1. Изменение учетной записи\n";
                        cout << "2. Просмотр данных о товаре на складе\n";
                        cout << "3. Выход из аккаунта\n";
                        cout << "Ваш выбор: ";

                        cin >> choice;

                        if (!validateInput(choice)) {
                            displayMessage("Некорректный ввод. Пожалуйста, попробуйте снова.");
                            continue;
                        }

                        int userChoice = stoi(choice);

                        if (userChoice == 1) {
                            manageUserAccount(username);
                        }
                        else if (userChoice == 2) {
                            displayInformation(products);
                        }
                        else if (userChoice == 3) {
                            break; // Выход из аккаунта
                        }
                        else {
                            displayMessage("Некорректный ввод. Пожалуйста, выберите существующий пункт меню.");
                        }
                    }
                }
            }
            break;
        }

        case 3: // Выход из программы
            clearConsole();
            saveDataToFile(products);
            displayMessage("Выход из программы. До свидания!");
            return 0;

        default: // Некорректный ввод
            displayMessage("Некорректный ввод. Пожалуйста, выберите существующий пункт меню.");
        }
    }

    return 0;
}