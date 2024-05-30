#include "Admin.h"
#include"System.h"
Viewer* StoresProductsDisplay = new Viewer();
Admin::Admin(int id, string username , string pass , map<int, Store*>& stores)
{
	AdminID = id;
	AdminUserName = username;
	password = pass;
	Astores = &stores;
	adminPage();
}

void Admin::adminPage()
{
	int sid = 100;
	bool cont;
	do
	{
		int funchoice;
		cout << "***Welcome Admin***" << endl;
		cout << "Enter 1 to Add a store" << endl;
		cout << "Enter 2 to Delete a store" << endl;
		cout << "Enter 3 to Add a product" << endl;
		cout << "Enter 4 to Delete a product" << endl;
		cout << "Enter 5 to Update a product" << endl;
		cout << "Enter 6 to View stores and products" << endl;
		cout << "Your Choice is : ";
		cin >> funchoice;
		switch (funchoice)
		{
		case 1:
			addStore(sid++);
			break;
		case 2:
			deleteStore();
			break;
		case 3:
			addProduct();
			break;
		case 4:
			deleteProduct();
			break;
		case 5:
			updateProduct();
			break;
		case 6:
			StoresProductsDisplay->ViewStoresAndProducts(*Astores);
			break;
		default:
			cout << "Enter valid number !" << endl;
			adminPage();
			break;
		}
		cout << "Do you want to continue as an admin ? (Enter 1 : for yes , 0 : for No )" << endl;
		cin >> cont;
	} while (cont == 1);
}
void Admin::addStore(int sID)
{
	string storename;
	cout << "***Adding Store***" << endl;
	cout << "Enter your Store Name : "; 
	cin >> storename;
	cout << "Your Store ID : " <<sID <<endl;
	Store* store = new Store(sID, storename);
	(*Astores)[sID] = store;
}

void Admin::deleteStore()
{
	int storeid;
	cout << "***Deleting Store***" << endl;
	cout << "Enter store ID : ";
	cin >> storeid;
	if ((*Astores)[storeid] != NULL)
	{
		Astores->erase(storeid);
	}
	else
	{
		cout << "Invalid store ID" << endl;
	}
}

void Admin::addProduct()
{
	string proname;
	float proprice;
	int proquantity;
	int storeid;
	cout << "***Adding Product***" << endl;
	cout << "Enter store ID :";
	cin >> storeid;
	if ((*Astores)[storeid] != NULL)
	{
		cout << "Enter your product name : "; cin >> proname;
		cout << "Enter your product price :  "; cin >> proprice;
		cout << "Enter your product quantity : "; cin >> proquantity;
		Product* product = new Product(proname, proprice, proquantity);

		if ((*Astores)[storeid]->products[proname] != NULL)
		{
			cout << "Product Name already exist please enter new ID !" << endl;
		}
		else
		{
			(*Astores)[storeid]->products[proname] = product;
		}
	}
	else 
	{
		cout << "Invalid store ID" << endl;
	}
}

void Admin::deleteProduct()
{
	int storeid;
	string proname;
	cout << "***Deleting Product***" << endl;
	cout << "Enter store ID : ";
	cin >> storeid;
	if ((*Astores)[storeid] != NULL)
	{
		cout << "Enter product Name : ";
		cin >> proname;

		if ((*Astores)[storeid]->products[proname] != NULL)
		{
			(*Astores)[storeid]->products.erase(proname);
		}
		else
			cout << "Invalid product Name" << endl;
	}
	else
		cout << "Invalid store ID" << endl;
}

void Admin::updateProduct()
{
	int choice;
	float price;
	int quantity;
	int StoreID;
	string proname;
	bool Sfound = false;
	bool Pfound = false;
	bool newprice = false;
	bool newquantity = false;
	cout << "***Updating Product***" << endl;
	cout << "Enter Store ID : ";
	cin >> StoreID;
	if ((*Astores)[StoreID] != NULL)
	{
		cout << "Enter Product product Name : ";
		cin >> proname;

		if ((*Astores)[StoreID]->products[proname] != NULL)
		{
			cout << "Enter 1 to update Price " << endl;
			cout << "Enter 2 to update Quantity " << endl;
			cout << "Enter 3 to update Both " << endl;
			cin >> choice;
			switch (choice)
			{
			case 1:
				cout << "Enter Product Price : ";
				cin >> price;
				newprice = true;
				break;
			case 2:
				cout << "Enter Product Quantity : ";
				cin >> quantity;
				newquantity = true;
				break;
			case 3:
				cout << "Enter Product Price : ";
				cin >> price;
				cout << "Enter Product Quantity : ";
				cin >> quantity;
				newprice = true;
				newquantity = true;
				break;
			default:
				cout << "Enter valid Number ! " << endl;
				updateProduct();
			}

			if (newprice)
			{
				(*Astores)[StoreID]->products[proname]->Price = price;
			}
			if (newquantity)
			{
				(*Astores)[StoreID]->products[proname]->Quantity = quantity;
			}
		}
		else
			cout << "Invalid product Name" << endl;
	}
	else
		cout << "Invalid store ID" << endl;
}

Admin::~Admin()
{
	delete Astores;
}