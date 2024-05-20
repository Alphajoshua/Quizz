#pragma once

#include "SmartPointers.h"
#include "AlphaString.h"

namespace Alpha
{
	template <class T>
	SharedPtr<T> refNew()
	{
		return std::make_shared<T>();
	}
	template <class T, class U>
	SharedPtr<T> refCast( const std::shared_ptr<U>& ptr )
	{
		return std::static_pointer_cast<T>(ptr);
	}
	
	class BaseObject : public SharedPtrFromThis<BaseObject>
	{

	public:

#pragma region Constructors/Destructors

		BaseObject();
		~BaseObject();

#pragma endregion

#pragma region **** Heritage ****

	public:

	protected:

	private:

#pragma endregion

#pragma region **** Accessors ****

	public:
		int getId()const;
		void setId(int value);

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