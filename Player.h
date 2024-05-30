#pragma once
#include<iostream>
#include<string>
#include<map>
#include"Viewer.h"
#include"Store.h"
#include"Product.h"

using namespace std;

class Player
{
public:
	int Pid;
	string PName;
	string PPassword;
	float budget;
	int modify;
	float Points;
	map<string, Product*> DecorationSet;
	map<int, Store*>* Pstores;

	Player(int, string, string, map<int, Store*> stores);
	void playerPage();
	Product* ChooseRandomly(int);
	void SearchProduct();
	void buyProduct();
	void sellProduct();
	void replaceProduct(int);
	void displaySet();

	~Player();
};

