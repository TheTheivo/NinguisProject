
#include "MessageTypes.h"

template<typename T>
class Packet
{
	T data;
	unsifned char buff[sizeof(T)]
};

template<typename T>
class Message
{
public:
	Message();
	~Message();

	virtual in Pack()const
	int messageType; // See MessageTypes.h for ID references
	//TODO: implement data?
	Packet data;

};

