#ifndef __ENEMYSPACESHIP_H__
#define __ENEMYSPACESHIP_H__

#include "GameUtil.h"
#include "GameObject.h"
#include "Shape.h"

class Alien : public GameObject
{
public:
	Alien();
	Alien(GLVector3f p, GLVector3f v, GLVector3f a, GLfloat h, GLfloat r);
	Alien(const Alien& s);
	virtual ~Alien(void);

	virtual void Update(int t);
	virtual void Render(void);

	virtual void Thrust(float t);
	virtual void Rotate(float r);
	virtual void Shoot(void);

	void SetAlienShape(shared_ptr<Shape> spaceship_shape) { mAlienShape = spaceship_shape; }
	void SetAlienThrusterShape(shared_ptr<Shape> thruster_shape) { mAlienThrusterShape = thruster_shape; }
	void SetAlienBulletShape(shared_ptr<Shape> bullet_shape) { mEnemyBulletShape = bullet_shape; }

	bool CollisionTest(shared_ptr<GameObject> o);
	void OnCollision(const GameObjectList &objects);

	bool mShield;
	bool mShieldlevel2;
	bool mShieldlevel3;

private:
	float mAlienThrust;

	shared_ptr<Shape> mAlienShape;
	shared_ptr<Shape> mAlienThrusterShape;
	shared_ptr<Shape> mEnemyBulletShape;
};

#endif