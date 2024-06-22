#include "stdafx.h"
#include "Widget.h"

namespace Alpha
{
#pragma region Anonymous

	namespace
	{

	}

#pragma endregion

#pragma  region Private

	class Widget::Private
	{
	public:
		ImVec2 startingDrawingZone, sizeDrawingZone;
		ImVec4 backgroundColor;
		int horizontalPadding{ DEFAULT_INT }, verticalPadding{ DEFAULT_INT };
		bool enabled { true };
	};

#pragma endregion

#pragma region Constructors/Destructors

	Widget::Widget()
		:d(new Private())
	{

	}

	Widget::~Widget()
	{
		delete d;
	}
#pragma endregion

#pragma region **** Heritage ****

#pragma endregion

#pragma region **** Accessors ****

	ImVec2 Widget::getStartingDrawingZone() const
	{
		return d->startingDrawingZone;
	}

	void Widget::setStartingDrawingZone(const ImVec2& zone)
	{
		d->startingDrawingZone = zone;
	}

	ImVec2 Widget::getSizeDrawingZone() const
	{
		return d->sizeDrawingZone;
	}

	void Widget::setSizeDrawingZone(const ImVec2& zone)
	{
		d->sizeDrawingZone = zone;
	}

	ImVec2 Widget::getEndingDrawingZone() const
	{
		const auto startingDZ = getStartingDrawingZone();
		const auto sizeDZ = getSizeDrawingZone();
		return ImVec2(startingDZ.x + sizeDZ.x + (2 * getHorizontalPadding()), startingDZ.y + sizeDZ.y + (2 * getVerticalPadding()));
	}

	ImVec4 Widget::getBackgroundColor() const
	{
		return d->backgroundColor;
	}

	void Widget::setBackGroundColor(const ImVec4& color)
	{
		d->backgroundColor = color;
	}

	ImVec2 Widget::getDrawingCursor() const
	{
		return ImVec2( {getHorizontalCursor(), getVerticalCursor()});
	}

	void Widget::setDrawingCursor( const ImVec2& cursor )
	{
		setHorizontalCursor(cursor.x);
		setVerticalCursor(cursor.y);
	}

	float Widget::getHorizontalCursor() const
	{
		return ImGui::GetCursorPosX();
	}

	void Widget::setHorizontalCursor(const float& position)
	{
		ImGui::SetCursorPosX(position);
	}

	float Widget::getVerticalCursor() const
	{
		return ImGui::GetCursorPosY();
	}

	void Widget::setVerticalCursor(const float& position)
	{
		ImGui::SetCursorPosY(position);
	}

	int Widget::getHorizontalPadding()const
	{
		return d->horizontalPadding;
	}

	void Widget::setHorizontalPadding( int padding )
	{
		d->horizontalPadding = padding;
	}

	int Widget::getVerticalPadding()const
	{
		return d->verticalPadding;
	}

	void Widget::setVerticalPadding( int padding )
	{
		d->verticalPadding = padding;
	}
	bool Widget::isEnabled() const
	{
		return d->enabled;
	}
	void Widget::setEnabled(bool value)
	{
		d->enabled = value;
	}
#pragma endregion

#pragma region **** Methods ****

	bool Widget::render()
	{
		const auto startingDrawingZone = getStartingDrawingZone();

		ImGui::GetWindowDrawList()->AddRectFilled(startingDrawingZone, getEndingDrawingZone(), ImGui::ColorConvertFloat4ToU32(getBackgroundColor()));
		setHorizontalCursor(startingDrawingZone.x + getHorizontalPadding() );
		setVerticalCursor(startingDrawingZone.y + getVerticalPadding() );

		return false;
	}
	void Widget::increaseDrawingCursor(float value)
	{
		setDrawingCursor({ getHorizontalCursor() + value, getVerticalCursor() + value });
	}

	void Widget::decreaseDrawingCursor(float value)
	{
		setDrawingCursor({ getHorizontalCursor() - value, getVerticalCursor() - value });
	}

	void Widget::increaseHorizontalDrawingCursor(float value)
	{
		setHorizontalCursor(getHorizontalCursor() + value);
	}

	void Widget::decreaseHorizontalDrawingCursor(float value)
	{
		setHorizontalCursor(getHorizontalCursor() - value);
	}

	void Widget::increaseVerticalDrawingCursor(float value)
	{
		setVerticalCursor(getVerticalCursor() + value);
	}

	void Widget::decreaseVerticalDrawingCursor(float value)
	{
		setVerticalCursor(getVerticalCursor() - value);
	}

	void Widget::upper(const SharedPtr<Widget>& widget)
	{
		setStartingDrawingZone({ widget->getStartingDrawingZone().x, widget->getStartingDrawingZone().y - getSizeDrawingZone().y });
	}

	void Widget::left(const SharedPtr<Widget>& widget)
	{
		setStartingDrawingZone({ widget->getStartingDrawingZone().x - getSizeDrawingZone().x, widget->getStartingDrawingZone().y });
	}

	void Widget::right(const SharedPtr<Widget>& widget)
	{
		setStartingDrawingZone({ widget->getStartingDrawingZone().x + getSizeDrawingZone().x, widget->getStartingDrawingZone().y });
	}

	void Widget::under(const SharedPtr<Widget>& widget)
	{
		setStartingDrawingZone({ widget->getStartingDrawingZone().x, widget->getStartingDrawingZone().y + getSizeDrawingZone().y });
	}

#pragma endregion
}