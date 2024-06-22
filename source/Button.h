#pragma once
#include "ImGui.h"
#include <string>
#include <functional>
#include "Widget.h"

namespace Alpha
{
	class Button : public Widget
	{

	public:

#pragma region Constructors/Destructors

		Button();
		~Button();

#pragma endregion

#pragma region **** Heritage ****

	public:
		virtual bool render() override;

	protected:

	private:

#pragma endregion

#pragma region **** Accessors ****

	public:
		ImVec2 getButtonSize()const;
		void setButtonSize(const ImVec2& buttonSize);

		std::wstring getDisplayedText()const;
		void setDisplayedText(const std::wstring& displayedText);

		ImVec4 getDisabledBackgroundColor()const;
		void setDisabledBackgroundColor(const ImVec4& color);

		ImVec4 getStillBackgroundColor()const;
		void setStillBackgroundColor(const ImVec4& color);
		
		ImVec4 getHoverBackgroundColor()const;
		void setHoverBackgroundColor(const ImVec4& color);
		
		ImVec4 getActiveBackgroundColor()const;
		void setActiveBackgroundColor(const ImVec4& color);
		
		ImVec4 getSelectedBackgroundColor()const;
		void setSelectedBackgroundColor(const ImVec4& color);

		void setEnabledStyle();
		void setDisabledStyle();

		void setOnClick(std::function<bool()> callback);

		bool isSelected()const;
		void setSelected(bool value);

	protected:

	private:

#pragma endregion

#pragma region **** Methods ****

	public:
		bool onClick();

	protected:

	private:

#pragma endregion

	private:

		class Private;
		Private* const d;
	};
}