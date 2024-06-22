#pragma once

#include "BaseObject.h"

namespace Alpha
{
	class Category : public BaseObject
	{

	public:

#pragma region Constructors/Destructors

		Category();
		~Category();

#pragma endregion

#pragma region **** Heritage ****

	public:

	protected:

	private:

#pragma endregion

#pragma region **** Accessors ****

	public:
		UnicodeString getName()const;
		void setName(const UnicodeString& name);

	protected:

	private:

#pragma endregion

#pragma region **** Methods ****

	public:

	protected:

	private:

#pragma endregion

	private:

		class Private;
		Private* const d;
	};
}