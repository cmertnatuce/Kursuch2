#pragma once

#include <iostream> 
#include <fstream>  
#include <string>   
#include <vector>   
#include <algorithm>
#include <iomanip>  
#include <conio.h> 
#include <ctime>

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
void displayInformation(const vector<Product>& products);
void displayTableWithMenu(const vector<Product>& products);
void manageData(vector<Product>& products);
vector<Product> searchProducts(const vector<Product>& products, const string& query);
vector<Product> filterByPriceRange(const vector<Product>& products, double minPrice, double maxPrice);
void editProduct(vector<Product>& products, int index, const Product& newProduct);
void exportToCSV(const vector<Product>& products, const string& filename);
void displayStatistics(const vector<Product>& products);
void logAction(const string& action);

/*
 setInputOutputEncoding() – устанавливает кодировку ввода/вывода;
 clearConsole() – очищает консольный экран;
 displayMessage(const string& message) – выводит сообщение на экран;
 displayMainMenu() – отображает главное меню программы;
 saveDataToFile(const vector<Product>& products) – сохраняет данные о продуктах в файл;
 loadDataFromFile(vector<Product>& products) – загружает данные о продуктах из файла;
 inputData(vector<Product>& products) – вводит данные о продуктах;
 deleteByNumber(vector<Product>& products) – удаляет продукт по номеру;
 deleteAllData(vector<Product>& products) – удаляет все данные о продуктах;
 sortByName(vector<Product>& products) – сортирует продукты по имени;
 sortByPrice(vector<Product>& products) – сортирует продукты по цене;
 sortByQuantity(vector<Product>& products) – сортирует продукты по количеству;
 registration() – процесс регистрации пользователя;
 login(string& username, string& password) – авторизация пользователя;
 manageUsers() – управление учетными записями пользователей;
 validateInput(const string& input) – проверяет валидность ввода;
 displayDeleteTableWithMenu(const vector<Product>& products) – отображает таблицу для удаления продуктов с меню;
 manageDeletion(vector<Product>& products) – управляет процессом удаления продуктов;
 displaySortTableWithMenu(const vector<Product>& products) – отображает таблицу для сортировки продуктов с меню;
 manageSorting(vector<Product>& products) – управляет процессом сортировки продуктов;
 manageUserAccount(const string& currentUser) – управляет учетной записью текущего пользователя;
 displaySearchTableWithMenu(const vector<Product>& products, const string& query = "", int searchChoice = 3) – отображает таблицу для поиска продуктов с меню;
 manageSearch(vector<Product>& products) – управляет процессом поиска продуктов;
 displayInformation(vector<Product>& products) – отображает информацию о продуктах;
 displayTableWithMenu(const vector<Product>& products) – отображает таблицу с меню для управления данными о продуктах;
 manageData(vector<Product>& products) – управляет данными о продуктах;
 main() – главная функция программы.
*/