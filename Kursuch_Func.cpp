#pragma once

#include "Kursuch_Header.h"

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

void registration()
{
    clearConsole();
    string username, password;
    string role = "user"; // Новая характеристика "user"

    cout << "Введите логин: ";
    cin >> username;

    cout << "Введите пароль: ";
    cin >> password;

    ofstream file("users.txt", ios::app);
    if (file.is_open()) {



        file << username << " " << password << " " << role << endl; // Запись роли "user"
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
        if (ch == 8) {
            if (!password.empty()) {
                cout << "\b \b";
                password.pop_back();
            }
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
            return; // Возврат назад
        }
        if (userChoice < 1 || userChoice > users.size()) {
            cout << "Неверный выбор пользователя!" << endl;
            continue;
        }

        string selectedUser = users[userChoice - 1];
        string username = selectedUser.substr(0, selectedUser.find(' '));
        string password = selectedUser.substr(selectedUser.find(' ') + 1, selectedUser.rfind(' ') - selectedUser.find(' ') - 1);
        string role = selectedUser.substr(selectedUser.rfind(' ') + 1); // Получаем роль пользователя

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
            continue; // Возврат к выбору пользователя
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

    // Вывод таблицы с данными о товарах
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

    // Вывод меню удаления
    cout << "\nУдалить данные:\n"
        << "1. Удалить по номеру\n"
        << "2. Удалить все данные\n"
        << "3. Назад\nВаш выбор: ";
}

void manageDeletion(vector<Product>& products) {
    while (true) {
        displayDeleteTableWithMenu(products); // Вывод таблицы с данными и меню удаления

        int deleteChoice;
        cin >> deleteChoice;
        cin.ignore(); // Игнорирование символа новой строки после ввода выбора

        switch (deleteChoice) {
        case 1: {
            clearConsole();
            displayDeleteTableWithMenu(products); // Обновление таблицы перед вводом номера для удаления
            int index;
            cout << "Введите номер продукта для удаления: ";
            cin >> index;
            if (index > 0 && index <= products.size()) { // Изменение условия на 1-based index
                products.erase(products.begin() + index - 1); // Корректировка индекса на 0-based
                saveDataToFile(products);
            }
            else {
                cerr << "Некорректный номер продукта.\n";
            }
            break;
        }
        case 2:
            clearConsole();
            displayDeleteTableWithMenu(products); // Обновление таблицы перед удалением всех данных
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

    // Вывод меню сортировки
    cout << "\nСортировать данные:\n"
        << "1. Сортировать по названию\n"
        << "2. Сортировать по цене\n"
        << "3. Сортировать по количеству\n"
        << "4. Назад\nВаш выбор: ";
}

void manageSorting(vector<Product>& products) {
    while (true) {
        displaySortTableWithMenu(products); // Вывод таблицы с данными и меню сортировки

        int sortChoice;
        cin >> sortChoice;
        cin.ignore(); // Игнорирование символа новой строки после ввода выбора

        switch (sortChoice) {
        case 1:
            (products);
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

void manageUserAccount(const string& currentUser) {
    while (true) {
        clearConsole();
        ifstream file("users.txt");
        if (!file.is_open()) {
            cout << "Ошибка при открытии файла пользователей!" << endl;
            return;
        }

        vector<string> users;
        string line;
        while (getline(file, line)) {
            users.push_back(line);
        }
        file.close();

        string selectedUser;
        for (const auto& user : users) {
            if (user.substr(0, user.find(' ')) == currentUser) {
                selectedUser = user;
                break;
            }
        }

        if (selectedUser.empty()) {
            cout << "Пользователь не найден!" << endl;
            return;
        }

        string username = selectedUser.substr(0, selectedUser.find(' '));
        string password = selectedUser.substr(selectedUser.find(' ') + 1, selectedUser.rfind(' ') - selectedUser.find(' ') - 1);

        cout << "Выберите, что вы хотите сделать:" << endl;
        cout << "1. Изменить логин" << endl;
        cout << "2. Изменить пароль" << endl;
        cout << "3. Удалить аккаунт" << endl;
        cout << "4. Вернуться назад" << endl;
        cout << "Ваш выбор: ";
        int actionChoice;
        cin >> actionChoice;

        switch (actionChoice) {
        case 1: {
            cout << "Введите новый логин: ";
            string newUsername;
            cin >> newUsername;
            for (auto& user : users) {
                if (user == selectedUser) {
                    user.replace(0, username.length(), newUsername);


                    selectedUser = user;
                    username = newUsername;
                }
            }
            cout << "Логин успешно изменен на '" << username << "'!" << endl;
            break;
        }
        case 2: {
            cout << "Введите новый пароль: ";
            string newPassword;
            cin >> newPassword;
            for (auto& user : users) {
                if (user == selectedUser) {
                    size_t pos = user.find(username) + username.length() + 1;
                    user.replace(pos, password.length(), newPassword);
                    selectedUser = user;
                    password = newPassword;
                }
            }
            cout << "Пароль успешно изменен!" << endl;
            break;
        }
        case 3: {
            users.erase(remove(users.begin(), users.end(), selectedUser), users.end());
            cout << "Аккаунт успешно удален!" << endl;
            return; // Возврат в начальное меню
        }
        case 4: {
            return; // Возврат в начальное меню
        }
        default:
            cout << "Неверный выбор!" << endl;
            continue;
        }

        ofstream outFile("users.txt");
        if (!outFile.is_open()) {
            cout << "Ошибка при открытии файла для записи!" << endl;
        }
    }
}

//////////////////////////////////////////////////

void setInputOutputEncoding() {
SetConsoleCP(1251); 
SetConsoleOutputCP(1251);
}


void clearConsole()
{
    system("cls");
}

void displayMessage(const string& message) {
    cout << message << endl;
    cout << "Нажмите любую клавишу для продолжения..." << endl;
    _getch();
}

void displayMainMenu() {
    cout << "Выберите действие:\n";
    cout << "1. Регистрация\n";
    cout << "2. Вход в систему\n";
    cout << "3. Выход\n";
    cout << "Ваш выбор: ";
}

void saveDataToFile(const vector<Product>& products) {
    ofstream outFile("products.txt"); // Открытие файла для записи

    if (!outFile) {
        cerr << "Ошибка при открытии файла для записи!" << endl;
        return;
    }

    for (const auto& product : products) {
        outFile << product.name << '\n'
            << product.price << '\n'
            << product.quantity << '\n';
    }

    outFile.close(); // Закрытие файла
    displayMessage("Данные успешно сохранены в файл.");
}

void loadDataFromFile(vector<Product>& products) {
    ifstream inFile("products.txt"); // Открытие файла для чтения

    if (!inFile) {
        cerr << "Ошибка при открытии файла для чтения!" << endl;
        return;
    }

    products.clear(); // Очищаем вектор перед загрузкой новых данных

    Product product;
    while (getline(inFile, product.name)) { // Чтение имени продукта
        inFile >> product.price >> product.quantity;
        inFile.ignore(); // Игнорируем символ новой строки после числа
        products.push_back(product); // Добавление в вектор
    }

    inFile.close(); // Закрытие файла
    displayMessage("Данные успешно загружены из файла.");
}

void inputData(vector<Product>& products) {
    Product newProduct;
    cout << "Введите имя товара: ";
    cin.ignore(); // Игнорируем остаточный символ новой строки
    getline(cin, newProduct.name); // Вводим имя товара

    cout << "Введите цену товара: ";
    cin >> newProduct.price; // Вводим цену товара

    cout << "Введите количество товара: ";
    cin >> newProduct.quantity; // Вводим количество товара

    products.push_back(newProduct); // Добавляем новый товар в вектор
    displayMessage("Товар успешно добавлен.");
}

// Удаляет продукт по номеру
void deleteByNumber(vector<Product>& products) {
    int index;
    cout << "Введите номер товара для удаления (от 1 до " << products.size() << "): ";
    cin >> index;

    if (index > 0 && index <= products.size()) {
        products.erase(products.begin() + index - 1);
        displayMessage("Товар успешно удален.");
    }
    else {
        ("Некорректный номер товара.");
    }
}

// Отображает таблицу для поиска продуктов с меню
void displaySearchTableWithMenu(const vector<Product>& products, const string& query, int searchChoice) {
    cout << "Поиск данных:\n";
    cout << "1. По количеству\n";
    cout << "2. По цене\n";
    cout << "3. По названию\n";
    cout << "4. Назад (ESC)\n";
    cout << "Ваш выбор: ";

    if (searchChoice != 3) {
        string searchQuery;
        cout << "Введите запрос для поиска: ";
        cin.ignore();
        getline(cin, searchQuery);
        cout << "Результаты поиска:\n";

        for (const auto& product : products) {
            bool match = false;
            if (searchChoice == 1 && to_string(product.quantity).find(searchQuery) != string::npos)
                match = true;
            if (searchChoice == 2 && to_string(product.price).find(searchQuery) != string::npos)
                match = true;
            if (searchChoice == 3 && product.name.find(searchQuery) != string::npos)
                match = true;

            if (match) {
                cout << setw(20) << left << product.name
                    << setw(10) << product.price
                    << setw(10) << product.quantity << endl;
            }
        }
    }
}

// Отображает информацию о продуктах
void displayInformation(vector<Product>& products) {
    cout << "Информация о продуктах:\n";
    for (const auto& product : products) {
        cout << setw(20) << left << product.name
            << setw(10) << product.price
            << setw(10) << product.quantity << endl;
    }
}

// Отображает таблицу с меню для управления данными о продуктах
void displayTableWithMenu(const vector<Product>& products) {
    cout << "Управление данными товара на складе:\n";
    cout << "1. Ввести данные о товаре\n";
    cout << "2. Удалить данные\n";
    cout << "3. Сортировать данные\n";
    cout << "4. Поиск данных\n";
    cout << "5. Назад\n";
    cout << "Ваш выбор: ";
}

// Управляет данными о продуктах
void manageData(vector<Product>& products) {
    while (true) {
        clearConsole();
        displayTableWithMenu(products);
        string choice;
        cin >> choice;

        if (choice == "1") {
            inputData(products); // Ввод данных
        }
        else if (choice == "2") {
            displayDeleteTableWithMenu(products); // Удаление данных
        }
        else if (choice == "3") {
            (products); // Сортировка данных
        }
        else if (choice == "4") {
            manageSearch(products); // Поиск данных
        }
        else if (choice == "5") {
            break; // Назад
        }
        else {
            ("Некорректный ввод. Пожалуйста, выберите существующий пункт меню.");
        }
    }
}

// Управляет процессом поиска продуктов
void manageSearch(vector<Product>& products) {
    string choice;
    while (true) {
        clearConsole();
        displaySearchTableWithMenu(products);
        cin >> choice;

        if (choice == "1" || choice == "2" || choice == "3") {
            displaySearchTableWithMenu(products, "", stoi(choice)); // Поиск по выбранному критерию
        }
        else if (choice == "4") {
            break; // Назад
        }
        else {
            ("Некорректный ввод. Пожалуйста, выберите существующий пункт меню.");
        }
    }
}