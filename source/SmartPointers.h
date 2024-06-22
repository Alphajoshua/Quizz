#pragma once

#include <memory>

namespace Alpha
{
	template <class T>
	using SharedPtr = std::shared_ptr<T>;


	template <class T>
	using WeakPtr = std::weak_ptr<T>;

	template <class T>
	using UniquePtr = std::unique_ptr<T>;

	template<class T>
	using SharedPtrFromThis = std::enable_shared_from_this<T>;

	template<class T>
	bool empty(const std::shared_ptr<T>& ptr)
	{
		return ptr.use_count() == 0;
	}
}