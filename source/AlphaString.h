#pragma once

#include <string>
#include <vector>

namespace Alpha
{
	using AlphaChar = char;
	using UnicodeChar = wchar_t;

	using AlphaString = std::string;
	using UnicodeString = std::wstring;
	using AlphaBuffer = AlphaChar **;

	const AlphaString EmptyAlphaString{ "" };
	const UnicodeString EmptyUnicodeString{ L"" };

	const AlphaChar DEFAULT_ALPHASTRING_SEPARATOR{ ',' };
	const UnicodeChar DEFAULT_UNICODESTRING_SEPARATOR{ L',' };
	

	using AlphaStringArray = std::vector<AlphaString>;
	using UnicodeStringArray = std::vector<UnicodeString>;

	/*AlphaStringArray SplitString(const AlphaString& str, const AlphaChar& separator = DEFAULT_ALPHASTRING_SEPARATOR)
	{
		AlphaStringArray result;
		AlphaString::size_type start = 0;
		AlphaString::size_type end = str.find(separator);

		while (end != AlphaString::npos)
		{
			result.push_back(str.substr(start, end - start));
			start = end + 1;
			end = str.find(separator, start);
		}

		result.push_back(str.substr(start));

		return result;
	}
	AlphaString JoinString(const AlphaStringArray& arr, const AlphaChar& separator = DEFAULT_ALPHASTRING_SEPARATOR)
	{
		AlphaString result{ EmptyAlphaString };

		for (int index{ 0 }; index < arr.size(); ++index)
		{
			result += arr[index];
			if (index < arr.size())
				result += separator;
		}
		return result;
	}
	UnicodeStringArray SplitString(const UnicodeString& str, const UnicodeChar& separator = DEFAULT_UNICODESTRING_SEPARATOR)
	{
		UnicodeStringArray result;
		UnicodeString::size_type start = 0;
		UnicodeString::size_type end = str.find(separator);

		while (end != UnicodeString::npos)
		{
			result.push_back(str.substr(start, end - start));
			start = end + 1;
			end = str.find(separator, start);
		}

		result.push_back(str.substr(start));

		return result;
	}
	UnicodeString JoinString(const UnicodeStringArray& arr, const UnicodeChar& separator = DEFAULT_UNICODESTRING_SEPARATOR)
	{
		UnicodeString result{ EmptyUnicodeString };

		for (int index{ 0 }; index < arr.size(); ++index)
		{
			result += arr[index];
			if (index < arr.size())
				result += separator;
		}
		return result;
	}*/
}