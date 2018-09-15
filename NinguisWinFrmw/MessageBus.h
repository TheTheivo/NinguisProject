#include "SingletonTemplate.h"
#include <mutex>
#include <queue>

namespace NinguisFramework
{
	template<class T>
	class MessageBus //final : public SingletonTemplate<MessageBus>
	{
		std::queue<T*> queue;
		std::mutex mutex;
	public:
		MessageBus();
		~MessageBus();

		void MessagePush(T);
		bool MessagePop(T&);
	private:

	};
}
