#pragma once
#include "BaseObjectCTRL.h"
#include <vector>

namespace Alpha
{
	class Category;
	class CategoryCTRL :public BaseObjectCTRL
	{

	public:

#pragma region Constructors/Destructors

		CategoryCTRL();
		~CategoryCTRL();

#pragma endregion

#pragma region **** Heritage ****

	public:

	protected:
		virtual void updateQueryValues(const SharedPtr<BaseObject>& baseObject, sqlite::database_binder& statement) override;
		virtual void updateObjectValues(const SharedPtr<BaseObject>& baseObject, sqlite::database_binder& statement) override;

		virtual void updatePrimaryKeyValue(const SharedPtr<BaseObject>& baseObject, sqlite::database_binder& statement) override;

	private:

#pragma endregion

#pragma region **** Accessors ****

	public:

	protected:

	private:

#pragma endregion

#pragma region **** Methods ****

	public:
		void addCategory( const SharedPtr<Category>& category );
		void modifyCategory(const SharedPtr<Category>& category);
		void deleteCategory(const SharedPtr<Category>& category);

		SharedPtr<std::vector<SharedPtr<Category>>> loadColCategory()const;

	protected:

	private:

#pragma endregion

	private:

		class Private;
		Private* const d;
	};
}