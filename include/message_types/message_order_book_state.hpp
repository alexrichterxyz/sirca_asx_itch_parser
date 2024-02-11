#ifndef MESSAGE_ORDER_BOOK_STATE
#define MESSAGE_ORDER_BOOK_STATE
#include "../message.hpp"
#include <cstdint>

namespace asxitch {
template <class T> class message_order_book_state : public message<T> {
	public:
	inline message_order_book_state(const T &message_str);
	inline std::int32_t order_book_id() const;
	inline const T &state_name() const;
	inline const T &symbol() const;
};
} // namespace asxitch

template <class T>
asxitch::message_order_book_state<T>::message_order_book_state(
    const T &message_str)
    : asxitch::message<T>(message_str) {}

template <class T>
inline std::int32_t
asxitch::message_order_book_state<T>::order_book_id() const {
	return std::stoul(asxitch::message<T>::component_at(2).data());
}

template <class T>
inline const T &asxitch::message_order_book_state<T>::state_name() const {
	return std::stoul(asxitch::message<T>::component_at(3).data());
}
template <class T>
inline const T &asxitch::message_order_book_state<T>::symbol() const {
	return std::stoul(asxitch::message<T>::component_at_back(1).data());
}

#endif // MESSAGE_ORDER_BOOK_STATE