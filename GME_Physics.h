//-----------------------------------------------
// Graph_Mode_Engine version 0.2.6
// GME_PHYSICS
// Part of GMEv0.2.6
// Copyright (c) 2012-2016. All rights reserved.
//-----------------------------------------------

#ifndef __GME_PHYSICS_H__
#define __GME_PHYSICS_H__

#include <iostream>
#include <math.h>
#include "GME_Vector.h"

using namespace std;

namespace GME
{
namespace GME_PHYSICS
{
//-------------------------
// GME - Classic Particle
//-------------------------

class ClassicParticle
{
public:
                    ClassicParticle();
                    ~ClassicParticle();
                    ClassicParticle(Vector3& r, Vector3& a);
        Vector3     position;
        Vector3     prevPosition;
        Vector3     velocity;
        Vector3     acceleration;
        float       radius;
        float       mass;
        void        move (const float dt);
        bool        collisionDetect(ClassicParticle& a, ClassicParticle& b);
        void        solver(ClassicParticle& a, ClassicParticle& b) const;
};
    
class PositionBasedParticle: public ClassicParticle
{
public:
    
};

ClassicParticle::ClassicParticle()
{
	position = Vector3();
	prevPosition = Vector3();
	acceleration = Vector3();
}

ClassicParticle::ClassicParticle(Vector3& r, Vector3& a)//экспериментальный метод, создаем два вектора и передаем их в функцию. Vector3 a = (1,1,1) и т.д.
{
	position = (Vector3) r;
	acceleration = (Vector3) a;
}

ClassicParticle::~ClassicParticle()
{

}

void ClassicParticle::move(const float dt)
{
  Vector3 delta = position - prevPosition;
  prevPosition = position;
  position += delta + acceleration * dt * dt;
}

bool ClassicParticle::collisionDetect(ClassicParticle& a, ClassicParticle& b)
{
	Vector3 r1 = a.position;
	Vector3 r2 = b.position;
	if((r1-r2).abs() < (a.radius + b.radius))
		return true;
	else return false;
}

void ClassicParticle::solver(ClassicParticle& a, ClassicParticle& b) const//локальные переменные а и б остаются внутри функции, вызывая функцию для глобальных переменных-частиц, не получаем возврат -> не получаем координаты для движения
{
	Vector3 r1 = a.position;
	Vector3 r2 = b.position;
	Vector3 penetrationDirection = (r2 - r1).normalize();
	float penetrationDepth = a.radius + b.radius - (r2 - r1).abs();
    a.position -= penetrationDirection * penetrationDepth * 1.0f;//0.5f;
    b.position += penetrationDirection * penetrationDepth * 1.0f;//0.5f;
    //return Vector2(a.position.x, b.position.x);
}

/*class PositionBasedParticle
{
public:
	PositionBasedParticle();
	~PositionBasedParticle();
	Vector3 Position;
	Vector3 Acceleration;
	Vector3 delta;
	float radius;
	void Move(float dt);
	void Push(Vector3 delta);
};

PositionBasedParticle::PositionBasedParticle (void)
{
	Position = Vector3(0.0f, 0.0f, 0.0f);
	delta = Vector3(0.0f, 0.0f, 0.0f);
	Acceleration = Vector3(0.0f, 0.0f, 0.0f);
}

PositionBasedParticle::~PositionBasedParticle (void)
{

}

void PositionBasedParticle::Move(float dt)
{
  delta += Acceleration * dt * dt;
  Position += delta;
}

void PositionBasedParticle::Push(Vector3 delta)
{
  Position += delta;
  delta += delta;
}*/

}//end namespace GME_MATH
}//end namespace GMEngine

#endif /* __GME_PHYSICS_H__ */
