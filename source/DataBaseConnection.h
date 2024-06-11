#pragma once
#include "BaseObject.h"
#include "sqlite_modern_cpp.h"

namespace Alpha
{
	class DataBaseConnection :public BaseObject
	{

	public:

#pragma region Constructors/Destructors

		DataBaseConnection();
		DataBaseConnection( const UnicodeString& name );
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

		SharedPtr<sqlite::database> getConnection()const;
		void setConnection(const SharedPtr<sqlite::database>& object);

		bool connect();
		bool disconnect();

		void checkTable(const UnicodeString& tableName, const UnicodeString& columnsDefinition);
		void checkTables();
		void checkTableQuestion();
		void checkTableCategory();
		void checkTableLink();

		bool executeQuery(const UnicodeString& query);
		void cleanExecuteQuery(const UnicodeString& query);
		
		int getLastInsertedId();

		bool begin();
		bool commit();
		bool rollBack();

		void logQueryExecutionSuccess();
		void logQueryExecutionSuccess(const UnicodeString& query);
		void logQueryExecutionFailed(const sqlite::sqlite_exception& e);
		void logQueryExecutionFailed(const UnicodeString& query);
		void logQueryPreparationFailed(const sqlite::sqlite_exception& e);
	protected:

	private:
		bool isTableExist(const SharedPtr<sqlite::database>& connection, const UnicodeString& tableName);
		UnicodeString getTableExistQuery(const UnicodeString& tableName)const ;
		UnicodeString getTableInfoQuery(const UnicodeString& tableName)const ;
#pragma endregion

	private:

		class Private;
		Private* const d;
	};
}