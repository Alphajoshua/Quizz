#pragma once
#include "Page.h"

namespace Alpha
{
	class Category;
	class Question;
	class ManageQuestionPage :public Page
	{

	public:

#pragma region Constructors/Destructors

		ManageQuestionPage();
		~ManageQuestionPage();

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
		void setColCategory(const SharedPtr<std::vector<SharedPtr<Category>>>& colCategory);

		SharedPtr<std::vector<SharedPtr<Question>>> getColQuestion()const;
		void setColQuestion(const SharedPtr<std::vector<SharedPtr<Question>>>& colQuestion);

		SharedPtr<Category> getSelectedCategory()const;
		void setSelectedCategory(const SharedPtr<Category>& selectedCategory);

		SharedPtr<Question> getSelectedQuestion()const;
		void setSelectedQuestion(const SharedPtr<Question>& selectedQuestion);

	protected:

	private:

#pragma endregion

#pragma region **** Methods ****

	public:

	protected:

	private:

#pragma endregion

	private:

		class Private;
		Private* const d;
	};
}