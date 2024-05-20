#include "stdafx.h"
#include "BaseObjectCTRL.h"
#include "DataBaseConnection.h"

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

	void BaseObjectCTRL::updateQueryValues(const SharedPtr<BaseObject>& baseObject, sqlite3_stmt** stmt)
	{
		//TO IMPLEMENT
	}

	void BaseObjectCTRL::updateObjectValues(const SharedPtr<BaseObject>& baseObject, sqlite3_stmt** stmt)
	{
		//TO IMPLEMENT
	}

	bool BaseObjectCTRL::addBaseObject(const SharedPtr<BaseObject>& baseObject)
	{
		bool result{ false };
		const auto connection = getDataBaseConnection();
		const auto colColumn = getColColumn();
		const auto preparedColColumn = StringToolBox::JoinUnicodeString(colColumn);

		UnicodeString query = L"INSERT INTO " + getTableName() + L" (" + preparedColColumn + L") VALUES";
		for (int index{ 0 }; index < colColumn->size(); ++index)
			query += L" (?)";
		query += L";";
		
		sqlite3_stmt* stmt;
		int code = connection->prepareQuery(query,&stmt);
		updateQueryValues(baseObject, &stmt);

		if (code != SQLITE_OK)
		{
			connection->logQueryPreparationFailed();
			connection->finalizeStatement(stmt, getTableName());
			return result;
		}

		if (sqlite3_step(stmt) == SQLITE_DONE)
		{
			int nbrParameterCount = sqlite3_bind_parameter_count(stmt);
			UnicodeString message = L": INSERT INTO : ";
			for (int index{ 0 }; index < nbrParameterCount; ++index)
				addValueToMessage(&stmt, index, &message);
			logMessage(getTableName() + message);
			updateObjectValues(baseObject, &stmt);
			result = true;
		}

		connection->finalizeStatement(stmt, getTableName());
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

	void BaseObjectCTRL::addValueToMessage(sqlite3_stmt** stmt, int index, UnicodeString* message)
	{
		const auto type = sqlite3_column_type(*stmt, index);
		const auto value = getColumnValueAsString(stmt,index,type);
		message->append(index == 0 ? value : STRING_SEPARATOR + value);
	}

	UnicodeString BaseObjectCTRL::getColumnValueAsString(sqlite3_stmt** stmt, int index, int type)
	{
		UnicodeString result;

		switch (type)
		{
		case SQLITE_INTEGER:
		{
			const auto value = sqlite3_column_int(*stmt, index);
			result = std::to_wstring(value);
			break;
		}
		case SQLITE_TEXT:
		{
			const auto value = sqlite3_column_text(*stmt, index);
			result = StringToolBox::getUnicodeString(value);
			break;
		}
		default:
			logError(L"Unknown returned type");
			break;
		}

		return result;
	}

#pragma endregion

}