#include "stdafx.h"
#include "DataBaseConnection.h"

namespace Alpha
{
#pragma region Anonymous

	namespace
	{

	}

#pragma endregion

#pragma  region Private

	class DataBaseConnection::Private
	{
	public:
		UnicodeString dataBaseName{ DEFAULT_DB_CONNECTION };
		SharedPtr<sqlite::database> connection;
	};

#pragma endregion

#pragma region Constructors/Destructors

	DataBaseConnection::DataBaseConnection()
		:d(new Private())
	{

	}

	DataBaseConnection::DataBaseConnection(const UnicodeString& name)
		:d(new Private())
	{
		setDataBaseName(name);
	}

	DataBaseConnection::~DataBaseConnection()
	{
		delete d;
	}
#pragma endregion

#pragma region **** Heritage ****

#pragma endregion

#pragma region **** Accessors ****

	UnicodeString DataBaseConnection::getDataBaseName() const
	{
		return d->dataBaseName;
	}
	void DataBaseConnection::setDataBaseName(const UnicodeString& name)
	{
		if (!name.empty() )
			d->dataBaseName = name;
	}

#pragma endregion

#pragma region **** Methods ****

	SharedPtr<sqlite::database> DataBaseConnection::getConnection() const
	{
		return d->connection;
	}

	void DataBaseConnection::setConnection(const SharedPtr<sqlite::database>& object)
	{
		d->connection = object;
	}

	bool DataBaseConnection::connect()
	{
		bool result{ false };
		auto path = std::filesystem::current_path() / SOFTWARE_DIRECTORY / getDataBaseName();
		auto message =  (UnicodeString) path.wstring();
		try
		{
			setConnection(refNew<sqlite::database>(path.string()));
			result = true;
			logMessage(L"Succes connection to db: " + message);
		}
		catch (const std::exception& e)
		{
			logError(L"Failed connection to db: " + message + L" " + UnicodeString(e.what(), e.what() + strlen(e.what())));
		}
		
		return result;
	}

	bool DataBaseConnection::disconnect()
	{
		bool result{ false };

		setConnection(nullptr);

		if (const auto connection = getConnection(); !empty(connection))
			logError(L"Failed disconnection to db: " + getDataBaseName());
		else
		{
			result = true;
			logMessage(L"Succes disconnection to db: " + getDataBaseName());
		}

		return result;
	}

	void DataBaseConnection::checkTable(const UnicodeString& tableName, const UnicodeString& columnsDefinition)
	{
		const auto connection = getConnection();

		if (isTableExist(connection, tableName))
		{
			logSeparator();
			logMessage(L"TABLE " + tableName + L" exists");

			// Get the composition of the table
			try
			{
				*connection << StringToolBox::getUtf8(getTableInfoQuery(tableName)) >> [&](int id, AlphaString name, AlphaString type, int notnull, AlphaString dflt_value, int pk)
					{logMessage(L"ColumnName: " + StringToolBox::getUnicodeString(name) + L", Type: " + StringToolBox::getUnicodeString(type)); };
			}
			catch (const sqlite::sqlite_exception& e)
			{
				logQueryPreparationFailed(e);
			}
			
		}
		else
			cleanExecuteQuery(L"CREATE TABLE IF NOT EXISTS " + tableName + columnsDefinition);
	}

	void DataBaseConnection::checkTables()
	{
		checkTableQuestion();
		checkTableCategory();
		checkTableLink();
		logSeparator();
	}

	void DataBaseConnection::checkTableQuestion()
	{
		UnicodeString columnsDefinition = L" (ID INTEGER PRIMARY KEY AUTOINCREMENT, QUESTION_TITLE TEXT NOT NULL, RIGHT_ANSWER TEXT NOT NULL,"
			L"DUMMY_ANSWER TEXT NOT NULL, WRONG_ANSWER_1 TEXT NOT NULL, WRONG_ANSWER_2 TEXT NOT NULL, WRONG_ANSWER_3 TEXT NOT NULL, "
			L"WRONG_ANSWER_4 TEXT NOT NULL, WRONG_ANSWER_5 TEXT NOT NULL, DIFFICULTY INTEGER NOT NULL)";
		checkTable(L"QUESTION", columnsDefinition);
	}

	void DataBaseConnection::checkTableCategory()
	{
		UnicodeString columnsDefinition = L" ( ID INTEGER PRIMARY KEY AUTOINCREMENT,NAME TEXT NOT NULL)";
		checkTable(L"CATEGORY", columnsDefinition);
	}

	void DataBaseConnection::checkTableLink()
	{
		UnicodeString columnsDefinition = L" ( ID INTEGER PRIMARY KEY AUTOINCREMENT,QUESTION_ID INTEGER NOT NULL, CATEGORY_ID INTEGER NOT NULL)";
		checkTable(L"LINK", columnsDefinition);
	}

	bool DataBaseConnection::isTableExist(const SharedPtr<sqlite::database>& connection, const UnicodeString& tableName)
	{
		UnicodeString query = getTableExistQuery(tableName);
		bool tableExist{ false };
		try
		{
			*connection << StringToolBox::getUtf8(query) >> [&](AlphaString name) {tableExist = true; };
		}
		catch (const sqlite::sqlite_exception& e)
		{
			logQueryPreparationFailed(e);
		}
		return tableExist;
	}

	UnicodeString DataBaseConnection::getTableExistQuery(const UnicodeString& tableName) const
	{
		return L"SELECT name FROM sqlite_master WHERE type='table' AND name='" + tableName + L"'";
	}

	UnicodeString DataBaseConnection::getTableInfoQuery(const UnicodeString& tableName) const
	{
		return L"PRAGMA table_info(" + tableName + L")";
	}

	void DataBaseConnection::logQueryPreparationFailed(const sqlite::sqlite_exception& e)
	{
		logError(L"Failed to prepare query: " + UnicodeString(e.what(), e.what() + strlen(e.what())));
	}

	bool DataBaseConnection::executeQuery(const UnicodeString& query)
	{
		bool result{ false };
		try 
		{
			*getConnection() << StringToolBox::getUtf8(query);
			result = true;
		}
		catch (const sqlite::sqlite_exception& e) 
		{
			logQueryExecutionFailed(e);
		}
		return result;
	}

	void DataBaseConnection::cleanExecuteQuery(const UnicodeString& query)
	{
		begin();
		if (executeQuery(query))
		{
			commit();
			logQueryExecutionSuccess(query);
		}
		else
		{
			rollBack();
			logQueryExecutionFailed(query);
		}
	}

	int DataBaseConnection::getLastInsertedId()
	{
		return static_cast<int>(getConnection()->last_insert_rowid());
	}

	bool DataBaseConnection::begin()
	{
		bool result{ false };
		try 
		{
			*getConnection() << "BEGIN TRANSACTION";
			logMessage(L"Begin");
			result = true;
		}
		catch (const sqlite::sqlite_exception& e) 
		{
			logError(L"Failed to begin transaction: " + UnicodeString(e.what(), e.what() + strlen(e.what())));
		}
		return result;
	}

	bool DataBaseConnection::commit()
	{
		bool result{ false };
		try 
		{
			*getConnection() << "COMMIT";
			logMessage(L"Commit");
			result = true;
		}
		catch (const sqlite::sqlite_exception& e)
		{
			logError(L"Failed to commit transaction: " + UnicodeString(e.what(), e.what() + strlen(e.what())));
		}
		return result;
	}

	bool DataBaseConnection::rollBack()
	{
		bool result{ false };
		try 
		{
			*getConnection() << "ROLLBACK";
			logMessage(L"Rollback");
			result = true;
		}
		catch (const sqlite::sqlite_exception& e) 
		{
			logError(L"Failed to rollback transaction: " + UnicodeString(e.what(), e.what() + strlen(e.what())));
		}
		return result;
	}

	void DataBaseConnection::logQueryExecutionSuccess()
	{
		logMessage(L"Query executed successfully");
	}

	void DataBaseConnection::logQueryExecutionSuccess(const UnicodeString& query)
	{
		logMessage(L"Query executed successfully: " + query);
	}

	void DataBaseConnection::logQueryExecutionFailed(const sqlite::sqlite_exception& e)
	{
		logError(L"Query execution failed: " + UnicodeString(e.what(), e.what() + strlen(e.what())));
	}

	void DataBaseConnection::logQueryExecutionFailed(const UnicodeString& query)
	{
		logError(L"Query execution failed: " + query);
	}

#pragma endregion

}