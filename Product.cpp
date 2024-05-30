#include "Product.h"

Product :: Product(string name, float price, int quantity)
{
	Name = name;
	Price = price;
	Quantity = quantity;
	Rate = 0.00;
	NumofRates = 0;
}
Product::Product(string name, float price, int quantity , float rate)
{
	Name = name;
	Price = price;
	Quantity = quantity;
	Rate = rate;
}
void Product::CalculateRate()
{
	Rate = 0;
	for (auto it : rates)
	{
		Rate += it.second;
	}
	Rate = Rate/ NumofRates;
	if (Rate > 5)
		Rate = 5;
}