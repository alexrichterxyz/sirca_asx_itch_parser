#ifndef MESSAGE_SECONDS_HPP
#define MESSAGE_SECONDS_HPP
#include "../message.hpp"
#include <cstdint>

namespace asxitch {
template <class T> class message_seconds : public message<T> {
	public:
	inline  message_seconds(const T &message_str);
};
} // namespace asxitch

template <class T>
asxitch::message_seconds<T>::message_seconds(
    const T &message_str)
    : asxitch::message<T>(message_str) {}

#endif // MESSAGE_SECONDS_HPP