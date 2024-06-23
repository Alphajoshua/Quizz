#pragma once
#include "Widget.h"

namespace Alpha
{
	class TextElement:public Widget
	{

	public:

#pragma region Constructors/Destructors

		TextElement();
		~TextElement();

#pragma endregion

#pragma region **** Heritage ****

	public:
		virtual bool render() override;

	protected:

	private:

#pragma endregion

#pragma region **** Accessors ****

	public:
		AlphaString getProcessedName()const;

		bool isNameHidden()const;
		void setNameHidden(bool value = true);

		UnicodeString getName()const;
		void setName(const UnicodeString& name);

		float getWidth()const;
		void setWidth(float value);

		int getBufferSize()const;
		void setBufferSize(int value);

		UnicodeString getText();
		void setText(const UnicodeString& text);

	protected:

	private:

#pragma endregion

#pragma region **** Methods ****

	public:
		void init();
		void mapBufferToString(const SharedPtr<UnicodeString>& text);
		void mapBufferToString( UnicodeString& text);
		void mapStringToBuffer(const SharedPtr<UnicodeString>& text);
		void mapStringToBuffer(const UnicodeString& text);
		void resetBuffer();

	protected:

	private:

#pragma endregion

	private:

		class Private;
		Private* const d;
	};
}