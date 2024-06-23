#pragma once
#include "Page.h"

namespace Alpha
{
	class Category;
	class CategoryCTRL;
	class ManageCategoryPage :public Page
	{

	public:

#pragma region Constructors/Destructors

		ManageCategoryPage();
		~ManageCategoryPage();

#pragma endregion

#pragma region **** Heritage ****

	public:

		virtual void init() override;

		virtual bool render() override;

	protected:

	private:

#pragma endregion

#pragma region **** Accessors ****

	public:
		SharedPtr<std::vector<SharedPtr<Category>>> getColCategory()const;
		void setColCategory(const SharedPtr<std::vector<SharedPtr<Category>>>& col);

		int getIndexSelectedCategory()const;
		void setIndexSelectedCategory(int value);

		SharedPtr<Category> getSelectedCategory()const;
		void setSelectedCategory(const SharedPtr<Category>& category);

		SharedPtr<CategoryCTRL> getCategoryCTRL()const;
		void setCategoryCTRL(const SharedPtr<CategoryCTRL>& categoryCTRL);

	protected:

	private:

#pragma endregion

#pragma region **** Methods ****

	public:

	protected:

	private:
		bool isNameAlreadyUsed( const SharedPtr<std::vector<SharedPtr<Category>>>& colCategory, const UnicodeString& name);
		bool isNameAlreadyUsed( const SharedPtr<std::vector<SharedPtr<Category>>>& colCategory, const SharedPtr<UnicodeString>& name);

#pragma endregion

	private:

		class Private;
		Private* const d;
	};
}