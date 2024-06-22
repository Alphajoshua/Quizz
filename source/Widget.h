#pragma once
#include "BaseObject.h"

namespace Alpha
{
	class Widget : public BaseObject
	{

	public:

#pragma region Constructors/Destructors

		Widget();
		~Widget();

#pragma endregion

#pragma region **** Heritage ****

	public:

	protected:

	private:

#pragma endregion

#pragma region **** Accessors ****

	public:

		ImVec2 getStartingDrawingZone()const;
		void setStartingDrawingZone(const ImVec2& zone);

		ImVec2 getSizeDrawingZone()const;
		void setSizeDrawingZone(const ImVec2& zone);

		ImVec2 getEndingDrawingZone()const;

		ImVec4 getBackgroundColor()const;
		void setBackGroundColor(const ImVec4& color);

		ImVec2 getDrawingCursor()const;
		void setDrawingCursor( const ImVec2& cursor);

		float getHorizontalCursor()const;
		void setHorizontalCursor(const float& position);

		float getVerticalCursor()const;
		void setVerticalCursor(const float& position);

		int getHorizontalPadding()const;
		void setHorizontalPadding(int padding);

		int getVerticalPadding()const;
		void setVerticalPadding(int padding);

		bool isEnabled()const;
		void setEnabled(bool value);

	protected:

	private:

#pragma endregion

#pragma region **** Methods ****

	public:
		virtual bool render();

		void increaseDrawingCursor(float value);
		void decreaseDrawingCursor(float value);
		void increaseHorizontalDrawingCursor(float value);
		void decreaseHorizontalDrawingCursor(float value);
		void increaseVerticalDrawingCursor(float value);
		void decreaseVerticalDrawingCursor(float value);

		void upper(const SharedPtr<Widget>& widget);
		void left(const SharedPtr<Widget>& widget);
		void right(const SharedPtr<Widget>& widget);
		void under(const SharedPtr<Widget>& widget);

	protected:

	private:

#pragma endregion

	private:

		class Private;
		Private* const d;
	};
}