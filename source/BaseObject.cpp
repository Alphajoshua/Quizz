#include "stdafx.h"
#include "BaseObject.h"

namespace Alpha
{
#pragma region Anonymous

	namespace
	{

	}

#pragma endregion

#pragma  region Private

	class BaseObject::Private
	{
	public:
		int id{ DEFAULT_ID };
	};

#pragma endregion

#pragma region Constructors/Destructors

	BaseObject::BaseObject()
		:d(new Private())
	{

	}

	BaseObject::~BaseObject()
	{
		delete d;
	}
#pragma endregion

#pragma region **** Heritage ****

#pragma endregion

#pragma region **** Accessors ****

	int BaseObject::getId() const
	{
		return d->id;
	}

	void BaseObject::setId(int value)
	{
		d->id = value;
	}

#pragma endregion

#pragma region **** Methods ****

#pragma endregion

}