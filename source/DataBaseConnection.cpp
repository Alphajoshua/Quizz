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
		sqlite3* connection;
	};

#pragma endregion

#pragma region Constructors/Destructors

	DataBaseConnection::DataBaseConnection()
		:d(new Private())
	{

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

	bool DataBaseConnection::connect()
	{
		bool result{ false };
		auto path = std::filesystem::current_path() / SOFTWARE_DIRECTORY / getDataBaseName();
		auto message = StringToolBox::getUnicodeString(( path.string()).c_str() );
		int code = sqlite3_open(StringToolBox::getUtf8(path).c_str(), &d->connection);

		if (code == SQLITE_ERROR || code == SQLITE_CANTOPEN )
			logError(L"Failed connection to db: " + message + L" " + StringToolBox::getUnicodeString(sqlite3_errmsg(d->connection)));
		else if( code == SQLITE_OK )
		{
			result = true;
			logMessage(L"Succes connection to db: " + message);
		}
		return result;
	}

	bool DataBaseConnection::disconnect()
	{
		int code = sqlite3_close(d->connection);
		bool result = { false };
		auto path = std::filesystem::current_path() / SOFTWARE_DIRECTORY / getDataBaseName();
		auto message = StringToolBox::getUnicodeString((path.string()).c_str());

		if (code == SQLITE_ERROR || code == SQLITE_CANTOPEN)
			logError(L"Failed disconnection to db: " + message + L" " + StringToolBox::getUnicodeString(sqlite3_errmsg(d->connection)));
		else if (code == SQLITE_OK)
		{
			result = true;
			logMessage(L"Succes disconnection to db: " + message);
		}
		return result;
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
		const UnicodeString tableName = L"QUESTION";

		// Vérifier l'existence de la table
		UnicodeString query = getTableExistQuery(tableName);
		sqlite3_stmt* stmt;
		int code = prepareQuery(query, &stmt);
		if (code != SQLITE_OK)
			logQueryPreparationFailed();
		else if (const auto stmtCode = sqlite3_step(stmt); stmtCode == SQLITE_ROW)
		{
			logSeparator();
			logMessage(L"TABLE " + tableName + L" exist");

			// Obtenir la composition de la table
			query = getTableInfoQuery(tableName);
			code = prepareQuery(query, &stmt);
			if (code != SQLITE_OK)
				logQueryPreparationFailed();

			while (sqlite3_step(stmt) == SQLITE_ROW)
				logMessage(L"ColumnName: " + StringToolBox::getUnicodeString(sqlite3_column_text(stmt, 1)) + L", Type : " + StringToolBox::getUnicodeString(sqlite3_column_text(stmt, 2)));

			finalizeStatement(stmt, tableName);
		}
		else if (stmtCode == SQLITE_DONE)
		{
			UnicodeString create_table_query = L"CREATE TABLE IF NOT EXISTS " + tableName;
			create_table_query += L" ( ID INTEGER PRIMARY KEY AUTOINCREMENT,QUESTION_TITLE TEXT NOT NULL, RIGHT_ANSWER TEXT NOT NULL,"
			"DUMMY_ANSWER TEXT NOT NULL, WRONG_ANSWER_1 TEXT NOT NULL, WRONG_ANSWER_2 TEXT NOT NULL, WRONG_ANSWER_3 TEXT NOT NULL, WRONG_ANSWER_4 TEXT NOT NULL, WRONG_ANSWER_5 TEXT NOT NULL);";
			AlphaChar* err_msg = nullptr;
			code = executeQuery(create_table_query, err_msg);
			cleanExecuteQuery(code, err_msg);
			sqlite3_free(err_msg);
		}
	}

	void DataBaseConnection::checkTableCategory()
	{
		const UnicodeString tableName = L"CATEGORY";

		// Vérifier l'existence de la table
		UnicodeString query = getTableExistQuery(tableName);
		sqlite3_stmt* stmt;
		int code = prepareQuery(query, &stmt);
		if (code != SQLITE_OK)
			logQueryPreparationFailed();
		else if (const auto stmtCode = sqlite3_step(stmt); stmtCode == SQLITE_ROW)
		{
			logSeparator();
			logMessage(L"TABLE " + tableName + L" exist");

			// Obtenir la composition de la table
			query = getTableInfoQuery(tableName);
			code = prepareQuery(query, &stmt);
			if (code != SQLITE_OK)
				logQueryPreparationFailed();

			while (sqlite3_step(stmt) == SQLITE_ROW)
				logMessage(L"ColumnName: " + StringToolBox::getUnicodeString(sqlite3_column_text(stmt, 1)) + L", Type : " + StringToolBox::getUnicodeString(sqlite3_column_text(stmt, 2)));

			finalizeStatement(stmt, tableName);
		}
		else if (stmtCode == SQLITE_DONE)
		{
			UnicodeString create_table_query = L"CREATE TABLE IF NOT EXISTS " + tableName;
			create_table_query += L" ( ID INTEGER PRIMARY KEY AUTOINCREMENT,NAME TEXT NOT NULL);";
			AlphaChar* err_msg = nullptr;
			code = executeQuery(create_table_query, err_msg);
			cleanExecuteQuery(code, err_msg);
			sqlite3_free(err_msg);
		}
	}

	void DataBaseConnection::checkTableLink()
	{
		const UnicodeString tableName = L"LINK";

		// Vérifier l'existence de la table
		UnicodeString query = getTableExistQuery(tableName);
		sqlite3_stmt* stmt;
		int code = prepareQuery(query, &stmt);
		if (code != SQLITE_OK)
			logQueryPreparationFailed();
		else if (const auto stmtCode = sqlite3_step(stmt); stmtCode == SQLITE_ROW)
		{
			logSeparator();
			logMessage(L"TABLE " + tableName + L" exist");

			// Obtenir la composition de la table
			query = L"PRAGMA table_info(" + tableName + L");";
			code = prepareQuery(query, &stmt);
			if (code != SQLITE_OK)
				logQueryPreparationFailed();

			while (sqlite3_step(stmt) == SQLITE_ROW)
				logMessage(L"ColumnName: " + StringToolBox::getUnicodeString(sqlite3_column_text(stmt, 1)) + L", Type : " + StringToolBox::getUnicodeString(sqlite3_column_text(stmt, 2)));

			finalizeStatement(stmt, tableName);
		}
		else if (stmtCode == SQLITE_DONE)
		{
			UnicodeString create_table_query = L"CREATE TABLE IF NOT EXISTS " + tableName;
			create_table_query += L" ( ID INTEGER PRIMARY KEY AUTOINCREMENT,QUESTION_ID INTEGER NOT NULL, CATEGORY_ID INTEGER NOT NULL);";
			AlphaChar* err_msg = nullptr;
			code = executeQuery(create_table_query, err_msg);
			cleanExecuteQuery(code, err_msg);
			sqlite3_free(err_msg);
		}
	}

	void DataBaseConnection::logQueryPreparationFailed()
	{
		logError(L"Query preparation : " + StringToolBox::getUnicodeString(sqlite3_errmsg(d->connection)));
	}

	UnicodeString DataBaseConnection::getTableExistQuery(const UnicodeString& tableName)
	{
		return L"SELECT name FROM sqlite_master WHERE type='table' AND name='" + tableName + L"';";
	}

	UnicodeString DataBaseConnection::getTableInfoQuery(const UnicodeString& tableName)
	{
		return L"PRAGMA table_info(" + tableName + L");";
	}

	int DataBaseConnection::prepareQuery(const UnicodeString& query, sqlite3_stmt** stmt)
	{
		return sqlite3_prepare_v2(d->connection, StringToolBox::getUtf8(query).c_str(), -1, stmt, NULL);;
	}

	int DataBaseConnection::executeQuery(const UnicodeString& query, AlphaChar* err_msg)
	{
		logMessage(L"Execute query: " + query);
		return sqlite3_exec(d->connection, StringToolBox::getUtf8(query).c_str(), nullptr, nullptr, &err_msg);
	}

	void DataBaseConnection::cleanExecuteQuery(int code, AlphaChar* err_msg)
	{
		if (code != SQLITE_OK)
		{
			rollBack();
			logError(StringToolBox::getUnicodeString(err_msg));
		}
		else
		{
			commit();
			logMessage(L"Succes table creation");
		}
	}

	int DataBaseConnection::getLastInsertedId()
	{
		return static_cast<int>(sqlite3_last_insert_rowid(d->connection));
	}

	void DataBaseConnection::finalizeStatement(sqlite3_stmt* stmt, const UnicodeString& tableName)
	{
		if (sqlite3_finalize(stmt) != SQLITE_OK)
			logError(L"Finalization failed :" + tableName);
	}

	void DataBaseConnection::commit()
	{
		sqlite3_exec(d->connection, StringToolBox::getUtf8(COMMIT).c_str(), nullptr, nullptr, nullptr);
	}

	void DataBaseConnection::rollBack()
	{
		sqlite3_exec(d->connection, StringToolBox::getUtf8(ROLLBACK).c_str(), nullptr, nullptr, nullptr);
	}

#pragma endregion

}