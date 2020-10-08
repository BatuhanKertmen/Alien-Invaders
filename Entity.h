#pragma once
#include <iostream>
#include <vector>

using namespace std;


class Entity
{
public:

	int x;
	int y;

	int width;
	int length;

	int hp;
	bool shooting;

	char type;

public:

	Entity(int x, int y, int width, int length, int hp, bool shooting, char type): x(x), y(y), width(width), length(length), hp(hp), shooting(shooting), type(type) {}
	virtual void Move(char dir) = 0;
};

class Bullet : public Entity
{
private:
	char dir;

public:
	Bullet(int x, int y, char GivenDir, int GivenID) : Entity(x, y, 1, 1, 1, false, 'b') { dir = GivenDir; }

	char GetDir();
	void Move(char Dir) override;
	void IfHit(vector<Entity*>& SpaceShips);

};

class Player : public Entity
{
private:
	char action = 'a';

public:
	Player(int x, int y, int hp) : Entity(x, y, 3, 2, hp, true, 'p') {}

	char GetAction();
	void Move(char dir) override;
	void Shoot(vector<Bullet>& bullets);
	bool IfHit(vector<Entity*>& SpaceShips, vector<Bullet>& bullets);

	
};

class IdleEnemy : public Entity
{
public:
	
	IdleEnemy(int x, int y, int hp, char type) : Entity(x, y, 3, 2, hp, false, type){}
	
	bool IfHit(Player* player, vector<Bullet> &bullets);
	void Move(char HordDir) override;
	
};

class ShootingEnemy : public Entity
{


public:
	ShootingEnemy(int x, int y, int hp) : Entity(x, y, 3, 2, hp, true, 's') {}

	void Shoot(vector<Bullet> &bullets);
	bool IfHit(Player* player, vector<Bullet> &bullets);
	void Move(char HordDir) override;
};
