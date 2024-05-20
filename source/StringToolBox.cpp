#include "stdafx.h"

#include <Windows.h>

#include "StringToolBox.h"

namespace Alpha
{
#pragma region Anonymous

	namespace
	{

	}

#pragma endregion

#pragma  region Private

	class StringToolBox::Private
	{
	public:

	};

#pragma endregion

#pragma region Constructors/Destructors

	StringToolBox::StringToolBox()
		:d(new Private())
	{

	}

	StringToolBox::~StringToolBox()
	{
		delete d;
	}
#pragma endregion

#pragma region **** Heritage ****

#pragma endregion

#pragma region **** Accessors ****

#pragma endregion

#pragma region **** Methods ****

	AlphaString StringToolBox::getUtf8(const UnicodeString& wideString)
	{
		int utf8Length = WideCharToMultiByte(CP_UTF8, 0, wideString.c_str(), -1, nullptr, 0, nullptr, nullptr);
		if (utf8Length == 0) {
			// Gestion de l'erreur de conversion
			return EmptyAlphaString;
		}
		AlphaString utf8String(utf8Length, '\0');
		WideCharToMultiByte(CP_UTF8, 0, wideString.c_str(), -1, &utf8String[0], utf8Length, nullptr, nullptr);
		return utf8String;
	}

	UnicodeString StringToolBox::getUnicodeString(const AlphaChar* charArray) {
		int length = static_cast<int>(strlen(charArray));
		int requiredLength = MultiByteToWideChar(CP_UTF8, 0, charArray, length, NULL, 0);
		if (requiredLength == 0) {
			// La conversion a échoué
			return EmptyUnicodeString;
		}

		UnicodeString wideString(requiredLength, L'\0');
		if (MultiByteToWideChar(CP_UTF8, 0, charArray, length, &wideString[0], requiredLength) == 0) {
			// La conversion a échoué
			return EmptyUnicodeString;
		}

		return wideString;
	}

	UnicodeString StringToolBox::getUnicodeString(const unsigned char* charArray)
	{
		int len = MultiByteToWideChar(CP_UTF8, 0, reinterpret_cast<LPCCH>(charArray), -1, NULL, 0);
		if (len == 0) {
			// Gestion de l'erreur si MultiByteToWideChar échoue
			DWORD dwError = GetLastError();
			switch (dwError)
			{
			case ERROR_INSUFFICIENT_BUFFER:
				logError(L"Code 122: Too small buffer to contain the converted string");
				break;
			case ERROR_INVALID_FLAGS:
				logError(L"Code 1004: Invalid indications passed to \'MultiByteToWideChar\'");
				break;
			case ERROR_INVALID_PARAMETER:
				logError(L"Code 87: One or several parameters passed to the function are invalids");
				break;
			case ERROR_NO_UNICODE_TRANSLATION:
				logError(L"Code 1113: String of characters can't be converted in Unicode");
				break;
			default:
				logError(L"Conversion error code: " + std::to_wstring(dwError));
				break;
			}
			return EmptyUnicodeString;
		}

		// Allouer un tampon pour stocker la chaîne de caractères large
		UnicodeChar* buffer = new UnicodeChar[len];

		// Convertir la chaîne de caractères UTF-8 en wchar_t
		MultiByteToWideChar(CP_UTF8, 0, reinterpret_cast<LPCCH>(charArray), -1, buffer, len);

		// Convertir wchar_t en std::wstring
		UnicodeString wstr(buffer);

		// Libérer la mémoire allouée
		delete[] buffer;

		return wstr;
	}

	UnicodeString StringToolBox::JoinUnicodeString(const SharedPtr<std::vector<UnicodeString>>& colUnicodeString, const UnicodeChar unicodeStringSeparator)
	{
		UnicodeString result = EmptyUnicodeString;
		const auto size = colUnicodeString->size();
		if (size > 0)
		{
			result = colUnicodeString->at(0);
			if (size > 1)
			{
				for (int index{ 1 }; index < size; ++index)
				{
					result += unicodeStringSeparator;
					result += colUnicodeString->at(index);
				}
			}
		}

		return result;
	}

#pragma endregion

}