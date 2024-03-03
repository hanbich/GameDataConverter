#pragma once
//! @date   2024/02/28
//! @file   Singleton.h
//! @author chsoo82
//! @brief  
//!         

#ifndef __GDC_SINGLETON_H__
#define __GDC_SINGLETON_H__

namespace GDC
{
	template <typename T>
	class Singleton
	{
	public:
		static T* Get()
		{
			if (instance == nullptr)
			{
				instance = new T();
			}

			return instance;
		}

		static void Delete()
		{
			delete instance;
		}

	protected:
		static T* instance;
	};

	template<typename T>
	T* Singleton<T>::instance = nullptr;
} // namespace GDC

#endif // __GDC_SINGLETON_H__