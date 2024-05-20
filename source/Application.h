#pragma once

#include "BaseObject.h"

namespace Alpha
{
	class Page;
	class DataBaseConnection;
	class Application : public BaseObject
	{

	public:

#pragma region Constructors/Destructors

		Application();
		~Application();

#pragma endregion

#pragma region **** Heritage ****

	public:

	protected:

	private:

#pragma endregion

#pragma region **** Accessors ****

	public:

		ImVec2 getWindowSize()const;

		ImVec4 getClearColor()const;
		void setClearColor(const ImVec4& clearColor);
		
		SharedPtr<Page> getPage()const;
		void setPage(const SharedPtr<Page>& page);

		SharedPtr<DataBaseConnection> getCultureDataBaseConnection();
		void setCultureDataBaseConnection(const SharedPtr<DataBaseConnection>& connection);

	protected:

	private:

#pragma endregion

#pragma region **** Methods ****

	public:

		bool init();
		void setupParent();
		bool render();
		bool run();
		bool shutdown();

	protected:

	private:
		bool checkInstallation();

#pragma endregion

	private:

		class Private;
		Private* const d;
	};
}