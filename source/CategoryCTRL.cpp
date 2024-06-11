#include "stdafx.h"
#include "Category.h"
#include "CategoryCTRL.h"
#include "DataBaseConnection.h"

namespace Alpha
{
#pragma region Anonymous

	namespace
	{

	}

#pragma endregion

#pragma  region Private

	class CategoryCTRL::Private
	{
	public:

	};

#pragma endregion

#pragma region Constructors/Destructors

	CategoryCTRL::CategoryCTRL()
		:d(new Private())
	{
		const auto colColumn = refNew<std::vector<UnicodeString>>();
		colColumn->push_back(L"NAME");

		setColColumn(colColumn);
		setTableName(L"CATEGORY");
	}

	CategoryCTRL::~CategoryCTRL()
	{
		delete d;
	}
#pragma endregion

#pragma region **** Heritage ****

	void CategoryCTRL::updateQueryValues(const SharedPtr<BaseObject>& baseObject, sqlite::database_binder& statement)
	{
		const auto category = refCast<Category>(baseObject);
		statement << StringToolBox::getUtf8(category->getName()).c_str();
	}

	void CategoryCTRL::updateObjectValues(const SharedPtr<BaseObject>& baseObject, sqlite::database_binder& statement)
	{
		const auto category = refCast<Category>(baseObject);
		category->setId(getDataBaseConnection()->getLastInsertedId());
	}

#pragma endregion

#pragma region **** Accessors ****
	
#pragma endregion

#pragma region **** Methods ****

	void CategoryCTRL::addCategory(const SharedPtr<Category>& category)
	{
		addBaseObject(refCast<BaseObject>(category));
	}
	void CategoryCTRL::modifyCategory(const SharedPtr<Category>& category)
	{
		modifyBaseObject(refCast<BaseObject>(category));
	}
	void CategoryCTRL::removeCategory(const SharedPtr<Category>& category)
	{
		removeBaseObject(refCast<BaseObject>(category));
	}

#pragma endregion

}