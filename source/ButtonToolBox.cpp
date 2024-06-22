#include "ButtonToolBox.h"

#include "imgui.h"
#include "Button.h"

namespace Alpha
{
#pragma region Anonymous

	namespace
	{

	}

#pragma endregion

#pragma  region Private

	class ButtonToolBox::Private
	{
	public:

	};

#pragma endregion

#pragma region Constructors/Destructors

	ButtonToolBox::ButtonToolBox()
		:d(new Private())
	{

	}

	ButtonToolBox::~ButtonToolBox()
	{
		delete d;
	}
#pragma endregion

#pragma region **** Heritage ****

#pragma endregion

#pragma region **** Accessors ****

#pragma endregion

#pragma region **** Methods ****

	void ButtonToolBox::setDefaultStyle(const SharedPtr<Button>& button)
	{
		ImVec4 disabledColor(0.33f, 0.41f, 0.54f, 1.0f);
		ImVec4 stillColor(0.29f, 0.42f, 0.65f, 1.0f);
		ImVec4 hoverColor(0.20f, 0.34f, 0.58f, 1.0f);
		ImVec4 activeColor(0.20f, 0.34f, 0.58f, 1.0f);
		ImVec4 selectedColor(0.18f, 0.32f, 0.62f, 1.0f);

		button->setDisabledBackgroundColor(disabledColor);
		button->setStillBackgroundColor(stillColor);
		button->setHoverBackgroundColor(hoverColor);
		button->setSelectedBackgroundColor(selectedColor);

		button->setHorizontalPadding(5);
		button->setVerticalPadding(5);
	}

	void ButtonToolBox::setHomepageStyle(const SharedPtr<Button>& button)
	{
		ImVec4 disabledColor(0.33f, 0.41f, 0.54f, 1.0f);
		ImVec4 stillColor(0.18f, 0.32f, 0.62f, 1.0f);
		ImVec4 hoverColor(0.29f, 0.42f, 0.65f, 1.0f);
		ImVec4 activeColor(0.20f, 0.34f, 0.58f, 1.0f);
		ImVec4 selectedColor(0.20f, 0.34f, 0.58f, 1.0f);

		button->setDisabledBackgroundColor(disabledColor);
		button->setStillBackgroundColor(stillColor);
		button->setHoverBackgroundColor(hoverColor);
		button->setSelectedBackgroundColor(selectedColor);

		button->setHorizontalPadding(5);
		button->setVerticalPadding(5);
	}

	void ButtonToolBox::setNavMenuStyle(const SharedPtr<Button>& button)
	{
		ImVec4 disabledColor(0.33f, 0.41f, 0.54f, 1.0f);
		ImVec4 stillColor(0.29f, 0.42f, 0.65f, 1.0f);
		ImVec4 hoverColor(0.20f, 0.34f, 0.58f, 1.0f);
		ImVec4 activeColor(0.20f, 0.34f, 0.58f, 1.0f);
		ImVec4 selectedColor(0.18f, 0.32f, 0.62f, 1.0f);

		button->setDisabledBackgroundColor(disabledColor);
		button->setStillBackgroundColor(stillColor);
		button->setHoverBackgroundColor(hoverColor);
		button->setSelectedBackgroundColor(selectedColor);

		button->setVerticalPadding(5);
	}

#pragma endregion

}