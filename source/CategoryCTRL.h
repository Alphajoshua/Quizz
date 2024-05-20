#pragma once
#include "BaseObjectCTRL.h"

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
		virtual void updateQueryValues(const SharedPtr<BaseObject>& baseObject, sqlite3_stmt** stmt) override;
		virtual void updateObjectValues(const SharedPtr<BaseObject>& baseObject, sqlite3_stmt** stmt) override;

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
		void removeCategory(const SharedPtr<Category>& category);

	protected:

	private:

#pragma endregion

	private:

		class Private;
		Private* const d;
	};
}