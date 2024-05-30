#pragma once
#include<iostream>
#include<String>
#include<map>
#include"Store.h"
#include"Product.h"
#include"Viewer.h"
class Player;
using namespace std;

class User
{
public:
	int UID;
	string UserName;
	string Password;
	map<int, Store*>* Ustores;

	User(int, string, string , map<int, Store*>& stores);
	void userPage();
	void addProductPoints();
	void removeProductPoints();
	void updateProductPoints();
	~User();
};

