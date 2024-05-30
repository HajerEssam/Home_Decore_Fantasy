#include "System.h"
#include "Admin.h"
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int Id = 1;
map<int, Store*> stores;

System::System()
{
	systemPage();
}
void System::systemPage()
{
	int choice;
	cout << "***Welcome to Home Décor Fantasy***" << endl;
	cout << "First time to visit us..? " << endl;
	cout << "        Enter 1 to SignUp " << endl;
	cout << "You have an account..? " << endl;
	cout << "        Enter 2 to Login" << endl;
	cout << "        Enter 3 to View Top 3 players" << endl;
	cin >> choice;

	switch (choice)
	{
	case 1:
		SignUp();
		break;
	case 2:
		Login();
		break;
	case 3:
		if (players.empty())
		{
			cout << "The game did not start yet !!\n\n";
			systemPage();
		}
		else
			topThree();
		break;
	default:
		cout << "Enter valid number " << endl;
		systemPage();
	}
}

void System::SignUp()
{
	string name;
	string password;
	string role;
	Id = Id + 1;
	cout << "***Sign Up***" << endl;
	cout << "UserName : ";
	cin >> name;
	cout << "Password : ";
	cin >> password;
	cout << "Role : ";
	cin >> role;
	cout << "Your ID is : " << Id<<endl;
	transform(role.begin(), role.end(), role.begin(), ::tolower);

	if (role == "user")
	{
		User* user = new User(Id, name, password , stores);
		users[Id] = user;
		systemPage();
	}
	else if (role == "player")
	{
		Player *player = new Player(Id ,name, password, stores);
		players[Id] = player;
		systemPage();
	}    
}

void System::Login()
{
	int id;
	string name;
	string password;
	string role;

	cout << "***Login***" << endl;
	cout << "ID : ";
	cin >> id;
	cout << "UserName : ";
	cin >> name;
	cout << "Password : ";
	cin >> password;
	cout << "Role : ";
	cin >> role;
	transform(role.begin(), role.end(), role.begin(), ::tolower);
	if (id == 1 && name == "Admin" && password == "A1111" && role == "admin")
	{
		Admin* admin = new Admin(1, name, password, stores);
		systemPage();
	}
	else if (role == "user")
	{
		if (users[id] != NULL)
		{
			if (name == users[id]->UserName && password == users[id]->Password)
				users[id]->userPage();
			else
				cout << "Invalid Data !\n" << endl;
			systemPage();
		}
		else
			cout << "ID is not exist !" <<endl;
	}
	else if (role == "player")
	{
		if (players[id] != NULL)
		{
			if (name == players[id]->PName && password == players[id]->PPassword)
				players[id]->playerPage();
			else
				cout << "Invalid Data !\n" << endl;
			systemPage();
		}
		else
			cout << "ID is not exist !" << endl;
	}
}

void System::topThree()
{
	float max;
	int maxID;
	for (int i = 0; i < 3; i++)
	{
		max = 0;
		for (auto& it : players)
		{
			if (it.second->Points > max)
			{
				max = it.second->Points;
				maxID = it.first;
			}
		}
		winners.push_back(players[maxID]);
		players.erase(maxID);
	}
	cout << "The winners are : " << endl;
	for (auto it : winners)
	{
		cout << it->PName << "  " << it->Points << endl;
	}
}
System::~System()
{
	players.clear();
	users.clear();
}