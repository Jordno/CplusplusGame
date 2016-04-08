#include "GameUtil.h"
#include "GameWorld.h"
#include "EnemyBullet.h"
#include "Alien.h"
#include "BoundingSphere.h"

using namespace std;

// PUBLIC INSTANCE CONSTRUCTORS ///////////////////////////////////////////////

/**  Default constructor. */
Alien::Alien()
	: GameObject("Alien"), mAlienThrust(0)
{
	mShield = true;
	mShieldlevel2 = false;
	mShieldlevel3 = false;
}

/** Construct a spaceship with given position, velocity, acceleration, angle, and rotation. */
Alien::Alien(GLVector3f p, GLVector3f v, GLVector3f a, GLfloat h, GLfloat r)
	: GameObject("Spaceship", p, v, a, h, r), mAlienThrust(0)
{
}

/** Copy constructor. */
Alien::Alien(const Alien& s)
	: GameObject(s), mAlienThrust(0)
{
}

/** Destructor. */
Alien::~Alien(void)
{
}

// PUBLIC INSTANCE METHODS ////////////////////////////////////////////////////

/** Update this spaceship. */
void Alien::Update(int t)
{
	// Call parent update function
	GameObject::Update(t);
}

/** Render this spaceship. */
void Alien::Render(void)
{
	if (mAlienShape.get() != NULL)
	{
		mAlienShape->Render();
	}

	// If ship is thrusting
	if ((mAlienThrust > 0) && (mAlienThrusterShape.get() != NULL))
	{
		mAlienThrusterShape->Render();
	}


	// Enable lighting
	GameObject::Render();

	if (mShield)
	{
		glScalef(7, 6, 8);
		// Disable lighting for solid colour lines
		glDisable(GL_LIGHTING);
		// Start drawing lines
		glBegin(GL_LINE_LOOP);

		if (mShieldlevel3)
		{
			// Set colour to Dark blue
			glColor3f(0.0, 0.0, 0.8);
		}
		else if (mShieldlevel2)
		{
			// Set colour to Blue
			glColor3f(0.0, 0.5, 0.8);
		}
		else
		{
			// Set colour to light blue
			glColor3f(0.5, 0.8, 0.8);
		}
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

	glColor3f(0.9, 0.0, 0.0);
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

/** Fire the rockets. */
void Alien::Thrust(float t)
{
	mAlienThrust = t;
	// Increase acceleration in the direction of ship
	mAcceleration.x = mAlienThrust*cos(DEG2RAD*mAngle);
	mAcceleration.y = mAlienThrust*sin(DEG2RAD*mAngle);
}

/** Set the rotation. */
void Alien::Rotate(float r)
{
	mRotation = r;
}

/** Shoot a bullet. */
void Alien::Shoot(void)
{
	// Check the world exists
	if (!mWorld) return;
	// Construct a unit length vector in the direction the spaceship is headed
	GLVector3f Enemyspaceship_heading(cos(DEG2RAD*mAngle), sin(DEG2RAD*mAngle), 0);
	Enemyspaceship_heading.normalize();
	// Calculate the point at the node of the spaceship from position and heading
	GLVector3f bullet_position = mPosition + (Enemyspaceship_heading * 4);
	// Calculate how fast the bullet should travel
	float bullet_speed = 30;
	// Construct a vector for the bullet's velocity
	GLVector3f bullet_velocity = mVelocity + Enemyspaceship_heading * bullet_speed;
	// Construct a new bullet
	shared_ptr<GameObject> enemybullet
		(new EnemyBullet(bullet_position, bullet_velocity, mAcceleration, mAngle, 0, 2000));
	enemybullet->SetBoundingShape(make_shared<BoundingSphere>(enemybullet->GetThisPtr(), 2.0f));
	enemybullet->SetShape(mEnemyBulletShape);
	// Add the new bullet to the game world
	mWorld->AddObject(enemybullet);

}

bool Alien::CollisionTest(shared_ptr<GameObject> o)
{
	if (o->GetType() != GameObjectType("Asteroid") && o->GetType() != GameObjectType("Bullet") && o->GetType() != GameObjectType("Alien")) return false;
	if (mBoundingShape.get() == NULL) return false;
	if (o->GetBoundingShape().get() == NULL) return false;
	return mBoundingShape->CollisionTest(o->GetBoundingShape());
}

void Alien::OnCollision(const GameObjectList &objects)
{
	if (mShield == true)
	{
		if (mShieldlevel3 == true)
		{
			mShieldlevel3 = false;
		}
		else if (mShieldlevel2 == true)
		{
			mShieldlevel2 = false;
		}
		else
		{
			mShield = false;
		}
	}
	else
	{
		mWorld->FlagForRemoval(GetThisPtr());
	}
}