#include "stdafx.h"
#include "Application.h"
#include "OptionsPage.h"
#include "Homepage.h"
#include "ManageCategoryPage.h"
#include "ManageQuestionPage.h"
#include "Button.h"
#include "ButtonToolBox.h"

namespace Alpha
{
#pragma region Anonymous

	namespace
	{

	}

#pragma endregion

#pragma  region Private

	class OptionsPage::Private
	{
	public:
		SharedPtr<Page> composite;
		SharedPtr<Button> returnButton{ refNew<Button>() }, manageCategoryButton{ refNew<Button>() }, manageQuestionButton{ refNew<Button>() };
	};

#pragma endregion

#pragma region Constructors/Destructors

	OptionsPage::OptionsPage()
		:d(new Private())
	{

	}

	OptionsPage::~OptionsPage()
	{
		delete d;
	}
#pragma endregion

#pragma region **** Heritage ****

	void OptionsPage::init()
	{
		const auto windowSize = getParent()->getWindowSize(); windowSize.x > DEFAULT_X_COORDINATE&& windowSize.y > DEFAULT_Y_COORDINATE;
		initButtons(windowSize);
		setInitialized(true);
	}

	bool OptionsPage::render()
	{
		if (const auto windowSize = getParent()->getWindowSize(); windowSize.x > DEFAULT_X_COORDINATE && windowSize.y > DEFAULT_Y_COORDINATE)
		{
			//Draw nav menu
			drawLeftRectangle(windowSize);

			//Draw menu buttons
			setVerticalCursor(0);
			d->returnButton->render();
			d->manageCategoryButton->render();
			d->manageQuestionButton->render();

			//Draw composite
			renderComposite(windowSize);
		}
		return false;
	}

#pragma endregion

#pragma region **** Accessors ****

	SharedPtr<Page> OptionsPage::getComposite() const
	{
		return d->composite;
	}

	void OptionsPage::setComposite(const SharedPtr<Page>& composite)
	{
		const auto windowSize = getParent()->getWindowSize();
		composite->setStartingDrawingZone({ getMenuSize().x,0 });
		composite->setSizeDrawingZone({ windowSize.x - getMenuSize().x,windowSize.y });
		composite->setParent(getParent());
		composite->init();

		d->composite = composite;
	}

	ImVec2 OptionsPage::getMenuSize() const
	{
		const auto windowSize = getParent()->getWindowSize();
		return { windowSize.x / 10.0f, windowSize.y };
	}

#pragma endregion

#pragma region **** Methods ****

	void OptionsPage::initButtons(ImVec2 windowSize)
	{
		float buttonWidth = windowSize.x / 10.0f;
		float buttonHeight = windowSize.y / 20.0f;
		ImVec2 buttonSize{ buttonWidth, buttonHeight - 5.0f  };

		d->returnButton->setDisplayedText(L"[<] Retour");
		d->manageCategoryButton->setDisplayedText(L"[Gestion] Catégorie(s)");
		d->manageQuestionButton->setDisplayedText(L"[Gestion] Question(s)");

		d->returnButton->setButtonSize(buttonSize);
		d->manageCategoryButton->setButtonSize(buttonSize);
		d->manageQuestionButton->setButtonSize(buttonSize);

		ButtonToolBox::setNavMenuStyle(d->returnButton);
		ButtonToolBox::setNavMenuStyle(d->manageCategoryButton);
		ButtonToolBox::setNavMenuStyle(d->manageQuestionButton);

		d->returnButton->setStartingDrawingZone({ 0, 0 });
		d->manageCategoryButton->setStartingDrawingZone({ 0, d->returnButton->getEndingDrawingZone().y });
		d->manageQuestionButton->setStartingDrawingZone({ 0, d->manageCategoryButton->getEndingDrawingZone().y });

		auto returnOnClick = [&]() { getParent()->setPage(refNew<Homepage>()); return false; };
		d->returnButton->setOnClick(std::function<bool()>(returnOnClick));

		auto manageCategoryOnClick = [&]() { setComposite(refNew<ManageCategoryPage>()); resetButtonSelection(); d->manageCategoryButton->setSelected(true); return false; };
		d->manageCategoryButton->setOnClick(std::function<bool()>(manageCategoryOnClick));

		auto manageQestionOnClick = [&]() { setComposite(refNew<ManageQuestionPage>()); resetButtonSelection(); d->manageQuestionButton->setSelected(true); return false; };
		d->manageQuestionButton->setOnClick(std::function<bool()>(manageQestionOnClick));
	}

	void OptionsPage::renderComposite( ImVec2 windowSize )
	{
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, { windowSize.x / 10.0f ,windowSize.y });

		if (const auto composite = getComposite(); composite != nullptr && composite.use_count() > 0)
		{
			if (!composite->isInitialized())
				composite->init();

			composite->render();
		}

		ImGui::PopStyleVar(1);
	}

	void OptionsPage::drawLeftRectangle(ImVec2 windowSize) const
	{
		ImVec2 rectMin{ 0, 0 }; // Coin supérieur gauche du rectangle
		ImVec2 rectMax{ getMenuSize() };  // Coin inférieur droit du rectangle

		const auto clearColor = getParent()->getClearColor();
		float darkenFactor = 0.7f;
		int red = lround(clearColor.x * darkenFactor * 255.0f);
		int green = lround(clearColor.y * darkenFactor * 255.0f);
		int blue = lround(clearColor.z * darkenFactor * 255.0f);
		const auto newColor = IM_COL32(red, green, blue, 255);
		ImGui::GetWindowDrawList()->AddRectFilled(rectMin, rectMax, newColor); // Dessiner un rectangle rouge
	}

	void OptionsPage::resetButtonSelection()
	{
		d->manageCategoryButton->setSelected(false);
		d->manageQuestionButton->setSelected(false);
	}

#pragma endregion

}