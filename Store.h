#pragma once
#include "Product.h"
#include<iostream>
#include<map>
#include<String>
using namespace std;
class Store
{
public:
	int ID;
	string Name;
	map<string, Product*> products ;

	Store(int, string);
};