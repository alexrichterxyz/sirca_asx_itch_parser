#ifndef MESSAGE_ADD_ORDER_NO_PARTICIPANT_HPP
#define MESSAGE_ADD_ORDER_NO_PARTICIPANT_HPP
#include "message_order_replace.hpp"

namespace asxitch {
template <class T> class message_add_order_no_participant : public message_order_replace<T> {
	public:

	inline message_add_order_no_participant(const T &message_str);
	inline lot_type_t lot_type() const;
};
} // namespace asxitch

template <class T>
asxitch::message_add_order_no_participant<T>::message_add_order_no_participant(
    const T &message_str)
    : asxitch::message_order_replace<T>(message_str) {}


template <class T>
inline asxitch::lot_type_t
asxitch::message_add_order_no_participant<T>::lot_type() const {
	return static_cast<asxitch::lot_type_t>(
	    std::stoi(asxitch::message<T>::component_at(9)));
}




#endif // MESSAGE_ADD_ORDER_NO_PARTICIPANT_HPP