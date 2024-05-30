#pragma once
#include<string>
#include<map>
using namespace std;
class Product
{
public:
	string Name;
	float Price;
	int Quantity;
	float Rate;
	int NumofRates;
	map<int, float> rates;
	Product(string, float, int);
	Product(string, float, int, float);
	void CalculateRate();
};