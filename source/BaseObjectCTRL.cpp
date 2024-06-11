#include "stdafx.h"
#include "BaseObjectCTRL.h"

namespace Alpha
{
#pragma region Anonymous

	namespace
	{

	}

#pragma endregion

#pragma  region Private

	class BaseObjectCTRL::Private
	{
	public:
		WeakPtr<DataBaseConnection> connection;
		UnicodeString tableName;
		SharedPtr<std::vector<UnicodeString>> colColumn;
	};

#pragma endregion

#pragma region Constructors/Destructors

	BaseObjectCTRL::BaseObjectCTRL()
		:d(new Private())
	{

	}

	BaseObjectCTRL::~BaseObjectCTRL()
	{
		delete d;
	}
		
#pragma endregion

#pragma region **** Heritage ****

#pragma endregion

#pragma region **** Accessors ****

	SharedPtr<DataBaseConnection> BaseObjectCTRL::getDataBaseConnection() const
	{
		if( empty(d->connection.lock()))
			logError(L"You have to set a connection before you use it");
		return d->connection.lock();
	}
	void BaseObjectCTRL::setDataBaseConnection(const SharedPtr<DataBaseConnection>& connection)
	{
		d->connection = connection;
	}
	UnicodeString BaseObjectCTRL::getTableName() const
	{
		if( d->tableName.empty())
			logError(L"You have to set a table name before you use it");
		return d->tableName;
	}
	void BaseObjectCTRL::setTableName(const UnicodeString& name)
	{
		d->tableName = name;
	}

	SharedPtr<std::vector<UnicodeString>> BaseObjectCTRL::getColColumn() const
	{
		if( empty(d->colColumn) )
			logError(L"You have to set a colColumn before you use it");
		return d->colColumn;
	}

	void BaseObjectCTRL::setColColumn(const SharedPtr<std::vector<UnicodeString>>& colColumn) const
	{
		d->colColumn = colColumn;
	}

#pragma endregion

#pragma region **** Methods ****

	void BaseObjectCTRL::updateQueryValues(const SharedPtr<BaseObject>& baseObject, sqlite::database_binder& statement)
	{
		//TO IMPLEMENT

		// Assuming Category is derived from BaseObject and has a getName method
		//const auto category = std::static_pointer_cast<Category>(baseObject);
		//statement << category->getName(); // Bind the value of name, add more bindings as necessary

	}

	void BaseObjectCTRL::updateObjectValues(const SharedPtr<BaseObject>& baseObject, sqlite::database_binder& statement)
	{
		//TO IMPLEMENT
	}

	bool BaseObjectCTRL::addBaseObject(const SharedPtr<BaseObject>& baseObject)
	{
		bool result{ false };
		const auto dbConnection = getDataBaseConnection();
		const auto connection = dbConnection->getConnection();
		const auto colColumn = getColColumn();
		const auto preparedColColumn = StringToolBox::JoinUnicodeString(colColumn);

		UnicodeString query = L"INSERT INTO " + getTableName() + L" (" + preparedColColumn + L") VALUES (";
		for (int index{ 0 }; index < colColumn->size(); ++index)
		{
			query += L"?";
			if (index < colColumn->size() - 1)
				query += L", ";
		}
		query += L");";

		try
		{
			dbConnection->begin(),
			*connection << StringToolBox::getUtf8(query).c_str();
			auto statement = *connection << StringToolBox::getUtf8(query).c_str();
			updateQueryValues(baseObject, statement);
			statement.execute();

			// Log the successful insertion
			UnicodeString message = L": INSERT INTO : ";
			for (const auto& col : *colColumn)
			{
				message += col + L", ";
			}
			logMessage(getTableName() + message);
			updateObjectValues(baseObject, statement);

			dbConnection->commit();
			result = true;
		}
		catch (const sqlite::sqlite_exception& e)
		{
			dbConnection->rollBack();
			logError(L"SQLite error: " + StringToolBox::getUnicodeString(e.what()));
		}
		return result;
	}
	bool BaseObjectCTRL::modifyBaseObject(const SharedPtr<BaseObject>& baseObject)
	{
		return false;
	}
	bool BaseObjectCTRL::removeBaseObject(const SharedPtr<BaseObject>& baseObject)
	{
		return false;
	}
#pragma endregion

}