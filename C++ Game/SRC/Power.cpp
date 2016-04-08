#include <stdlib.h>
#include "GameUtil.h"
#include "Power.h"
#include "BoundingShape.h"

Power::Power(void) : GameObject("Power")
{
	mAngle = rand() % 360;
	mRotation = rand() % 90;
	mPosition.x = rand() / 2;
	mPosition.y = rand() / 2;
	mPosition.z = 0.0;
	mVelocity.x = 10.0 * cos(DEG2RAD*mAngle);
	mVelocity.y = 10.0 * sin(DEG2RAD*mAngle);
	mVelocity.z = 0.0;
}

Power::~Power(void)
{
}

void Power::Render(void)
{
	glScalef(2.0, 2.0, 2.0);
	// Disable lighting for solid colour lines
	glDisable(GL_LIGHTING);
	// Start drawing lines
	glBegin(GL_LINE_LOOP);
	// Set colour to Yellow
	glColor3f(0.9, 0.9, 0.0);
	// Add vertices to draw an octagon
	glVertex3f(-7, -7, 0.0);
	glVertex3f(-10, 0, 0.0);
	glVertex3f(-7, 7, 0.0);
	glVertex3f(0, 10, 0.0);
	glVertex3f(7, 7, 0.0);
	glVertex3f(10, 0, 0.0);
	glVertex3f(7, -7, 0.0);
	glVertex3f(0, -10, 0.0);
	// Finish drawing lines
	glEnd();
	// Enable lighting
	glEnable(GL_LIGHTING);
}

bool Power::CollisionTest(shared_ptr<GameObject> o)
{
	if (o->GetType() == GameObjectType("Asteroid")) return false;
	if (o->GetType() == GameObjectType("Bullet")) return false;
	if (o->GetType() == GameObjectType("EnemyBullet")) return false;
	if (GetType() == o->GetType()) return false;
	if (mBoundingShape.get() == NULL) return false;
	if (o->GetBoundingShape().get() == NULL) return false;
	return mBoundingShape->CollisionTest(o->GetBoundingShape());
}

void Power::OnCollision(const GameObjectList& objects)
{
	mWorld->FlagForRemoval(GetThisPtr());
}