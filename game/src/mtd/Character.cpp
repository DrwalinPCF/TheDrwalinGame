
//	This file is part of The Drwalin Game project
// Copyright (C) 2018-2019 Marek Zalewski aka Drwalin aka DrwalinPCF

#ifndef CHARACTER_CPP
#define CHARACTER_CPP

#include "..\css\Character.h"

#include <Engine.h>

#include <Debug.h>
#include <Math.hpp>

#include <ctime>

#include "CharacterEvent.cpp"

void Character::QueueMove( float val )
{
	if( queueStep < val )
		queueStep = val;
}

void Character::SetScale( btVector3 scale )
{
	Object::SetScale( scale );
}

void Character::NextOverlappingFrame()
{
	Object::NextOverlappingFrame();
}

float Character::GetBottomY()
{
	std::shared_ptr<const btRigidBody> rigidBody = this->GetBody<const btRigidBody>();
	if( rigidBody )
	{
		btVector3 min, max, origin;
		rigidBody->getAabb( min, max );
		return min.y();
		//return (min.y()*0.85) + (GetLocation().y()*0.15);
	}
	return currentTransform.getOrigin().y();
}

btTransform Character::MakeTransformFromEuler( const btVector3 & euler )
{
	btQuaternion quat( btVector3( 0, 1, 0 ), -euler.y() );
	quat *= btQuaternion( btVector3( 1, 0, 0 ), euler.x() );
	quat *= btQuaternion( btVector3( 0, 0, 1 ), euler.z() );
	return btTransform( quat );
}

float Character::GetMovementVelocity() const
{
	return this->defaultVelocity;
}

btVector3 Character::GetJumpVelocity() const
{
	return btVector3(0,64,0);
}



void Character::CorrectCameraRotation()
{
	if( cameraRotation.m_floats[0] < -Math::PI*0.5f )
		cameraRotation.m_floats[0] = -Math::PI*0.5f;
	else if( cameraRotation.m_floats[0] > Math::PI*0.5f )
		cameraRotation.m_floats[0] = Math::PI*0.5f;
	
	while( cameraRotation.m_floats[1] >= Math::PI * 2.0f )
		cameraRotation.m_floats[1] -= Math::PI * 2.0f;
	while( cameraRotation.m_floats[1] < 0.0f )
		cameraRotation.m_floats[1] += Math::PI * 2.0f;
}

void Character::SetCamera( std::shared_ptr<Camera> camera )
{
	this->camera = camera;
}

void Character::SetCameraLocation( const btVector3 & location )
{
	cameraLocation = location;
	if( camera )
		camera->SetPos( cameraLocation );
}

void Character::SetCameraRotation( const btVector3 & rotation )
{
	cameraRotation = rotation;
	CorrectCameraRotation();
	if( camera )
		camera->SetRotation( cameraRotation );
}

btVector3 Character::GetCameraLocation() const
{
	return GetLocation() + cameraLocation;
}

btVector3 Character::GetForwardVector() const
{
	return ( Character::MakeTransformFromEuler( btVector3( cameraRotation.x(), cameraRotation.y(), 0.0 ) ) * btVector3(0.0,0.0,-1.0) ) * btVector3( 1, -1, 1 );
}

btVector3 Character::GetFlatForwardVector() const
{
	return Character::MakeTransformFromEuler( btVector3( 0.0, cameraRotation.y(), 0.0 ) ) * btVector3(0.0,0.0,-1.0);
}

btVector3 Character::GetLeftVector() const/////////////////////////////
{
	return Character::MakeTransformFromEuler( btVector3( 0.0, cameraRotation.y(), cameraRotation.z() ) ) * btVector3(-1.0,0.0,0.0);
}

btVector3 Character::GetFlatLeftVector() const
{
	return Character::MakeTransformFromEuler( btVector3( 0.0, cameraRotation.y(), 0.0 ) ) * btVector3(-1.0,0.0,0.0);
}


void Character::Tick( const float deltaTime )
{
	Object::Tick( deltaTime );
}

void Character::ApplyDamage( const float damage, btVector3 point, btVector3 normal )
{
}

void Character::ApplyImpactDamage( const float damage, const float impetus, btVector3 direction, btVector3 point, btVector3 normal )
{
	Object::ApplyImpactDamage( damage, impetus, direction, point, normal );
	Character::ApplyDamage( damage, point, normal );
}






void Character::Load( std::istream & stream )
{
	Object::Load( stream );
}

void Character::Save( std::ostream & stream ) const
{
	Object::Save( stream );
}

void Character::Spawn( std::string name, std::shared_ptr<btCollisionShape> shape, btTransform transform )
{
	Object::Spawn( name, shape, transform );
}

void Character::Despawn()
{
	Object::Despawn();
}

void Character::Destroy()
{
	Object::Destroy();
}

extern "C" std::shared_ptr<Object> GetClassInstantiator(){ static std::shared_ptr<Object> instantiator( new Character(), [](Object * ptr){delete ptr;} ); return instantiator; }
int Character::GetTypeSize() const{ return sizeof(Character); }
void Character::Free(){ delete this; }
std::shared_ptr<Object> Character::New() const{ return std::dynamic_pointer_cast<Object>( std::shared_ptr<Character>( new Character(), [](Object * ptr){delete ptr;} ) ); }
std::string Character::GetClassName() const{ return "Character"; }

Character::Character() :
	Object(), cameraRotation(0,0,0), cameraLocation(0,0,0),
	defaultVelocity(3.7), height(1.75),
	queueStep(0.0)
{
	
	this->SetCameraLocation( btVector3( 0.0, height * 0.9, 0.0 ) );
}

Character::~Character()
{
	this->Destroy();
}

#endif

