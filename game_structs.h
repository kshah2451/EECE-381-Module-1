#ifndef _GAME_STRUCTS_H_
#define _GAME_STRUCTS_H_

typedef struct
{
	int health;
	int bullet;
	int fire_rate;
	// Position of Tower's body (assuming tower is just a rectangle)
	//right x-coordinate = position[0], right y-coordinate = pos[1], 
	//left x-coordinate = pos[2], left y-coordinate = pos[3]
	int body_pos[4];  
	// vga info like the boxes that make up the image and colour


}Tower;

typedef struct 
{
	int type;
	int damage;
	int health;
	int speed;
	int attack_rate;
	// Position of Enemy's body (assuming enemy is just a rectangle)
	//right x-coordinate = position[0], right y-coordinate = pos[1], 
	//left x-coordinate = pos[2], left y-coordinate = pos[3]
	int body_pos[4];
	int ID;
	// vga info like the boxes that make up the image and colour

}Enemy;

typedef struct 
{
	int damage;
	int type;
	// Position of a single bullet
	//right x-coordinate = position[0], right y-coordinate = pos[1], 
	//left x-coordinate = pos[2], left y-coordinate = pos[3]
	int pos[4];
	int speed;
	// vga info like colour
}Bullet;

typedef struct
{




} HUD;




#endif