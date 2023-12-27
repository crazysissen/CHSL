#pragma once

#include "CSTypedef.h"

namespace cs
{

	template <class T>
	class InitList
	{
	public:
		constexpr InitList() noexcept;
		constexpr InitList(const T* first, const T* last) noexcept;

		[[nodiscard]] constexpr const T* begin() const noexcept;
		[[nodiscard]] constexpr const T* end() const noexcept;
		[[nodiscard]] constexpr ullong size() const noexcept;

	private:
		const T* first;
		const T* last;
	};

	template<class T>
	inline constexpr InitList<T>::InitList() noexcept : first(nullptr), last(nullptr)
	{
	}

	template<class T>
	inline constexpr InitList<T>::InitList(const T* first, const T* last) noexcept : first(first), last(last)
	{
	}

	template<class T>
	inline constexpr const T* InitList<T>::begin() const noexcept
	{
		return first;
	}

	template<class T>
	inline constexpr const T* InitList<T>::end() const noexcept
	{
		return last;
	}

	template<class T>
	inline constexpr ullong InitList<T>::size() const noexcept
	{
		return (ullong)(last - first);
	}

}