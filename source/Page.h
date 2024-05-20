#pragma once
#include "Widget.h"

namespace Alpha
{
	class Application;
	class Page : public Widget
	{

	public:

#pragma region Constructors/Destructors

		Page();
		~Page();

#pragma endregion

#pragma region **** Heritage ****

	public:
		virtual bool render() override;

	protected:

	private:

#pragma endregion

#pragma region **** Accessors ****

	public:
		bool isInitialized()const;
		void setInitialized(bool value);

		SharedPtr<Application> getParent()const;
		void setParent(const SharedPtr<Application>& parent);

		ImVec2 getWindowSize() const;

	protected:

	private:

#pragma endregion

#pragma region **** Methods ****

	public:
		virtual void init();

	protected:

	private:

#pragma endregion

	private:

		class Private;
		Private* const d;
	};
}