#pragma once
#include "Kursuch_Header.h"
#include "Kursuch_main.cpp"

void deleteAllData(vector<Product>& products) {
    clearConsole();
    products.clear();
    saveDataToFile(products);
}

void sortByName(vector<Product>& products) {
    sort(products.begin(), products.end(), [](const Product& a, const Product& b) {
        return a.name < b.name;
        });
    saveDataToFile(products);
}

void sortByPrice(vector<Product>& products) {
    sort(products.begin(), products.end(), [](const Product& a, const Product& b) {
        return a.price < b.price;
        });
    saveDataToFile(products);
}

void sortByQuantity(vector<Product>& products) {
    sort(products.begin(), products.end(), [](const Product& a, const Product& b) {
        return a.quantity < b.quantity;
        });
    saveDataToFile(products);
}

void registration() {
    clearConsole();
    string username, password;
    string role = "user";

    cout << "Введите логин: ";
    cin >> username;

    cout << "Введите пароль: ";
    cin >> password;

    ofstream file("users.txt", ios::app);
    if (file.is_open()) {
        file << username << " " << password << " " << role << endl;
        file.close();
        cout << "Регистрация завершена успешно!" << endl;
    }
    else {
        cout << "Ошибка при открытии файла!" << endl;
    }
}

bool login(string& username, string& password) {
    clearConsole();
    cout << "Введите логин: ";
    cin >> username;

    cout << "Введите пароль: ";
    char ch;
    password = "";
    while ((ch = _getch()) != 13) {
        if (ch == 8 && !password.empty()) {
            cout << "\b \b";
            password.pop_back();
        }
        else {
            cout << "*";
            password += ch;
        }
    }
    cout << endl;

    if (username == ADMIN_USERNAME && password == ADMIN_PASSWORD) {
        cout << "Вход выполнен как администратор!" << endl;
        return true;
    }

    ifstream file("users.txt");
    if (file.is_open()) {
        string savedUsername, savedPassword, role;
        while (file >> savedUsername >> savedPassword >> role) {
            if (savedUsername == username && savedPassword == password) {
                cout << "Вход выполнен успешно!" << endl;
                file.close();
                return true;
            }
        }
        file.close();
    }

    cout << "Логин или пароль неверные." << endl;
    return false;
}

void manageUsers() {
    while (true) {
        clearConsole();
        ifstream file("users.txt");
        if (!file.is_open()) {
            cout << "Ошибка при открытии файла пользователей!" << endl;
            return;
        }

        vector<string> users;
        cout << "Список пользователей:" << endl;
        string line;
        int i = 1;
        while (getline(file, line)) {
            string username = line.substr(0, line.find(' '));
            if (username != ADMIN_USERNAME) {
                cout << i << ". " << username << endl;
                users.push_back(line);
                i++;
            }
        }
        file.close();

        cout << "Выберите пользователя для управления (введите номер) или 0 для возврата: ";
        int userChoice;
        cin >> userChoice;
        if (userChoice == 0) {
            return;
        }
        if (userChoice < 1 || userChoice > users.size()) {
            cout << "Неверный выбор пользователя!" << endl;
            continue;
        }

        string selectedUser = users[userChoice - 1];
        string username = selectedUser.substr(0, selectedUser.find(' '));
        string password = selectedUser.substr(selectedUser.find(' ') + 1, selectedUser.rfind(' ') - selectedUser.find(' ') - 1);
        string role = selectedUser.substr(selectedUser.rfind(' ') + 1);

        clearConsole();
        cout << "Вы выбрали пользователя '" << username << "'." << endl;
        cout << "Данные пользователя:" << endl;

        cout << "Логин: " << username << endl;
        cout << "Пароль: " << password << endl;
        cout << "Выберите, что вы хотите сделать:" << endl;
        cout << "1. Изменить логин" << endl;
        cout << "2. Изменить пароль" << endl;
        cout << "3. Удалить аккаунт" << endl;
        cout << "4. Вернуться назад" << endl;
        cout << "Ваш выбор: ";
        int actionChoice;
        cin >> actionChoice;

        if (actionChoice == 4) {
            continue;
        }

        switch (actionChoice) {
        case 1: {
            cout << "Введите новый логин для пользователя '" << username << "': ";
            string newUsername;
            cin >> newUsername;
            for (auto& user : users) {
                if (user == selectedUser) {
                    user.replace(0, username.length(), newUsername);
                }
            }
            break;
        }
        case 2: {
            cout << "Введите новый пароль для пользователя '" << username << "': ";
            string newPassword;
            cin >> newPassword;
            for (auto& user : users) {
                if (user == selectedUser) {
                    size_t pos = user.find(username) + username.length() + 1;
                    user.replace(pos, password.length(), newPassword);
                }
            }
            break;
        }
        case 3: {
            users.erase(remove(users.begin(), users.end(), selectedUser), users.end());
            break;
        }
        default:
            cout << "Неверный выбор!" << endl;
            continue;
        }

        ofstream outFile("users.txt");
        if (!outFile.is_open()) {
            cout << "Ошибка при открытии файла для записи!" << endl;
            return;
        }

        for (const auto& user : users) {
            outFile << user << endl;
        }
        outFile.close();

        cout << "Данные успешно обновлены!" << endl;
        return;
    }
}

bool validateInput(const string& input) {
    for (char c : input) {
        if (!isdigit(c)) {
            return false;
        }
    }
    return true;
}

void displayDeleteTableWithMenu(const vector<Product>& products) {
    clearConsole();

    cout << left << setw(10) << "N" << setw(20) << "Название" << setw(10) << "Цена" << setw(10) << "Количество" << "\n";
    cout << string(50, '-') << "\n";

    int index = 1;
    for (const auto& product : products) {
        cout << setw(10) << index
            << setw(20) << product.name
            << setw(10) << product.price
            << setw(10) << product.quantity
            << "\n";
        index++;
    }

    cout << "\nУдалить данные:\n"
        << "1. Удалить по номеру\n"
        << "2. Удалить все данные\n"
        << "3. Назад\nВаш выбор: ";
}

void manageDeletion(vector<Product>& products) {
    while (true) {
        displayDeleteTableWithMenu(products);

        int deleteChoice;
        cin >> deleteChoice;
        cin.ignore();

        switch (deleteChoice) {
        case 1: {
            clearConsole();
            displayDeleteTableWithMenu(products);
            int index;
            cout << "Введите номер продукта для удаления: ";
            cin >> index;
            if (index > 0 && index <= products.size()) {
                products.erase(products.begin() + index - 1);
                saveDataToFile(products);
            }
            else {
                cerr << "Некорректный номер продукта.\n";
            }
            break;
        }
        case 2:
            clearConsole();
            displayDeleteTableWithMenu(products);
            products.clear();
            saveDataToFile(products);
            break;
        case 3:
            return;
        default:
            cout << "Неверный выбор!" << endl;
            break;
        }
    }
}

void displaySortTableWithMenu(const vector<Product>& products) {
    clearConsole();

    cout << left << setw(10) << "N" << setw(20) << "Название" << setw(10) << "Цена" << setw(10) << "Количество" << "\n";
    cout << string(50, '-') << "\n";

    int index = 1;
    for (const auto& product : products) {
        cout << setw(10) << index
            << setw(20) << product.name
            << setw(10) << product.price
            << setw(10) << product.quantity
            << "\n";
        index++;
    }

    cout << "\nСортировать данные:\n"
        << "1. Сортировать по названию\n"
        << "2. Сортировать по цене\n"
        << "3. Сортировать по количеству\n"
        << "4. Назад\nВаш выбор: ";
}

void manageSorting(vector<Product>& products) {
    while (true) {
        displaySortTableWithMenu(products);

        int sortChoice;
        cin >> sortChoice;
        cin.ignore();

        switch (sortChoice) {
        case 1:
            sortByName(products);
            break;
        case 2:
            sortByPrice(products);
            break;
        case 3:
            sortByQuantity(products);
            break;
        case 4:
            return;
        default:
            cout << "Неверный выбор!" << endl;
            break;
        }
    }
}
