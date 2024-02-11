#ifndef MESSAGE_SYSTEM_EVENT_HPP
#define MESSAGE_SYSTEM_EVENT_HPP
#include "../message.hpp"
#include <cstdint>

namespace asxitch {
template <class T> class message_system_event : public message<T> {
	protected:
	public:
	inline message_system_event(const T &message_str);
	inline const T &event_name() const;
};
} // namespace asxitch

template <class T>
asxitch::message_system_event<T>::message_system_event(
    const T &message_str)
    : asxitch::message<T>(message_str) {}

template <class T>
const T &asxitch::message_system_event<T>::event_name() const {
	return message<T>::component_at_back(1);
}

#endif // MESSAGE_SYSTEM_EVENT_HPP