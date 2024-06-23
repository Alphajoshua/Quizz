#include "stdafx.h"

#include "Application.h"
#include "ManageCategoryPage.h"
#include "Category.h"
#include "CategoryCTRL.h"
#include "Button.h"
#include "TextElement.h"
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

		SharedPtr<std::vector<SharedPtr<Category>>> colCategory{ refNew<std::vector<SharedPtr<Category>>>() };
		
		int indexSelectedCategory;
		WeakPtr<Category> selectedCategory;
		
		SharedPtr<Button> deleteButton{ refNew<Button>() }, createButton{ refNew<Button>() }, modifyButton{ refNew<Button>() };

		SharedPtr<TextElement> categoryNameElement { refNew<TextElement>() };

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

		d->categoryNameElement->setName(L"Name");
		d->categoryNameElement->setBufferSize(256);
		d->categoryNameElement->setWidth(200.0f);
		d->categoryNameElement->init();

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

		auto createOnClick = [&]() 
		{
			const auto colCategory = getColCategory();
			auto newName = refNew<UnicodeString>();
			d->categoryNameElement->mapBufferToString(newName);
			if( !newName->empty() && !isNameAlreadyUsed(colCategory, newName) )
			{
				const auto newCategory = refNew<Category>();
				newCategory->setName(*newName);
				getCategoryCTRL()->addCategory(newCategory);
				colCategory->push_back(newCategory);
				d->categoryNameElement->resetBuffer();
				setIndexSelectedCategory(static_cast<int>( colCategory->size() ) - 1);
				setSelectedCategory(colCategory->at(getIndexSelectedCategory()));
			}
			return false;
		};
		d->createButton->setOnClick(std::function<bool()>(createOnClick));
		
		auto modifyOnClick = [&]() 
		{
			if (int index = getIndexSelectedCategory(); index > -1)
			{
				const auto colCategory = getColCategory();
				const auto selectedCategory = getSelectedCategory();
				const auto modifiedName = d->categoryNameElement->getText();
				if( !empty(selectedCategory) && !modifiedName.empty() && modifiedName != selectedCategory->getName() && !isNameAlreadyUsed(colCategory, modifiedName) )
				{
					selectedCategory->setName(modifiedName);
					getCategoryCTRL()->modifyCategory(selectedCategory);
				}
			}
			return false;
		};
		d->modifyButton->setOnClick(std::function<bool()>(modifyOnClick));

		auto deleteOnClick = [&]() 
		{
			if (int index = getIndexSelectedCategory(); index > -1)
			{
				const auto selectedCategory = getSelectedCategory();
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
					d->categoryNameElement->resetBuffer();
				}
				getCategoryCTRL()->deleteCategory(selectedCategory);
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
		const auto selectedCategory = getSelectedCategory();

		const auto startingDrawingZone = getStartingDrawingZone();
		const auto sizeDrawingZone = getSizeDrawingZone();

		d->categoryNameElement->setStartingDrawingZone({ startingDrawingZone.x + 10, startingDrawingZone.y + 10 });
		d->categoryNameElement->render();

		d->createButton->setStartingDrawingZone({ startingDrawingZone.x + 200 + 5, startingDrawingZone.y + 10 });
		d->modifyButton->setStartingDrawingZone({ d->createButton->getEndingDrawingZone().x, getStartingDrawingZone().y + 10 });
		d->deleteButton->setStartingDrawingZone({ d->modifyButton->getEndingDrawingZone().x, getStartingDrawingZone().y + 10 });

		const auto hasSelection = !empty(selectedCategory);
		const auto name = d->categoryNameElement->getText();
		const auto validName = !name.empty();
		d->createButton->setEnabled(validName && !isNameAlreadyUsed(colCategory, name));
		d->modifyButton->setEnabled(hasSelection && validName && name != selectedCategory->getName());
		d->deleteButton->setEnabled(hasSelection && validName && name == selectedCategory->getName());

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
		d->categoryNameElement->mapStringToBuffer(category->getName());
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

	bool ManageCategoryPage::isNameAlreadyUsed(const SharedPtr<std::vector<SharedPtr<Category>>>& colCategory, const UnicodeString& name)
	{
		return std::find_if(colCategory->begin(), colCategory->end(), [name](const SharedPtr<Category>& category) {return category->getName() == name; }) != colCategory->end();
	}

	bool ManageCategoryPage::isNameAlreadyUsed(const SharedPtr<std::vector<SharedPtr<Category>>>& colCategory, const SharedPtr<UnicodeString>& name)
	{
		return std::find_if(colCategory->begin(), colCategory->end(), [name](const SharedPtr<Category>& category) {return category->getName() == *name; }) != colCategory->end();
	}

#pragma endregion

}