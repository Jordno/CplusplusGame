//#include <stdlib.h>
//#include "GameUtil.h"
//#include "Shield.h"
//#include "BoundingShape.h"
//
//Shield::Shield(void) : GameObject("Shield")
//{
//	mAngle = rand() % 360;
//	mRotation = rand() % 90;
//	mPosition.x = rand() / 2;
//	mPosition.y = rand() / 2;
//	mPosition.z = 0.0;
//	mVelocity.x = 10.0 * cos(DEG2RAD*mAngle);
//	mVelocity.y = 10.0 * sin(DEG2RAD*mAngle);
//	mVelocity.z = 0.0;
//}
//
//Shield::~Shield(void)
//{
//}
//
//void Shield::Render(void)
//{
//	// Disable lighting for solid colour lines
//	glDisable(GL_LIGHTING);
//	// Start drawing lines
//	glBegin(GL_LINE_LOOP);
//	// Set outline  colour to yellow
//	glColor3f(0, 191, 255);
//	//set fill colour to yellow
//
//	// Add vertices to draw an octagon
//	glVertex3f(-7, -7, 0.0);
//	glVertex3f(-10, 0, 0.0);
//	glVertex3f(-7, 7, 0.0);
//	glVertex3f(0, 10, 0.0);
//	glVertex3f(7, 7, 0.0);
//	glVertex3f(10, 0, 0.0);
//	glVertex3f(7, -7, 0.0);
//	glVertex3f(0, -10, 0.0);
//	// Finish drawing lines
//	glEnd();
//	// Enable lighting
//	glEnable(GL_LIGHTING);
//}
//
//bool Shield::CollisionTest(shared_ptr<GameObject> o)
//{
//	if (o->GetType() != GameObjectType("Spaceship")) return false;
//	if (o->GetType() == GameObjectType("Asteroid")) return true;
//	if (mBoundingShape.get() == NULL) return false;
//	if (o->GetBoundingShape().get() == NULL) return false;
//	return mBoundingShape->CollisionTest(o->GetBoundingShape());
//
//}
//
//void Shield::OnCollision(const GameObjectList& objects)
//{
//	mWorld->FlagForRemoval(GetThisPtr());
//}
//
//
//
