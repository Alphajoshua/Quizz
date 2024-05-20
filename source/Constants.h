#pragma once

#include "AlphaString.h"
#include "ImGui.h"

namespace Alpha
{

#pragma region *** Enums ***

	enum class Difficulty
	{
		Easy = 10,
		Intermediate = 20,
		Hard = 50
	};

#pragma endregion

#pragma region *** DEFAULT MODEL VALUES

	const int DEFAULT_ID{ 0 };
	const int DEFAULT_INT{ 0 };
	const int DEFAULT_X_COORDINATE{ 0 };
	const int DEFAULT_Y_COORDINATE{ 0 };

#pragma endregion

#pragma region *** QUESTIONS DEFAULT TEXT ***

	const UnicodeString DEFAULT_QUESTION_TEXT{ L"Énoncé de la question" };
	const UnicodeString DEFAULT_RIGHT_ANSWER{ L"Réponse juste" };
	const UnicodeString DEFAULT_DUMMY_ANSWER{ L"Réponse stupide" };
	const UnicodeString DEFAULT_WRONG_ANSWER_1{ L"Réponse fausse 1" };
	const UnicodeString DEFAULT_WRONG_ANSWER_2{ L"Réponse fausse 2" };
	const UnicodeString DEFAULT_WRONG_ANSWER_3{ L"Réponse fausse 3" };
	const UnicodeString DEFAULT_WRONG_ANSWER_4{ L"Réponse fausse 4" };
	const UnicodeString DEFAULT_WRONG_ANSWER_5{ L"Réponse fausse 5" };

#pragma endregion

#pragma region *** COLORS ***

	const ImVec4 FULL_RED{ 1.0f,0.0f,0.0f,1.0f };
	const ImVec4 FULL_GREEN{ 0.0f,1.0f,0.0f,1.0f };
	const ImVec4 FULL_BLUE{ 0.0f,0.0f,1.0f,1.0f };

	const ImVec4 FULL_WHITE{ 1.0f,1.0f,1.0f,1.0f };
	const ImVec4 FULL_BLACK{ 0.0f,0.0f,0.0f,1.0f };

#pragma endregion

#pragma region ***PATH***

	const UnicodeString SOFTWARE_DIRECTORY{ L"AlphaSoftware" };
	const UnicodeString DEFAULT_DB_CONNECTION{ L"culture" };

#pragma endregion

#pragma region ***STRING***

	const UnicodeString LOG_SEPARATOR{ L"#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#" };
	const UnicodeChar STRING_SEPARATOR{ L',' };

#pragma endregion

#pragma region *** DATABASE ***

	const UnicodeString COMMIT{ L"COMMIT;" };
	const UnicodeString ROLLBACK{ L"ROLLBACK;" };

#pragma endregion
}