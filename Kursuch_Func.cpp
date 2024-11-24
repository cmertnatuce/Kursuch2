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
    string role = "user"; // ����� �������������� "user"

    cout << "������� �����: ";
    cin >> username;

    cout << "������� ������: ";
    cin >> password;

    ofstream file("users.txt", ios::app);
    if (file.is_open()) {



        file << username << " " << password << " " << role << endl; // ������ ���� "user"
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
            return; // ������� �����
        }
        if (userChoice < 1 || userChoice > users.size()) {
            cout << "�������� ����� ������������!" << endl;
            continue;
        }

        string selectedUser = users[userChoice - 1];
        string username = selectedUser.substr(0, selectedUser.find(' '));
        string password = selectedUser.substr(selectedUser.find(' ') + 1, selectedUser.rfind(' ') - selectedUser.find(' ') - 1);
        string role = selectedUser.substr(selectedUser.rfind(' ') + 1); // �������� ���� ������������

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
            continue; // ������� � ������ ������������
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

    // ����� ������� � ������� � �������
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

    // ����� ���� ��������
    cout << "\n������� ������:\n"
        << "1. ������� �� ������\n"
        << "2. ������� ��� ������\n"
        << "3. �����\n��� �����: ";
}

void manageDeletion(vector<Product>& products) {
    while (true) {
        displayDeleteTableWithMenu(products); // ����� ������� � ������� � ���� ��������

        int deleteChoice;
        cin >> deleteChoice;
        cin.ignore(); // ������������� ������� ����� ������ ����� ����� ������

        switch (deleteChoice) {
        case 1: {
            clearConsole();
            displayDeleteTableWithMenu(products); // ���������� ������� ����� ������ ������ ��� ��������
            int index;
            cout << "������� ����� �������� ��� ��������: ";
            cin >> index;
            if (index > 0 && index <= products.size()) { // ��������� ������� �� 1-based index
                products.erase(products.begin() + index - 1); // ������������� ������� �� 0-based
                saveDataToFile(products);
            }
            else {
                cerr << "������������ ����� ��������.\n";
            }
            break;
        }
        case 2:
            clearConsole();
            displayDeleteTableWithMenu(products); // ���������� ������� ����� ��������� ���� ������
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

    // ����� ���� ����������
    cout << "\n����������� ������:\n"
        << "1. ����������� �� ��������\n"
        << "2. ����������� �� ����\n"
        << "3. ����������� �� ����������\n"
        << "4. �����\n��� �����: ";
}

void manageSorting(vector<Product>& products) {
    while (true) {
        displaySortTableWithMenu(products); // ����� ������� � ������� � ���� ����������

        int sortChoice;
        cin >> sortChoice;
        cin.ignore(); // ������������� ������� ����� ������ ����� ����� ������

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
            cout << "�������� �����!" << endl;
            break;
        }
    }
}

void manageUserAccount(const string& currentUser) {
    while (true) {
        clearConsole();
        ifstream file("users.txt");
        if (!file.is_open()) {
            cout << "������ ��� �������� ����� �������������!" << endl;
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
            cout << "������������ �� ������!" << endl;
            return;
        }

        string username = selectedUser.substr(0, selectedUser.find(' '));
        string password = selectedUser.substr(selectedUser.find(' ') + 1, selectedUser.rfind(' ') - selectedUser.find(' ') - 1);

        cout << "��������, ��� �� ������ �������:" << endl;
        cout << "1. �������� �����" << endl;
        cout << "2. �������� ������" << endl;
        cout << "3. ������� �������" << endl;
        cout << "4. ��������� �����" << endl;
        cout << "��� �����: ";
        int actionChoice;
        cin >> actionChoice;

        switch (actionChoice) {
        case 1: {
            cout << "������� ����� �����: ";
            string newUsername;
            cin >> newUsername;
            for (auto& user : users) {
                if (user == selectedUser) {
                    user.replace(0, username.length(), newUsername);


                    selectedUser = user;
                    username = newUsername;
                }
            }
            cout << "����� ������� ������� �� '" << username << "'!" << endl;
            break;
        }
        case 2: {
            cout << "������� ����� ������: ";
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
            cout << "������ ������� �������!" << endl;
            break;
        }
        case 3: {
            users.erase(remove(users.begin(), users.end(), selectedUser), users.end());
            cout << "������� ������� ������!" << endl;
            return; // ������� � ��������� ����
        }
        case 4: {
            return; // ������� � ��������� ����
        }
        default:
            cout << "�������� �����!" << endl;
            continue;
        }

        ofstream outFile("users.txt");
        if (!outFile.is_open()) {
            cout << "������ ��� �������� ����� ��� ������!" << endl;
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
    cout << "������� ����� ������� ��� �����������..." << endl;
    _getch();
}

void displayMainMenu() {
    cout << "�������� ��������:\n";
    cout << "1. �����������\n";
    cout << "2. ���� � �������\n";
    cout << "3. �����\n";
    cout << "��� �����: ";
}

void saveDataToFile(const vector<Product>& products) {
    ofstream outFile("products.txt"); // �������� ����� ��� ������

    if (!outFile) {
        cerr << "������ ��� �������� ����� ��� ������!" << endl;
        return;
    }

    for (const auto& product : products) {
        outFile << product.name << '\n'
            << product.price << '\n'
            << product.quantity << '\n';
    }

    outFile.close(); // �������� �����
    displayMessage("������ ������� ��������� � ����.");
}

void loadDataFromFile(vector<Product>& products) {
    ifstream inFile("products.txt"); // �������� ����� ��� ������

    if (!inFile) {
        cerr << "������ ��� �������� ����� ��� ������!" << endl;
        return;
    }

    products.clear(); // ������� ������ ����� ��������� ����� ������

    Product product;
    while (getline(inFile, product.name)) { // ������ ����� ��������
        inFile >> product.price >> product.quantity;
        inFile.ignore(); // ���������� ������ ����� ������ ����� �����
        products.push_back(product); // ���������� � ������
    }

    inFile.close(); // �������� �����
    displayMessage("������ ������� ��������� �� �����.");
}

void inputData(vector<Product>& products) {
    Product newProduct;
    cout << "������� ��� ������: ";
    cin.ignore(); // ���������� ���������� ������ ����� ������
    getline(cin, newProduct.name); // ������ ��� ������

    cout << "������� ���� ������: ";
    cin >> newProduct.price; // ������ ���� ������

    cout << "������� ���������� ������: ";
    cin >> newProduct.quantity; // ������ ���������� ������

    products.push_back(newProduct); // ��������� ����� ����� � ������
    displayMessage("����� ������� ��������.");
}

// ������� ������� �� ������
void deleteByNumber(vector<Product>& products) {
    int index;
    cout << "������� ����� ������ ��� �������� (�� 1 �� " << products.size() << "): ";
    cin >> index;

    if (index > 0 && index <= products.size()) {
        products.erase(products.begin() + index - 1);
        displayMessage("����� ������� ������.");
    }
    else {
        ("������������ ����� ������.");
    }
}

// ���������� ������� ��� ������ ��������� � ����
void displaySearchTableWithMenu(const vector<Product>& products, const string& query, int searchChoice) {
    cout << "����� ������:\n";
    cout << "1. �� ����������\n";
    cout << "2. �� ����\n";
    cout << "3. �� ��������\n";
    cout << "4. ����� (ESC)\n";
    cout << "��� �����: ";

    if (searchChoice != 3) {
        string searchQuery;
        cout << "������� ������ ��� ������: ";
        cin.ignore();
        getline(cin, searchQuery);
        cout << "���������� ������:\n";

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

// ���������� ���������� � ���������
void displayInformation(vector<Product>& products) {
    cout << "���������� � ���������:\n";
    for (const auto& product : products) {
        cout << setw(20) << left << product.name
            << setw(10) << product.price
            << setw(10) << product.quantity << endl;
    }
}

// ���������� ������� � ���� ��� ���������� ������� � ���������
void displayTableWithMenu(const vector<Product>& products) {
    cout << "���������� ������� ������ �� ������:\n";
    cout << "1. ������ ������ � ������\n";
    cout << "2. ������� ������\n";
    cout << "3. ����������� ������\n";
    cout << "4. ����� ������\n";
    cout << "5. �����\n";
    cout << "��� �����: ";
}

// ��������� ������� � ���������
void manageData(vector<Product>& products) {
    while (true) {
        clearConsole();
        displayTableWithMenu(products);
        string choice;
        cin >> choice;

        if (choice == "1") {
            inputData(products); // ���� ������
        }
        else if (choice == "2") {
            displayDeleteTableWithMenu(products); // �������� ������
        }
        else if (choice == "3") {
            (products); // ���������� ������
        }
        else if (choice == "4") {
            manageSearch(products); // ����� ������
        }
        else if (choice == "5") {
            break; // �����
        }
        else {
            ("������������ ����. ����������, �������� ������������ ����� ����.");
        }
    }
}

// ��������� ��������� ������ ���������
void manageSearch(vector<Product>& products) {
    string choice;
    while (true) {
        clearConsole();
        displaySearchTableWithMenu(products);
        cin >> choice;

        if (choice == "1" || choice == "2" || choice == "3") {
            displaySearchTableWithMenu(products, "", stoi(choice)); // ����� �� ���������� ��������
        }
        else if (choice == "4") {
            break; // �����
        }
        else {
            ("������������ ����. ����������, �������� ������������ ����� ����.");
        }
    }
}