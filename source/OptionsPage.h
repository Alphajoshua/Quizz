#pragma once
#include "Page.h"

namespace Alpha
{
	class OptionsPage :public Page
	{

	public:

#pragma region Constructors/Destructors

		OptionsPage();
		~OptionsPage();

#pragma endregion

#pragma region **** Heritage ****

	public:
		virtual void init() override;

		virtual bool render() override;

	protected:

	private:

#pragma endregion

#pragma region **** Accessors ****

	public:
		SharedPtr<Page> getComposite()const;
		void setComposite(const SharedPtr<Page>& composite);

		ImVec2 getMenuSize()const;

	protected:

	private:

#pragma endregion

#pragma region **** Methods ****

	public:
		void initButtons(ImVec2 windowSize);
		void renderComposite( ImVec2 windowSize );

		void drawLeftRectangle( ImVec2 windowSize ) const;
		
		void resetButtonSelection();

	protected:

	private:

#pragma endregion

	private:

		class Private;
		Private* const d;
	};
}