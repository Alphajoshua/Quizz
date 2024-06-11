#include "stdafx.h"

#include "Application.h"
#include "ManageCategoryPage.h"
#include "Category.h"
#include "CategoryCTRL.h"
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

	class ManageCategoryPage::Private
	{
	public:
		char textBuffer[255];

		SharedPtr<std::vector<SharedPtr<Category>>> colCategory{ refNew<std::vector<SharedPtr<Category>>>() };
		
		int indexSelectedCategory;
		WeakPtr<Category> selectedCategory;
		
		SharedPtr<Button> deleteButton{ refNew<Button>() }, createButton{ refNew<Button>() }, modifyButton{ refNew<Button>() };

		SharedPtr<CategoryCTRL> categoryCTRL{ refNew<CategoryCTRL>() };
	};

#pragma endregion

#pragma region Constructors/Destructors

	ManageCategoryPage::ManageCategoryPage()
		:d(new Private())
	{

	}

	ManageCategoryPage::~ManageCategoryPage()
	{
		delete d;
	}
#pragma endregion

#pragma region **** Heritage ****

	void ManageCategoryPage::init()
	{
		getCategoryCTRL()->setDataBaseConnection(getParent()->getCultureDataBaseConnection());
		setColCategory(getCategoryCTRL()->loadColCategory());

		setBackGroundColor({ 0.18f, 0.32f, 0.62f, 1.0f });

		//const auto colCategory = getColCategory();
		//for (int index{ 0 }; index < 10; ++index)
		//{
		//	const auto category = refNew<Category>();
		//	category->setId(index);
		//	category->setName(L"Category " + std::to_wstring(index));
		//	colCategory->push_back(category);
		//}
		const auto windowSize = getParent()->getWindowSize();
		float buttonWidth = windowSize.x / 10.0f;
		float buttonHeight = windowSize.y / 20.0f;
		ImVec2 buttonSize{ buttonWidth, buttonHeight };

		d->createButton->setDisplayedText(L"Ajouter");
		d->modifyButton->setDisplayedText(L"Modifier");
		d->deleteButton->setDisplayedText(L"Supprimer");
		
		d->createButton->setButtonSize(buttonSize);
		d->modifyButton->setButtonSize(buttonSize);
		d->deleteButton->setButtonSize(buttonSize);
		
		ButtonToolBox::setDefaultStyle(d->createButton);
		ButtonToolBox::setDefaultStyle(d->modifyButton);
		ButtonToolBox::setDefaultStyle(d->deleteButton);

		auto createOnClick = [&]() {
				const auto colCategory = getColCategory();
				UnicodeString newName = StringToolBox::getUnicodeString(d->textBuffer );
				if (!newName.empty() && std::find_if(colCategory->begin(), colCategory->end(), [newName](const SharedPtr<Category>& category) {return category->getName() == newName; }) == colCategory->end())
				{
					const auto newCategory = refNew<Category>();
					newCategory->setName(newName);
					getCategoryCTRL()->addCategory(newCategory);
					colCategory->push_back(newCategory);
					UnicodeString emptyString{ EmptyUnicodeString };
					strcpy_s(d->textBuffer, StringToolBox::getUtf8(emptyString).c_str() );
					setIndexSelectedCategory(static_cast<int>(colCategory->size()) - 1);
					setSelectedCategory(colCategory->at(getIndexSelectedCategory()));
				}
				return false;
		};
		d->createButton->setOnClick(std::function<bool()>(createOnClick));
		
		auto modifyOnClick = [&]() {
			if (int index = getIndexSelectedCategory(); index > -1)
			{
				const auto colCategory = getColCategory();
				const auto selectedCategory = getSelectedCategory();
				UnicodeString newName = StringToolBox::getUnicodeString(d->textBuffer);
				if (!newName.empty() && std::find_if(colCategory->begin(), colCategory->end(), [newName](const SharedPtr<Category>& category) {return category->getName() == newName; }) == colCategory->end())
					selectedCategory->setName(newName);
			}
				return false;
			};
		d->modifyButton->setOnClick(std::function<bool()>(modifyOnClick));

		auto deleteOnClick = [&]() {
			if (int index = getIndexSelectedCategory(); index > -1)
			{
				const auto colCategory = getColCategory();
				colCategory->erase(colCategory->begin() + getIndexSelectedCategory());
				if (index > 0)
				{
					setIndexSelectedCategory(index-1);
					setSelectedCategory(colCategory->at(index - 1));
				}
				else
				{
					setIndexSelectedCategory(-1);
					UnicodeString emptyString{ EmptyUnicodeString };
					strcpy_s(d->textBuffer, StringToolBox::getUtf8(emptyString).c_str());

				}
			}
			return false;
			};
		d->deleteButton->setOnClick(std::function<bool()>(deleteOnClick));

		setInitialized(true);
	}

	bool ManageCategoryPage::render()
	{
		Page::render();
		const auto colCategory = getColCategory();

		const auto startingDrawingZone = getStartingDrawingZone();
		const auto sizeDrawingZone = getSizeDrawingZone();

		setHorizontalCursor(startingDrawingZone.x + 10);
		setVerticalCursor(startingDrawingZone.y + 10);
		
		ImGui::SetNextItemWidth(200);
		ImGui::InputText("Name", d->textBuffer, IM_ARRAYSIZE(d->textBuffer), ImGuiInputTextFlags_None);

		d->createButton->setStartingDrawingZone({ startingDrawingZone.x + 200 + 5, startingDrawingZone.y + 10 });
		d->modifyButton->setStartingDrawingZone({ d->createButton->getEndingDrawingZone().x, getStartingDrawingZone().y + 10 });
		d->deleteButton->setStartingDrawingZone({ d->modifyButton->getEndingDrawingZone().x, getStartingDrawingZone().y + 10 });

		d->createButton->render();
		d->modifyButton->render();
		d->deleteButton->render();

		setHorizontalCursor(startingDrawingZone.x + 10);
		ImVec2 listBoxDrawableZone = { sizeDrawingZone.x - 20.0f, sizeDrawingZone.y - 20.0f - ( getWindowSize().y / 20.0f) };

		if (ImGui::BeginListBox("##Liste", listBoxDrawableZone)) {
			for (int index{ 0 }; index < colCategory->size(); ++index) {
				bool isSelected = ( getIndexSelectedCategory() == index);
				if (ImGui::Selectable( StringToolBox::getUtf8( colCategory->at(index)->getName()).c_str(), isSelected)) {
					setIndexSelectedCategory(index);
					setSelectedCategory(colCategory->at(index));
				}
			}
			ImGui::EndListBox();
		}

		return false;
	}


#pragma endregion

#pragma region **** Accessors ****

	SharedPtr<std::vector<SharedPtr<Category>>> ManageCategoryPage::getColCategory() const
	{
		return d->colCategory;
	}

	void ManageCategoryPage::setColCategory(const SharedPtr<std::vector<SharedPtr<Category>>>& col)
	{
		d->colCategory = col;
	}

	int ManageCategoryPage::getIndexSelectedCategory() const
	{
		return d->indexSelectedCategory;
	}

	void ManageCategoryPage::setIndexSelectedCategory(int value)
	{
		d->indexSelectedCategory = value;
	}

	SharedPtr<Category> ManageCategoryPage::getSelectedCategory() const
	{
		return d->selectedCategory.lock();
	}

	void ManageCategoryPage::setSelectedCategory(const SharedPtr<Category>& category)
	{
		d->selectedCategory = category;
		strcpy_s(d->textBuffer, StringToolBox::getUtf8( category->getName() ).c_str());
	}

	SharedPtr<CategoryCTRL> ManageCategoryPage::getCategoryCTRL() const
	{
		return d->categoryCTRL;
	}

	void ManageCategoryPage::setCategoryCTRL(const SharedPtr<CategoryCTRL>& categoryCTRL)
	{
		d->categoryCTRL = categoryCTRL;
	}


#pragma endregion

#pragma region **** Methods ****

#pragma endregion

}