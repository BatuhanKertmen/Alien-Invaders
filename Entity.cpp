#include "Entity.h"

using namespace std;




static int BulletCounter = 0;

////////////////\\\\\\\\\\\\\\\\\\
///                            \\\
///          BULLET            \\\
///                            \\\
////////////////\\\\\\\\\\\\\\\\\\

char Bullet::GetDir()
{
	return dir;
}

void Bullet::Move(char dir)
{
	if (dir == 's')
	{
		y++;
	}
	else if (dir == 'w')
	{
		y--;
	}
}

void Bullet::IfHit(vector<Entity*>& SpaceShips)
{
	for (int ship = 0; ship < SpaceShips.size(); ship++)
	{
		for (int dboy = 0; dboy < SpaceShips[ship]->length; dboy++)
		{
			for (int dgenis = 0; dgenis < SpaceShips[ship]->width; dgenis++)
			{
				if (x == SpaceShips[ship]->x + dgenis && y == SpaceShips[ship]->y + dboy)
				{
					hp = 0;
				}
			}
		}
	}
}



////////////////\\\\\\\\\\\\\\\\\\
///                            \\\
///          PLAYER            \\\
///                            \\\
////////////////\\\\\\\\\\\\\\\\\\



char Player::GetAction()
{
	cin >> action;
	return action;
}

void Player::Move(char dir)
{
	if (dir == 'z' && x != 2)
	{
		x -= 1;
	}

	else if (dir == 'c' && x != 50 - width)
	{
		x += 1;
	}
}

void Player::Shoot(vector<Bullet>& bullets)
{
	Bullet temp(x + 1, y - 1, 'w', BulletCounter);
	bullets.push_back(temp);
	++BulletCounter;	
}

bool Player::IfHit(vector<Entity*> &SpaceShips, vector<Bullet> &bullets)
{
	for (int ship = 1; ship < SpaceShips.size(); ship++)
	{
		for (int boy = 0; boy < length; boy++)
		{
			for (int genis = 0; genis < width; genis++)
			{
				for (int dboy = 0; dboy < SpaceShips[ship]->length; dboy++)
				{
					for (int dgenis = 0; dgenis < SpaceShips[ship]->width; dgenis++)
					{
						if (x + genis == SpaceShips[ship]->x + dgenis && y + boy == SpaceShips[ship]->y + dboy)
						{
							hp = 0;
							return true;
						}
					}
				}
			}
		}
	}

	for (int bullet = 0; bullet < bullets.size(); bullet++)
	{
		for (int boy = 0; boy < length; boy++)
		{
			for (int genis = 0; genis < width; genis++)
			{
				if (x + genis == bullets[bullet].x && y + boy == bullets[bullet].y)
				{
					hp--;
					return true;
				}
			}
		}
	}

	return false;
}

////////////////\\\\\\\\\\\\\\\\\\
///                            \\\
///        IDLE ENEMY          \\\
///                            \\\
////////////////\\\\\\\\\\\\\\\\\\

void IdleEnemy::Move(char HordDir)
{
	if (HordDir == 'a')
	{
		x -= 1;
	}

	else if (HordDir == 'd')
	{
		x += 1;
	}

	else if (HordDir == 's')
	{
		y += 1;
	}
}

bool IdleEnemy::IfHit(Player* player, vector<Bullet> &bullets)
{
	for (int genis = 0; genis < width; genis++)
	{
		for (int boy = 0; boy < length; boy++)
		{
			for (int dgenis = 0; dgenis < player->width; dgenis++)
			{
				for (int dboy = 0; dboy < player->length; dboy++)
				{
					if (x + genis == player->x + dgenis && y + boy == player->y + dboy)
					{
						hp = 0;
						return true;
					}
				}
			}
		}
	}

	for (int bullet = 0; bullet < bullets.size(); bullet++)
	{
		for (int boy = 0; boy < length; boy++)
		{
			for (int genis = 0; genis < width; genis++)
			{
				if (x + genis == bullets[bullet].x && y + boy == bullets[bullet].y)
				{
					hp--;
					return true;
				}
			}
		}
	}

	return false;
}


////////////////\\\\\\\\\\\\\\\\\\
///                            \\\
///      SHOOTING ENEMY        \\\
///                            \\\
////////////////\\\\\\\\\\\\\\\\\\


void ShootingEnemy::Shoot(vector<Bullet> &bullets)
{
	Bullet temp(x + 1, y + 2, 's', BulletCounter);
	bullets.push_back(temp);
	++BulletCounter;
}

void ShootingEnemy::Move(char HordDir)
{
	if (HordDir == 'a')
	{
		x -= 1;
	}

	else if (HordDir == 'd')
	{
		x += 1;
	}

	else if (HordDir == 's')
	{
		y += 1;
	}
}

bool ShootingEnemy::IfHit(Player* player, vector<Bullet>& bullets)
{
	for (int genis = 0; genis < width; genis++)
	{
		for (int boy = 0; boy < length; boy++)
		{
			for (int dgenis = 0; dgenis < player->width; dgenis++)
			{
				for (int dboy = 0; dboy < player->length; dboy++)
				{
					if (x + genis == player->x + dgenis && y + boy  == player->y + dboy)
					{
						hp = 0;
						return true;
					}
				}
			}
		}
	}

	for (int bullet = 0; bullet < bullets.size(); bullet++)
	{
		for (int boy = 0; boy < length; boy++)
		{
			for (int genis = 0; genis < width; genis++)
			{
				if (x + genis == bullets[bullet].x && y + boy == bullets[bullet].y)
				{
					hp--;
					return true;
				}
			}
		}
	}

	return false;
}
