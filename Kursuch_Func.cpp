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
