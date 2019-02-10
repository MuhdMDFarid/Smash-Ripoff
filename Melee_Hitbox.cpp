#include "Melee_Hitbox.h"
#include "Player.h"

//class Player;

Melee_Hitbox::Melee_Hitbox() : Hitbox::Hitbox()
{
	//Hitbox::Hitbox();

	//Lifetime = 0.1f;
	//Expired = false;
	//collisionType = entityNS::BOX;
	//edge.top = -TILE_SIZE / 2;
	//edge.bottom = TILE_SIZE / 2;
	//edge.left = -TILE_SIZE / 2;
	//edge.right = TILE_SIZE / 2;

	//damage_component = new Damage_Component();
}


Melee_Hitbox::~Melee_Hitbox()
{
}

//bool Melee_Hitbox::initialize(Game * gamePtr, int width, int height, int ncols, TextureManager * textureM)
//{
//	return (Entity::initialize(gamePtr, width, height, ncols, textureM));
//}

//void Melee_Hitbox::draw()
//{
//	Entity::draw();
//}

//void Melee_Hitbox::remove()
//{
//	//SAFE_DELETE(this);
//}

void Melee_Hitbox::update(float frameTime,Player& player)
{
	// Hitbox_Attacks should move based on the player
	setCenterX(player.getCenterX() + (player.playerface)*getEdge().right*getScale()/*+X spawn offset*/);
	setCenterY(player.getCenterY());						//centers the Y coords of hitbox to player

	Hitbox::update(frameTime,player);

}

void Melee_Hitbox::collided()
{
	// when hitbox collides
}

void Melee_Hitbox::activate(Player & player)
{
	//setVisible(false);
	setVisible(true);
	Hitbox::activate(player);
	//setCenterX(player.getCenterX());
	//setCenterY(player.getCenterY());
}
