#include "stdafx.h"
#include "Question.h"

namespace Alpha
{
#pragma region Anonymous

	namespace
	{

	}

#pragma endregion

#pragma  region Private

	class Question::Private
	{
	public:
		int id{ DEFAULT_ID };
		UnicodeString questionText{ DEFAULT_QUESTION_TEXT }, rightAnswer{ DEFAULT_RIGHT_ANSWER }, dummyAnswer{ DEFAULT_DUMMY_ANSWER };
		UnicodeString wrongAnswer1{ DEFAULT_WRONG_ANSWER_1 }, wrongAnswer2{ DEFAULT_WRONG_ANSWER_2 }, wrongAnswer3{ DEFAULT_WRONG_ANSWER_3 };
		UnicodeString wrongAnswer4{ DEFAULT_WRONG_ANSWER_4 }, wrongAnswer5{ DEFAULT_WRONG_ANSWER_5 };
		Difficulty difficulty{ Difficulty::Easy };

		//TODO:: categories
	};

#pragma endregion

#pragma region Constructors/Destructors

	Question::Question()
		:d(new Private())
	{
	}

	Question::~Question()
	{
		delete d;
	}
#pragma endregion

#pragma region **** Heritage ****

#pragma endregion

#pragma region **** Accessors ****

	UnicodeString Question::getQuestionText() const
	{
		return d->questionText;
	}

	void Question::setQuestionText(const UnicodeString& questionText)
	{
		d->questionText = questionText;
	}

	UnicodeString Question::getRightAnswerText() const
	{
		return d->rightAnswer;
	}

	void Question::setRightAnswerText(const UnicodeString& answerText)
	{
		d->rightAnswer = answerText;
	}

	UnicodeString Question::getDummyAnswerText() const
	{
		return d->dummyAnswer;
	}

	void Question::setDummyAnswerText(const UnicodeString& answerText)
	{
		d->dummyAnswer = answerText;
	}

	UnicodeString Question::getWrongAnswerText1() const
	{
		return d->wrongAnswer1;
	}

	void Question::setWrongAnswerText1(const UnicodeString& answerText)
	{
		d->wrongAnswer1 = answerText;
	}

	UnicodeString Question::getWrongAnswerText2() const
	{
		return d->wrongAnswer2;
	}

	void Question::setWrongAnswerText2(const UnicodeString& answerText)
	{
		d->wrongAnswer2 = answerText;
	}

	UnicodeString Question::getWrongAnswerText3() const
	{
		return d->wrongAnswer3;
	}

	void Question::setWrongAnswerText3(const UnicodeString& answerText)
	{
		d->wrongAnswer3 = answerText;
	}

	UnicodeString Question::getWrongAnswerText4() const
	{
		return d->wrongAnswer4;
	}

	void Question::setWrongAnswerText4(const UnicodeString& answerText)
	{
		d->wrongAnswer4 = answerText;
	}

	UnicodeString Question::getWrongAnswerText5() const
	{
		return d->wrongAnswer5;
	}

	void Question::setWrongAnswerText5(const UnicodeString& answerText)
	{
		d->wrongAnswer5 = answerText;
	}

	Difficulty Question::getDifficulty() const
	{
		return d->difficulty;
	}

	void Question::setDifficulty(Difficulty value)
	{
		d->difficulty = value;
	}

#pragma endregion

#pragma region **** Methods ****

#pragma endregion


}