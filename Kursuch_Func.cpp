#pragma once

#include "Kursuch_Header.h"
#include "Kursuch_main.cpp"

vector<Product> searchProducts(const vector<Product>& products, const string& query) {
    vector<Product> results;
    for (const auto& product : products) {
        if (product.name.find(query) != string::npos) {
            results.push_back(product);
        }
    }
    return results;
}

vector<Product> filterByPriceRange(const vector<Product>& products, double minPrice, double maxPrice) {
    vector<Product> filtered;
    for (const auto& product : products) {
        if (product.price >= minPrice && product.price <= maxPrice) {
            filtered.push_back(product);
        }
    }
    return filtered;
}

void editProduct(vector<Product>& products, int index, const Product& newProduct) {
    if (index >= 0 && index < products.size()) {
        products[index] = newProduct;
        saveDataToFile(products);
    }
    else {
        cerr << "Некорректный индекс продукта.\n";
    }
}

void exportToCSV(const vector<Product>& products, const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Ошибка открытия файла для экспорта.\n";
        return;
    }
    file << "Название,Цена,Количество\n";
    for (const auto& product : products) {
        file << product.name << "," << product.price << "," << product.quantity << "\n";
    }
    file.close();
}

void displayStatistics(const vector<Product>& products) {
    if (products.empty()) {
        cout << "Нет данных для отображения статистики.\n";
        return;
    }
    double totalCost = 0, maxPrice = products[0].price, minPrice = products[0].price;
    int totalQuantity = 0;
    for (const auto& product : products) {
        totalCost += product.price;
        totalQuantity += product.quantity;
        if (product.price > maxPrice) maxPrice = product.price;
        if (product.price < minPrice) minPrice = product.price;
    }
    cout << "Общая стоимость товаров: " << totalCost << "\n";
    cout << "Средняя цена: " << totalCost / products.size() << "\n";
    cout << "Максимальная цена: " << maxPrice << "\n";
    cout << "Минимальная цена: " << minPrice << "\n";
    cout << "Общее количество: " << totalQuantity << "\n";
}

void logAction(const string& action) {
    ofstream logFile("log.txt", ios::app);
    if (logFile.is_open()) {
        logFile << action << " - " << time(nullptr) << "\n";
        logFile.close();
    }
}

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

void clearConsole() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void setInputOutputEncoding() {
#ifdef _WIN32
    system("chcp 65001");
#endif
}

void displayMessage(const string& message) {
    cout << message << endl;
    cout << "Нажмите любую клавишу для продолжения..." << endl;
    _getch();
    clearConsole();
}

void displayMainMenu() {
    cout << "\n=== Главное меню ===\n";
    cout << "1. Добавить данные\n";
    cout << "2. Управление данными\n";
    cout << "3. Сортировать данные\n";
    cout << "4. Поиск данных\n";
    cout << "5. Удаление данных\n";
    cout << "6. Показать статистику\n";
    cout << "7. Управление пользователями\n";
    cout << "8. Экспортировать данные в CSV\n";
    cout << "9. Выход\n";
    cout << "Ваш выбор: ";
}

void inputData(vector<Product>& products) {
    clearConsole();
    Product newProduct;

    cout << "Введите название продукта: ";
    getline(cin, newProduct.name);

    cout << "Введите цену продукта: ";
    cin >> newProduct.price;

    cout << "Введите количество продукта: ";
    cin >> newProduct.quantity;
    cin.ignore();

    products.push_back(newProduct);
    saveDataToFile(products);
    displayMessage("Данные успешно добавлены.");
}

void manageData(vector<Product>& products) {
    while (true) {
        clearConsole();
        displayTableWithMenu(products);

        int index;
        cout << "Введите номер продукта для редактирования или 0 для выхода: ";
        cin >> index;
        cin.ignore();

        if (index == 0) break;

        if (index > 0 && index <= products.size()) {
            Product updatedProduct;
            cout << "Введите новое название: ";
            getline(cin, updatedProduct.name);

            cout << "Введите новую цену: ";
            cin >> updatedProduct.price;

            cout << "Введите новое количество: ";
            cin >> updatedProduct.quantity;
            cin.ignore();

            editProduct(products, index - 1, updatedProduct);
        }
        else {
            displayMessage("Неверный индекс. Попробуйте снова.");
        }
    }
}

void saveDataToFile(const vector<Product>& products) {
    ofstream file("products.txt");
    if (!file.is_open()) {
        cerr << "Ошибка записи данных в файл.\n";
        return;
    }
    for (const auto& product : products) {
        file << product.name << "|" << product.price << "|" << product.quantity << "\n";
    }
    file.close();
}

void loadDataFromFile(vector<Product>& products) {
    ifstream file("products.txt");
    if (!file.is_open()) {
        cerr << "Ошибка чтения данных из файла.\n";
        return;
    }
    products.clear();
    string line;
    while (getline(file, line)) {
        Product product;
        size_t pos1 = line.find('|');
        size_t pos2 = line.rfind('|');
        if (pos1 == string::npos || pos2 == string::npos || pos1 == pos2) continue;

        product.name = line.substr(0, pos1);
        product.price = stod(line.substr(pos1 + 1, pos2 - pos1 - 1));
        product.quantity = stoi(line.substr(pos2 + 1));
        products.push_back(product);
    }
    file.close();
}

void displayTableWithMenu(const vector<Product>& products) {
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
}

void deleteByNumber(vector<Product>& products) {
    int productNumber;
    cout << "Введите номер продукта для удаления (от 0 до " << products.size() - 1 << "): ";
    cin >> productNumber;

    // Проверка на валидность индекса
    if (productNumber >= 0 && productNumber < products.size()) {
        products.erase(products.begin() + productNumber);
        cout << "Продукт удален." << endl;
    }
    else {
        cout << "Неверный номер продукта!" << endl;
    }
}

void displayInformation(const vector<Product>& products) {
    if (products.empty()) {
        cout << "Список продуктов пуст." << endl;
        return;
    }

    cout << "Список продуктов:\n";
    for (size_t i = 0; i < products.size(); ++i) {
        cout << "Продукт " << i << ":\n";
        cout << "Название: " << products[i].name << endl;
        cout << "Цена: " << products[i].price << endl;
        cout << "Количество: " << products[i].quantity << endl;
        cout << "---------------------------------" << endl;
    }
}

void displaySearchTableWithMenu(const vector<Product>& products, const string& query, int searchChoice) {
    vector<Product> searchResults;

    for (const auto& product : products) {
        switch (searchChoice) {
        case 1: // Поиск по имени
            if (product.name.find(query) != string::npos) {
                searchResults.push_back(product);
            }
            break;
        case 2: // Поиск по цене
            if (to_string(product.price).find(query) != string::npos) {
                searchResults.push_back(product);
            }
            break;
        case 3: // Поиск по количеству
            if (to_string(product.quantity).find(query) != string::npos) {
                searchResults.push_back(product);
            }
            break;
        default:
            cout << "Неверный выбор поиска." << endl;
            return;
        }
    }

    // Показ результатов
    if (searchResults.empty()) {
        cout << "Продукты не найдены." << endl;
    }
    else {
        cout << "Результаты поиска:\n";
        for (size_t i = 0; i < searchResults.size(); ++i) {
            cout << "Продукт " << i << ":\n";
            cout << "Название: " << searchResults[i].name << endl;
            cout << "Цена: " << searchResults[i].price << endl;
            cout << "Количество: " << searchResults[i].quantity << endl;
            cout << "---------------------------------" << endl;
        }
    }
}

void manageUserAccount(const string& currentUser) {
    int choice;
    cout << "Добро пожаловать, " << currentUser << endl;
    cout << "1. Изменить имя\n";
    cout << "2. Изменить пароль\n";
    cout << "3. Выйти\n";
    cout << "Выберите опцию: ";
    cin >> choice;

    switch (choice) {
    case 1: {
        string newName;
        cout << "Введите новое имя: ";
        cin >> newName;
        cout << "Имя изменено на: " << newName << endl;
        break;
    }
    case 2: {
        string newPassword;
        cout << "Введите новый пароль: ";
        cin >> newPassword;
        cout << "Пароль изменен." << endl;
        break;
    }
    case 3:
        cout << "Выход из аккаунта..." << endl;
        break;
    default:
        cout << "Неверный выбор!" << endl;
    }
}

void manageSearch(vector<Product>& products) {
    string query;
    int searchChoice;

    cout << "Введите поисковый запрос: ";
    cin.ignore(); // Для очистки буфера ввода
    getline(cin, query);

    cout << "Выберите способ поиска:\n";
    cout << "1. По имени\n";
    cout << "2. По цене\n";
    cout << "3. По количеству\n";
    cout << "Ваш выбор: ";
    cin >> searchChoice;

    displaySearchTableWithMenu(products, query, searchChoice);
}
