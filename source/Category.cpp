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