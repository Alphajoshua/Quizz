#include "stdafx.h"
#include "Application.h"
#include "Page.h"

namespace Alpha
{
#pragma region Anonymous

	namespace
	{

	}

#pragma endregion

#pragma  region Private

	class Page::Private
	{
	public:
		WeakPtr<Application> parent;
		ImVec4 drawableZone;
		bool initialized{ false };
	};

#pragma endregion

#pragma region Constructors/Destructors

	Page::Page()
		:d(new Private())
	{

	}

	Page::~Page()
	{
		delete d;
	}
#pragma endregion

#pragma region **** Heritage ****

	bool Page::render()
	{
		return Widget::render();
	}


#pragma endregion

#pragma region **** Accessors ****

	bool Page::isInitialized() const
	{
		return d->initialized;
	}

	void Page::setInitialized(bool value)
	{
		d->initialized = value;
	}

	SharedPtr<Application> Page::getParent() const
	{
		return d->parent.lock();
	}

	void Page::setParent(const SharedPtr<Application>& parent)
	{
		d->parent = parent;
	}

	ImVec2 Page::getWindowSize() const
	{
		return getParent()->getWindowSize();
	}

#pragma endregion

#pragma region **** Methods ****

	void Page::init()
	{
	}

#pragma endregion

}