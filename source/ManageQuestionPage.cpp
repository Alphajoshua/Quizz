#include "stdafx.h"
#include "ManageQuestionPage.h"

#include "Category.h"
#include "Question.h"

namespace Alpha
{
#pragma region Anonymous

	namespace
	{

	}

#pragma endregion

#pragma  region Private

	class ManageQuestionPage::Private
	{
	public:
		char questionTextBuffer[4000], rightAnswerTextBuffer[4000], dummyAnswerTextBuffer[4000];
		char wrongAnswer1TextBuffer[4000], wrongAnswer2TextBuffer[4000], wrongAnswer3TextBuffer[4000];
		char wrongAnswer4TextBuffer[4000], wrongAnswer5TextBuffer[4000];
		
		Difficulty difficulty{ Difficulty::Easy };

		SharedPtr<std::vector<SharedPtr<Category>>> colCategory{ refNew<std::vector<SharedPtr<Category>>>() };
		SharedPtr<std::vector<SharedPtr<Question>>> colQuestion{ refNew<std::vector<SharedPtr<Question>>>() };

		int indexSelectedCategory, indexSelectedQuestion;
		WeakPtr<Category> selectedCategory;
		WeakPtr<Question> selectedQuestion;
	};

#pragma endregion

#pragma region Constructors/Destructors

	ManageQuestionPage::ManageQuestionPage()
		:d(new Private())
	{

	}

	ManageQuestionPage::~ManageQuestionPage()
	{
		delete d;
	}

#pragma endregion

#pragma region **** Heritage ****

	void ManageQuestionPage::init()
	{
		setBackGroundColor({ 0.18f, 0.32f, 0.62f, 1.0f });

		setInitialized(true);
	}

	bool ManageQuestionPage::render()
	{
		Page::render();
		const auto colCategory = getColCategory();
		const auto colQuestion = getColQuestion();

		const auto startingDrawingZone = getStartingDrawingZone();
		const auto sizeDrawingZone = getSizeDrawingZone();

		setHorizontalCursor(startingDrawingZone.x + 10);
		setVerticalCursor(startingDrawingZone.y + 10);

		ImGui::SetNextItemWidth(200);
		ImGui::InputText( StringToolBox::getUtf8( DEFAULT_QUESTION_TEXT ).c_str(),		d->questionTextBuffer, IM_ARRAYSIZE(d->questionTextBuffer));
		
		setHorizontalCursor(startingDrawingZone.x + 10);
		ImGui::SetNextItemWidth(200);
		ImGui::InputText( StringToolBox::getUtf8( DEFAULT_RIGHT_ANSWER ).c_str(),		d->rightAnswerTextBuffer, IM_ARRAYSIZE(d->rightAnswerTextBuffer));

		setHorizontalCursor(startingDrawingZone.x + 10);
		ImGui::SetNextItemWidth(200);
		ImGui::InputText( StringToolBox::getUtf8( DEFAULT_DUMMY_ANSWER ).c_str(),		d->dummyAnswerTextBuffer, IM_ARRAYSIZE(d->dummyAnswerTextBuffer));

		setHorizontalCursor(startingDrawingZone.x + 10);
		ImGui::SetNextItemWidth(200);
		ImGui::InputText( StringToolBox::getUtf8( DEFAULT_WRONG_ANSWER_1 ).c_str(),	d->wrongAnswer1TextBuffer, IM_ARRAYSIZE(d->wrongAnswer1TextBuffer));

		setHorizontalCursor(startingDrawingZone.x + 10);
		ImGui::SetNextItemWidth(200);
		ImGui::InputText(StringToolBox::getUtf8( DEFAULT_WRONG_ANSWER_2 ).c_str(),	d->wrongAnswer2TextBuffer, IM_ARRAYSIZE(d->wrongAnswer2TextBuffer));
		
		setHorizontalCursor(startingDrawingZone.x + 10);
		ImGui::SetNextItemWidth(200);
		ImGui::InputText(StringToolBox::getUtf8( DEFAULT_WRONG_ANSWER_3 ).c_str(),	d->wrongAnswer3TextBuffer, IM_ARRAYSIZE(d->wrongAnswer3TextBuffer));
		
		setHorizontalCursor(startingDrawingZone.x + 10);
		ImGui::SetNextItemWidth(200);
		ImGui::InputText(StringToolBox::getUtf8( DEFAULT_WRONG_ANSWER_4 ).c_str(),	d->wrongAnswer4TextBuffer, IM_ARRAYSIZE(d->wrongAnswer4TextBuffer));
		
		setHorizontalCursor(startingDrawingZone.x + 10);
		ImGui::SetNextItemWidth(200);
		ImGui::InputText( StringToolBox::getUtf8( DEFAULT_WRONG_ANSWER_5 ).c_str(),	d->wrongAnswer5TextBuffer, IM_ARRAYSIZE(d->wrongAnswer5TextBuffer));

		setHorizontalCursor(startingDrawingZone.x + 10);
		ImVec2 listBoxDrawableZone = { sizeDrawingZone.x - 20.0f, sizeDrawingZone.y / 2.0f };

		increaseVerticalDrawingCursor(10);
		if (ImGui::BeginListBox("##Liste", listBoxDrawableZone)) {
			for (int index{ 0 }; index < colQuestion->size(); ++index) {
				bool isSelected = (d->indexSelectedQuestion == index);
				if (ImGui::Selectable(StringToolBox::getUtf8( colQuestion->at(index)->getQuestionText() ).c_str(), isSelected)) {
					d->indexSelectedQuestion = index;
					setSelectedQuestion(colQuestion->at(index));
				}
			}
			ImGui::EndListBox();
		}

		return false;
	}


#pragma endregion

#pragma region **** Accessors ****

	SharedPtr<std::vector<SharedPtr<Category>>> ManageQuestionPage::getColCategory() const
	{
		return d->colCategory;
	}

	void ManageQuestionPage::setColCategory(const SharedPtr<std::vector<SharedPtr<Category>>>& colCategory)
	{
		d->colCategory = colCategory;
	}

	SharedPtr<std::vector<SharedPtr<Question>>> ManageQuestionPage::getColQuestion() const
	{
		return d->colQuestion;
	}

	void ManageQuestionPage::setColQuestion(const SharedPtr<std::vector<SharedPtr<Question>>>& colQuestion)
	{
		d->colQuestion = colQuestion;
	}

	SharedPtr<Category> ManageQuestionPage::getSelectedCategory() const
	{
		return d->selectedCategory.lock();
	}

	void ManageQuestionPage::setSelectedCategory(const SharedPtr<Category>& selectedCategory)
	{
		d->selectedCategory = selectedCategory;
	}

	SharedPtr<Question> ManageQuestionPage::getSelectedQuestion() const
	{
		return d->selectedQuestion.lock();
	}

	void ManageQuestionPage::setSelectedQuestion(const SharedPtr<Question>& selectedQuestion)
	{
		d->selectedQuestion = selectedQuestion;
		strcpy_s(d->questionTextBuffer,     StringToolBox::getUtf8( selectedQuestion->getQuestionText()     ).c_str() );
		strcpy_s(d->rightAnswerTextBuffer,  StringToolBox::getUtf8( selectedQuestion->getRightAnswerText()  ).c_str() );
		strcpy_s(d->dummyAnswerTextBuffer,  StringToolBox::getUtf8( selectedQuestion->getDummyAnswerText()  ).c_str() );
		strcpy_s(d->wrongAnswer1TextBuffer, StringToolBox::getUtf8( selectedQuestion->getWrongAnswerText1() ).c_str() );
		strcpy_s(d->wrongAnswer2TextBuffer, StringToolBox::getUtf8( selectedQuestion->getWrongAnswerText2() ).c_str() );
		strcpy_s(d->wrongAnswer3TextBuffer, StringToolBox::getUtf8( selectedQuestion->getWrongAnswerText3() ).c_str() );
		strcpy_s(d->wrongAnswer4TextBuffer, StringToolBox::getUtf8( selectedQuestion->getWrongAnswerText4() ).c_str() );
		strcpy_s(d->wrongAnswer5TextBuffer, StringToolBox::getUtf8( selectedQuestion->getWrongAnswerText5() ).c_str() );
	}

#pragma endregion

#pragma region **** Methods ****

#pragma endregion

}