#pragma once

#include "Kursuch_Header.h"
#include "Kursuch_Func.cpp"

int main() {
    vector<Product> products;
    setInputOutputEncoding();
    clearConsole();

    while (true) {
        displayMainMenu();
        char choice;
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case '1': inputData(products); break;
        case '2': manageData(products); break;
        case '3': manageSorting(products); break;
        case '4': manageSearch(products); break;
        case '5': manageDeletion(products); break;
        case '6': displayStatistics(products); break;
        case '7': manageUsers(); break;
        case '8': exportToCSV(products, "exported_data.csv"); break;
        case '9': clearConsole(); exit(0);
        default: displayMessage("Неверный ввод. Попробуйте снова.");
        }
    }

    return 0;
}