#pragma once
#include "BaseObject.h"
#include "sqlite3.h"

namespace Alpha
{
	class DataBaseConnection :public BaseObject
	{

	public:

#pragma region Constructors/Destructors

		DataBaseConnection();
		~DataBaseConnection();

#pragma endregion

#pragma region **** Heritage ****

	public:

	protected:

	private:

#pragma endregion

#pragma region **** Accessors ****

	public:
		UnicodeString getDataBaseName()const;
		void setDataBaseName(const UnicodeString& name);

	protected:

	private:

#pragma endregion

#pragma region **** Methods ****

	public:
		bool connect();
		bool disconnect();

		void checkTables();
		void checkTableQuestion();
		void checkTableCategory();
		void checkTableLink();
		
		int prepareQuery(const UnicodeString& query, sqlite3_stmt** stmt);
		int executeQuery(const UnicodeString& query, AlphaChar* err_msg);
		void cleanExecuteQuery(int code, AlphaChar* err_msg);
		
		int getLastInsertedId();

		void finalizeStatement(sqlite3_stmt* stmt, const UnicodeString& tableName);
		void commit();
		void rollBack();

		void logQueryPreparationFailed();
	protected:

	private:
		UnicodeString getTableExistQuery(const UnicodeString& tableName);
		UnicodeString getTableInfoQuery(const UnicodeString& tableName);
#pragma endregion

	private:

		class Private;
		Private* const d;
	};
}