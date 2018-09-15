#include "stdafx.h"
#include "MessageBus.h"

using namespace NinguisFramework;

template <class T>
MessageBus<T>::MessageBus()
{
}

template<class T>
MessageBus<T>::~MessageBus()
{
}

template<class T>
void MessageBus<T>::MessagePush(T elem)
{
	std::lock_guard<std::mutex> lock(mutex);
	queue.push(elem);
}

template<class T>
bool NinguisFramework::MessageBus<T>::MessagePop(T &elem)
{
	std::lock_guard<std::mutex> lock(mutex);
	if (queue.empty()) {
		return false;
	}
	elem = queue.front();
	queue.pop();
	return true;
}



