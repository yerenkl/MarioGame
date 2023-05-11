#include "Common.h"

class Object
{
protected:
	Texture textures[14];
	RenderWindow* window;
	int state;
	int heading;
private:
	Sprite sprite;
	Vector2f pos;
public:
	Object(RenderWindow* window); //Constructor
	void setPosition(Vector2f pos); //Sets position of the object
	Vector2f getPosition(); //Gets position of the object
	IntRect boundingBox(void); //Returns the bounding rectangle of the object texture
	void draw(RenderWindow& window);//Draws current the object texture to screen
	void move(void); //Abstract method that will be overridden
	void fall(void); //Abstract method that will be overridden
	void jump(bool down); //Abstract method that will be overridden
};
