#include "stdafx.h"
#include "Application.h"

#include <filesystem>

#include "Homepage.h"
#include "Page.h"
#include "DataBaseConnection.h"

namespace Alpha
{
#pragma region Anonymous

	namespace
	{

	}

#pragma endregion

#pragma  region Private

	class Application::Private
	{
	public:
		SharedPtr<DataBaseConnection> cultureConnection;
		SharedPtr<Page> displayedPage{ refNew<Homepage>() };
		ImVec4 clearColor{ ImVec4(0.294f, 0.42f, 0.659f, 1.00f) };
	};

#pragma endregion

#pragma region Constructors/Destructors

	Application::Application()
		:d(new Private())
	{
	}

	Application::~Application()
	{
		delete d;
	}

#pragma endregion

#pragma region **** Heritage ****

#pragma endregion

#pragma region **** Accessors ****

	ImVec2 Application::getWindowSize() const
	{
		return ImGui::GetMainViewport()->Size;
	}

	ImVec4 Application::getClearColor() const
	{
		return d->clearColor;
	}

	void Application::setClearColor(const ImVec4& clearColor)
	{
		d->clearColor = clearColor;
	}

	SharedPtr<Page> Application::getPage() const
	{
		return d->displayedPage;
	}

	void Application::setPage(const SharedPtr<Page>& page)
	{
		page->setStartingDrawingZone({ 0,0 });
		page->setSizeDrawingZone({ getWindowSize().x,getWindowSize().y });
		d->displayedPage = page;
	}

	SharedPtr<DataBaseConnection> Application::getCultureDataBaseConnection()
	{
		return d->cultureConnection;
	}

	void Application::setCultureDataBaseConnection(const SharedPtr<DataBaseConnection>& connection)
	{
		d->cultureConnection = connection;
	}

#pragma endregion

#pragma region **** Methods ****

	bool Application::init()
	{
		bool result{ checkInstallation() };
		return result;
	}

	void Application::setupParent()
	{
		if (const auto pageParent = getPage()->getParent(); empty(pageParent) )
			getPage()->setParent(refCast<Application>(shared_from_this()));
	}

	bool Application::render()
	{
		if (!getPage()->isInitialized())
			getPage()->init();

		return getPage()->render();
	}

	bool Application::run()
	{
		bool result = false;
		setupParent();
		result = render();
		return result;
	}

	bool Application::shutdown()
	{
		return getCultureDataBaseConnection()->disconnect();
	}

	bool Application::checkInstallation()
	{
		bool result{ true };

		const auto currentDir = std::filesystem::current_path();
		const auto installationDirectory = currentDir / SOFTWARE_DIRECTORY;
		const auto dbAcces = installationDirectory / DEFAULT_DB_CONNECTION;

		//CHECK DIRECTORY
		if (!std::filesystem::exists(installationDirectory) || !std::filesystem::is_directory(installationDirectory))
		{
			std::filesystem::create_directory(installationDirectory);
			logMessage(L"!! First launch !!");
		}

		//CHECK LOG
		for( int index{0}; index < 5; ++index )
			logSeparator();
	
		logMessage(L"Initialization...");

		//CHECK DB FILE
		const auto connection = refNew<DataBaseConnection>(dbAcces);
		if (result = !connection->connect(); result)
			logError(L"Cannot run the soft without a database");
		else
			setCultureDataBaseConnection(connection);

		connection->checkTables();

		return result;
	}

#pragma endregion

}