#pragma once

#include "BaseObject.h"

namespace Alpha
{
	class Question : public BaseObject
	{

	public:

#pragma region Constructors/Destructors

		Question();
		~Question();

#pragma endregion

#pragma region **** Heritage ****

	public:

	protected:

	private:

#pragma endregion

#pragma region **** Accessors ****

	public:

		UnicodeString getQuestionText()const;
		void setQuestionText(const UnicodeString& questionText);

		UnicodeString getRightAnswerText()const;
		void setRightAnswerText(const UnicodeString& answerText);
		
		UnicodeString getDummyAnswerText()const;
		void setDummyAnswerText(const UnicodeString& answerText);
		
		UnicodeString getWrongAnswerText1()const;
		void setWrongAnswerText1(const UnicodeString& answerText);
		
		UnicodeString getWrongAnswerText2()const;
		void setWrongAnswerText2(const UnicodeString& answerText);
		
		UnicodeString getWrongAnswerText3()const;
		void setWrongAnswerText3(const UnicodeString& answerText);
		
		UnicodeString getWrongAnswerText4()const;
		void setWrongAnswerText4(const UnicodeString& answerText);
		
		UnicodeString getWrongAnswerText5()const;
		void setWrongAnswerText5(const UnicodeString& answerText);

		Difficulty getDifficulty()const;
		void setDifficulty(Difficulty value);

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