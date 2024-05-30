#pragma once
#include <map>
#include<vector>
#include"Player.h"
#include"User.h"
class Player;
class User;
using namespace std;

class System
{
public:
	map<int, User*> users;
	map<int, Player*> players;
	vector<Player*> winners;

	System();
	void systemPage();
	void SignUp();
	void Login();
	void topThree();
	~System();
};

