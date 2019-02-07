
#include "Potion.h"
class HealthPotion : public Potion
{
public:
	HealthPotion();
	void apply(Player* player);
	void draw();
	bool initialize(Game *gamePtr, int width, int height, int ncols, TextureManager *textureM);
	void update(float frameTime);
	~HealthPotion();
};
