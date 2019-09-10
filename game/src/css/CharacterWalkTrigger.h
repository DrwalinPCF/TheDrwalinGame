
//	This file is part of The Drwalin Game project
// Copyright (C) 2018-2019 Marek Zalewski aka Drwalin aka DrwalinPCF

#ifndef CHARACTER_WALK_TRIGGER_H
#define CHARACTER_WALK_TRIGGER_H

#include "Trigger.h"
#include "Character.h"

#include <cmath>

class CharacterWalkTrigger : public Trigger
{
protected:
	
	std::shared_ptr<Entity> parent;
	bool isAnyInside;
	
	void EventOverlapp( Entity * other, btPersistentManifold * persisstentManifold );
	
public:
	
	virtual void NextOverlappingFrame() override;
	
	bool IsAnyInside() const;
	void SetParent( std::shared_ptr<Entity> parent );
	
	virtual void EventOnEntityBeginOverlapp( Entity * other, btPersistentManifold * persisstentManifold ) override;
	virtual void EventOnEntityTickOverlapp( Entity * other, btPersistentManifold * persisstentManifold ) override;
	virtual void EventOnEntityEndOverlapp( Entity * other ) override;
	
	virtual void Tick( const float deltaTime ) override;
	
	virtual void Load( std::istream & stream ) override;
	virtual void Save( std::ostream & stream ) const override;
	virtual void Spawn( std::string name, std::shared_ptr<btCollisionShape> shape, btTransform transform ) override;
	virtual void Despawn() override;
	
	virtual void Destroy() override;
	
	virtual int GetTypeSize() const override;
	virtual void Free() override;
	virtual std::shared_ptr<Entity> New() const override;
	virtual std::string GetClassName() const override;
	
	CharacterWalkTrigger();
	virtual ~CharacterWalkTrigger() override;
};

#endif

