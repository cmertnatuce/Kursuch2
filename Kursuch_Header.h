#pragma once

#include <iostream> 
#include <fstream>  
#include <string>   
#include <vector>   
#include <algorithm>
#include <iomanip>  
#include <conio.h> 
#include <ctime>
#include <windows.h>

using namespace std;

const string ADMIN_USERNAME = "admin";
const string ADMIN_PASSWORD = "12345";

struct Product {
    string name;
    double price;
    int quantity;
};

 void setInputOutputEncoding();
 void clearConsole();
 void displayMessage(const string& message);
 void displayMainMenu();
 void saveDataToFile(const vector<Product>& products);
 void loadDataFromFile(vector<Product>& products);
 void inputData(vector<Product>& products);
 void deleteByNumber(vector<Product>& products);
 void deleteAllData(vector<Product>& products);
 void sortByName(vector<Product>& products);
 void sortByPrice(vector<Product>& products);
 void sortByQuantity(vector<Product>& products);
 void registration();
 bool login(string& username, string& password);
 void manageUsers();
 bool validateInput(const string& input);
 void displayDeleteTableWithMenu(const vector<Product>& products);
 void manageDeletion(vector<Product>& products);
 void displaySortTableWithMenu(const vector<Product>& products);
 void manageSorting(vector<Product>& products);
 void manageUserAccount(const string& currentUser);
 void displaySearchTableWithMenu(const vector<Product>& products, const string& query = "", int searchChoice = 3);
 void manageSearch(vector<Product>& products);
 void displayInformation(vector<Product>& products);
 void displayTableWithMenu(const vector<Product>& products);
 void manageData(vector<Product>& products);