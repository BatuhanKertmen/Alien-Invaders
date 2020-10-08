#include <iostream>
#include <chrono>
#include <string>
#include <thread>
#include "strutils.h"
#include "Entity.h"

using namespace std;
static bool FirstDir = true;


/*
Every enemy crated at starting locations
Player created
*/
void setup(vector<Entity*> &SpaceShips, int BoardWidth, int BoardLength)
{
	int BoardOffSetX = 10;
	int BoardOffSetY = 3;
	int ToughEnemyHP = 4;
	int IdleEnemyHp = 1;
	int ShootingEnemyHP = 2;
	int EnemyBottomLine = 17;
	
	Player* player = new Player((BoardWidth / 2) - 1,BoardLength - BoardOffSetY, 3);
	SpaceShips.push_back(player);

	IdleEnemy ForCalculation(0, 0, 0, 's');

	for (int  y = BoardOffSetY;  y <= EnemyBottomLine ;  y += ForCalculation.length + 1)
	{
		for (int x = BoardOffSetX; x < BoardWidth - BoardOffSetX; x += ForCalculation.width + 3)
		{
			if (y == BoardOffSetY)
			{
				IdleEnemy* Tough = new IdleEnemy(x, y, ToughEnemyHP, 't');
				SpaceShips.push_back(Tough);
			}
			else if(y > 4 && y < EnemyBottomLine - (ForCalculation.length + 2))
			{
				IdleEnemy* Normal = new IdleEnemy(x, y, IdleEnemyHp, 'i');
				SpaceShips.push_back(Normal);
			}
			else if( y > EnemyBottomLine - (ForCalculation.length + 2))
			{
				ShootingEnemy* Shooter = new ShootingEnemy(x, y, ShootingEnemyHP);
				SpaceShips.push_back(Shooter);
			}
		}
	}
}

int GameOver(vector<Entity*>& SpaceShips)
{
	if (!dynamic_cast<Player*>(SpaceShips[0]))
	{
		return 2;
	}
	else if (SpaceShips.size() == 1)
	{
		return 1;
	}
	return 0;
}

void BulletCalculation(vector<Bullet> &bullets)
{
	for (int i = 0; i < bullets.size(); i++)
	{
		bullets[i].Move(bullets[i].GetDir());
	}
}

void DrawGame(int BoardWidth, int BoardLength, vector<Entity*> &SpaceShips, vector<Bullet> &bullets)
{
	system("cls");

	string screen = "";
	for (int x = 0; x < BoardWidth + 2; x++)
	{
		screen += (char)178;
	}
	screen += "\n";
	for (int y = 1; y < BoardLength + 1; y++)
	{
		for (int x = 0; x < BoardWidth + 2; x++)
		{
			if (x == 0 || x == BoardWidth + 1)
			{
				screen += (char)178;
			}
			else
			{
				bool enteredIf = false;
				for (int i = 0; i < SpaceShips.size(); i++)
				{

					// Tough Enemy drawing
					if (SpaceShips[i]->x == x && SpaceShips[i]->y == y && SpaceShips[i]->type == 't')
					{
						screen += "#";
						enteredIf = true;
					}
					else if (SpaceShips[i]->x + 1 == x && SpaceShips[i]->y == y && SpaceShips[i]->type == 't')
					{
						screen += "#";
						enteredIf = true;
					}
					else if (SpaceShips[i]->x + 2 == x && SpaceShips[i]->y == y && SpaceShips[i]->type == 't')
					{
						screen += "#";
						enteredIf = true;
					}
					else if (SpaceShips[i]->x == x && SpaceShips[i]->y + 1 == y && SpaceShips[i]->type == 't')
					{
						screen += "#";
						enteredIf = true;
					}
					else if (SpaceShips[i]->x + 2 == x && SpaceShips[i]->y + 1 == y && SpaceShips[i]->type == 't')
					{
						screen += "#";
						enteredIf = true;
					}

					//Idle Enemy drawing
					if (SpaceShips[i]->x == x && SpaceShips[i]->y == y && SpaceShips[i]->type == 'i')
					{
						screen += "#";
						enteredIf = true;
					}
					else if (SpaceShips[i]->x + 1 == x && SpaceShips[i]->y == y && SpaceShips[i]->type == 'i')
					{
						screen += "#";
						enteredIf = true;
					}
					else if (SpaceShips[i]->x + 2 == x && SpaceShips[i]->y == y && SpaceShips[i]->type == 'i')
					{
						screen += "#";
						enteredIf = true;
					}
					else if (SpaceShips[i]->x + 1 == x && SpaceShips[i]->y + 1 == y && SpaceShips[i]->type == 'i')
					{
						screen += "U";
						enteredIf = true;
					}
					
					//Shooting Enemy Drawing
					if (SpaceShips[i]->x == x && SpaceShips[i]->y == y && SpaceShips[i]->type == 's')
					{
						screen += "#";
						enteredIf = true;
					}
					else if (SpaceShips[i]->x + 1 == x && SpaceShips[i]->y == y && SpaceShips[i]->type == 's')
					{
						screen += "#";
						enteredIf = true;
					}
					else if (SpaceShips[i]->x + 2 == x && SpaceShips[i]->y == y && SpaceShips[i]->type == 's')
					{
						screen += "#";
						enteredIf = true;
					}
					else if (SpaceShips[i]->x + 2 == x && SpaceShips[i]->y + 1 == y && SpaceShips[i]->type == 's')
					{
						screen += "/";
						enteredIf = true;
					}
					else if (SpaceShips[i]->x == x && SpaceShips[i]->y + 1 == y && SpaceShips[i]->type == 's')
					{
						screen += "\\";
						enteredIf = true;
					}

					//Player Drawing
					if (SpaceShips[i]->x + 1 == x && SpaceShips[i]->y == y && SpaceShips[i]->type == 'p')
					{
						screen += "^";
						enteredIf = true;
					}
					else if (SpaceShips[i]->x == x && SpaceShips[i]->y + 1 == y && SpaceShips[i]->type == 'p')
					{
						screen += "<";
						enteredIf = true;
					}
					else if (SpaceShips[i]->x + 1 == x && SpaceShips[i]->y + 1 == y && SpaceShips[i]->type == 'p')
					{
						screen += "_";
						enteredIf = true;
					}
					else if (SpaceShips[i]->x + 2 == x && SpaceShips[i]->y + 1 == y && SpaceShips[i]->type == 'p')
					{
						screen += ">";
						enteredIf = true;
					}
				}
				if (!enteredIf)
				{
					screen += " ";
				}
			}
		}
		screen += "\n";
	}
	for (int x = 0; x < BoardWidth + 2; x++)
	{
		screen += (char)178;
	}

	// draw bullets
	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets[i].GetDir() == 's')
		{
			screen.at(((bullets[i].y * (BoardWidth + 3)) - 1) + (bullets[i].x + 1)) = (char)203;
		}
		else if (bullets[i].GetDir() == 'w')
		{
			screen.at(((bullets[i].y* (BoardWidth + 3)) - 1) + (bullets[i].x + 1)) = (char)202;
		}
	}

	screen += "\n Remaining lives: ";
	screen += itoa(SpaceShips[0]->hp);

	cout << screen;
}

char HordLogic(vector<Entity*> &SpaceShips, vector<Bullet> &bullets, int BoardWidth, int BoardLength, char PreDir, bool &PreNearBorder)
{
	bool NearBorder = false;
	char dir = PreDir;

	for (int Ship = 1; Ship < SpaceShips.size(); Ship++)
	{
		if (SpaceShips[Ship]->x == 1 || SpaceShips[Ship]->x + SpaceShips[Ship]->width - 1 == BoardWidth)
		{
			NearBorder = true;
		}
	}
	if (PreNearBorder && NearBorder)
	{
		if (dir == 'a')
		{
			dir = 'd';
		}
		else if (dir == 'd')
		{
			dir = 'a';
		}
		for (int Ship = 1; Ship < SpaceShips.size(); Ship++)
		{
			SpaceShips[Ship]->Move(dir);
		}
		PreNearBorder = false;
		return dir;

	}
	if (!NearBorder)
	{
		for (int Ship = 1; Ship < SpaceShips.size(); Ship++)
		{
			SpaceShips[Ship]->Move(dir);
		}
	}
	else
	{
		for (int Ship = 1; Ship < SpaceShips.size(); Ship++)
		{
			SpaceShips[Ship]->Move('s');
		}
		
	}

	for (int i = 1; i < SpaceShips.size(); i++)
	{
		if (SpaceShips[i]->hp == 2)
		{
			float Shootability = rand() % 100;
			if (Shootability > 74)
			{
				auto ptr = SpaceShips[i];
				if (ShootingEnemy* SE = dynamic_cast<ShootingEnemy*>(ptr))
					SE->Shoot(bullets);
			}
		}
	}

	PreNearBorder = NearBorder;
	return dir;
}

void HealthCalculation(vector<Entity*> &SpaceShips, vector<Bullet> &bullets)
{
	for (int i = 0; i < SpaceShips.size(); i++)
	{
		auto ship = SpaceShips[i];
		if (Player* ply = dynamic_cast<Player*>(ship))
		{
			ply->IfHit(SpaceShips, bullets);
		}
		else if (IdleEnemy* IE = dynamic_cast<IdleEnemy*>(ship))
		{
			Player* temp = dynamic_cast<Player*>(SpaceShips[0]);
			IE->IfHit(temp, bullets);
		}
		else if (ShootingEnemy* SE = dynamic_cast<ShootingEnemy*>(ship))
		{
			if (SpaceShips[0]->hp > 0)
			{
				Player* temp = dynamic_cast<Player*>(SpaceShips[0]);
				SE->IfHit(temp, bullets);
			}
		}
	}

	for (int i = 0; i < bullets.size(); i++)
	{
		bullets[i].IfHit(SpaceShips);
	}
}

void RemoveDead(vector<Entity*> &SpaceShips, vector<Bullet> &bullets)
{
	for (int i = 0; i < SpaceShips.size(); i++)
	{
		if (SpaceShips[i]->hp <= 0)
		{
			SpaceShips.erase(SpaceShips.begin() + i);
		}
	}
	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets[i].hp <= 0)
		{
			bullets.erase(bullets.begin() + i);
		}
	}
}

void ControlPlayer(Player* ply, vector<Bullet> &bullets, bool IsGameOver)
{
	float ElapsedTime = 0;
	auto start = chrono::steady_clock::now();

	while (!IsGameOver)
	{
		char action = ply->GetAction();
		if (action == 'x' && ElapsedTime > 1000)
		{
			ply->Shoot(bullets);
			ElapsedTime = 0;
			start = chrono::steady_clock::now();
		}
		if (action == 'z')
		{
			ply->Move('z');
		}
		if (action == 'c')
		{
			ply->Move('c');
		}
		this_thread::sleep_for(chrono::milliseconds(250));

		auto end = chrono::steady_clock::now();
		ElapsedTime += chrono::duration_cast<chrono::milliseconds>(end - start).count();
	}
}

void RemoveBulletsOutsideOfTheBoard(vector<Bullet>& bullets, int BoardLength)
{
	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets[i].y < 1 || bullets[i].y > BoardLength - 1)
		{
			bullets.erase(bullets.begin() + i);
		}
	}
}

int main()
{
	int BoardWidth = 75;
	int BoardLength = 26;
	vector<Bullet> bullets;
	vector<Entity*> SpaceShips;
	
	setup(SpaceShips, BoardWidth, BoardLength);	

	double ElapsedTime = 0;
	int PreviousRoundSec = 0;
	int PreviousRoundQSec = 0;

	auto pply = SpaceShips[0];
	Player* ply = dynamic_cast<Player*>(pply);
	

	bool PreNearBorder = false;
	char PreDir = HordLogic(SpaceShips, bullets, BoardWidth, BoardLength, 'a', PreNearBorder);
	DrawGame(BoardWidth, BoardLength, SpaceShips, bullets);
	int IsGameOver = 0;
	auto start = chrono::steady_clock::now();
	thread PlayerControls(ControlPlayer, ply, ref(bullets), IsGameOver);
	
	//game loop
	while(!IsGameOver)
	{
		
		// Updates every half a second
		if ((int)(ElapsedTime / 500) > PreviousRoundQSec)
		{
			PreviousRoundQSec = (int)(ElapsedTime / 500);


			BulletCalculation(bullets);
			RemoveBulletsOutsideOfTheBoard(bullets, BoardLength);
			HealthCalculation(SpaceShips, bullets);
			RemoveDead(SpaceShips, bullets);
			DrawGame(BoardWidth, BoardLength, SpaceShips, bullets);
		}
		
		// Updates EverySecond
		if ((int)(ElapsedTime / 1000) > PreviousRoundSec)
		{
			PreviousRoundSec = (int)(ElapsedTime / 1000);


			PreDir = HordLogic(SpaceShips, bullets,BoardWidth, BoardLength, PreDir, PreNearBorder);
			
		}

		IsGameOver = GameOver(SpaceShips);

		// To keep time
		auto end = chrono::steady_clock::now();
		ElapsedTime = chrono::duration_cast<chrono::milliseconds>(end - start).count();
	}

	PlayerControls.detach();
	
	
	// conjualations
	if (IsGameOver == 1)
	{
		cout << "CONGsddLATUIONS";
	}
	else if (IsGameOver == 2)
	{
		system("cls");
		string lol =
			"\n\n\n\n"
			"     ######                ####        #############\n"
			"   ##########              ####        #############\n"
			"  ####                     ####             ###\n"
			" ####     #####            ####             ###\n"
			" ####    #######           ####             ###\n"
			" ####        ####          ####             ###\n"
			"  ####     #####           ####             ###\n"
			"   ############            ####             ###\n"
			"    #########              ####             ###\n"
			"\n\n"
			"      ######           ####     ####        ######\n"
			"   ##########          ####     ####        #########\n"
			"  ####                 ####     ####        ####   ####\n"
			" ####     #####        ####     ####        ####    ####\n"
			" ####    #######       ####     ####        ####    ####\n"
			" ####        ####      ####     ####        ####    ####\n"
			"  ####     #####       #####   #####        ####   ####\n"
			"   ############         ###########         #########\n"
			"    #########            #########          ######\n";
		cout << lol << endl;
		cin >> lol;
	}
	return 0;
}