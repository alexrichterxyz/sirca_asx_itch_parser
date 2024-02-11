#ifndef MESSAGE_ADD_ORDER_WITH_PARTICIPANT_HPP
#define MESSAGE_ADD_ORDER_WITH_PARTICIPANT_HPP
#include "message_add_order_no_participant.hpp"

namespace asxitch {
template <class T>
class message_add_order_with_participant
    : public message_add_order_no_participant<T> {
	public:
	inline message_add_order_with_participant(const T &message_str);
	inline const T &participant() const;
};
} // namespace asxitch

template <class T>
asxitch::message_add_order_with_participant<
    T>::message_add_order_with_participant(const T &message_str)
    : asxitch::message_add_order_no_participant<T>(message_str) {}

template <class T>
const T &asxitch::message_add_order_with_participant<T>::participant() const {
	return asxitch::message<T>::component_at(10);
}

#endif // MESSAGE_ADD_ORDER_WITH_PARTICIPANT_HPP