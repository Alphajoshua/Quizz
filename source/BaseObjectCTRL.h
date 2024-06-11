#pragma once
#include "BaseObject.h"
#include "DataBaseConnection.h"

namespace Alpha
{
	class BaseObjectCTRL :public BaseObject
	{

	public:

#pragma region Constructors/Destructors

		BaseObjectCTRL();
		~BaseObjectCTRL();

#pragma endregion

#pragma region **** Heritage ****

	public:

	protected:

	private:

#pragma endregion

#pragma region **** Accessors ****

	public:
		SharedPtr<DataBaseConnection> getDataBaseConnection()const;
		void setDataBaseConnection(const SharedPtr<DataBaseConnection>& connection);

		UnicodeString getTableName()const;
		void setTableName(const UnicodeString& name);

		virtual SharedPtr<std::vector<UnicodeString>> getColColumn()const;
		virtual void setColColumn(const SharedPtr<std::vector<UnicodeString>>& colColumn)const;

	protected:

	private:

#pragma endregion

#pragma region **** Methods ****

	public:

	protected:
		virtual void updateQueryValues(const SharedPtr<BaseObject>& baseObject, sqlite::database_binder& statement) = 0;
		virtual void updateObjectValues(const SharedPtr<BaseObject>& baseObject, sqlite::database_binder& statement) = 0;

		bool addBaseObject(const SharedPtr<BaseObject>& baseObject);
		bool modifyBaseObject(const SharedPtr<BaseObject>& baseObject);
		bool removeBaseObject(const SharedPtr<BaseObject>& baseObject);

#pragma endregion

	private:

		class Private;
		Private* const d;
	};
}