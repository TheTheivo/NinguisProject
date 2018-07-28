
template<typename T>
class SingletonTemplate
{
public:
	static T& instance();

	SingletonTemplate(const SingletonTemplate&) = delete;
	SingletonTemplate& operator= (const SingletonTemplate) = delete;

protected:
	struct token{};
	SingletonTemplate(){}
};

#include <memory>
template<typename T>
T& SingletonTemplate<T>::instance()
{
	static const std::unique_ptr<T> insatnce{ new T{ token{} } };
	return *instance;
}

