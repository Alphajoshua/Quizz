#pragma once
#include "BaseObject.h"

namespace Alpha
{
	class StringToolBox :public BaseObject
	{

	public:

#pragma region Constructors/Destructors

		StringToolBox();
		~StringToolBox();

#pragma endregion

#pragma region **** Heritage ****

	public:

	protected:

	private:

#pragma endregion

#pragma region **** Accessors ****

	public:

	protected:

	private:

#pragma endregion

#pragma region **** Methods ****

	public:
		static AlphaString getUtf8(const SharedPtr<UnicodeString>& wideString);
		static AlphaString getUtf8(const UnicodeString& wideString);
		static UnicodeString getUnicodeString(const AlphaString str);
		static UnicodeString getUnicodeString(const AlphaChar* charArray);
		static UnicodeString getUnicodeString(const unsigned char* charArray);
		static UnicodeString JoinUnicodeString(const SharedPtr<std::vector<UnicodeString>>& colUnicodeString, const UnicodeChar unicodeStringSeparator = STRING_SEPARATOR);
	protected:

	private:

#pragma endregion

	private:

		class Private;
		Private* const d;
	};
}