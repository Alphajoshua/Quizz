#include "stdafx.h"

#include "Application.h"
#include "Button.h"
#include "ButtonToolBox.h"
#include "Homepage.h"
#include "OptionsPage.h"

namespace Alpha
{
#pragma region Anonymous

	namespace
	{
		const int NBR_ROW = 10;
		const int NBR_COLUMN = 3;
	}

#pragma endregion

#pragma  region Private

	class Homepage::Private
	{
	public:
		ImVec2 buttonSize;
		SharedPtr<Button> quickGameButton{ refNew<Button>() }, newGameButton{ refNew<Button>() }, optionsButton{ refNew<Button>() }, quitButton{ refNew<Button>() };
	};

#pragma endregion

#pragma region Constructors/Destructors

	Homepage::Homepage()
		:d(new Private())
	{

	}

	Homepage::~Homepage()
	{
		delete d;
	}
#pragma endregion

#pragma region **** Heritage ****

	void Homepage::init()
	{
	}

	bool Homepage::render()
	{
		bool result = false;
		auto windowSize = getParent()->getWindowSize();
		
		displayEmptySpace(windowSize, NBR_ROW);

		// Grand titre centré
		displayTitle(windowSize);

		displayEmptySpace(windowSize, NBR_ROW);
		displayEmptySpace(windowSize, NBR_ROW);

		ImGui::Columns(NBR_COLUMN, nullptr, false);

		ImGui::NextColumn();

		//Create buttons
		if (!isInitialized())
		{
			initButtons(windowSize);
			setInitialized(true);
		}

		//Draw buttons
		d->quickGameButton->render();
		d->newGameButton->render();
		d->optionsButton->render();
		result = d->quitButton->render();
		
		return result;
	}


#pragma endregion

#pragma region **** Accessors ****

#pragma endregion

#pragma region **** Methods ****

	void Homepage::initButtons(ImVec2 windowSize)
	{	
		float buttonWidth = windowSize.x / NBR_COLUMN;
		float buttonHeight = windowSize.y / NBR_ROW;
		ImVec2 buttonSize{ buttonWidth, buttonHeight - 5.0f };

		d->quickGameButton->setDisplayedText(L"Partie rapide");
		d->newGameButton->setDisplayedText(L"Nouvelle partie");
		d->optionsButton->setDisplayedText(L"Options");
		d->quitButton->setDisplayedText(L"Quitter");

		d->quickGameButton->setButtonSize(buttonSize);
		d->newGameButton->setButtonSize(buttonSize);
		d->optionsButton->setButtonSize(buttonSize);
		d->quitButton->setButtonSize(buttonSize);

		ButtonToolBox::setHomepageStyle(d->quickGameButton);
		ButtonToolBox::setHomepageStyle(d->newGameButton);
		ButtonToolBox::setHomepageStyle(d->optionsButton);
		ButtonToolBox::setHomepageStyle(d->quitButton);

		d->quickGameButton->setStartingDrawingZone({ (windowSize.x - d->quickGameButton->getButtonSize().x) * 0.5f , getVerticalCursor() });
		d->newGameButton->setStartingDrawingZone({ d->quickGameButton->getStartingDrawingZone().x, d->quickGameButton->getEndingDrawingZone().y });
		d->optionsButton->setStartingDrawingZone({ d->newGameButton->getStartingDrawingZone().x, d->newGameButton->getEndingDrawingZone().y });
		d->quitButton->setStartingDrawingZone({ d->optionsButton->getStartingDrawingZone().x, d->optionsButton->getEndingDrawingZone().y });

		auto optionsOnClick = [&]() { getParent()->setPage(refNew<OptionsPage>()); return false; };
		d->optionsButton->setOnClick(std::function<bool()>(optionsOnClick));

		auto quitOnClick = [&]() { return true; };
		d->quitButton->setOnClick(std::function<bool()>(quitOnClick));
	}

	void Homepage::displayTitle(ImVec2 windowSize)
	{
		float screenHeight = windowSize.y;
		float textSize = screenHeight / 5.0f;

		// Modifier temporairement la taille du texte et la couleur
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 10)); // Espacement entre les éléments
		ImGui::PushStyleVar(ImGuiStyleVar_ItemInnerSpacing, ImVec2(10, 0)); // Espacement à l'intérieur des éléments
		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(5, 5)); // Marge du cadre des éléments
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(10, 10)); // Marge de la fenêtre

		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 1.0f, 1.0f)); // Couleur du texte

		// Afficher le texte avec la taille et la couleur définies
		const auto title = "Valouc\'ulture";
		ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[0]);
		auto size = ImGui::GetFontSize();
		if (screenHeight > 0)
		{
			auto fontScale = textSize * (size / screenHeight);
			ImGui::SetWindowFontScale(fontScale);
			auto fontSize = ImGui::CalcTextSize(title).x;
			ImGui::SetCursorPosX((windowSize.x - fontSize) / 2);
		}
		ImGui::Text(title, textSize);
		ImGui::PopFont();
		ImGui::SetWindowFontScale(1);

		// Restaurer les paramètres par défaut
		ImGui::PopStyleColor();
		ImGui::PopStyleVar(4);
	}

	void Homepage::displayEmptySpace(ImVec2 windowSize, int nbrRow)
	{
		ImGui::Dummy(ImVec2(0, windowSize.y / nbrRow)); //Espace vide
	}

#pragma endregion

}