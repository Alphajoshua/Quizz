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
		const auto name = StringToolBox::getUtf8(category->getName());
		statement << name;
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

	SharedPtr<std::vector<SharedPtr<Category>>> CategoryCTRL::loadColCategory() const
	{
		const auto colCategory = refNew<std::vector<SharedPtr<Category>>>();
		const auto connection = getDataBaseConnection()->getConnection();
		try {
			*connection << "SELECT id, name FROM CATEGORY" >> [&](int id, const AlphaString& name) 
			{ 
				const auto category = refNew<Category>();
				category->setId(id);
				category->setName(StringToolBox::getUnicodeString(name));
				colCategory->push_back(category);
			};
		}
		catch( const sqlite::sqlite_exception& e ) {
			std::cerr << "SQLite error: " << e.what() << std::endl;
		}

		
		return colCategory;
	}

#pragma endregion

}