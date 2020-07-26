
//	This file is part of The Drwalin Engine project
// Copyright (C) 2018-2020 Marek Zalewski aka Drwalin aka DrwalinPCF

#ifndef COLLISION_OBJECT_MANAGER_CPP
#define COLLISION_OBJECT_MANAGER_CPP

#include "../css/CollisionObjectManager.h"

#include <bullet/BulletCollision/CollisionDispatch/btGhostObject.h>

std::shared_ptr<btCollisionObject> CollisionObjectManager::CreateCollisionObject(std::shared_ptr<CollisionShape> shape, btTransform transform) {
	if(shape == NULL)
		return NULL;
	
	std::shared_ptr<btCollisionObject> object(new btCollisionObject());
	object->setCollisionShape(shape->GetNewBtCollisionShape());
	object->setWorldTransform(transform);
	return object;
}

std::shared_ptr<btCollisionObject> CollisionObjectManager::CreateRigidBody(std::shared_ptr<CollisionShape> shape, btTransform transform, float mass, btVector3 inertia) {
	if(shape == NULL)
		return NULL;
	btCollisionShape *btShape = shape->GetNewBtCollisionShape();
	if(mass > 0.0f)
		btShape->calculateLocalInertia(mass, inertia);
	
	btDefaultMotionState *motionState = new btDefaultMotionState(transform);
	return std::dynamic_pointer_cast<btCollisionObject>(std::shared_ptr<btRigidBody>(new btRigidBody(mass <= 0.0f ? 0.0f : mass, motionState, btShape, inertia)));
}

std::shared_ptr<btCollisionObject> CollisionObjectManager::CreatePairCachingGhostObject() {
	return std::dynamic_pointer_cast<btCollisionObject>(std::shared_ptr<btPairCachingGhostObject>(new btPairCachingGhostObject()));
}

std::shared_ptr<btCollisionObject> CollisionObjectManager::CreateGhostObject(std::shared_ptr<CollisionShape> shape, btTransform transform) {
	std::shared_ptr<btGhostObject> ghost(new btGhostObject());
	ghost->setCollisionShape(shape->GetNewBtCollisionShape());
	ghost->setWorldTransform(transform);
	return std::dynamic_pointer_cast<btCollisionObject>(ghost);
}

#endif
