#pragma once
#include"Store.h"
#include "Product.h"
#include"Viewer.h"
#include<String>
#include <map>
#include<iostream>

using namespace std;

class Admin
{
public:
	int AdminID;
	string AdminUserName;
	string password;
	map<int, Store*> *Astores;

	Admin(int id, string username, string pass , map<int, Store*>& stores);
	void adminPage();
	void addStore(int);
	void addProduct();
	void deleteStore();
	void deleteProduct();
	void updateProduct();
	~Admin();
};
