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
#pragma once
#include "Kursuch_Header.h"
#include "Kursuch_Func.cpp"

int main() {
	printf("xep");
	validateInput(const string & input);
}