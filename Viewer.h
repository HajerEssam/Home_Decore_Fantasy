#pragma once
#include<iostream>
using namespace std;
#include"Store.h"
#include "Product.h"
#include<String>
#include<vector>
#include <map>
#include"System.h"
class Viewer
{
public:
	void ViewStoresAndProducts(map<int, Store*>&);
};

