#pragma once

#include "Page.h"

namespace Alpha
{
	class Homepage :public Page
	{

	public:

#pragma region Constructors/Destructors

		Homepage();
		~Homepage();

#pragma endregion

#pragma region **** Heritage ****

	public:
		virtual void init() override;

		bool render() override;

	protected:

	private:

#pragma endregion

#pragma region **** Accessors ****

	public:

		ImVec2 getButtonSize();
		void setButtonSize(ImVec2 size);

	protected:

	private:

#pragma endregion

#pragma region **** Methods ****

	public:

		void initButtons(ImVec2 windowSize);

		void displayTitle(ImVec2 windowSize);
		void displayEmptySpace(ImVec2 windowSize, int nbrRow);

	protected:

	private:

#pragma endregion

	private:

		class Private;
		Private* const d;
	};
}