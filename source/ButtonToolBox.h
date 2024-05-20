#pragma once

#include "SmartPointers.h"

namespace Alpha
{
	class Button;
	class ButtonToolBox
	{

	public:

#pragma region Constructors/Destructors

		ButtonToolBox();
		~ButtonToolBox();

#pragma endregion

#pragma region **** Heritage ****

	public:

	protected:

	private:

#pragma endregion

#pragma region **** Accessors ****

	public:

	protected:

	private:

#pragma endregion

#pragma region **** Methods ****

	public:
		static void setDefaultStyle(const SharedPtr<Button>& button);
		static void setHomepageStyle(const SharedPtr<Button>& button);
		static void setNavMenuStyle(const SharedPtr<Button>& button);
	
	protected:

	private:

#pragma endregion

	private:

		class Private;
		Private* const d;
	};
}