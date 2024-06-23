#include "stdafx.h"
#include "TextElement.h"

namespace Alpha
{
#pragma region Anonymous

	namespace
	{

	}

#pragma endregion

#pragma  region Private

	class TextElement::Private
	{
	public:
		bool nameHidden { true };
		UnicodeString name { EmptyUnicodeString };

		char* buffer;
		int bufferSize {DEFAULT_BUFFER_SIZE};
	};

#pragma endregion

#pragma region Constructors/Destructors

	TextElement::TextElement()
		:d(new Private())
	{

	}

	TextElement::~TextElement()
	{
		delete[] d->buffer;
		delete d;
	}
#pragma endregion

#pragma region **** Heritage ****

	bool TextElement::render()
	{
		bool result { false };

		const auto drawingZone = getStartingDrawingZone();
		setHorizontalCursor(drawingZone.x);
		setVerticalCursor(drawingZone.y);

		ImGui::SetNextItemWidth(getWidth());
		ImGui::InputText(getProcessedName().c_str(), d->buffer, IM_ARRAYSIZE(d->buffer), ImGuiInputTextFlags_None);

		return result;
	}


#pragma endregion

#pragma region **** Accessors ****

	AlphaString TextElement::getProcessedName() const
	{
		AlphaString processedName, name { StringToolBox::getUtf8(getName()) };
		processedName = isNameHidden() ? HIDDEN_PREFIX + name : name;
		return processedName;
	}

	bool TextElement::isNameHidden() const
	{
		return d->nameHidden;
	}
	void TextElement::setNameHidden(bool value /*=true*/)
	{
		d->nameHidden = value;
	}
	UnicodeString TextElement::getName() const
	{
		return d->name;
	}
	void TextElement::setName(const UnicodeString& name)
	{
		d->name = name;
	}
	float TextElement::getWidth() const
	{
		return getSizeDrawingZone().x;
	}
	void TextElement::setWidth(float value)
	{
		setSizeDrawingZone({ value , 0.0f });
	}
	int TextElement::getBufferSize() const
	{
		return d->bufferSize;
	}
	void TextElement::setBufferSize(int value)
	{
		d->bufferSize = value;
	}
	UnicodeString TextElement::getText()
	{
		auto str = EmptyUnicodeString;
		mapBufferToString(str);
		return str;
	}
	void TextElement::setText(const UnicodeString& text)
	{
		mapStringToBuffer(text);
	}
#pragma endregion

#pragma region **** Methods ****

	void TextElement::init()
	{
		d->buffer = new char[getBufferSize()];
		resetBuffer();
	}

	void TextElement::mapBufferToString(const SharedPtr<UnicodeString>& text)
	{
		*text = StringToolBox::getUnicodeString(d->buffer);
	}

	void TextElement::mapBufferToString( UnicodeString& text)
	{
		text = StringToolBox::getUnicodeString(d->buffer);
	}

	void TextElement::mapStringToBuffer(const SharedPtr<UnicodeString>& text)
	{
		strcpy_s(d->buffer, getBufferSize(), StringToolBox::getUtf8(*text).c_str());
	}

	void TextElement::mapStringToBuffer(const UnicodeString& text)
	{
		strcpy_s(d->buffer, getBufferSize(), StringToolBox::getUtf8(text).c_str());
	}

	void TextElement::resetBuffer()
	{
		strcpy_s(d->buffer, getBufferSize(), EmptyAlphaString.c_str());
	}

#pragma endregion

}