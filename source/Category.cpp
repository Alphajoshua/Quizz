#include "Category.h"

namespace Alpha
{
#pragma region Anonymous

	namespace
	{

	}

#pragma endregion

#pragma  region Private

	class Category::Private
	{
	public:
		int id{ 0 };
		UnicodeString name;

	};

#pragma endregion

#pragma region Constructors/Destructors

	Category::Category()
		:d(new Private())
	{

	}

	Category::~Category()
	{
		delete d;
	}
#pragma endregion

#pragma region **** Heritage ****

#pragma endregion

#pragma region **** Accessors ****

	int Category::getId() const
	{
		return d->id;
	}

	void Category::setId(int value)
	{
		d->id = value;
	}

	UnicodeString Category::getName() const
	{
		return d->name;
	}

	void Category::setName(const UnicodeString& name)
	{
		d->name = name;
	}

#pragma endregion

#pragma region **** Methods ****

#pragma endregion

}