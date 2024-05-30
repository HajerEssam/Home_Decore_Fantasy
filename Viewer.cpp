#include "Viewer.h"
void Viewer::ViewStoresAndProducts(map<int, Store*>& access_stores)
{
	int i = 1;
	int j = 1;
	cout << "**View Stores and Products**" << endl;
	for (auto& it : access_stores)
	{
		cout << "store number " << i++ << " :        ";
		cout << "store ID : " << it.first << "        store Name : " << it.second->Name << endl;
		for (auto& itt : it.second->products)
		{
			cout << "  product number " << j++ << " :        ";
			cout << "product Name : " << itt.first << "        product Price : " << itt.second->Price << endl;
			cout << "  product Quantity : " << itt.second->Quantity << "        product Rate : " << itt.second->Rate << endl;
			cout << "**" << endl;
		}
		cout << "********" << endl;
	}
}