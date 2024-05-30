#include "Player.h"
#include<iostream>
using namespace std;
Viewer* MapView = new Viewer();

Player::Player(int playerId, string playerName, string playerPassword, map<int, Store*> stores)
{
	Pid = playerId;
	PName = playerName;
	PPassword = playerPassword;
	budget = 100000.0;
	modify = 0;
	Pstores = &stores;
	playerPage();
}

void Player::playerPage()
{
	int funchoice;
	int cont;
	do
	{
		cout << "****Welcome " << this->PName << "******\n\n";
		MapView->ViewStoresAndProducts(*Pstores);
		cout << "\n\nEnter (1) to Buy a Product \n";
		cout << "Enter (2) to sell a Product from your Set !\n";
		cout << "Enter (3) to replace a Product from your Set !\n";
		cout << "Enter (4) to search for a product by its name\n";
		cout << "Your Choice is : ";
		cin >> funchoice;
		switch (funchoice)
		{
		case 1:
			buyProduct();
			break;
		case 2:
			sellProduct();
			break;
		case 3:
			replaceProduct(++modify);
			break;
		case 4:
			SearchProduct();
		}
		cout << "Do you want to continue as a Player ? (Enter 1 : for yes , 0 : for No )" << endl;
		cin >> cont;
	} while (cont);
}

Product* Player::ChooseRandomly(int StoreId)
{

	int randomIndex = rand() % (*Pstores)[StoreId]->products.size();
	auto prodIt = (*Pstores)[StoreId]->products.begin();
	advance(prodIt, randomIndex);
	return prodIt->second;
}

void Player::buyProduct()
{
	bool check, Buy;
	int StoreId;
	cout << "\nEnter The Store ID : "; cin >> StoreId;
	cout << "\n\nDo You Want to buy a product randomly ?! (Enter 1 : for yes , 0 : for No )" << endl;
	cin >> check;

	if (check)
	{
		do
		{
			string randomlyName = this->ChooseRandomly(StoreId)->Name;
			cout << "\n\nOK , The Product Name : " << randomlyName << ", its Price is : " << (*Pstores)[StoreId]->products[randomlyName]->Price;
			cout << "\n If you want to buy that Product (Enter 1 : for yes , 0 : for No ) :"; cin >> check;
			cout << "\n\n";
			if (check)
			{
				if (DecorationSet[randomlyName] != nullptr)
					cout << "\n\nAgainst The Rules ! , You Already have that Product in your set !!!\n\n";
				else
				{
					if (budget >= (*Pstores)[StoreId]->products[randomlyName]->Price)
					{

						Product* pro = new Product(randomlyName, (*Pstores)[StoreId]->products[randomlyName]->Price, 1, (*Pstores)[StoreId]->products[randomlyName]->Rate);
						(*Pstores)[StoreId]->products[randomlyName]->Quantity--;
						budget -= (*Pstores)[StoreId]->products[randomlyName]->Price;
						DecorationSet[randomlyName] = pro;
						Points += pro->Rate;

						cout << "Added to your Decoration Set Successfully :)\n\n\n";
					}
					else
						cout << "Your Budget may not afford its Price :(\n\n";
				}

			}
			cout << "Want to choose another product randomly again ?! (Enter 1 : for yes , 0 : for No ) : "; cin >> Buy;
		} while (Buy);
	}

	cout << "Want to choose a Product by its name ?! (Enter 1 : for yes , 0 : for No ) :"; cin >> check;
	if (check)
	{
		string proName;
		cout << "\n\nEnter Product Name :"; cin >> proName;
		if ((*Pstores)[StoreId]->products[proName] != nullptr && DecorationSet[proName] == nullptr)
		{
			if (budget >= (*Pstores)[StoreId]->products[proName]->Price && (*Pstores)[StoreId]->products[proName]->Quantity > 0)
			{
				(*Pstores)[StoreId]->products[proName]->Quantity--;
				budget -= (*Pstores)[StoreId]->products[proName]->Price;
				DecorationSet[proName] = new Product(proName, (*Pstores)[StoreId]->products[proName]->Price, 1, (*Pstores)[StoreId]->products[proName]->Rate);
				Points += DecorationSet[proName]->Rate;
				cout << "\nAdded to your Decoration Set Successfully :)\n";
			}
			else
			{
				cout << "Your Budget may not afford the product price or the product is not available in the store anymore :( \n";
			}
		}
		else
		{
			cout << "\nThis product deos not exist in that Store !! or you already have that Product in your Set :(\n";
		}

	}
	displaySet();
}

void Player::sellProduct()
{
	string ProName;
	cout << "Enter the Product Name  : "; cin >> ProName;
	float UpdatedPrice;
	cout << "Enter the Price you want for that Product  : "; cin >> UpdatedPrice;
	auto it = DecorationSet.find(ProName);
	// Erase the element
	if (it != DecorationSet.end()) {
		Points -= it->second->Rate;
		budget += UpdatedPrice;
		DecorationSet.erase(it);
	}
	else
		cout << "this product not found in your set !\n\n";
	displaySet();
}

void Player::replaceProduct(int mod)
{
	if (mod == 4)
	{
		cout << "You are going against the compitition rules !! ,  you are no longer a player !!";
		delete this;
	}
	else
	{
		string ProductName, StoreProduct;
		int StoreId;
		cout << "Enter The product you want to replace from Your Set : ";
		cin >> ProductName;
		auto it = DecorationSet.find(ProductName);


		if (it != DecorationSet.end()) {
			cout << "**" << endl;
			cout << "Enter Store ID : "; cin >> StoreId;
			cout << "Enter the Product name  :"; cin >> StoreProduct;
			//check if the product in the set existed in that store before ?!
			budget += DecorationSet[ProductName]->Price;
			if ((*Pstores)[StoreId]->products[ProductName] != nullptr)
			{

				if (budget >= (*Pstores)[StoreId]->products[StoreProduct]->Price)
				{
					(*Pstores)[StoreId]->products[ProductName]->Quantity++;
					budget -= (*Pstores)[StoreId]->products[StoreProduct]->Price;
					Points -= it->second->Rate;
					DecorationSet.erase(it);
					DecorationSet[StoreProduct] = new Product(StoreProduct, (*Pstores)[StoreId]->products[StoreProduct]->Price, 1, (*Pstores)[StoreId]->products[StoreProduct]->Rate);
					Points += DecorationSet[StoreProduct]->Rate;
					cout << "You replaced Your Product Succesfully with " << StoreProduct << "\n";
				}
				else
					cout << "Your Budget may not afford its Price :(\n";
			}
			else
			{
				(*Pstores)[StoreId]->products[ProductName] = new Product(it->second->Name, it->second->Price, 1, it->second->Rate);
				budget -= (*Pstores)[StoreId]->products[StoreProduct]->Price;
				DecorationSet.erase(it);
				DecorationSet[StoreProduct] = new Product(StoreProduct, (*Pstores)[StoreId]->products[StoreProduct]->Price, 1, (*Pstores)[StoreId]->products[StoreProduct]->Rate);
				cout << "You replaced Your Product Succesfully with " << StoreProduct << "\n";
			}
		}
		else
			cout << "You dont have that Product in your Set !!\n";

		displaySet();

		cout << "\n\n::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n\n\n\n";
	}

}

void Player::SearchProduct()
{
	string ProName;
	cout << "Enter Product Name :"; cin >> ProName;
	bool productFound = false;
	for (auto const& store : *Pstores) {
		auto it = store.second->products.find(ProName);
		if (it != store.second->products.end())
		{
			cout << "Product Name: " << it->second->Name << endl;
			cout << "Store Name: " << store.second->Name << endl;
			cout << "Store ID : " << store.second->ID<<endl;
			cout << "Points/Rating: " << it->second->Rate << endl;
			cout << "Price: " << it->second->Price << endl;
			productFound = true;
		}

	}
	if (!productFound) {
		cout << "Product not found in any store." << endl;
	}

}
void Player::displaySet()
{
	cout << "Your Set Products now :\n";
	for (auto it : DecorationSet)
	{
		cout << it.second->Name << "    "<< it.second->Rate<<endl;
	}
	cout << "\n Your Budget is : " << budget<<endl;
}

Player::~Player()
{
	delete Pstores;
}