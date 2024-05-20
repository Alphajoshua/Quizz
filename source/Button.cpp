#include "stdafx.h"
#include "Button.h"

namespace Alpha
{
#pragma region Anonymous

	namespace
	{

	}

#pragma endregion

#pragma  region Private

	class Button::Private
	{
	public:
		std::wstring displayedText;
		ImVec2 buttonSize;
		ImVec4 hoverBackgroundColor, activeBackgroundColor, selectedBackgroundColor;
		std::function<bool()> onClick{ []() {return false; } };
		bool isSelected{ false };
	};

#pragma endregion

#pragma region Constructors/Destructors

	Button::Button()
		:d(new Private())
	{

	}

	Button::~Button()
	{
		delete d;
	}
#pragma endregion

#pragma region **** Heritage ****

	bool Button::render()
	{
		bool result = false;

		if (isSelected())
			ImGui::PushStyleColor(ImGuiCol_Button, getSelectedBackgroundColor());	//Selected color
		else
			ImGui::PushStyleColor(ImGuiCol_Button, getStillBackgroundColor());		//Still color
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, getHoverBackgroundColor());	//Hover color
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, getActiveBackgroundColor());	//Active color

		setDrawingCursor(getStartingDrawingZone());
		increaseHorizontalDrawingCursor( static_cast<float>( getHorizontalPadding() ) );
		increaseVerticalDrawingCursor( static_cast<float>( getVerticalPadding() ) );

		if (ImGui::Button( StringToolBox::getUtf8(getDisplayedText()).c_str(), getButtonSize()))
		{
			result = onClick();
		}

		ImGui::PopStyleColor(3);

		return result;
	}

#pragma endregion

#pragma region **** Accessors ****

	ImVec2 Button::getButtonSize() const
	{
		return getSizeDrawingZone();
	}

	void Button::setButtonSize(const ImVec2& buttonSize)
	{
		setSizeDrawingZone(buttonSize);
	}

	std::wstring Button::getDisplayedText() const
	{
		auto result = d->displayedText;
		if (result.empty())
			result = L"Button";

		return result;
	}

	void Button::setDisplayedText(const std::wstring& displayedText)
	{
		d->displayedText = displayedText;
	}

	ImVec4 Button::getStillBackgroundColor() const
	{
		return getBackgroundColor();
	}
	
	void Button::setStillBackgroundColor(const ImVec4& color)
	{
		setBackGroundColor(color);
	}

	ImVec4 Button::getHoverBackgroundColor() const
	{
		return d->hoverBackgroundColor;
	}

	void Button::setHoverBackgroundColor(const ImVec4& color)
	{
		d->hoverBackgroundColor = color;
	}
	ImVec4 Button::getActiveBackgroundColor() const
	{
		return d->activeBackgroundColor;
	}
	void Button::setActiveBackgroundColor(const ImVec4& color)
	{
		d->activeBackgroundColor = color;
	}
	ImVec4 Button::getSelectedBackgroundColor() const
	{
		return d->selectedBackgroundColor;
	}
	void Button::setSelectedBackgroundColor(const ImVec4& color)
	{
		d->selectedBackgroundColor = color;
	}
	void Button::setOnClick(std::function<bool()> callback)
	{
		d->onClick = callback;
	}

	bool Button::isSelected() const
	{
		return d->isSelected;
	}

	void Button::setSelected(bool value)
	{
		d->isSelected = value;
	}

#pragma endregion

#pragma region **** Methods ****

	bool Button::onClick()
	{
		logMessage(L"ButtonClick: " + getDisplayedText());
		return d->onClick();
	}

#pragma endregion

}