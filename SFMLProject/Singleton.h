#pragma once
#include "Object.h"

template<typename T>
class Singleton
{
protected:
	static Singleton<T>* instance;
protected:
	Singleton() = default;
	virtual ~Singleton() = default; 
	Singleton(const Singleton&) = delete;
	Singleton& operator=(const Singleton&) = delete;
public:
	static Singleton<T>& GetInstance();
};

template<typename T>
inline Singleton<T>& Singleton<T>::GetInstance()
{
	static T instance;
	return instance;
}
