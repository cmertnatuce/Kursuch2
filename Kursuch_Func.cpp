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
        cerr << "������������ ������ ��������.\n";
    }
}

void exportToCSV(const vector<Product>& products, const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "������ �������� ����� ��� ��������.\n";
        return;
    }
    file << "��������,����,����������\n";
    for (const auto& product : products) {
        file << product.name << "," << product.price << "," << product.quantity << "\n";
    }
    file.close();
}

void displayStatistics(const vector<Product>& products) {
    if (products.empty()) {
        cout << "��� ������ ��� ����������� ����������.\n";
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
    cout << "����� ��������� �������: " << totalCost << "\n";
    cout << "������� ����: " << totalCost / products.size() << "\n";
    cout << "������������ ����: " << maxPrice << "\n";
    cout << "����������� ����: " << minPrice << "\n";
    cout << "����� ����������: " << totalQuantity << "\n";
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

    cout << "������� �����: ";
    cin >> username;

    cout << "������� ������: ";
    cin >> password;

    ofstream file("users.txt", ios::app);
    if (file.is_open()) {
        file << username << " " << password << " " << role << endl;
        file.close();
        cout << "����������� ��������� �������!" << endl;
    }
    else {
        cout << "������ ��� �������� �����!" << endl;
    }
}

bool login(string& username, string& password) {
    clearConsole();
    cout << "������� �����: ";
    cin >> username;

    cout << "������� ������: ";
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
        cout << "���� �������� ��� �������������!" << endl;
        return true;
    }

    ifstream file("users.txt");
    if (file.is_open()) {
        string savedUsername, savedPassword, role;
        while (file >> savedUsername >> savedPassword >> role) {
            if (savedUsername == username && savedPassword == password) {
                cout << "���� �������� �������!" << endl;
                file.close();
                return true;
            }
        }
        file.close();
    }

    cout << "����� ��� ������ ��������." << endl;
    return false;
}

void manageUsers() {
    while (true) {
        clearConsole();
        ifstream file("users.txt");
        if (!file.is_open()) {
            cout << "������ ��� �������� ����� �������������!" << endl;
            return;
        }

        vector<string> users;
        cout << "������ �������������:" << endl;
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

        cout << "�������� ������������ ��� ���������� (������� �����) ��� 0 ��� ��������: ";
        int userChoice;
        cin >> userChoice;
        if (userChoice == 0) {
            return;
        }
        if (userChoice < 1 || userChoice > users.size()) {
            cout << "�������� ����� ������������!" << endl;
            continue;
        }

        string selectedUser = users[userChoice - 1];
        string username = selectedUser.substr(0, selectedUser.find(' '));
        string password = selectedUser.substr(selectedUser.find(' ') + 1, selectedUser.rfind(' ') - selectedUser.find(' ') - 1);
        string role = selectedUser.substr(selectedUser.rfind(' ') + 1);

        clearConsole();
        cout << "�� ������� ������������ '" << username << "'." << endl;
        cout << "������ ������������:" << endl;

        cout << "�����: " << username << endl;
        cout << "������: " << password << endl;
        cout << "��������, ��� �� ������ �������:" << endl;
        cout << "1. �������� �����" << endl;
        cout << "2. �������� ������" << endl;
        cout << "3. ������� �������" << endl;
        cout << "4. ��������� �����" << endl;
        cout << "��� �����: ";
        int actionChoice;
        cin >> actionChoice;

        if (actionChoice == 4) {
            continue;
        }

        switch (actionChoice) {
        case 1: {
            cout << "������� ����� ����� ��� ������������ '" << username << "': ";
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
            cout << "������� ����� ������ ��� ������������ '" << username << "': ";
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
            cout << "�������� �����!" << endl;
            continue;
        }

        ofstream outFile("users.txt");
        if (!outFile.is_open()) {
            cout << "������ ��� �������� ����� ��� ������!" << endl;
            return;
        }

        for (const auto& user : users) {
            outFile << user << endl;
        }
        outFile.close();

        cout << "������ ������� ���������!" << endl;
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

    cout << left << setw(10) << "N" << setw(20) << "��������" << setw(10) << "����" << setw(10) << "����������" << "\n";
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

    cout << "\n������� ������:\n"
        << "1. ������� �� ������\n"
        << "2. ������� ��� ������\n"
        << "3. �����\n��� �����: ";
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
            cout << "������� ����� �������� ��� ��������: ";
            cin >> index;
            if (index > 0 && index <= products.size()) {
                products.erase(products.begin() + index - 1);
                saveDataToFile(products);
            }
            else {
                cerr << "������������ ����� ��������.\n";
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
            cout << "�������� �����!" << endl;
            break;
        }
    }
}

void displaySortTableWithMenu(const vector<Product>& products) {
    clearConsole();

    cout << left << setw(10) << "N" << setw(20) << "��������" << setw(10) << "����" << setw(10) << "����������" << "\n";
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

    cout << "\n����������� ������:\n"
        << "1. ����������� �� ��������\n"
        << "2. ����������� �� ����\n"
        << "3. ����������� �� ����������\n"
        << "4. �����\n��� �����: ";
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
            cout << "�������� �����!" << endl;
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
    cout << "������� ����� ������� ��� �����������..." << endl;
    _getch();
    clearConsole();
}

void displayMainMenu() {
    cout << "\n=== ������� ���� ===\n";
    cout << "1. �������� ������\n";
    cout << "2. ���������� �������\n";
    cout << "3. ����������� ������\n";
    cout << "4. ����� ������\n";
    cout << "5. �������� ������\n";
    cout << "6. �������� ����������\n";
    cout << "7. ���������� ��������������\n";
    cout << "8. �������������� ������ � CSV\n";
    cout << "9. �����\n";
    cout << "��� �����: ";
}

void inputData(vector<Product>& products) {
    clearConsole();
    Product newProduct;

    cout << "������� �������� ��������: ";
    getline(cin, newProduct.name);

    cout << "������� ���� ��������: ";
    cin >> newProduct.price;

    cout << "������� ���������� ��������: ";
    cin >> newProduct.quantity;
    cin.ignore();

    products.push_back(newProduct);
    saveDataToFile(products);
    displayMessage("������ ������� ���������.");
}

void manageData(vector<Product>& products) {
    while (true) {
        clearConsole();
        displayTableWithMenu(products);

        int index;
        cout << "������� ����� �������� ��� �������������� ��� 0 ��� ������: ";
        cin >> index;
        cin.ignore();

        if (index == 0) break;

        if (index > 0 && index <= products.size()) {
            Product updatedProduct;
            cout << "������� ����� ��������: ";
            getline(cin, updatedProduct.name);

            cout << "������� ����� ����: ";
            cin >> updatedProduct.price;

            cout << "������� ����� ����������: ";
            cin >> updatedProduct.quantity;
            cin.ignore();

            editProduct(products, index - 1, updatedProduct);
        }
        else {
            displayMessage("�������� ������. ���������� �����.");
        }
    }
}

void saveDataToFile(const vector<Product>& products) {
    ofstream file("products.txt");
    if (!file.is_open()) {
        cerr << "������ ������ ������ � ����.\n";
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
        cerr << "������ ������ ������ �� �����.\n";
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
    cout << left << setw(10) << "N" << setw(20) << "��������" << setw(10) << "����" << setw(10) << "����������" << "\n";
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
    cout << "������� ����� �������� ��� �������� (�� 0 �� " << products.size() - 1 << "): ";
    cin >> productNumber;

    // �������� �� ���������� �������
    if (productNumber >= 0 && productNumber < products.size()) {
        products.erase(products.begin() + productNumber);
        cout << "������� ������." << endl;
    }
    else {
        cout << "�������� ����� ��������!" << endl;
    }
}

void displayInformation(const vector<Product>& products) {
    if (products.empty()) {
        cout << "������ ��������� ����." << endl;
        return;
    }

    cout << "������ ���������:\n";
    for (size_t i = 0; i < products.size(); ++i) {
        cout << "������� " << i << ":\n";
        cout << "��������: " << products[i].name << endl;
        cout << "����: " << products[i].price << endl;
        cout << "����������: " << products[i].quantity << endl;
        cout << "---------------------------------" << endl;
    }
}

void displaySearchTableWithMenu(const vector<Product>& products, const string& query, int searchChoice) {
    vector<Product> searchResults;

    for (const auto& product : products) {
        switch (searchChoice) {
        case 1: // ����� �� �����
            if (product.name.find(query) != string::npos) {
                searchResults.push_back(product);
            }
            break;
        case 2: // ����� �� ����
            if (to_string(product.price).find(query) != string::npos) {
                searchResults.push_back(product);
            }
            break;
        case 3: // ����� �� ����������
            if (to_string(product.quantity).find(query) != string::npos) {
                searchResults.push_back(product);
            }
            break;
        default:
            cout << "�������� ����� ������." << endl;
            return;
        }
    }

    // ����� �����������
    if (searchResults.empty()) {
        cout << "�������� �� �������." << endl;
    }
    else {
        cout << "���������� ������:\n";
        for (size_t i = 0; i < searchResults.size(); ++i) {
            cout << "������� " << i << ":\n";
            cout << "��������: " << searchResults[i].name << endl;
            cout << "����: " << searchResults[i].price << endl;
            cout << "����������: " << searchResults[i].quantity << endl;
            cout << "---------------------------------" << endl;
        }
    }
}

void manageUserAccount(const string& currentUser) {
    int choice;
    cout << "����� ����������, " << currentUser << endl;
    cout << "1. �������� ���\n";
    cout << "2. �������� ������\n";
    cout << "3. �����\n";
    cout << "�������� �����: ";
    cin >> choice;

    switch (choice) {
    case 1: {
        string newName;
        cout << "������� ����� ���: ";
        cin >> newName;
        cout << "��� �������� ��: " << newName << endl;
        break;
    }
    case 2: {
        string newPassword;
        cout << "������� ����� ������: ";
        cin >> newPassword;
        cout << "������ �������." << endl;
        break;
    }
    case 3:
        cout << "����� �� ��������..." << endl;
        break;
    default:
        cout << "�������� �����!" << endl;
    }
}

void manageSearch(vector<Product>& products) {
    string query;
    int searchChoice;

    cout << "������� ��������� ������: ";
    cin.ignore(); // ��� ������� ������ �����
    getline(cin, query);

    cout << "�������� ������ ������:\n";
    cout << "1. �� �����\n";
    cout << "2. �� ����\n";
    cout << "3. �� ����������\n";
    cout << "��� �����: ";
    cin >> searchChoice;

    displaySearchTableWithMenu(products, query, searchChoice);
}
