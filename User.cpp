#include "User.h"
Viewer* ProductsDisplay = new Viewer();
User::User(int id , string username, string pass , map<int, Store*>& stores)
{
	UID = id;
	UserName = username;
	Password = pass;
	Ustores = &stores;
	userPage();
}
void User::userPage()
{
	int choice;
	int cont;

	cout << "***Welcome User***" << endl;
	ProductsDisplay->ViewStoresAndProducts((*Ustores));
	cout << endl;

	do
	{
		cout << "Enter 1 to Add a PRODUCT's points" << endl;
		cout << "Enter 2 to Remove a PRODUCT's points" << endl;
		cout << "Enter 3 to Update a PRODUCT's points" << endl;
		cout << "Enter 4 to view PRODUCTS" << endl;
		cout << "Your Choice is : ";
		cin >> choice;

		switch (choice)
		{
		case 1:
			addProductPoints();
			break;
		case 2:
			removeProductPoints();
			break;
		case 3:
			updateProductPoints();
			break;
		case 4:
			ProductsDisplay->ViewStoresAndProducts((*Ustores));
			break;
		default:
			cout << "Enter invalid number !" << endl;
			userPage();
			break;
		}
		cout << "Do you want to continue as a User ? (Enter 1 : for yes , 0 : for No )" << endl;
		cin >> cont;
	} while (cont == 1);
}
void User::addProductPoints()
{
	int storeId;
	string productName;
	float Rate;
	cout << "Enter Store ID : ";
	cin >> storeId;
	cout << "Enter Product Name : ";
	cin >> productName;
	if ((*Ustores)[storeId] != NULL)
	{
		if ((*Ustores)[storeId]->products[productName] != NULL)
		{
			cout << "Enter Product's Points : ";
			cin >> Rate;
			if ((*Ustores)[storeId]->products[productName]->rates[this->UID] == 0)
			{
				(*Ustores)[storeId]->products[productName]->rates[this->UID] = Rate;	
			}
			else
			{
				(*Ustores)[storeId]->products[productName]->rates[this->UID] = (*Ustores)[storeId]->products[productName]->rates[this->UID] + Rate;
			}
			(*Ustores)[storeId]->products[productName]->NumofRates++;
			(*Ustores)[storeId]->products[productName]->CalculateRate();
			(*Ustores)[storeId]->products[productName]->Price += ((*Ustores)[storeId]->products[productName]->Rate / 3);
		}
		else
		{
			cout << "Product Name is not correct !" << endl;
		}
	}
	else
	{
		cout << "Store ID is not correct !" << endl;
	}
}
void User::removeProductPoints()
{
	int storeId;
	string productName;
	cout << "Enter Store ID : ";
	cin >> storeId;
	cout << "Enter Product Name : ";
	cin >> productName;
	if ((*Ustores)[storeId] != NULL)
	{
		if ((*Ustores)[storeId]->products[productName] != NULL)
		{
			if ((*Ustores)[storeId]->products[productName]->rates[this->UID] != NULL)
			{
				cout << "Old Rating : " << (*Ustores)[storeId]->products[productName]->rates[this->UID];
				(*Ustores)[storeId]->products[productName]->rates.erase(this->UID);
				(*Ustores)[storeId]->products[productName]->NumofRates--;
				(*Ustores)[storeId]->products[productName]->CalculateRate();
				(*Ustores)[storeId]->products[productName]->Price -= ((*Ustores)[storeId]->products[productName]->Rate / 3);
				cout << " Removed Successfully" << endl;
			}
			else
			{
				cout << "You Didn't Rate this Product before !" << endl;
			}
		}
		else
		{
			cout << "Product Name is not correct !" << endl;
		}
	}
	else
	{
		cout << "Store ID is not correct !" << endl;
	}
}
void User::updateProductPoints()
{
	int storeId;
	string productName;
	float NRate;
	cout << "Enter Store ID : ";
	cin >> storeId;
	cout << "Enter Product Name : ";
	cin >> productName;
	if ((*Ustores)[storeId] != NULL)
	{
		if ((*Ustores)[storeId]->products[productName] != NULL)
		{
			if ((*Ustores)[storeId]->products[productName]->rates[this->UID] != NULL)
			{
				cout << "Old Rating : " << (*Ustores)[storeId]->products[productName]->rates[this->UID] << " Removed Successfully" << endl;
				cout << "Enter New Rating : ";
				cin >> NRate;
				(*Ustores)[storeId]->products[productName]->rates[this->UID] = NRate;
				(*Ustores)[storeId]->products[productName]->Price -= ((*Ustores)[storeId]->products[productName]->Rate / 3);
				(*Ustores)[storeId]->products[productName]->CalculateRate();
				(*Ustores)[storeId]->products[productName]->Price += ((*Ustores)[storeId]->products[productName]->Rate / 3);
			}
			else
			{
				cout << "You Didn't Rate this Product before !" << endl;
			}
		}
		else
		{
			cout << "Product Name is not correct !" << endl;
		}
	}
	else
	{
		cout << "Store ID is not correct !" << endl;
	}
}

User::~User()
{
	delete Ustores;
}